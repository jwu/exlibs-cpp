// ======================================================================================
// File         : typedefs.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 14:15:08 PM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef TYPEDEFS_H_1281715105
#define TYPEDEFS_H_1281715105
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// undefine any used types
///////////////////////////////////////////////////////////////////////////////

// #ifdef BYTE
// #undef BYTE
// #endif

// #ifdef WORD
// #undef WORD
// #endif

// #ifdef DWORD
// #undef DWORD
// #endif

// #ifdef INT
// #undef INT
// #endif

// #ifdef FLOAT
// #undef FLOAT
// #endif

// #ifdef DOUBLE
// #undef DOUBLE
// #endif

// #ifdef INT
// #undef INT
// #endif

// #ifdef INT8
// #undef INT8
// #endif

// #ifdef INT16
// #undef INT16
// #endif

// #ifdef INT32
// #undef INT32
// #endif

// #ifdef INT64
// #undef INT64
// #endif

// #ifdef UINT
// #undef UINT
// #endif

// #ifdef UINT8
// #undef UINT8
// #endif

// #ifdef UINT16
// #undef UINT16
// #endif

// #ifdef UINT32
// #undef UINT32
// #endif

// #ifdef UINT64
// #undef UINT64
// #endif

// #ifdef FLOAT
// #undef FLOAT
// #endif

// #ifdef DOUBLE
// #undef DOUBLE
// #endif

// #ifdef CHAR
// #undef CHAR
// #endif

// #ifdef WCHAR
// #undef WCHAR
// #endif

// #ifdef TCHAR
// #undef TCHAR
// #endif

// #ifdef TEXT
// #undef TEXT
// #endif

// #ifdef SIZE_T
// #undef SIZE_T
// #endif

// #ifdef INLINE
// #undef INLINE
// #endif

// #ifdef BOOL
// #undef BOOL
// #endif

// #ifdef UBOOL
// #undef UBOOL
// #endif

// #ifdef TRUE
// #undef TRUE
// #endif

// #ifdef FALSE
// #undef FALSE
// #endif

// #ifdef NULL
// #undef NULL
// #endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

///////////////////////////////////////////////////////////////////////////////
// Compiler different types
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//  MSVC 
///////////////////////////////////////////////////////////////////////////////

#if ( EX_COMPILER == EX_MSVC )

    // ------------------------------------------------------------------
    // Desc: signed base types
    // ------------------------------------------------------------------

    // typedef signed int       int;
    typedef signed char         int8;
    typedef signed short        int16;
    typedef signed int          int32;
    typedef signed __int64      int64;

    // ------------------------------------------------------------------
    // Desc: unsigned base types
    // ------------------------------------------------------------------

    typedef unsigned int        uint;
    typedef unsigned char       uint8;
    typedef unsigned short      uint16;
    typedef unsigned int        uint32;
    typedef unsigned __int64    uint64;

    // ------------------------------------------------------------------
    // Desc: char types
    // ------------------------------------------------------------------

    // DISABLE { 
    // typedef wchar_t wchar;
    // NOTE: in msvc, pls turn off the whar_t as bultin-type option in C/C++ - Language
    // } DISABLE end 

    // we don't turn off wchar_t as builtin-type, instead we use static_cast for wchar_t to wchar
    typedef unsigned short wchar;
    #ifdef W
        #undef W
    #endif
    #define W(s) (const ::ex::wchar*)(L##s)

    // ------------------------------------------------------------------
    // Desc: text & tchar 
    // ------------------------------------------------------------------

    #ifdef TE
        #undef TE
    #endif
    #if EX_USE_UNICODE
        typedef wchar   tchar;
        #define TE(s) W(s)
    #else 
        typedef char    tchar;
        #define TE(s) s
    #endif // END EX_USE_UNICODE

    // ------------------------------------------------------------------
    // Desc: bool type
    // ------------------------------------------------------------------

    // typedef int     BOOL; // vc have defined this

    // ------------------------------------------------------------------
    // Desc: true
    // ------------------------------------------------------------------

    #ifdef TRUE
        #undef TRUE
    #endif
    #define TRUE    1

    // ------------------------------------------------------------------
    // Desc: false
    // ------------------------------------------------------------------

    #ifdef FALSE
        #undef FALSE
    #endif
    #define FALSE   0

    // ------------------------------------------------------------------
    // Desc: NULL
    // ------------------------------------------------------------------

    #ifdef NULL
        #undef NULL
    #endif
    #define NULL    0

    // ------------------------------------------------------------------
    // Desc: max,min size
    // ------------------------------------------------------------------

    #pragma warning( push )
    #pragma warning( disable : 4309 ) 

    const int8      EX_INT8_MIN    = 0x80; // warning C4309: 'initializing' : truncation of constant value
    const int8      EX_INT8_MAX    = 0x7F;
    const uint8     EX_UINT8_MIN   = 0x00;
    const uint8     EX_UINT8_MAX   = 0xFF;
    const int16     EX_INT16_MIN   = 0x8000; // warning C4309: 'initializing' : truncation of constant value 
    const int16     EX_INT16_MAX   = 0x7FFF;
    const uint16    EX_UINT16_MIN  = 0x0000;
    const uint16    EX_UINT16_MAX  = 0xFFFF;
    const int32     EX_INT32_MIN   = 0x80000000;
    const int32     EX_INT32_MAX   = 0x7FFFFFFF;
    const uint32    EX_UINT32_MIN  = 0x00000000;
    const uint32    EX_UINT32_MAX  = 0xFFFFFFFF;
    const int64     EX_INT64_MIN   = 0x8000000000000000;
    const int64     EX_INT64_MAX   = 0x7FFFFFFFFFFFFFFF;
    const uint64    EX_UINT64_MIN  = 0x0000000000000000;
    const uint64    EX_UINT64_MAX  = 0xFFFFFFFFFFFFFFFF;
    const float     EX_FLOAT_MIN   = 1.175494351E-38F;
    const float     EX_FLOAT_MAX   = 3.402823466E+38F;
    const double    EX_DOUBLE_MIN  = 2.2250738585072014E-308;
    const double    EX_DOUBLE_MAX  = 1.7976931348623158E+308;

    #pragma warning( pop )

    // ------------------------------------------------------------------
    // Desc: attributes of function
    // ------------------------------------------------------------------

    // ========================================================
    // inline
    // ========================================================

    #ifdef INLINE
        #undef INLINE
    #endif
    #if EX_USE_FORCEINLINE
        #define INLINE  EX_FORCE_INLINE
    #else
        #define INLINE  inline        
    #endif

    // ========================================================
    // noinline
    // ========================================================

    #ifdef NOINLINE
        #undef NOINLINE
    #endif
    #define NOINLINE __declspec(noinline)

    // ========================================================
    // stdcall
    // ========================================================

    #ifdef STDCALL
        #undef STDCALL
    #endif
    #define STDCALL stdcall 

    // ========================================================
    // cdecl
    // ========================================================

    #ifdef CDECL
        #undef CDECL
    #endif
    #define CDECL cdecl

    // ========================================================
    // deprecated
    // ========================================================

    #ifdef EX_DEPRECATED
        #undef EX_DEPRECATED
    #endif
    #define EX_DEPRECATED __declspec(deprecated) 

