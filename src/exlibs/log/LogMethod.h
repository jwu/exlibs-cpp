// ======================================================================================
// File         : LogMethod.h
// Author       : Wu Jie 
// Last Change  : 02/01/2010 | 00:45:50 AM | Monday,February
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef LOGMETHOD_H_1264956357
#define LOGMETHOD_H_1264956357
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class LogMethod 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL LogMethod
{
    friend class Log;
    static const uint32 MAX_LEN = 128;

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    LogMethod () { ex::mem::zero( m_name, MAX_LEN ); }
    virtual ~LogMethod () {}

    virtual void logMsg ( const char* _msg ) = 0;
    virtual void logMsg ( const wchar* _msg ) = 0;

    INLINE const char* name() const { return m_name; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member
    ///////////////////////////////////////////////////////////////////////////////

    // NOTE: only set by Log when Hook.
    void SetName ( const char* _name );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member
    ///////////////////////////////////////////////////////////////////////////////

protected:

    char m_name[MAX_LEN];

}; // end class LogMethod

///////////////////////////////////////////////////////////////////////////////
// class LogPrintf 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL LogPrintf : public LogMethod
{
    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    LogPrintf () {}
    virtual ~LogPrintf () {}

    virtual void logMsg( const char* _msg );
    virtual void logMsg( const wchar* _msg );

}; // end class LogPrintf

///////////////////////////////////////////////////////////////////////////////
// class LogFile 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL LogFile : public LogMethod
{
    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    LogFile ( const char* _fileName );
    virtual ~LogFile ();

    virtual void logMsg( const char* _msg );
    virtual void logMsg( const wchar* _msg );

protected:

    FILE* m_pFile;

}; // end class LogFile

///////////////////////////////////////////////////////////////////////////////
// class LogCallback 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL LogCallback : public LogMethod
{
public:

    typedef void (*pfn_char_t)( const char* );
    typedef void (*pfn_wchar_t)( const wchar* );

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    LogCallback ( pfn_char_t _pfn );
    LogCallback ( pfn_wchar_t _pfn );
    virtual ~LogCallback ();

    virtual void logMsg( const char* _msg );
    virtual void logMsg( const wchar* _msg );

protected:

    pfn_char_t   m_pfnChar;
    pfn_wchar_t  m_pfnWChar;

}; // end class LogCallback

///////////////////////////////////////////////////////////////////////////////
// class LogObjectCallback 
// 
// Purpose: 
//  the object-callback log-method is support for cpp-gui, which hook the callback
//  with a class.
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL LogObjectCallback : public LogMethod
{
public:

    typedef void (*pfn_char_t)( void*, const char* );
    typedef void (*pfn_wchar_t)( void*, const wchar* );

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    LogObjectCallback ( void* _pObj, pfn_char_t _pfn );
    LogObjectCallback ( void* _pObj, pfn_wchar_t _pfn );
    virtual ~LogObjectCallback ();

    virtual void logMsg( const char* _msg );
    virtual void logMsg( const wchar* _msg );

protected:

    void*        m_pObject;
    pfn_char_t   m_pfnChar;
    pfn_wchar_t  m_pfnWChar;

}; // end class LogObjectCallback

// ######################### 
} // end namespace ex 
// ######################### 


// #################################################################################
#endif // END LOGMETHOD_H_1264956357
// #################################################################################


