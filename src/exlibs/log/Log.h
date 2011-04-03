// ======================================================================================
// File         : Log.h
// Author       : Wu Jie 
// Last Change  : 01/31/2010 | 20:32:54 PM | Sunday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef LOG_H_1264941179
#define LOG_H_1264941179
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "LogMethod.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern "C" EX_LIBS_DLL void Log_HookGlobalCallbackA ( const char* _hookName, void* _pfn );
extern "C" EX_LIBS_DLL void Log_HookGlobalCallbackW ( const char* _hookName, void* _pfn );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern "C" EX_LIBS_DLL void Log_UnHookGlobalCallback ( const char* _hookName );

///////////////////////////////////////////////////////////////////////////////
// class Log 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Log
{
    ///////////////////////////////////////////////////////////////////////////////
    // singleton decl
    ///////////////////////////////////////////////////////////////////////////////

    EX_DECL_SINGLETON ( Log );

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

    typedef List<LogMethod*,NoManaged<NullType>::TAllocator> method_list_t;
    // KEEPME: friend EX_LIBS_DLL void SetupLogCallBack ( void* _pfn );

    ///////////////////////////////////////////////////////////////////////////////
    // public member funcionts
    ///////////////////////////////////////////////////////////////////////////////

public:

    Log ();
    ~Log ();

    // NOTE: only new can be used to create LogMethod!
    void hookMethod ( const char* _name, LogMethod* _pMethod );
    void unhookMethod ( const char* _name );

    //
    void logMsg ( const string_t& _msg );
    void logMsg ( const wstring_t& _msg );
    void logMsg ( const char* _format, ... );
    void logMsg ( const wchar* _format, ... );

    //
    void logWarning ( const char* _file_name, const char* _function_name, size_t _line, const string_t& _msg );
    void logWarning ( const char* _file_name, const char* _function_name, size_t _line, const wstring_t& _msg );
    void logWarning ( const char* _file_name, const char* _function_name, size_t _line, const char* _format, ... );
    void logWarning ( const char* _file_name, const char* _function_name, size_t _line, const wchar* _format, ... );

    //
    void logError ( const char* _file_name, const char* _function_name, size_t _line, const string_t& _msg );
    void logError ( const char* _file_name, const char* _function_name, size_t _line, const wstring_t& _msg );
    void logError ( const char* _file_name, const char* _function_name, size_t _line, const char* _format, ... );
    void logError ( const char* _file_name, const char* _function_name, size_t _line, const wchar* _format, ... );

protected:

    method_list_t m_methodList;

}; // end class Log

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END LOG_H_1264941179
// #################################################################################


