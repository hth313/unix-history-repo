/*-
 * Copyright 1996, 1997, 1998, 1999 John D. Polstra.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD$
 */

/*
 * Dynamic linker for ELF.
 *
 * John Polstra <jdp@polstra.com>.
 */

#ifndef __GNUC__
#error "GCC is needed to compile this file"
#endif

#include <sys/param.h>
#include <sys/mman.h>

#include <dlfcn.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "debug.h"
#include "rtld.h"

/*
 * Debugging support.
 */

#define assert(cond)	((cond) ? (void) 0 :\
    (msg("oops: " __XSTRING(__LINE__) "\n"), abort()))
#define msg(s)		(write(1, s, strlen(s)))
#define trace()		msg("trace: " __XSTRING(__LINE__) "\n");

#ifndef _PATH_RTLD
#define _PATH_RTLD	"/usr/libexec/ld-elf.so.1"
#endif

#define END_SYM		"_end"

/* Types. */
typedef void (*func_ptr_type)();

/*
 * Function declarations.
 */
static const char *basename(const char *);
static void call_fini_functions(Obj_Entry *);
static void call_init_functions(Obj_Entry *);
static void die(void);
static void digest_dynamic(Obj_Entry *);
static Obj_Entry *digest_phdr(const Elf_Phdr *, int, caddr_t, const char *);
static Obj_Entry *dlcheck(void *);
static char *find_library(const char *, const Obj_Entry *);
static const char *gethints(void);
static void init_dag(Obj_Entry *);
static void init_dag1(Obj_Entry *root, Obj_Entry *obj);
static void init_rtld(caddr_t);
static bool is_exported(const Elf_Sym *);
static void linkmap_add(Obj_Entry *);
static void linkmap_delete(Obj_Entry *);
static int load_needed_objects(Obj_Entry *);
static int load_preload_objects(void);
static Obj_Entry *load_object(char *);
static Obj_Entry *obj_from_addr(const void *);
static void objlist_add(Objlist *, Obj_Entry *);
static Objlist_Entry *objlist_find(Objlist *, const Obj_Entry *);
static void objlist_remove(Objlist *, Obj_Entry *);
static int relocate_objects(Obj_Entry *, bool);
static void rtld_exit(void);
static char *search_library_path(const char *, const char *);
static void set_program_var(const char *, const void *);
static const Elf_Sym *symlook_list(const char *, unsigned long,
  Objlist *, const Obj_Entry **, bool in_plt);
static void trace_loaded_objects(Obj_Entry *obj);
static void unload_object(Obj_Entry *, bool do_fini_funcs);
static void unref_dag(Obj_Entry *);

void r_debug_state(void);
void xprintf(const char *, ...);

/*
 * Data declarations.
 */
static char *error_message;	/* Message for dlerror(), or NULL */
struct r_debug r_debug;	/* for GDB; */
static bool trust;		/* False for setuid and setgid programs */
static char *ld_bind_now;	/* Environment variable for immediate binding */
static char *ld_debug;		/* Environment variable for debugging */
static char *ld_library_path;	/* Environment variable for search path */
static char *ld_preload;	/* Environment variable for libraries to
				   load first */
static char *ld_tracing;	/* Called from ldd to print libs */
static Obj_Entry *obj_list;	/* Head of linked list of shared objects */
static Obj_Entry **obj_tail;	/* Link field of last object in list */
static Obj_Entry *obj_main;	/* The main program shared object */
static Obj_Entry obj_rtld;	/* The dynamic linker shared object */
static unsigned long curmark;	/* Current mark value */

static Objlist list_global =	/* Objects dlopened with RTLD_GLOBAL */
  STAILQ_HEAD_INITIALIZER(list_global);
static Objlist list_main =	/* Objects loaded at program startup */
  STAILQ_HEAD_INITIALIZER(list_main);

static Elf_Sym sym_zero;	/* For resolving undefined weak refs. */

#define GDB_STATE(s)	r_debug.r_state = s; r_debug_state();

extern Elf_Dyn _DYNAMIC;
#pragma weak _DYNAMIC

/*
 * These are the functions the dynamic linker exports to application
 * programs.  They are the only symbols the dynamic linker is willing
 * to export from itself.
 */
static func_ptr_type exports[] = {
    (func_ptr_type) &_rtld_error,
    (func_ptr_type) &dlclose,
    (func_ptr_type) &dlerror,
    (func_ptr_type) &dlopen,
    (func_ptr_type) &dlsym,
    (func_ptr_type) &dladdr,
    NULL
};

/*
 * Global declarations normally provided by crt1.  The dynamic linker is
 * not build with crt1, so we have to provide them ourselves.
 */
char *__progname;
char **environ;

/*
 * Main entry point for dynamic linking.  The first argument is the
 * stack pointer.  The stack is expected to be laid out as described
 * in the SVR4 ABI specification, Intel 386 Processor Supplement.
 * Specifically, the stack pointer points to a word containing
 * ARGC.  Following that in the stack is a null-terminated sequence
 * of pointers to argument strings.  Then comes a null-terminated
 * sequence of pointers to environment strings.  Finally, there is a
 * sequence of "auxiliary vector" entries.
 *
 * The second argument points to a place to store the dynamic linker's
 * exit procedure pointer and the third to a place to store the main
 * program's object.
 *
 * The return value is the main program's entry point.
 */
