// ======================================================================================
// File         : encoding.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 09:01:04 AM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ENCODING_H_1281834066
#define ENCODING_H_1281834066
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < uint SIZE >
void char_to_wchar ( const char* _src, wchar (&_dest)[SIZE] ) {
    size_t len = ex::str::len(_src)+1; 
    ex_assert_return ( len < SIZE, , "the dest size is smaller than the src" );
    for ( uint i = 0; i < len; ++i )
        _dest[i] = _src[i];
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < uint SIZE >
void wchar_to_char ( const wchar* _src, char (&_dest)[SIZE] ) {
    size_t len = ex::str::len(_src)+1; 
    ex_assert_return ( len < SIZE, , "the dest size is smaller than the src" );
    for ( uint i = 0; i < len; ++i ) {
#if ( EX_ENDIAN == EX_BIG_ENDIAN )
        _dest[i] = _src[i] & 0xFF00;
#else // else if EX_LITTLE_ENDIAN
        _dest[i] = (_src[i] & 0x00FF);
#endif 
    }
}

//
EX_LIBS_DLL void local8bit_to_utf8 ( const char*, char* );
EX_LIBS_DLL void local8bit_to_utf16 ( const char*, wchar* );
EX_LIBS_DLL void utf8_to_utf16 ( const char*, wchar* );
EX_LIBS_DLL void utf16_to_utf8 ( const wchar*, char* );

// ######################### 
} // end namespace ex 
// ######################### 


// #################################################################################
#endif // END ENCODING_H_1281834066
// #################################################################################
