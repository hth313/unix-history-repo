/* VMS crt0 returning Unix style condition codes .
   Copyright (C) 2001 Free Software Foundation, Inc.
   Contributed by Douglas B. Rupp (rupp@gnat.com).

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

In addition to the permissions in the GNU General Public License, the
Free Software Foundation gives you unlimited permission to link the
compiled version of this file into combinations with other programs,
and to distribute those combinations without any restriction coming
from the use of this file.  (The General Public License restrictions
do apply in other respects; for example, they cover modification of
the file, and distribution when not linked into a combine
executable.)

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#if !defined(__DECC)
You Lose! This file can only be compiled with DEC C.
#else

/* This file can only be compiled with DEC C, due to the call to
   lib$establish.  */

#include <stdlib.h>
#include <string.h>
#include <ssdef.h>
#include <stsdef.h>
#include <errnodef.h>

extern void decc$main ();
extern int main ();

static int
handler (sigargs, mechargs)
     void *sigargs;
     void *mechargs;
{
  return SS$_RESIGNAL;
}

int
__main (arg1, arg2, arg3, image_file_desc, arg5, arg6)
     void *arg1, *arg2, *arg3;
     void *image_file_desc;
     void *arg5, *arg6;
{
  int argc;
  char **argv;
  char **envp;
  int status;

  lib$establish (handler);
  decc$main (arg1, arg2, arg3, image_file_desc, arg5, arg6,
	     &argc, &argv, &envp);

  status = main (argc, argv, envp);

  /* Map into a range of 0 - 255.  */
  status = status & 255;

  if (status > 0)
    {
      int save_status = status;

      status = C$_EXIT1 + ((status - 1) << STS$V_MSG_NO);

      /* An exit failure status requires a "severe" error
	 All status values are defined in errno with a successful
	 (1) severity but can be changed to an error (2) severity by adding 1.
	 In addition for compatibility with UNIX exit() routines we inhibit
	 a run-time error message from being generated on exit(1).  */

      if (save_status == 1)
	{
	  status++;
	  status |= STS$M_INHIB_MSG;
	}
    }

  if (status == 0)
    status = SS$_NORMAL;

  return status;
}
#endif