func_ptr_type
_rtld(Elf_Addr *sp, func_ptr_type *exit_proc, Obj_Entry **objp)
{
    Elf_Auxinfo *aux_info[AT_COUNT];
    int i;
    int argc;
    char **argv;
    char **env;
    Elf_Auxinfo *aux;
    Elf_Auxinfo *auxp;
    const char *argv0;
    Obj_Entry *obj;

    /*
     * On entry, the dynamic linker itself has not been relocated yet.
     * Be very careful not to reference any global data until after
     * init_rtld has returned.  It is OK to reference file-scope statics
     * and string constants, and to call static and global functions.
     */

    /* Find the auxiliary vector on the stack. */
    argc = *sp++;
    argv = (char **) sp;
    sp += argc + 1;	/* Skip over arguments and NULL terminator */
    env = (char **) sp;
    while (*sp++ != 0)	/* Skip over environment, and NULL terminator */
	;
    aux = (Elf_Auxinfo *) sp;

    /* Digest the auxiliary vector. */
    for (i = 0;  i < AT_COUNT;  i++)
	aux_info[i] = NULL;
    for (auxp = aux;  auxp->a_type != AT_NULL;  auxp++) {
	if (auxp->a_type < AT_COUNT)
	    aux_info[auxp->a_type] = auxp;
    }

    /* Initialize and relocate ourselves. */
    assert(aux_info[AT_BASE] != NULL);
    init_rtld((caddr_t) aux_info[AT_BASE]->a_un.a_ptr);

    __progname = obj_rtld.path;
    argv0 = argv[0] != NULL ? argv[0] : "(null)";
    environ = env;

    trust = geteuid() == getuid() && getegid() == getgid();

    ld_bind_now = getenv("LD_BIND_NOW");
    if (trust) {
	ld_debug = getenv("LD_DEBUG");
	ld_library_path = getenv("LD_LIBRARY_PATH");
	ld_preload = getenv("LD_PRELOAD");
    }
    ld_tracing = getenv("LD_TRACE_LOADED_OBJECTS");

    if (ld_debug != NULL && *ld_debug != '\0')
	debug = 1;
    dbg("%s is initialized, base address = %p", __progname,
	(caddr_t) aux_info[AT_BASE]->a_un.a_ptr);
    dbg("RTLD dynamic = %p", obj_rtld.dynamic);
    dbg("RTLD pltgot  = %p", obj_rtld.pltgot);

    /*
     * Load the main program, or process its program header if it is
     * already loaded.
     */
    if (aux_info[AT_EXECFD] != NULL) {	/* Load the main program. */
	int fd = aux_info[AT_EXECFD]->a_un.a_val;
	dbg("loading main program");
	obj_main = map_object(fd, argv0);
	close(fd);
	if (obj_main == NULL)
	    die();
    } else {				/* Main program already loaded. */
	const Elf_Phdr *phdr;
	int phnum;
	caddr_t entry;

	dbg("processing main program's program header");
	assert(aux_info[AT_PHDR] != NULL);
	phdr = (const Elf_Phdr *) aux_info[AT_PHDR]->a_un.a_ptr;
	assert(aux_info[AT_PHNUM] != NULL);
	phnum = aux_info[AT_PHNUM]->a_un.a_val;
	assert(aux_info[AT_PHENT] != NULL);
	assert(aux_info[AT_PHENT]->a_un.a_val == sizeof(Elf_Phdr));
	assert(aux_info[AT_ENTRY] != NULL);
	entry = (caddr_t) aux_info[AT_ENTRY]->a_un.a_ptr;
	if ((obj_main = digest_phdr(phdr, phnum, entry, argv0)) == NULL)
	    die();
    }

    obj_main->path = xstrdup(argv0);
    obj_main->mainprog = true;
    digest_dynamic(obj_main);

    linkmap_add(obj_main);
    linkmap_add(&obj_rtld);

    /* Link the main program into the list of objects. */
    *obj_tail = obj_main;
    obj_tail = &obj_main->next;
    obj_main->refcount++;

    /* Initialize a fake symbol for resolving undefined weak references. */
    sym_zero.st_info = ELF_ST_INFO(STB_GLOBAL, STT_NOTYPE);
    sym_zero.st_shndx = SHN_ABS;

    dbg("loading LD_PRELOAD libraries");
    if (load_preload_objects() == -1)
	die();

    dbg("loading needed objects");
    if (load_needed_objects(obj_main) == -1)
	die();

    for (obj = obj_list;  obj != NULL;  obj = obj->next)
	objlist_add(&list_main, obj);

    if (ld_tracing) {		/* We're done */
	trace_loaded_objects(obj_main);
	exit(0);
    }

    dbg("relocating objects");
    if (relocate_objects(obj_main,
	ld_bind_now != NULL && *ld_bind_now != '\0') == -1)
	die();

    dbg("doing copy relocations");
    if (do_copy_relocations(obj_main) == -1)
	die();

    dbg("initializing key program variables");
    set_program_var("__progname", argv[0] != NULL ? basename(argv[0]) : "");
    set_program_var("environ", env);

    r_debug_state();		/* say hello to gdb! */

    dbg("calling _init functions");
    call_init_functions(obj_main->next);

    dbg("transferring control to program entry point = %p", obj_main->entry);

    /* Return the exit procedure and the program entry point. */
    *exit_proc = rtld_exit;
    *objp = obj_main;
    return (func_ptr_type) obj_main->entry;
}

Elf_Addr
_rtld_bind(Obj_Entry *obj, Elf_Word reloff)
{
    const Elf_Rel *rel;
    const Elf_Sym *def;
    const Obj_Entry *defobj;
    Elf_Addr *where;
    Elf_Addr target;

    if (obj->pltrel)
	rel = (const Elf_Rel *) ((caddr_t) obj->pltrel + reloff);
    else
	rel = (const Elf_Rel *) ((caddr_t) obj->pltrela + reloff);

    where = (Elf_Addr *) (obj->relocbase + rel->r_offset);
    def = find_symdef(ELF_R_SYM(rel->r_info), obj, &defobj, true);
    if (def == NULL)
	die();

    target = (Elf_Addr)(defobj->relocbase + def->st_value);

    dbg("\"%s\" in \"%s\" ==> %p in \"%s\"",
      defobj->strtab + def->st_name, basename(obj->path),
      (void *)target, basename(defobj->path));

    reloc_jmpslot(where, target);
    return target;
}

/*
 * Error reporting function.  Use it like printf.  If formats the message
 * into a buffer, and sets things up so that the next call to dlerror()
 * will return the message.
 */
void
_rtld_error(const char *fmt, ...)
{
    static char buf[512];
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    error_message = buf;
    va_end(ap);
}

static const char *
basename(const char *name)
{
    const char *p = strrchr(name, '/');
    return p != NULL ? p + 1 : name;
}

