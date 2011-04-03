// ======================================================================================
// File         : macros.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 14:15:04 PM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MACROS_H_1281718110
#define MACROS_H_1281718110
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// bit-op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: get bit number of a _value
// ------------------------------------------------------------------

#define EX_BIT_COUNT( _value ) sizeof(_value)*8

// ------------------------------------------------------------------
// Desc: rotate bit at _pos
// ------------------------------------------------------------------

#define EX_BIT_ROT( _val, _pos ) (((_val)<<(_pos)) | ((_val)>>(32-(_pos))))

///////////////////////////////////////////////////////////////////////////////
// ptr-op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

#define EX_ADD_PTR( _pType, _ptr, _offset ) ( (_pType) ((size_t)(_ptr) + (size_t)(_offset)) )

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

#define EX_SUB_PTR( _pType, _ptr, _offset ) ( (_pType) ((size_t)(_ptr) - (size_t)(_offset)) )

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

#define EX_DIFF_PTR( _pFirst, _pSecond ) ( (size_t) ((size_t)(_pFirst) - (size_t)(_pSecond)) )

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

#define EX_PTR_TO_ADDR( _ptr ) ( (uintptr_t) ((size_t)(_ptr)) )

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

#define EX_ADDR_TO_PTR( _addr ) ( (void*) ((size_t)(_addr)) )

///////////////////////////////////////////////////////////////////////////////
// c extend
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: EX_TRY, EX_CATCH 
// ------------------------------------------------------------------ 

#if EX_USE_EXCEPTIONS
    #define ex_try try
    #define ex_catch(_exp) catch(_exp)
    #define ex_catch_exp(_exp) catch(_exp)
    #define ex_throw throw
#else
    #define ex_try 
    #define ex_catch(_exp) if(0)
    #define ex_catch_exp(_exp) if( 0 && (_exp) )
    #define ex_throw return
#endif

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define EX_UNUSED(_param) (void)_param

// ------------------------------------------------------------------
// Desc: get va string
// ------------------------------------------------------------------

#define EX_GET_VA_STRING( _buffer, _count, _fmt )                                                           \
    {                                                                                                       \
        va_list args;                                                                                       \
        va_start( args, _fmt );                                                                             \
        ::ex::vsnprintf( _buffer, _count, _fmt, args );                                                     \
        va_end(args);                                                                                       \
        ex_assert_slow( ::ex::str::len(_buffer) <= _count, "extended string have over flow the buffer" );     \
    }

// ------------------------------------------------------------------
// Desc: get va string with result
// ------------------------------------------------------------------

#define EX_GET_VA_STRING_WITH_RESULT( _buffer, _count, _fmt, result )                                       \
    {                                                                                                       \
        va_list args;                                                                                       \
        va_start( args, _fmt );                                                                             \
        *result = ::ex::vsnprintf( _buffer, _count, _fmt, args );                                           \
        va_end(args);                                                                                       \
    }

// ------------------------------------------------------------------
// Desc: Floor Align
// Example: val = 19, align = 8. EX_ALIGN_FLOOR(19,8) = 16
// ------------------------------------------------------------------

#define EX_ALIGN_FLOOR(val, align)      ((val) & ~(align-1))

// ------------------------------------------------------------------
// Desc: Round Align
// Example: val = 19, align = 8. EX_ALIGN_ROUND(12,8) = 24
// ------------------------------------------------------------------

#define EX_ALIGN_ROUND(val, align)      (((val) + (align-1)) & ~(align-1))

// ------------------------------------------------------------------
// Desc: Get the array element count
//  The const value calculate should be optimaized by compiler, so this macro do not take any calculation in
//  runtime, all the result will be calculated in the pre-process.
// ------------------------------------------------------------------

#define EX_ARRAY_COUNT(arr)  (sizeof(arr)/sizeof(arr[0]))

// ------------------------------------------------------------------
// Desc: Memory Allocate Size for sizeof(uint8) = 1BYTE
// ------------------------------------------------------------------

#define EX_KB(nb)   ((unsigned)(nb)*1024)   // KiloBytes = 2^10
#define EX_MB(nb)   EX_KB((nb)*1024)        // MegaBytes = 2^20
#define EX_GB(nb)   EX_MB((nb)*1024)        // GegaBytes = 2^30

