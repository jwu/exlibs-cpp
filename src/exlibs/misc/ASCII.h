// ======================================================================================
// File         : ASCII.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:14:43 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ASCII_H_1250525686
#define ASCII_H_1250525686
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
//  Define: 
///////////////////////////////////////////////////////////////////////////////


// TODO: unused ??
// #define CharOrd(x)	((x) < 'a' ? (x) - 'A' : (x) - 'a')
// #define CharOrdLow(x)	((x) - 'a')
// #define CharOrdUp(x)	((x) - 'A')
// #define ROT13(c, a)	(((((c) - (a)) + 13) % 26) + (a))


// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

#define EX_NUL		     '\000'
#define EX_BELL          '\007'
#define EX_BS		     '\010'
#define EX_TAB		     '\011'
#define EX_NL		     '\012'
#define EX_NL_STR        (char_u *)"\012"
#define EX_FF		     '\014'
#define EX_CAR		     '\015'	/* CR is used by Mac OS X */
#define EX_ESC		     '\033'
#define EX_ESC_STR		 (char_u *)"\033"
#define EX_ESC_STR_nc	 "\033"
#define EX_DEL		     0x7f
#define EX_DEL_STR		 (char_u *)"\177"
#define EX_CSI		     0x9b	/* Control Sequence Introducer */
#define EX_CSI_STR		 "\233"
#define EX_DCS		     0x90	/* Device Control String */
#define EX_STERM		 0x9c	/* String Terminator */

#define EX_POUND		 0xA3

// TODO:
#define EX_CTRL(x)	     (TOUPPER_ASC(x) ^ 0x40) /* '?' -> DEL, '@' -> ^@, etc. */
#define EX_META(x)		 ((x) | 0x80)

#define EX_CTRL_F_STR	 "\006"
#define EX_CTRL_H_STR	 "\010"
#define EX_CTRL_V_STR	 "\026"

// TODO: ????? ctrl + a or a ?????
#define EX_CTRL_AT		0   /* @ */
#define EX_CTRL_A		1
#define EX_CTRL_B		2
#define EX_CTRL_C		3
#define EX_CTRL_D		4
#define EX_CTRL_E		5
#define EX_CTRL_F		6
#define EX_CTRL_G		7
#define EX_CTRL_H		8
#define EX_CTRL_I		9
#define EX_CTRL_J		10
#define EX_CTRL_K		11
#define EX_CTRL_L		12
#define EX_CTRL_M		13
#define EX_CTRL_N		14
#define EX_CTRL_O		15
#define EX_CTRL_P		16
#define EX_CTRL_Q		17
#define EX_CTRL_R		18
#define EX_CTRL_S		19
#define EX_CTRL_T		20
#define EX_CTRL_U		21
#define EX_CTRL_V		22
#define EX_CTRL_W		23
#define EX_CTRL_X		24
#define EX_CTRL_Y		25
#define EX_CTRL_Z		26
		                    /* CTRL- [ Left Square Bracket == ESC*/
#define EX_CTRL_BSL	    28  /* \ BackSLash */
#define EX_CTRL_RSB	    29  /* ] Right Square Bracket */
#define EX_CTRL_HAT	    30  /* ^ */
#define EX_CTRL__		31

// TODO: unused???
#if 0
/*
 * Character that separates dir names in a path.
 * For MS-DOS, WIN32 and OS/2 we use a backslash.  A slash mostly works
 * fine, but there are places where it doesn't (e.g. in a command name).
 * For Acorn we use a dot.
 */
#ifdef BACKSLASH_IN_FILENAME
# define PATHSEP	psepc
# define PATHSEPSTR	pseps
#else
# ifdef RISCOS
#  define PATHSEP	'.'
#  define PATHSEPSTR	"."
# else
#  define PATHSEP	'/'
#  define PATHSEPSTR	"/"
# endif
#endif
#endif

// #################################################################################
#endif // END ASCII_H_1250525686
// #################################################################################