static void
call_fini_functions(Obj_Entry *first)
{
    Obj_Entry *obj;

    for (obj = first;  obj != NULL;  obj = obj->next)
	if (obj->fini != NULL)
	    (*obj->fini)();
}

static void
call_init_functions(Obj_Entry *first)
{
    if (first != NULL) {
	call_init_functions(first->next);
	if (first->init != NULL)
	    (*first->init)();
    }
}

static void
die(void)
{
    const char *msg = dlerror();

    if (msg == NULL)
	msg = "Fatal error";
    errx(1, "%s", msg);
}

/*
 * Process a shared object's DYNAMIC section, and save the important
 * information in its Obj_Entry structure.
 */
static void
digest_dynamic(Obj_Entry *obj)
{
    const Elf_Dyn *dynp;
    Needed_Entry **needed_tail = &obj->needed;
    const Elf_Dyn *dyn_rpath = NULL;
    int plttype = DT_REL;

    for (dynp = obj->dynamic;  dynp->d_tag != DT_NULL;  dynp++) {
	switch (dynp->d_tag) {

	case DT_REL:
	    obj->rel = (const Elf_Rel *) (obj->relocbase + dynp->d_un.d_ptr);
	    break;

	case DT_RELSZ:
	    obj->relsize = dynp->d_un.d_val;
	    break;

	case DT_RELENT:
	    assert(dynp->d_un.d_val == sizeof(Elf_Rel));
	    break;

	case DT_JMPREL:
	    obj->pltrel = (const Elf_Rel *)
	      (obj->relocbase + dynp->d_un.d_ptr);
	    break;

	case DT_PLTRELSZ:
	    obj->pltrelsize = dynp->d_un.d_val;
	    break;

	case DT_RELA:
	    obj->rela = (const Elf_Rela *) (obj->relocbase + dynp->d_un.d_ptr);
	    break;

	case DT_RELASZ:
	    obj->relasize = dynp->d_un.d_val;
	    break;

	case DT_RELAENT:
	    assert(dynp->d_un.d_val == sizeof(Elf_Rela));
	    break;

	case DT_PLTREL:
	    plttype = dynp->d_un.d_val;
	    assert(dynp->d_un.d_val == DT_REL || plttype == DT_RELA);
	    break;

	case DT_SYMTAB:
	    obj->symtab = (const Elf_Sym *)
	      (obj->relocbase + dynp->d_un.d_ptr);
	    break;

	case DT_SYMENT:
	    assert(dynp->d_un.d_val == sizeof(Elf_Sym));
	    break;

	case DT_STRTAB:
	    obj->strtab = (const char *) (obj->relocbase + dynp->d_un.d_ptr);
	    break;

	case DT_STRSZ:
	    obj->strsize = dynp->d_un.d_val;
	    break;

	case DT_HASH:
	    {
		const Elf_Addr *hashtab = (const Elf_Addr *)
		  (obj->relocbase + dynp->d_un.d_ptr);
		obj->nbuckets = hashtab[0];
		obj->nchains = hashtab[1];
		obj->buckets = hashtab + 2;
		obj->chains = obj->buckets + obj->nbuckets;
	    }
	    break;

	case DT_NEEDED:
	    if (!obj->rtld) {
		Needed_Entry *nep = NEW(Needed_Entry);
		nep->name = dynp->d_un.d_val;
		nep->obj = NULL;
		nep->next = NULL;

		*needed_tail = nep;
		needed_tail = &nep->next;
	    }
	    break;

	case DT_PLTGOT:
	    obj->pltgot = (Elf_Addr *) (obj->relocbase + dynp->d_un.d_ptr);
	    break;

	case DT_TEXTREL:
	    obj->textrel = true;
	    break;

	case DT_SYMBOLIC:
	    obj->symbolic = true;
	    break;

	case DT_RPATH:
	    /*
	     * We have to wait until later to process this, because we
	     * might not have gotten the address of the string table yet.
	     */
	    dyn_rpath = dynp;
	    break;

	case DT_SONAME:
	    /* Not used by the dynamic linker. */
	    break;

	case DT_INIT:
	    obj->init = (void (*)(void)) (obj->relocbase + dynp->d_un.d_ptr);
	    break;

	case DT_FINI:
	    obj->fini = (void (*)(void)) (obj->relocbase + dynp->d_un.d_ptr);
	    break;

	case DT_DEBUG:
	    /* XXX - not implemented yet */
	    dbg("Filling in DT_DEBUG entry");
	    ((Elf_Dyn*)dynp)->d_un.d_ptr = (Elf_Addr) &r_debug;
	    break;

	default:
	    xprintf("Ignored d_tag %d\n",dynp->d_tag);
            break;
	}
    }

    obj->traced = false;

    if (plttype == DT_RELA) {
	obj->pltrela = (const Elf_Rela *) obj->pltrel;
	obj->pltrel = NULL;
	obj->pltrelasize = obj->pltrelsize;
	obj->pltrelsize = 0;
    }

    if (dyn_rpath != NULL)
	obj->rpath = obj->strtab + dyn_rpath->d_un.d_val;
}

/*
 * Process a shared object's program header.  This is used only for the
 * main program, when the kernel has already loaded the main program
 * into memory before calling the dynamic linker.  It creates and
 * returns an Obj_Entry structure.
 */
