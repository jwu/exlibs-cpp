// ======================================================================================
// File         : Log.cpp
// Author       : Wu Jie 
// Last Change  : 01/31/2010 | 20:38:06 PM | Sunday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "Log.h"

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
    else \
    { \
        str::ncpy( _short_name, len, _func_name, len ); \
    }

// ######################### 
namespace ex { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log_HookGlobalCallbackA ( const char* _hookName, void* _pfn )
{
    EX_GP(Log)->hookMethod ( _hookName, new LogCallback((LogCallback::pfn_char_t)_pfn) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log_HookGlobalCallbackW ( const char* _hookName, void* _pfn )
{
    EX_GP(Log)->hookMethod ( _hookName, new LogCallback((LogCallback::pfn_wchar_t)_pfn) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log_UnHookGlobalCallback ( const char* _hookName )
{
    EX_GP(Log)->unhookMethod ( _hookName );
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Log::Log()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

Log::~Log()
{
    // NOTE: no-mng in Log 
    for ( method_list_t::iterator iter = m_methodList.begin(); iter != m_methodList.end(); ++iter )
    {
        delete (*iter);
    }
    m_methodList.clear();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log::hookMethod ( const char* _name, LogMethod* _pMethod )
{
    //
    bool bFound = false;
    for ( method_list_t::iterator iter = m_methodList.begin(); iter != m_methodList.end(); ++iter )
    {
        if ( ex::str::cmp ( (*iter)->name(), _name ) == 0 ) 
        {
            bFound = true;
            break;
        }
    }

    //
    if ( !bFound )
    {
        _pMethod->SetName(_name);
        m_methodList.push_back(_pMethod);
    }
    else
    {
        ex_warning ( "Hook Failed! method name %s already exists!", _name );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log::unhookMethod ( const char* _name )
{
    //
    bool bFound = false;
    method_list_t::iterator iter;
    for ( iter = m_methodList.begin(); iter != m_methodList.end(); ++iter )
    {
        if ( ex::str::cmp ( (*iter)->name(), _name ) == 0 ) 
        {
            bFound = true;
            break;
        }
    }

    //
    if ( bFound )
    {
        delete (*iter);
        m_methodList.erase(iter);
    }
    else
    {
        ex_warning ( "Un-Hook Failed! method name %s not found!", _name );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log::logMsg ( const string_t& _msg ) { logMsg (_msg.c_str()); }
void Log::logMsg ( const wstring_t& _msg ) { logMsg (_msg.c_str()); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log::logMsg ( const char* _format, ... )
{
    //
    int     result = -1;
    int     buffer_count = 1024;
    char*   pBuffer = NULL;

    // keep get va string until success 
    while ( result == -1 )
    {
        pBuffer = (char*)ex_realloc_nomng( pBuffer, (buffer_count + 2) * sizeof(char), EX_GP(Allocator_dl283) );
        EX_GET_VA_STRING_WITH_RESULT( pBuffer, buffer_count, _format, &result );
        buffer_count *= 2;
    }

    // DISABLE { 
    // // add endl if request
    // memcpy ( pBuffer + result, "\n", 2 );
    // pBuffer[result+2] = 0;
    // } DISABLE end 

    // now triger hooked log method
    for ( method_list_t::iterator iter = m_methodList.begin(); iter != m_methodList.end(); ++iter )
    {
        (*iter)->logMsg(pBuffer);
    }
    // // TODO: change to different log method
    // (*s_pfnLogCallback) (pBuffer);

    // release buffer we allocate
    ex_free_nomng ( pBuffer, EX_GP(Allocator_dl283) );

}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log::logMsg ( const wchar* _format, ... )
{
    // TODO:
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log::logWarning ( const char* _file_name, const char* _function_name, size_t _line, const string_t& _msg ) 
{ logWarning ( _file_name, _function_name, _line, _msg.c_str() ); }

void Log::logWarning ( const char* _file_name, const char* _function_name, size_t _line, const wstring_t& _msg ) 
{ logWarning ( _file_name, _function_name, _line, _msg.c_str() ); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log::logWarning ( const char* _file_name, const char* _function_name, size_t _line, const char* _format, ... )
{
    //
    int     result = -1;
    int     buffer_count = 1024;
    char*   pBuffer = NULL;

    // keep get va string until success 
    while ( result == -1 )
    {
        pBuffer = (char*)ex_realloc_nomng( pBuffer, (buffer_count + 2) * sizeof(char), EX_GP(Allocator_dl283) );
        EX_GET_VA_STRING_WITH_RESULT( pBuffer, buffer_count, _format, &result );
        buffer_count *= 2;
    }

    // add endl if request
    pBuffer[result] = 0;

    // short the function name
    _SHORT_FUNCTION_NAME(short_name,_function_name);

    //
    logMsg ( "Warning: %s(%d)[%s]: %s\n", _file_name, _line, short_name, pBuffer );

    // release buffer we allocate
    ex_free_nomng ( pBuffer, EX_GP(Allocator_dl283) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log::logWarning ( const char* _file_name, const char* _function_name, size_t _line, const wchar* _format, ... )
{
    // TODO:
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log::logError ( const char* _file_name, const char* _function_name, size_t _line, const string_t& _msg )
{ logError ( _file_name, _function_name, _line, _msg.c_str() ); }

void Log::logError ( const char* _file_name, const char* _function_name, size_t _line, const wstring_t& _msg )
{ logError ( _file_name, _function_name, _line, _msg.c_str() ); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log::logError ( const char* _file_name, const char* _function_name, size_t _line, const char* _format, ... )
{
    //
    int     result = -1;
    int     buffer_count = 1024;
    char*   pBuffer = NULL;

    // keep get va string until success 
    while ( result == -1 )
    {
        pBuffer = (char*)ex_realloc_nomng( pBuffer, (buffer_count + 2) * sizeof(char), EX_GP(Allocator_dl283) );
        EX_GET_VA_STRING_WITH_RESULT( pBuffer, buffer_count, _format, &result );
        buffer_count *= 2;
    }

    // add endl if request
    pBuffer[result] = 0;

    // short the function name
    _SHORT_FUNCTION_NAME(short_name,_function_name);

    //
    logMsg ( "Error: %s(%d)[%s]: %s\n", _file_name, _line, short_name, pBuffer );
    ex::message_box( MSG_BOX_ERROR, "Error!", "Error: %s(%d)[%s]: %s", _file_name, _line, short_name, pBuffer );

    // release buffer we allocate
    ex_free_nomng ( pBuffer, EX_GP(Allocator_dl283) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Log::logError ( const char* _file_name, const char* _function_name, size_t _line, const wchar* _format, ... )
{
    // TODO:
}


// ######################### 
} // end namespace ex 
// ######################### 

