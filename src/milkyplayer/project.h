#ifndef MILKYPLAYER_PROJECT_H
#define MILKYPLAYER_PROJECT_H 1

#ifdef __AMIGA__
#include <libraries/mui.h>
#include <libraries/gadtools.h>
#include <libraries/iffparse.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/muimaster_lib.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include <proto/graphics.h>

#include <clib/alib_protos.h>
//#include <exec/types.h>
#include <utility/tagitem.h>
//#define printf(x) Printf
#else
#define BOOL bool
#define TRUE true
#define FALSE false
#define ULONG unsigned long
#define Printf printf
#endif

//#include <stdio.h>
//#include <stdlib.h>

#ifdef __AMIGA__
#define MAKE_ID(a,b,c,d) ((ULONG) (a)<<24 | (ULONG) (b)<<16 | (ULONG) (c)<<8 | (ULONG) (d))

#define IPTR ULONG

#endif

BOOL Open_Libs();

void Close_Libs();

#endif // MILKYPLAYER_PROJECT_H