static Obj_Entry *
digest_phdr(const Elf_Phdr *phdr, int phnum, caddr_t entry, const char *path)
{
    Obj_Entry *obj;
    const Elf_Phdr *phlimit = phdr + phnum;
    const Elf_Phdr *ph;
    int nsegs = 0;

    obj = obj_new();
    for (ph = phdr;  ph < phlimit;  ph++) {
	switch (ph->p_type) {

	case PT_PHDR:
	    if ((const Elf_Phdr *)ph->p_vaddr != phdr) {
		_rtld_error("%s: invalid PT_PHDR", path);
		return NULL;
	    }
	    obj->phdr = (const Elf_Phdr *) ph->p_vaddr;
	    obj->phsize = ph->p_memsz;
	    break;

	case PT_LOAD:
	    if (nsegs >= 2) {
		_rtld_error("%s: too many PT_LOAD segments", path);
		return NULL;
	    }
	    if (nsegs == 0) {	/* First load segment */
		obj->vaddrbase = trunc_page(ph->p_vaddr);
		obj->mapbase = (caddr_t) obj->vaddrbase;
		obj->relocbase = obj->mapbase - obj->vaddrbase;
		obj->textsize = round_page(ph->p_vaddr + ph->p_memsz) -
		  obj->vaddrbase;
	    } else {		/* Last load segment */
		obj->mapsize = round_page(ph->p_vaddr + ph->p_memsz) -
		  obj->vaddrbase;
	    }
	    nsegs++;
	    break;

	case PT_DYNAMIC:
	    obj->dynamic = (const Elf_Dyn *) ph->p_vaddr;
	    break;
	}
    }
    if (nsegs < 2) {
	_rtld_error("%s: too few PT_LOAD segments", path);
	return NULL;
    }

    obj->entry = entry;
    return obj;
}

static Obj_Entry *
dlcheck(void *handle)
{
    Obj_Entry *obj;

    for (obj = obj_list;  obj != NULL;  obj = obj->next)
	if (obj == (Obj_Entry *) handle)
	    break;

    if (obj == NULL || obj->dl_refcount == 0) {
	_rtld_error("Invalid shared object handle %p", handle);
	return NULL;
    }
    return obj;
}

/*
 * Hash function for symbol table lookup.  Don't even think about changing
 * this.  It is specified by the System V ABI.
 */
unsigned long
elf_hash(const char *name)
{
    const unsigned char *p = (const unsigned char *) name;
    unsigned long h = 0;
    unsigned long g;

    while (*p != '\0') {
	h = (h << 4) + *p++;
	if ((g = h & 0xf0000000) != 0)
	    h ^= g >> 24;
	h &= ~g;
    }
    return h;
}

/*
 * Find the library with the given name, and return its full pathname.
 * The returned string is dynamically allocated.  Generates an error
 * message and returns NULL if the library cannot be found.
 *
 * If the second argument is non-NULL, then it refers to an already-
 * loaded shared object, whose library search path will be searched.
 *
 * The search order is:
 *   LD_LIBRARY_PATH
 *   ldconfig hints
 *   rpath in the referencing file
 *   /usr/lib
 */
static char *
find_library(const char *name, const Obj_Entry *refobj)
{
    char *pathname;

    if (strchr(name, '/') != NULL) {	/* Hard coded pathname */
	if (name[0] != '/' && !trust) {
	    _rtld_error("Absolute pathname required for shared object \"%s\"",
	      name);
	    return NULL;
	}
	return xstrdup(name);
    }

    dbg(" Searching for \"%s\"", name);

    if ((refobj != NULL &&
      (pathname = search_library_path(name, refobj->rpath)) != NULL) ||
      (pathname = search_library_path(name, ld_library_path)) != NULL ||
      (pathname = search_library_path(name, gethints())) != NULL ||
      (pathname = search_library_path(name, STANDARD_LIBRARY_PATH)) != NULL)
	return pathname;

    _rtld_error("Shared object \"%s\" not found", name);
    return NULL;
}

/*
 * Given a symbol number in a referencing object, find the corresponding
 * definition of the symbol.  Returns a pointer to the symbol, or NULL if
 * no definition was found.  Returns a pointer to the Obj_Entry of the
 * defining object via the reference parameter DEFOBJ_OUT.
 */
const Elf_Sym *
find_symdef(unsigned long symnum, Obj_Entry *refobj,
    const Obj_Entry **defobj_out, bool in_plt)
{
    const Elf_Sym *ref;
    const Elf_Sym *def;
    const Elf_Sym *symp;
    const Obj_Entry *obj;
    const Obj_Entry *defobj;
    const Objlist_Entry *elm;
    const char *name;
    unsigned long hash;

    ref = refobj->symtab + symnum;
    name = refobj->strtab + ref->st_name;
    hash = elf_hash(name);
    def = NULL;
    defobj = NULL;
    curmark++;

    if (refobj->symbolic) {	/* Look first in the referencing object */
	symp = symlook_obj(name, hash, refobj, in_plt);
	refobj->mark = curmark;
	if (symp != NULL) {
	    def = symp;
	    defobj = refobj;
	}
    }

    /* Search all dlopened DAGs containing the referencing object. */
    STAILQ_FOREACH(elm, &refobj->dldags, link) {
	if (def != NULL && ELF_ST_BIND(def->st_info) != STB_WEAK)
	    break;
	symp = symlook_list(name, hash, &elm->obj->dagmembers, &obj, in_plt);
	if (symp != NULL &&
	  (def == NULL || ELF_ST_BIND(symp->st_info) != STB_WEAK)) {
	    def = symp;
	    defobj = obj;
	}
    }

    /* Search all objects loaded at program start up. */
    if (def == NULL || ELF_ST_BIND(def->st_info) == STB_WEAK) {
	symp = symlook_list(name, hash, &list_main, &obj, in_plt);
	if (symp != NULL &&
	  (def == NULL || ELF_ST_BIND(symp->st_info) != STB_WEAK)) {
	    def = symp;
	    defobj = obj;
	}
    }

    /* Search all RTLD_GLOBAL objects. */
    if (def == NULL || ELF_ST_BIND(def->st_info) == STB_WEAK) {
	symp = symlook_list(name, hash, &list_global, &obj, in_plt);
	if (symp != NULL &&
	  (def == NULL || ELF_ST_BIND(symp->st_info) != STB_WEAK)) {
	    def = symp;
	    defobj = obj;
	}
    }

    /*
     * Search the dynamic linker itself, and possibly resolve the
     * symbol from there.  This is how the application links to
     * dynamic linker services such as dlopen.  Only the values listed
     * in the "exports" array can be resolved from the dynamic linker.
     */
    if (def == NULL || ELF_ST_BIND(def->st_info) == STB_WEAK) {
	symp = symlook_obj(name, hash, &obj_rtld, in_plt);
	if (symp != NULL && is_exported(symp)) {
	    def = symp;
	    defobj = &obj_rtld;
	}
    }

    /*
     * If we found no definition and the reference is weak, treat the
     * symbol as having the value zero.
     */
    if (def == NULL && ELF_ST_BIND(ref->st_info) == STB_WEAK) {
	def = &sym_zero;
	defobj = obj_main;
    }

    if (def != NULL)
	*defobj_out = defobj;
    else
	_rtld_error("%s: Undefined symbol \"%s\"", refobj->path, name);
    return def;
}

