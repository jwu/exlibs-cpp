// ======================================================================================
// File         : debug.cpp
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 10:24:28 AM | Saturday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "debug.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

#define _SHORT_FUNCTION_NAME(_short_name,_func_name) \
    const int max_len = 64; \
    char _short_name[max_len]; \
    ex::mem::zero ( _short_name, sizeof(char)*max_len ); \
    int len = str::len(_func_name); \
    if ( len > max_len ) { \
        ex::mem::cpy ( _short_name, _func_name, sizeof(char)*(max_len-4) ); \
        _short_name[max_len-4] = '.'; \
        _short_name[max_len-3] = '.'; \
        _short_name[max_len-2] = '.'; \
        _short_name[max_len-1] = 0; \
    } \
    else { \
        str::ncpy( _short_name, len, _func_name, len ); \
    }

// #########################
namespace ex {
// #########################

///////////////////////////////////////////////////////////////////////////////
// defines 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

int message_box( int _msgType, const char* _caption, const char* _expr,  ... )
{
    //
    int     result = -1;
    int     buffer_count = 1024;
    char*   pBuffer = NULL;

    // keep get va string until success 
    while ( result == -1 ) {
        pBuffer = (char*)ex_realloc_nomng( pBuffer, buffer_count * sizeof(char), EX_GP(Allocator_dl283) );
        EX_GET_VA_STRING_WITH_RESULT( pBuffer, buffer_count, _expr, &result );
        buffer_count *= 2;
    }
    pBuffer[result] = 0;

#if (EX_PLATFORM == EX_WIN32) || (EX_PLATFORM == EX_XENON)
    uint type = MB_OK;
    if ( _msgType == MSG_BOX_FAILED )
        type = MB_ABORTRETRYIGNORE|MB_ICONWARNING; // TODO: should be "Skip, Break, Ignore"
    else if ( _msgType == MSG_BOX_ERROR )
        type = MB_ICONERROR;
    else if ( _msgType == MSG_BOX_WARNING )
        type = MB_ICONWARNING;

    int ret = ::MessageBox( NULL, pBuffer, _caption, type );
#endif

    // release buffer we allocate
    ex_free_nomng ( pBuffer, EX_GP(Allocator_dl283) );

    //
    return ret;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

bool assert_failed( bool* _pDoAssert, const char* _file_name, const char* _function_name, size_t _line_nr, const char* _expr, ... )
{
    //
    int     result = -1;
    int     buffer_count = 1024;
    char*   pBuffer = NULL;

    // keep get va string until success 
    while ( result == -1 ) {
        pBuffer = (char*)ex_realloc_nomng( pBuffer, buffer_count * sizeof(char), EX_GP(Allocator_dl283) );
        EX_GET_VA_STRING_WITH_RESULT( pBuffer, buffer_count, _expr, &result );
        buffer_count *= 2;
    }
    pBuffer[result] = 0;

    // short the function name
    _SHORT_FUNCTION_NAME(short_name,_function_name);

    //
    ex_log("Assert Failed: %s(%d)[%s], %s\n", _file_name, _line_nr, short_name, pBuffer );
    int mbResult = ex::message_box( MSG_BOX_FAILED, "Assert Failed", 
                                    "|ASSERT_FAILED|\n"
                                    "FileName: %s\n"
                                    "Line: %d\n"
                                    "FunctionName: %s\n" 
                                    "Expr: %s\n", 
                                    _file_name, _line_nr, short_name, pBuffer );

    // release buffer we allocate
    ex_free_nomng ( pBuffer, EX_GP(Allocator_dl283) );

    //
#if (EX_PLATFORM == EX_WIN32) || (EX_PLATFORM == EX_XENON)
    (*_pDoAssert) = (mbResult != IDIGNORE);
    return (mbResult == IDRETRY);
#else
    return true;
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool error_msg( bool* _pDoAssert, const char* _file_name, const char* _function_name, size_t _line_nr, const char* _expr, ... )
{
    //
    int     result = -1;
    int     buffer_count = 1024;
    char*   pBuffer = NULL;

    // keep get va string until success 
    while ( result == -1 ) {
        pBuffer = (char*)ex_realloc_nomng( pBuffer, buffer_count * sizeof(char), EX_GP(Allocator_dl283) );
        EX_GET_VA_STRING_WITH_RESULT( pBuffer, buffer_count, _expr, &result );
        buffer_count *= 2;
    }
    pBuffer[result] = 0;

    // short the function name
    _SHORT_FUNCTION_NAME(short_name,_function_name);

    //
    ex_log("Error: %s(%d)[%s], %s\n", _file_name, _line_nr, short_name, pBuffer );
    int mbResult = ex::message_box( MSG_BOX_FAILED, "Error", "Error: %s(%d)[%s], %s", _file_name, _line_nr, short_name, pBuffer );

    // release buffer we allocate
    ex_free_nomng ( pBuffer, EX_GP(Allocator_dl283) );

    //
#if (EX_PLATFORM == EX_WIN32) || (EX_PLATFORM == EX_XENON)
    (*_pDoAssert) = (mbResult != IDIGNORE);
    return (mbResult == IDRETRY);
#else
    return true;
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool warning_msg( bool* _pDoAssert, const char* _file_name, const char* _function_name, size_t _line_nr, const char* _expr, ... )
{
    //
    int     result = -1;
    int     buffer_count = 1024;
    char*   pBuffer = NULL;

    // keep get va string until success 
    while ( result == -1 ) {
        pBuffer = (char*)ex_realloc_nomng( pBuffer, buffer_count * sizeof(char), EX_GP(Allocator_dl283) );
        EX_GET_VA_STRING_WITH_RESULT( pBuffer, buffer_count, _expr, &result );
        buffer_count *= 2;
    }
    pBuffer[result] = 0;

    // short the function name
    _SHORT_FUNCTION_NAME(short_name,_function_name);

    //
    ex_log("Warning: %s(%d)[%s], %s\n", _file_name, _line_nr, _function_name, pBuffer );
    int mbResult = ex::message_box( MSG_BOX_FAILED, "Warning", "Warning: %s(%d)[%s], %s", _file_name, _line_nr, _function_name, pBuffer );

    // release buffer we allocate
    ex_free_nomng ( pBuffer, EX_GP(Allocator_dl283) );

    //
#if (EX_PLATFORM == EX_WIN32) || (EX_PLATFORM == EX_XENON)
    (*_pDoAssert) = (mbResult != IDIGNORE);
    return (mbResult == IDRETRY);
#else
    return true;
#endif
}

// #########################
} // end namespace ex
// #########################

#undef _SHORT_FUNCTION_NAME