///////////////////////////////////////////////////////////////////////////////
// engine extend
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Get Singleton instance/point
// ------------------------------------------------------------------

#define EX_G(class_name)  (class_name::instance())
#define EX_GP(class_name) (&class_name::instance())

///////////////////////////////////////////////////////////////////////////////
// platform extend
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: close handle with safe check. only for win32
// ------------------------------------------------------------------

#define EX_SAFE_CLOSE_HANDLE( handle ) { if ( handle ) { CloseHandle( (HANDLE)handle ); handle = NULL; } }

// ------------------------------------------------------------------
// Desc: EX_CHECK_PS3
// ------------------------------------------------------------------

#define EX_CHECK_PS3( err_no ) { ex_assert( err_no == CELL_OK, "Invalid PS3 API call: Error_Number = %#.8lX" ); }

///////////////////////////////////////////////////////////////////////////////
// macro extend
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Endian detect
//  first we define the usually platform endian known by experience
//  Then we define the endian by detail after "Base_GExternal.h"
//  endian define by detail
// ------------------------------------------------------------------

#if ( defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN ) || \
    ( defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(vax) || defined(MIPSEL) )
    // Big-endian machine
    #ifdef EX_ENDIAN
        #undef EX_ENDIAN
    #endif
    #define EX_ENDIAN EX_LITTLE_ENDIAN
#elif ( defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN ) || \
      ( defined(sparc) || defined(POWERPC) || defined(mc68000) || defined(sel) )
    // Little-endian machine
    #ifdef EX_ENDIAN
        #undef EX_ENDIAN
    #endif
    #define EX_ENDIAN EX_BIG_ENDIAN
#endif

// ------------------------------------------------------------------
// Desc: Expand Macro
//  Expand the macro for second scaned pre-process. 
//  Refer to Gcc-4.1.1\Manual\Cpp\Predefined-Macros.htm
// ------------------------------------------------------------------

#define EX_MACRO_EXPAND( macro_name, ... ) macro_name( __VA_ARGS__ )
#define EX_MACRO_EXPAND_SIMPLE( macro_name ) macro_name

// ------------------------------------------------------------------
// Desc: Macro String
// ------------------------------------------------------------------

#define EX_STRING(str) #str 
#define EX_STRING_EXPAND(str) EX_STRING(str)

// ------------------------------------------------------------------
// Desc:    cross Platform File Name Genreator
//          This macro is used in include the mulit-platform head file.
// Example: EX_PLATFORM_FILE( STDLIB, h ) will include STDLIB_Linux.h in linux or
//          include STDLIB_Win32.h in Windows. Depend on your EX_PLATFORM_NAME's value.
// ------------------------------------------------------------------


// ========================================================
// EX_CROSS_PLATFORM_FILE_NAME
// ========================================================

#define EX_CROSS_PLATFORM_FILE_NAME(base_name,platform_name,file_type) base_name##_##platform_name.file_type

// ========================================================
// EX_PLATFORM_FILE
// ========================================================

#if ( EX_COMPILER == EX_GCC )
    #define EX_PLATFORM_FILE( base_name, file_type ) EX_MACRO_EXPAND( EX_STRING, \
                                                                      EX_MACRO_EXPAND( EX_CROSS_PLATFORM_FILE_NAME, \
                                                                                       base_name, EX_PLATFORM_NAME, file_type ) )
#elif ( EX_COMPILER == EX_MSVC ) // MSVC can't not expand like beautiful gcc.
    #define EX_CROSS_PLATFORM_FILE_NAME_EXPAND( base_name, platform_name, file_type ) EX_CROSS_PLATFORM_FILE_NAME( base_name, platform_name, file_type )
    #define EX_PLATFORM_FILE( base_name, file_type ) EX_STRING_EXPAND( EX_CROSS_PLATFORM_FILE_NAME_EXPAND( base_name, EX_PLATFORM_NAME, file_type ) )
#endif

///////////////////////////////////////////////////////////////////////////////
//  Define: Misc
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: TODO: this is temp solution
// ------------------------------------------------------------------

#define EX_MEMORY_LOG_FILE_NAME "./memlog.txt"
#define EX_MEMORY_LEAK_FILE_NAME "./memleak.err"

// #################################################################################
#endif // END MACROS_H_1281718110
// #################################################################################