/*
 * Return the search path from the ldconfig hints file, reading it if
 * necessary.  Returns NULL if there are problems with the hints file,
 * or if the search path there is empty.
 */
static const char *
gethints(void)
{
    static char *hints;

    if (hints == NULL) {
	int fd;
	struct elfhints_hdr hdr;
	char *p;

	/* Keep from trying again in case the hints file is bad. */
	hints = "";

	if ((fd = open(_PATH_ELF_HINTS, O_RDONLY)) == -1)
	    return NULL;
	if (read(fd, &hdr, sizeof hdr) != sizeof hdr ||
	  hdr.magic != ELFHINTS_MAGIC ||
	  hdr.version != 1) {
	    close(fd);
	    return NULL;
	}
	p = xmalloc(hdr.dirlistlen + 1);
	if (lseek(fd, hdr.strtab + hdr.dirlist, SEEK_SET) == -1 ||
	  read(fd, p, hdr.dirlistlen + 1) != hdr.dirlistlen + 1) {
	    free(p);
	    close(fd);
	    return NULL;
	}
	hints = p;
	close(fd);
    }
    return hints[0] != '\0' ? hints : NULL;
}

static void
init_dag(Obj_Entry *root)
{
    curmark++;
    init_dag1(root, root);
}

static void
init_dag1(Obj_Entry *root, Obj_Entry *obj)
{
    const Needed_Entry *needed;

    if (obj->mark == curmark)
	return;
    obj->mark = curmark;
    objlist_add(&obj->dldags, root);
    objlist_add(&root->dagmembers, obj);
    for (needed = obj->needed;  needed != NULL;  needed = needed->next)
	if (needed->obj != NULL)
	    init_dag1(root, needed->obj);
}

/*
 * Initialize the dynamic linker.  The argument is the address at which
 * the dynamic linker has been mapped into memory.  The primary task of
 * this function is to relocate the dynamic linker.
 */
static void
init_rtld(caddr_t mapbase)
{
    /*
     * Conjure up an Obj_Entry structure for the dynamic linker.
     *
     * The "path" member is supposed to be dynamically-allocated, but we
     * aren't yet initialized sufficiently to do that.  Below we will
     * replace the static version with a dynamically-allocated copy.
     */
    obj_rtld.path = _PATH_RTLD;
    obj_rtld.rtld = true;
    obj_rtld.mapbase = mapbase;
#ifdef PIC
    obj_rtld.relocbase = mapbase;
#endif
    if (&_DYNAMIC != 0) {
	obj_rtld.dynamic = rtld_dynamic(&obj_rtld);
	digest_dynamic(&obj_rtld);
	assert(obj_rtld.needed == NULL);
	assert(!obj_rtld.textrel);

	/*
	 * Temporarily put the dynamic linker entry into the object list, so
	 * that symbols can be found.
	 */
	obj_list = &obj_rtld;
	obj_tail = &obj_rtld.next;

	relocate_objects(&obj_rtld, true);
    }

    /* Make the object list empty again. */
    obj_list = NULL;
    obj_tail = &obj_list;

    /* Replace the path with a dynamically allocated copy. */
    obj_rtld.path = xstrdup(obj_rtld.path);

    r_debug.r_brk = r_debug_state;
    r_debug.r_state = RT_CONSISTENT;
}

static bool
is_exported(const Elf_Sym *def)
{
    func_ptr_type value;
    const func_ptr_type *p;

    value = (func_ptr_type)(obj_rtld.relocbase + def->st_value);
    for (p = exports;  *p != NULL;  p++)
	if (*p == value)
	    return true;
    return false;
}

/*
 * Given a shared object, traverse its list of needed objects, and load
 * each of them.  Returns 0 on success.  Generates an error message and
 * returns -1 on failure.
 */
static int
load_needed_objects(Obj_Entry *first)
{
    Obj_Entry *obj;

    for (obj = first;  obj != NULL;  obj = obj->next) {
	Needed_Entry *needed;

	for (needed = obj->needed;  needed != NULL;  needed = needed->next) {
	    const char *name = obj->strtab + needed->name;
	    char *path = find_library(name, obj);

	    needed->obj = NULL;
	    if (path == NULL && !ld_tracing)
		return -1;

	    if (path) {
		needed->obj = load_object(path);
		if (needed->obj == NULL && !ld_tracing)
		    return -1;		/* XXX - cleanup */
	    }
	}
    }

    return 0;
}

static int
load_preload_objects(void)
{
    char *p = ld_preload;

    if (p == NULL)
	return NULL;

    p += strspn(p, ":;");
    while (*p != '\0') {
	size_t len = strcspn(p, ":;");
	char *path;
	char savech;

	savech = p[len];
	p[len] = '\0';
	if ((path = find_library(p, NULL)) == NULL)
	    return -1;
	if (load_object(path) == NULL)
	    return -1;	/* XXX - cleanup */
	p[len] = savech;
	p += len;
	p += strspn(p, ":;");
    }
    return 0;
}

/*
 * Load a shared object into memory, if it is not already loaded.  The
 * argument must be a string allocated on the heap.  This function assumes
 * responsibility for freeing it when necessary.
 *
 * Returns a pointer to the Obj_Entry for the object.  Returns NULL
 * on failure.
 */
