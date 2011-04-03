// ======================================================================================
// File         : compiler.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 14:14:49 PM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef COMPILER_H_1250525221
#define COMPILER_H_1250525221
// #################################################################################

// ------------------------------------------------------------------
// Desc: Compiler define
//  use EX_COMPILER to judge current compiler
//  use EX_COMPILER_VER to judge current compiler version 
// ------------------------------------------------------------------

#define EX_MSVC     0x01
#define EX_GCC      0x02

// ------------------------------------------------------------------
// Desc: Compiler choose & Compiler version choose
// ------------------------------------------------------------------

#if defined ( _MSC_VER )
    #define EX_COMPILER     EX_MSVC
    #define EX_COMPILER_VER _MSC_VER
#elif defined ( __GNUC__ )
    #define EX_COMPILER     EX_GCC 
    #define EX_COMPILER_VER (((__GNUC__)*100)+__GNUC_MINOR__)
#else
    #define EX_COMPILER     EX_UNKNOWN
    #define EX_COMPILER_VER EX_UNKNOWN
#endif

// ------------------------------------------------------------------
// Desc: Void cast
// ------------------------------------------------------------------

#if ( EX_COMPILER == EX_GCC )
    #if defined __cplusplus
        #define EX_VOID_CAST static_cast<void>
    #else
        #define EX_VOID_CAST (void)
    #endif
#else
    #define EX_VOID_CAST (void)
#endif

// ------------------------------------------------------------------
// Desc: Noop
// ------------------------------------------------------------------

#if ( EX_COMPILER == EX_MSVC )
    #define EX_NOOP __noop
#elif ( EX_COMPILER == EX_GCC )
    #define EX_NOOP EX_VOID_CAST(0)
#endif

// ------------------------------------------------------------------
// Desc: Force Inline
// ------------------------------------------------------------------

#if ( EX_COMPILER == EX_MSVC )
    #define EX_FORCE_INLINE __forceinline // msvc force inline method
#elif ( EX_COMPILER == EX_GCC )
    #define EX_FORCE_INLINE inline __attribute__ ((always_inline__)) // gcc force inline method
#endif

// ------------------------------------------------------------------
// Desc: Alignment
// ------------------------------------------------------------------

#if ( EX_COMPILER == EX_MSVC )
    #define EX_ALIGN(n) __declspec(align(n))
#elif ( EX_COMPILER == EX_GCC )
    #define EX_ALIGN(n) __attribute__((aligned(n)))
#endif

// ------------------------------------------------------------------
// Desc: Some Compiler do not support this macro.
// ------------------------------------------------------------------

#if ( (EX_COMPILER != EX_GCC) && (EX_COMPILER != EX_MSVC) )
    #ifndef __FUNCTION__
    #define __FUNCTION__ "???"
    #endif
#endif

// ------------------------------------------------------------------
// Desc: The msvc need the PCH included without any path specific,
//       but the gcc need the exactly path of the header file.
// ------------------------------------------------------------------

#if ( EX_COMPILER == EX_MSVC )
    #define EX_GCH_PCH( gch, pch ) EX_STRING(pch)
#elif ( EX_COMPILER == EX_GCC )
    #define EX_GCH_PCH( gch, pch ) EX_STRING(gch)
#endif

// ------------------------------------------------------------------ 
// Desc: EX_DEPRECATED 
// Usage1 func: EX_DEPRECATED("not allowed") void func1() {}
// Usage2 class: class EX_DEPRECATED("not allowed") CClassName { ... }; 
// ------------------------------------------------------------------ 

#if ( EX_COMPILER == EX_MSVC )
    #define EX_DEPRECATED(desc) __declspec(deprecated(desc))
#elif ( EX_COMPILER == EX_GCC )
    #if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
        #define EX_DEPRECATED(desc) __attribute__((__deprecated__))
    #else
        #define EX_DEPRECATED(desc)
    #endif
#endif

// ------------------------------------------------------------------ 
// Desc: EX_FUNC_INFO 
// ------------------------------------------------------------------ 

#if ( EX_COMPILER == EX_MSVC )
    #define EX_FUNC_INFO __FUNCSIG__
#elif ( EX_COMPILER == EX_GCC )
    #define EX_FUNC_INFO __FILE__(__LINE__): __FUNCTION__
#endif

///////////////////////////////////////////////////////////////////////////////
//  warning pragma
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: warnning pragma
// ------------------------------------------------------------------

#if ( EX_COMPILER == EX_MSVC )
    #pragma warning(disable : 4100)     // warning C4100: 'xxx': unreferenced formal parameter
    #pragma warning(disable : 4251)     // warning C4251: 'xxx': needs to have dll-interface to be used by clients of xxx
    #pragma warning(disable : 4275)     // warning C4275: non dll-interface 'xxx' used as base for dll-interface 'xxx'
    #pragma warning(disable : 4996)     // warning C4996: 'xxxxxx': This function or variable may be unsafe. Consider using xxxxxx_s instead.

    #if defined (EX_RELEASE)
        #pragma warning(disable : 4800) // warning C4800: 'BOOL' : forcing value to bool 'true' or 'false' (performance warning)
    #endif

    // NOTE:
    // this warning occurrs when the decorated name of a symbol is larger than 255
    // bytes. the debugger will truncate this to 255 byte for display. There is
    // nothing you can do about it.
    // This frequently happens with template libraries because they have large
    // mangled names. These warnings are harmless.
    #pragma warning(disable : 4503)     // warning C4503: decorated name length exceeded, name was truncated

#elif ( EX_COMPILER == EX_GCC )
#endif

// #################################################################################
#endif // END COMPILER_H_1250525221
// #################################################################################