#elif ( EX_COMPILER == EX_GCC )

///////////////////////////////////////////////////////////////////////////////
// Desc: GCC 
///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------
    // Desc: signed base types
    // ------------------------------------------------------------------

    // typedef signed int           int;
    typedef signed char             int8;
    typedef signed short            int16;
    typedef signed int              int32;
    typedef signed long long int    int64;

    // ------------------------------------------------------------------
    // Desc: unsigned base types
    // ------------------------------------------------------------------

    typedef unsigned int            uint;
    typedef unsigned char           uint8;
    typedef unsigned short          uint16;
    typedef unsigned int            uint32;
    typedef unsigned long long int  uint64;

    // ------------------------------------------------------------------
    // Desc: char types
    // ------------------------------------------------------------------

    // typedef char char;
    typedef wchar_t wchar;
    #ifdef W
        #undef W
    #endif
    #define W(s) (const ::ex::wchar*)(L##s)

    #ifdef TE
        #undef TE
    #endif
    #if EX_USE_UNICODE
        typedef wchar   tchar;
        #define TE(s) W(s)
    #else 
        typedef char    tchar;
        #define TE(s) s
    #endif // END EX_USE_UNICODE

    // ------------------------------------------------------------------
    // Desc: bool type
    // ------------------------------------------------------------------

    // typedef int     BOOL; 

    // ------------------------------------------------------------------
    // Desc: true
    // ------------------------------------------------------------------

    #ifdef TRUE
        #undef TRUE
    #endif
    #define TRUE    1

    // ------------------------------------------------------------------
    // Desc: false
    // ------------------------------------------------------------------

    #ifdef FALSE
        #undef FALSE
    #endif
    #define FALSE   0

    // ------------------------------------------------------------------
    // Desc: null
    // ------------------------------------------------------------------

    #ifdef NULL
        #undef NULL
    #endif
    #define NULL    0

    // ------------------------------------------------------------------
    // Desc: max,min size
    // ------------------------------------------------------------------

    // undefine the gcc __INT64_C & __UINT64_C
    #undef __INT64_C
    #undef __UINT64_C

    // undefine the gcc MIN/MAX macros
    #undef INT8_MIN
    #undef INT16_MIN
    #undef INT32_MIN
    #undef INT64_MIN
    #undef INT8_MAX
    #undef INT16_MAX
    #undef INT32_MAX
    #undef INT64_MAX
    #undef UINT8_MAX
    #undef UINT16_MAX
    #undef UINT32_MAX
    #undef UINT64_MAX

    #if __WORDSIZE == 64
        #define __INT64_C(c)	c ## L
        #define __UINT64_C(c)	c ## UL
    #else
        #define __INT64_C(c)	c ## LL
        #define __UINT64_C(c)	c ## ULL
    #endif
    
    /* Limits of integral types.  */
    
    /* Minimum of signed integral types.  */
    #define INT8_MIN		(-128)
    #define INT16_MIN		(-32767-1)
    #define INT32_MIN		(-2147483647-1)
    #define INT64_MIN		(-__INT64_C(9223372036854775807)-1)
    /* Maximum of signed integral types.  */
    #define INT8_MAX		(127)
    #define INT16_MAX		(32767)
    #define INT32_MAX		(2147483647)
    #define INT64_MAX		(__INT64_C(9223372036854775807))
    
    /* Maximum of unsigned integral types.  */
    #define UINT8_MAX		(255)
    #define UINT16_MAX		(65535)
    #define UINT32_MAX		(4294967295U)
    #define UINT64_MAX		(__UINT64_C(18446744073709551615))

    // define the EX MIN/MAX const value
    const int8      EX_INT8_MIN    = INT8_MIN;
    const int8      EX_INT8_MAX    = INT8_MAX;
    const uint8     EX_UINT8_MIN   = 0x00;
    const uint8     EX_UINT8_MAX   = UINT8_MAX;
    const int16     EX_INT16_MIN   = INT16_MIN; 
    const int16     EX_INT16_MAX   = INT16_MAX;
    const uint16    EX_UINT16_MIN  = 0x0000;
    const uint16    EX_UINT16_MAX  = UINT16_MAX;
    const int32     EX_INT32_MIN   = INT32_MIN;
    const int32     EX_INT32_MAX   = INT32_MAX;
    const uint32    EX_UINT32_MIN  = 0x00000000;
    const uint32    EX_UINT32_MAX  = UINT32_MAX;
    const int64     EX_INT64_MIN   = INT64_MIN;
    const int64     EX_INT64_MAX   = INT64_MAX;
    const uint64    EX_UINT64_MIN  = 0x0000000000000000;
    const uint64    EX_UINT64_MAX  = UINT64_MAX;
    const float     EX_FLOAT_MIN   = 1.175494351E-38F;
    const float     EX_FLOAT_MAX   = 3.402823466E+38F;
    const double    EX_DOUBLE_MIN  = 2.2250738585072014E-308;
    const double    EX_DOUBLE_MAX  = 1.7976931348623158E+308;

    // ------------------------------------------------------------------
    // Desc: attributes of functions
    // ------------------------------------------------------------------

    // ========================================================
    // inline
    // ========================================================

    #ifdef INLINE
        #undef INLINE
    #endif
    #if EX_USE_FORCEINLINE
        #define INLINE  EX_FORCE_INLINE
    #else
        #define INLINE  inline        
    #endif

    // ========================================================
    // noinline
    // ========================================================

    #ifdef NOINLINE
        #undef NOINLINE
    #endif
    #define NOINLINE 

    // ========================================================
    // stdcall
    // ========================================================

    #ifdef STDCALL
        #undef STDCALL
    #endif
    #define STDCALL __attribute__ ((stdcall)) 

    // ========================================================
    // cdecl
    // ========================================================

    #ifdef CDECL
        #undef CDECL
    #endif
    #define CDECL __attribute__ ((cdecl)) 

    // ========================================================
    // deprecated
    // ========================================================

    #ifdef EX_DEPRECATED
        #undef EX_DEPRECATED
    #endif
    #define EX_DEPRECATED __attribute__ ((deprecated))

#endif // END EX_COMPILER

///////////////////////////////////////////////////////////////////////////////
// platform different types 
///////////////////////////////////////////////////////////////////////////////

#if ( EX_PLATFORM == EX_WIN32 ) 
    typedef __m128 vec_f32_t;
    // typedef uint32 uintptr_t;
#elif ( EX_PLATFORM == EX_LINUX )
    typedef __m128 vec_f32_t;
    typedef uint32 uintptr_t;
#elif ( EX_PLATFORM == EX_XENON )
    typedef __vector4 vec_f32_t; 
    typedef uint32 uintptr_t;
#elif ( EX_PLATFORM == EX_PS3 )
    typedef vec_float4 vec_f32_t;
    // typedef uintptr_t addr_t;
#endif

// ######################### 
} // end namespace ex 
// ######################### 


// #################################################################################
#endif // END TYPEDEFS_H_1281715105
// #################################################################################