static Obj_Entry *
load_object(char *path)
{
    Obj_Entry *obj;

    for (obj = obj_list->next;  obj != NULL;  obj = obj->next)
	if (strcmp(obj->path, path) == 0)
	    break;

    if (obj == NULL) {	/* First use of this object, so we must map it in */
	int fd;

	if ((fd = open(path, O_RDONLY)) == -1) {
	    _rtld_error("Cannot open \"%s\"", path);
	    return NULL;
	}
	dbg("loading \"%s\"", path);
	obj = map_object(fd, path);
	close(fd);
	if (obj == NULL) {
	    free(path);
	    return NULL;
	}

	obj->path = path;
	digest_dynamic(obj);

	*obj_tail = obj;
	obj_tail = &obj->next;
	linkmap_add(obj);	/* for GDB */

	dbg("  %p .. %p: %s", obj->mapbase,
	  obj->mapbase + obj->mapsize - 1, obj->path);
	if (obj->textrel)
	    dbg("  WARNING: %s has impure text", obj->path);
    } else
	free(path);

    obj->refcount++;
    return obj;
}

static Obj_Entry *
obj_from_addr(const void *addr)
{
    unsigned long endhash;
    Obj_Entry *obj;

    endhash = elf_hash(END_SYM);
    for (obj = obj_list;  obj != NULL;  obj = obj->next) {
	const Elf_Sym *endsym;

	if (addr < (void *) obj->mapbase)
	    continue;
	if ((endsym = symlook_obj(END_SYM, endhash, obj, true)) == NULL)
	    continue;	/* No "end" symbol?! */
	if (addr < (void *) (obj->relocbase + endsym->st_value))
	    return obj;
    }
    return NULL;
}

static void
objlist_add(Objlist *list, Obj_Entry *obj)
{
    Objlist_Entry *elm;

    elm = NEW(Objlist_Entry);
    elm->obj = obj;
    STAILQ_INSERT_TAIL(list, elm, link);
}

static Objlist_Entry *
objlist_find(Objlist *list, const Obj_Entry *obj)
{
    Objlist_Entry *elm;

    STAILQ_FOREACH(elm, list, link)
	if (elm->obj == obj)
	    return elm;
    return NULL;
}

static void
objlist_remove(Objlist *list, Obj_Entry *obj)
{
    Objlist_Entry *elm;

    if ((elm = objlist_find(list, obj)) != NULL) {
	STAILQ_REMOVE(list, elm, Struct_Objlist_Entry, link);
	free(elm);
    }
}

/*
 * Relocate newly-loaded shared objects.  The argument is a pointer to
 * the Obj_Entry for the first such object.  All objects from the first
 * to the end of the list of objects are relocated.  Returns 0 on success,
 * or -1 on failure.
 */
static int
relocate_objects(Obj_Entry *first, bool bind_now)
{
    Obj_Entry *obj;

    for (obj = first;  obj != NULL;  obj = obj->next) {
	if (obj != &obj_rtld)
	    dbg("relocating \"%s\"", obj->path);
	if (obj->nbuckets == 0 || obj->nchains == 0 || obj->buckets == NULL ||
	    obj->symtab == NULL || obj->strtab == NULL) {
	    _rtld_error("%s: Shared object has no run-time symbol table",
	      obj->path);
	    return -1;
	}

	if (obj->textrel) {
	    /* There are relocations to the write-protected text segment. */
	    if (mprotect(obj->mapbase, obj->textsize,
	      PROT_READ|PROT_WRITE|PROT_EXEC) == -1) {
		_rtld_error("%s: Cannot write-enable text segment: %s",
		  obj->path, strerror(errno));
		return -1;
	    }
	}

	/* Process the non-PLT relocations. */
	if (reloc_non_plt(obj, &obj_rtld))
		return -1;

	if (obj->textrel) {	/* Re-protected the text segment. */
	    if (mprotect(obj->mapbase, obj->textsize,
	      PROT_READ|PROT_EXEC) == -1) {
		_rtld_error("%s: Cannot write-protect text segment: %s",
		  obj->path, strerror(errno));
		return -1;
	    }
	}

	/* Process the PLT relocations. */
	if (reloc_plt(obj, bind_now))
		return -1;

	/*
	 * Set up the magic number and version in the Obj_Entry.  These
	 * were checked in the crt1.o from the original ElfKit, so we
	 * set them for backward compatibility.
	 */
	obj->magic = RTLD_MAGIC;
	obj->version = RTLD_VERSION;

	/* Set the special PLT or GOT entries. */
	init_pltgot(obj);
    }

    return 0;
}

/*
 * Cleanup procedure.  It will be called (by the atexit mechanism) just
 * before the process exits.
 */
static void
rtld_exit(void)
{
    dbg("rtld_exit()");
    call_fini_functions(obj_list->next);
}

static char *
search_library_path(const char *name, const char *path)
{
    size_t namelen = strlen(name);
    const char *p = path;

    if (p == NULL)
	return NULL;

    p += strspn(p, ":;");
    while (*p != '\0') {
	size_t len = strcspn(p, ":;");

	if (*p == '/' || trust) {
	    char *pathname;
	    const char *dir = p;
	    size_t dirlen = len;

	    pathname = xmalloc(dirlen + 1 + namelen + 1);
	    strncpy(pathname, dir, dirlen);
	    pathname[dirlen] = '/';
	    strcpy(pathname + dirlen + 1, name);

	    dbg("  Trying \"%s\"", pathname);
	    if (access(pathname, F_OK) == 0)		/* We found it */
		return pathname;

	    free(pathname);
	}
	p += len;
	p += strspn(p, ":;");
    }

    return NULL;
}

int
dlclose(void *handle)
{
    Obj_Entry *root = dlcheck(handle);

    if (root == NULL)
	return -1;

    GDB_STATE(RT_DELETE);
    unload_object(root, true);
    root->dl_refcount--;
    GDB_STATE(RT_CONSISTENT);

    return 0;
}

const char *
dlerror(void)
{
    char *msg = error_message;
    error_message = NULL;
    return msg;
}

