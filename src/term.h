/* GNUPLOT - term.h */

/*[
 * Copyright 1986 - 1993, 1998, 2004   Thomas Williams, Colin Kelley
 *
 * Permission to use, copy, and distribute this software and its
 * documentation for any purpose with or without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 *
 * Permission to modify the software is granted, but not the right to
 * distribute the complete modified source code.  Modifications are to
 * be distributed as patches to the released version.  Permission to
 * distribute binaries produced by compiling modified sources is granted,
 * provided you
 *   1. distribute the corresponding source modifications from the
 *    released version in the form of a patch file along with the binaries,
 *   2. add special version identification to distinguish your version
 *    in addition to the base release version number,
 *   3. provide your name and address as the primary contact for the
 *    support of your modified version, and
 *   4. retain our contact information in regard to use of the base
 *    software.
 * Permission to distribute the released version of the source code along
 * with corresponding source modifications in the form of a patch file is
 * granted with same provisions 2 through 4 for binary distributions.
 *
 * This software is provided "as is" without express or implied warranty
 * to the extent permitted by applicable law.
]*/

/*
 * term.h: terminal support definitions
 *   Edit this file depending on the set of terminals you wish to support.
 * Comment out the terminal types that you don't want or don't have, and
 * uncomment those that you want included. Be aware that some terminal
 * types will require changes in the makefile LIBS definition.
 */

/*
 * first draft after all terminals are converted to new layout
 * Stefan Bodewig Dec. 1995
 */

/*
 * >>> CONFIGURATION OPTIONS FOLLOW <<<  PLEASE READ
 *
 * pslatex and epslatex support is now provided by the combination of
 * post.trm and pslatex.trm.  You cannot build pslatex without post.
 * Both drivers are selected by default, but you can disable them below.
 *
 * Enhanced text support is pretty much required for all terminals now.
 * If you build without GP_ENH_EST text layout will be degraded.
 */

#define contains_unicode(S) strstr(S, "\\U+")
#define DEFAULTTERM "gtkcairo"

#include "estimate.h"
#include "cairo.h"
