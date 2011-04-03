// ======================================================================================
// File         : IO.cpp
// Author       : Wu Jie 
// Last Change  : 10/19/2008 | 21:57:22 PM | Sunday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"

// #########################
namespace ex {
// #########################

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: printf
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

int printf( const char* _format, ... )
{
    va_list args;
    va_start( args, _format );
    int result = vfprintf( stdout, _format, args );
    va_end( args );
    return result;
}

// ========================================================
// wchar ver
// ========================================================

int printf( const wchar* _format, ... )
{
    va_list args;
    va_start( args, _format );
    int result = vfwprintf( stdout, (const wchar_t*)_format, args );
    va_end( args );
    return result;
}

// ------------------------------------------------------------------
// Desc: fprintf
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

int fprintf( FILE* _stream, const char* _format, ... )
{
    va_list args;
    va_start( args, _format );
    int result = vfprintf( _stream, _format, args );
    va_end( args );
    return result;
}

// ========================================================
// wchar ver
// ========================================================

int fprintf( FILE* _stream, const wchar* _format, ... )
{
    va_list args;
    va_start( args, _format );
    int result = vfwprintf( _stream, (const wchar_t*)_format, args );
    va_end( args );
    return result;
}

// ------------------------------------------------------------------
// Desc: snprintf
// ------------------------------------------------------------------

// ========================================================
// char ver
// ========================================================

int snprintf( char* _buffer, uint _count, const char* _format, ... )
{
    va_list args;
    va_start( args, _format );
    int result = ex::vsnprintf( _buffer, _count, _format, args );
    va_end( args );
    return result;
}

// ========================================================
// wchar ver
// ========================================================

int snprintf( wchar* _buffer, uint _count, const wchar* _format, ... )
{
    va_list args;
    va_start( args, _format );
    int result = ex::vsnprintf( _buffer, _count, _format, args );
    va_end( args );
    return result;
}

// ------------------------------------------------------------------
// Desc: stat() can't handle a trailing '/' or '\', remove it first.
// ------------------------------------------------------------------

int stat ( const char* _name, struct stat* _stp )
{
    char buf[ex::MaxPath + 1];
    char *p;

    ex::str::ncpy( buf, ex::MaxPath, _name, ex::MaxPath );
    p = buf + ex::str::len(buf);
    if ( p > buf )
        --p;
    if ( p > buf && (*p == '\\' || *p == '/') && p[-1] != ':' )
        *p = EX_NUL;

    // XXX:
#if 0
#ifdef FEAT_MBYTE
    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage
# ifdef __BORLANDC__
        /* Wide functions of Borland C 5.5 do not work on Windows 98. */
        && g_PlatformId == VER_PLATFORM_WIN32_NT
# endif
       )
    {
        WCHAR	*wp = enc_to_ucs2(buf, NULL);
        int	n;

        if (wp != NULL)
        {
            n = _wstat(wp, (struct _stat *)_stp);
            vim_free(wp);
            if (n >= 0)
                return n;
            /* Retry with non-wide function (for Windows 98). Can't use
             * GetLastError() here and it's unclear what errno gets set to if
             * the _wstat() fails for missing wide functions. */
        }
    }
#endif
#endif

    return ::stat(buf, _stp);
}

int stat ( const wchar* _name, struct _stat* _stp )
{
    wchar buf[ex::MaxPath + 1];
    wchar *p;

    ex::str::ncpy( buf, ex::MaxPath, _name, ex::MaxPath );
    p = buf + ex::str::len(buf);
    if ( p > buf )
        --p;
    if ( p > buf && (*p == L'\\' || *p == L'/') && p[-1] != L':' )
        *p = EX_NUL;

    return ::_wstat( (const wchar_t*)buf, _stp);
}

// ------------------------------------------------------------------
// Desc: logf
// ------------------------------------------------------------------

// ========================================================
// char log
// ========================================================

void logf( const char* _file_name, const char* _format, ... )
{
    // The Buffer
    char buffer[2048];
    EX_GET_VA_STRING( buffer, 2048, _format );

    // open the log file
    FILE* fp = ex::fopen( _file_name, "ab" );

    // The file must be opened
    ex_assert( fp, "Can't not open the log file:%s", _file_name );

    // print the log into the file
    ex::fprintf( fp, "%s", buffer );

    // close the file
    ex::fclose(fp);
}

#if EX_UNICODE_PLATFORM
// ========================================================
// wchar log
// ========================================================

void logf( const wchar* _file_name, const wchar* _format, ... )
{
    // The Buffer
    wchar buffer[2048];
    EX_GET_VA_STRING( buffer, 2048, _format );

    // Open the log file
    FILE* fp = ex::fopen( _file_name, W("ab") );

    // The file must be opened
    char* utf8 = (char*)ex_stack_malloc( ex::str::len(_file_name) * sizeof(wchar) );
    utf16_to_utf8( _file_name, utf8 );
    ex_assert( fp, "Can't not open the log file:%s", utf8 );

    // print the log into the file
    ex::fprintf( fp, W("%s"), buffer );

    // close the file
    ex::fclose(fp);
}
#endif // END EX_UNICODE_PLATFORM 

// #########################
} // end namespace ex
// #########################