void *
dlopen(const char *name, int mode)
{
    Obj_Entry **old_obj_tail = obj_tail;
    Obj_Entry *obj = NULL;

    GDB_STATE(RT_ADD);

    if (name == NULL) {
	obj = obj_main;
	obj->refcount++;
    } else {
	char *path = find_library(name, obj_main);
	if (path != NULL)
	    obj = load_object(path);
    }

    if (obj) {
	obj->dl_refcount++;
	if (mode & RTLD_GLOBAL && objlist_find(&list_global, obj) == NULL)
	    objlist_add(&list_global, obj);
	mode &= RTLD_MODEMASK;
	if (*old_obj_tail != NULL) {		/* We loaded something new. */
	    assert(*old_obj_tail == obj);

	    if (load_needed_objects(obj) == -1 ||
	      (init_dag(obj), relocate_objects(obj, mode == RTLD_NOW)) == -1) {
		unload_object(obj, false);
		obj->dl_refcount--;
		obj = NULL;
	    } else
		call_init_functions(obj);
	}
    }

    GDB_STATE(RT_CONSISTENT);

    return obj;
}

void *
dlsym(void *handle, const char *name)
{
    const Obj_Entry *obj;
    unsigned long hash;
    const Elf_Sym *def;
    const Obj_Entry *defobj;

    hash = elf_hash(name);
    def = NULL;
    defobj = NULL;

    if (handle == NULL || handle == RTLD_NEXT) {
	void *retaddr;

	retaddr = __builtin_return_address(0);	/* __GNUC__ only */
	if ((obj = obj_from_addr(retaddr)) == NULL) {
	    _rtld_error("Cannot determine caller's shared object");
	    return NULL;
	}
	if (handle == NULL) {	/* Just the caller's shared object. */
	    def = symlook_obj(name, hash, obj, true);
	    defobj = obj;
	} else {		/* All the shared objects after the caller's */
	    while ((obj = obj->next) != NULL) {
		if ((def = symlook_obj(name, hash, obj, true)) != NULL) {
		    defobj = obj;
		    break;
		}
	    }
	}
    } else {
	if ((obj = dlcheck(handle)) == NULL)
	    return NULL;

	if (obj->mainprog) {
	    /* Search main program and all libraries loaded by it. */
	    curmark++;
	    def = symlook_list(name, hash, &list_main, &defobj, true);
	} else {
	    /*
	     * XXX - This isn't correct.  The search should include the whole
	     * DAG rooted at the given object.
	     */
	    def = symlook_obj(name, hash, obj, true);
	    defobj = obj;
	}
    }

    if (def != NULL)
	return defobj->relocbase + def->st_value;

    _rtld_error("Undefined symbol \"%s\"", name);
    return NULL;
}

int
dladdr(const void *addr, Dl_info *info)
{
    const Obj_Entry *obj;
    const Elf_Sym *def;
    void *symbol_addr;
    unsigned long symoffset;
    
    obj = obj_from_addr(addr);
    if (obj == NULL) {
        _rtld_error("No shared object contains address");
        return 0;
    }
    info->dli_fname = obj->path;
    info->dli_fbase = obj->mapbase;
    info->dli_saddr = (void *)0;
    info->dli_sname = NULL;

    /*
     * Walk the symbol list looking for the symbol whose address is
     * closest to the address sent in.
     */
    for (symoffset = 0; symoffset < obj->nchains; symoffset++) {
        def = obj->symtab + symoffset;

        /*
         * For skip the symbol if st_shndx is either SHN_UNDEF or
         * SHN_COMMON.
         */
        if (def->st_shndx == SHN_UNDEF || def->st_shndx == SHN_COMMON)
            continue;

        /*
         * If the symbol is greater than the specified address, or if it
         * is further away from addr than the current nearest symbol,
         * then reject it.
         */
        symbol_addr = obj->relocbase + def->st_value;
        if (symbol_addr > addr || symbol_addr < info->dli_saddr)
            continue;

        /* Update our idea of the nearest symbol. */
        info->dli_sname = obj->strtab + def->st_name;
        info->dli_saddr = symbol_addr;

        /* Exact match? */
        if (info->dli_saddr == addr)
            break;
    }
    return 1;
}

static void
linkmap_add(Obj_Entry *obj)
{
    struct link_map *l = &obj->linkmap;
    struct link_map *prev;

    obj->linkmap.l_name = obj->path;
    obj->linkmap.l_addr = obj->mapbase;
    obj->linkmap.l_ld = obj->dynamic;
#ifdef __mips__
    /* GDB needs load offset on MIPS to use the symbols */
    obj->linkmap.l_offs = obj->relocbase;
#endif

    if (r_debug.r_map == NULL) {
	r_debug.r_map = l;
	return;
    }
    
    /*
     * Scan to the end of the list, but not past the entry for the
     * dynamic linker, which we want to keep at the very end.
     */
    for (prev = r_debug.r_map;
      prev->l_next != NULL && prev->l_next != &obj_rtld.linkmap;
      prev = prev->l_next)
	;

    /* Link in the new entry. */
    l->l_prev = prev;
    l->l_next = prev->l_next;
    if (l->l_next != NULL)
	l->l_next->l_prev = l;
    prev->l_next = l;
}

static void
linkmap_delete(Obj_Entry *obj)
{
    struct link_map *l = &obj->linkmap;

    if (l->l_prev == NULL) {
	if ((r_debug.r_map = l->l_next) != NULL)
	    l->l_next->l_prev = NULL;
	return;
    }

    if ((l->l_prev->l_next = l->l_next) != NULL)
	l->l_next->l_prev = l->l_prev;
}

/*
 * Function for the debugger to set a breakpoint on to gain control.
 */
void
r_debug_state(void)
{
}

/*
 * Set a pointer variable in the main program to the given value.  This
 * is used to set key variables such as "environ" before any of the
 * init functions are called.
 */
static void
set_program_var(const char *name, const void *value)
{
    const Obj_Entry *obj;
    unsigned long hash;

    hash = elf_hash(name);
    for (obj = obj_main;  obj != NULL;  obj = obj->next) {
	const Elf_Sym *def;

	if ((def = symlook_obj(name, hash, obj, false)) != NULL) {
	    const void **addr;

	    addr = (const void **)(obj->relocbase + def->st_value);
	    dbg("\"%s\": *%p <-- %p", name, addr, value);
	    *addr = value;
	    break;
	}
    }
}

