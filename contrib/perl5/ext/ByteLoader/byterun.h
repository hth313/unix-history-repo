/*
 *      Copyright (c) 1996-1999 Malcolm Beattie
 *
 *      You may distribute under the terms of either the GNU General Public
 *      License or the Artistic License, as specified in the README file.
 *
 */
/*
 * This file is autogenerated from bytecode.pl. Changes made here will be lost.
 */
struct byteloader_fdata {
    SV	*datasv;
    int next_out;
    int	idx;
};

struct byteloader_state {
    struct byteloader_fdata	*bs_fdata;
    SV				*bs_sv;
    void			**bs_obj_list;
    int				bs_obj_list_fill;
    XPV				bs_pv;
    int				bs_iv_overflows;
};

int bl_getc(struct byteloader_fdata *);
int bl_read(struct byteloader_fdata *, char *, size_t, size_t);
extern void byterun(pTHXo_ struct byteloader_state *);

enum {
    INSN_RET,			/* 0 */
    INSN_LDSV,			/* 1 */
    INSN_LDOP,			/* 2 */
    INSN_STSV,			/* 3 */
    INSN_STOP,			/* 4 */
    INSN_STPV,			/* 5 */
    INSN_LDSPECSV,			/* 6 */
    INSN_NEWSV,			/* 7 */
    INSN_NEWOP,			/* 8 */
    INSN_NEWOPN,			/* 9 */
    INSN_NOP,			/* 10 */
    INSN_NEWPV,			/* 11 */
    INSN_PV_CUR,			/* 12 */
    INSN_PV_FREE,			/* 13 */
    INSN_SV_UPGRADE,			/* 14 */
    INSN_SV_REFCNT,			/* 15 */
    INSN_SV_REFCNT_ADD,			/* 16 */
    INSN_SV_FLAGS,			/* 17 */
    INSN_XRV,			/* 18 */
    INSN_XPV,			/* 19 */
    INSN_XIV32,			/* 20 */
    INSN_XIV64,			/* 21 */
    INSN_XNV,			/* 22 */
    INSN_XLV_TARGOFF,			/* 23 */
    INSN_XLV_TARGLEN,			/* 24 */
    INSN_XLV_TARG,			/* 25 */
    INSN_XLV_TYPE,			/* 26 */
    INSN_XBM_USEFUL,			/* 27 */
    INSN_XBM_PREVIOUS,			/* 28 */
    INSN_XBM_RARE,			/* 29 */
    INSN_XFM_LINES,			/* 30 */
    INSN_XIO_LINES,			/* 31 */
    INSN_XIO_PAGE,			/* 32 */
    INSN_XIO_PAGE_LEN,			/* 33 */
    INSN_XIO_LINES_LEFT,			/* 34 */
    INSN_COMMENT,			/* 35 */
    INSN_XIO_TOP_NAME,			/* 36 */
    INSN_XIO_TOP_GV,			/* 37 */
    INSN_XIO_FMT_NAME,			/* 38 */
    INSN_XIO_FMT_GV,			/* 39 */
    INSN_XIO_BOTTOM_NAME,			/* 40 */
    INSN_XIO_BOTTOM_GV,			/* 41 */
    INSN_XIO_SUBPROCESS,			/* 42 */
    INSN_XIO_TYPE,			/* 43 */
    INSN_XIO_FLAGS,			/* 44 */
    INSN_XCV_STASH,			/* 45 */
    INSN_XCV_START,			/* 46 */
    INSN_XCV_ROOT,			/* 47 */
    INSN_XCV_GV,			/* 48 */
    INSN_XCV_FILE,			/* 49 */
    INSN_XCV_DEPTH,			/* 50 */
    INSN_XCV_PADLIST,			/* 51 */
    INSN_XCV_OUTSIDE,			/* 52 */
    INSN_XCV_FLAGS,			/* 53 */
    INSN_AV_EXTEND,			/* 54 */
    INSN_AV_PUSH,			/* 55 */
    INSN_XAV_FILL,			/* 56 */
    INSN_XAV_MAX,			/* 57 */
    INSN_XAV_FLAGS,			/* 58 */
    INSN_XHV_RITER,			/* 59 */
    INSN_XHV_NAME,			/* 60 */
    INSN_HV_STORE,			/* 61 */
    INSN_SV_MAGIC,			/* 62 */
    INSN_MG_OBJ,			/* 63 */
    INSN_MG_PRIVATE,			/* 64 */
    INSN_MG_FLAGS,			/* 65 */
    INSN_MG_PV,			/* 66 */
    INSN_XMG_STASH,			/* 67 */
    INSN_GV_FETCHPV,			/* 68 */
    INSN_GV_STASHPV,			/* 69 */
    INSN_GP_SV,			/* 70 */
    INSN_GP_REFCNT,			/* 71 */
    INSN_GP_REFCNT_ADD,			/* 72 */
    INSN_GP_AV,			/* 73 */
    INSN_GP_HV,			/* 74 */
    INSN_GP_CV,			/* 75 */
    INSN_GP_FILE,			/* 76 */
    INSN_GP_IO,			/* 77 */
    INSN_GP_FORM,			/* 78 */
    INSN_GP_CVGEN,			/* 79 */
    INSN_GP_LINE,			/* 80 */
    INSN_GP_SHARE,			/* 81 */
    INSN_XGV_FLAGS,			/* 82 */
    INSN_OP_NEXT,			/* 83 */
    INSN_OP_SIBLING,			/* 84 */
    INSN_OP_PPADDR,			/* 85 */
    INSN_OP_TARG,			/* 86 */
    INSN_OP_TYPE,			/* 87 */
    INSN_OP_SEQ,			/* 88 */
    INSN_OP_FLAGS,			/* 89 */
    INSN_OP_PRIVATE,			/* 90 */
    INSN_OP_FIRST,			/* 91 */
    INSN_OP_LAST,			/* 92 */
    INSN_OP_OTHER,			/* 93 */
    INSN_OP_PMREPLROOT,			/* 94 */
    INSN_OP_PMREPLROOTGV,			/* 95 */
    INSN_OP_PMREPLSTART,			/* 96 */
    INSN_OP_PMNEXT,			/* 97 */
    INSN_PREGCOMP,			/* 98 */
    INSN_OP_PMFLAGS,			/* 99 */
    INSN_OP_PMPERMFLAGS,			/* 100 */
    INSN_OP_SV,			/* 101 */
    INSN_OP_PADIX,			/* 102 */
    INSN_OP_PV,			/* 103 */
    INSN_OP_PV_TR,			/* 104 */
    INSN_OP_REDOOP,			/* 105 */
    INSN_OP_NEXTOP,			/* 106 */
    INSN_OP_LASTOP,			/* 107 */
    INSN_COP_LABEL,			/* 108 */
    INSN_COP_STASHPV,			/* 109 */
    INSN_COP_FILE,			/* 110 */
    INSN_COP_SEQ,			/* 111 */
    INSN_COP_ARYBASE,			/* 112 */
    INSN_COP_LINE,			/* 113 */
    INSN_COP_WARNINGS,			/* 114 */
    INSN_MAIN_START,			/* 115 */
    INSN_MAIN_ROOT,			/* 116 */
    INSN_CURPAD,			/* 117 */
    INSN_PUSH_BEGIN,			/* 118 */
    INSN_PUSH_INIT,			/* 119 */
    INSN_PUSH_END,			/* 120 */
    MAX_INSN = 120
};

enum {
    OPt_OP,		/* 0 */
    OPt_UNOP,		/* 1 */
    OPt_BINOP,		/* 2 */
    OPt_LOGOP,		/* 3 */
    OPt_LISTOP,		/* 4 */
    OPt_PMOP,		/* 5 */
    OPt_SVOP,		/* 6 */
    OPt_PADOP,		/* 7 */
    OPt_PVOP,		/* 8 */
    OPt_LOOP,		/* 9 */
    OPt_COP		/* 10 */
};