static const Elf_Sym *
symlook_list(const char *name, unsigned long hash, Objlist *objlist,
  const Obj_Entry **defobj_out, bool in_plt)
{
    const Elf_Sym *symp;
    const Elf_Sym *def;
    const Obj_Entry *defobj;
    const Objlist_Entry *elm;

    def = NULL;
    defobj = NULL;
    STAILQ_FOREACH(elm, objlist, link) {
	if (elm->obj->mark == curmark)
	    continue;
	elm->obj->mark = curmark;
	if ((symp = symlook_obj(name, hash, elm->obj, in_plt)) != NULL) {
	    if (def == NULL || ELF_ST_BIND(symp->st_info) != STB_WEAK) {
		def = symp;
		defobj = elm->obj;
		if (ELF_ST_BIND(def->st_info) != STB_WEAK)
		    break;
	    }
	}
    }
    if (def != NULL)
	*defobj_out = defobj;
    return def;
}

/*
 * Search the symbol table of a single shared object for a symbol of
 * the given name.  Returns a pointer to the symbol, or NULL if no
 * definition was found.
 *
 * The symbol's hash value is passed in for efficiency reasons; that
 * eliminates many recomputations of the hash value.
 */
const Elf_Sym *
symlook_obj(const char *name, unsigned long hash, const Obj_Entry *obj,
  bool in_plt)
{
    if (obj->buckets != NULL) {
	unsigned long symnum = obj->buckets[hash % obj->nbuckets];

	while (symnum != STN_UNDEF) {
	    const Elf_Sym *symp;
	    const char *strp;

	    if (symnum >= obj->nchains)
		return NULL;	/* Bad object */
	    symp = obj->symtab + symnum;
	    strp = obj->strtab + symp->st_name;

	    if (strcmp(name, strp) == 0)
		return symp->st_shndx != SHN_UNDEF ||
		  (!in_plt && symp->st_value != 0 &&
		  ELF_ST_TYPE(symp->st_info) == STT_FUNC) ? symp : NULL;

	    symnum = obj->chains[symnum];
	}
    }
    return NULL;
}

static void
trace_loaded_objects(Obj_Entry *obj)
{
    char	*fmt1, *fmt2, *fmt, *main_local;
    int		c;

    if ((main_local = getenv("LD_TRACE_LOADED_OBJECTS_PROGNAME")) == NULL)
	main_local = "";

    if ((fmt1 = getenv("LD_TRACE_LOADED_OBJECTS_FMT1")) == NULL)
	fmt1 = "\t%o => %p (%x)\n";

    if ((fmt2 = getenv("LD_TRACE_LOADED_OBJECTS_FMT2")) == NULL)
	fmt2 = "\t%o (%x)\n";

    for (; obj; obj = obj->next) {
	Needed_Entry		*needed;
	char			*name, *path;
	bool			is_lib;

	for (needed = obj->needed; needed; needed = needed->next) {
	    if (needed->obj != NULL) {
		if (needed->obj->traced)
		    continue;
		needed->obj->traced = true;
		path = needed->obj->path;
	    } else
		path = "not found";

	    name = (char *)obj->strtab + needed->name;
	    is_lib = strncmp(name, "lib", 3) == 0;	/* XXX - bogus */

	    fmt = is_lib ? fmt1 : fmt2;
	    while ((c = *fmt++) != '\0') {
		switch (c) {
		default:
		    putchar(c);
		    continue;
		case '\\':
		    switch (c = *fmt) {
		    case '\0':
			continue;
		    case 'n':
			putchar('\n');
			break;
		    case 't':
			putchar('\t');
			break;
		    }
		    break;
		case '%':
		    switch (c = *fmt) {
		    case '\0':
			continue;
		    case '%':
		    default:
			putchar(c);
			break;
		    case 'A':
			printf("%s", main_local);
			break;
		    case 'a':
			printf("%s", obj_main->path);
			break;
		    case 'o':
			printf("%s", name);
			break;
#if 0
		    case 'm':
			printf("%d", sodp->sod_major);
			break;
		    case 'n':
			printf("%d", sodp->sod_minor);
			break;
#endif
		    case 'p':
			printf("%s", path);
			break;
		    case 'x':
			printf("%p", needed->obj ? needed->obj->mapbase : 0);
			break;
		    }
		    break;
		}
		++fmt;
	    }
	}
    }
}

/*
 * Note, this is called only for objects loaded by dlopen().
 */
static void
unload_object(Obj_Entry *root, bool do_fini_funcs)
{
    unref_dag(root);
    if (root->refcount == 0) {	/* We are finished with some objects. */
	Obj_Entry *obj;
	Obj_Entry **linkp;
	Objlist_Entry *elm;

	/* Finalize objects that are about to be unmapped. */
	if (do_fini_funcs)
	    for (obj = obj_list->next;  obj != NULL;  obj = obj->next)
		if (obj->refcount == 0 && obj->fini != NULL)
		    (*obj->fini)();

	/* Remove the DAG from all objects' DAG lists. */
	STAILQ_FOREACH(elm, &root->dagmembers , link)
	    objlist_remove(&elm->obj->dldags, root);

	/* Remove the DAG from the RTLD_GLOBAL list. */
	objlist_remove(&list_global, root);

	/* Unmap all objects that are no longer referenced. */
	linkp = &obj_list->next;
	while ((obj = *linkp) != NULL) {
	    if (obj->refcount == 0) {
		dbg("unloading \"%s\"", obj->path);
		munmap(obj->mapbase, obj->mapsize);
		linkmap_delete(obj);
		*linkp = obj->next;
		obj_free(obj);
	    } else
		linkp = &obj->next;
	}
	obj_tail = linkp;
    }
}

static void
unref_dag(Obj_Entry *root)
{
    const Needed_Entry *needed;

    assert(root->refcount != 0);
    root->refcount--;
    if (root->refcount == 0)
	for (needed = root->needed;  needed != NULL;  needed = needed->next)
	    if (needed->obj != NULL)
		unref_dag(needed->obj);
}

/*
 * Non-mallocing printf, for use by malloc itself.
 * XXX - This doesn't belong in this module.
 */
void
xprintf(const char *fmt, ...)
{
    char buf[256];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    (void)write(1, buf, strlen(buf));
    va_end(ap);
}
