// ======================================================================================
// File         : ExternalTool.cpp
// Author       : Wu Jie 
// Last Change  : 04/22/2010 | 09:09:43 AM | Thursday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "ExternalTool.h"

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

QDataStream& operator << ( QDataStream& _out, const ExternalTool& _externalTool )
{
    return _out << _externalTool.m_fullPath
                << _externalTool.m_args;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

QDataStream &operator >> ( QDataStream& _in, ExternalTool& _externalTool)
{
    _in >> _externalTool.m_fullPath
        >> _externalTool.m_args;
    return _in;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ExternalTool::ExternalTool ()
    : m_fullPath ("")
    , m_args ("$1")
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ExternalTool::ExternalTool ( const QString& _fullPath, const QString& _args )
    : m_fullPath(_fullPath)
    , m_args(_args)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ExternalTool::ExternalTool ( const ExternalTool& _cpy )
    : m_fullPath(_cpy.m_fullPath)
    , m_args(_cpy.m_args)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ExternalTool::~ExternalTool ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ExternalTool::exec ( const QString& _fileName )
{
    QFileInfo fileInfo(m_fullPath);

    if ( fileInfo.exists() )
    {
        //
        QProcess* pProcess = new QProcess();

        //
        QString argString = m_args;
        int i = argString.indexOf("$1");
        if ( i != -1 ) {
            argString.replace( i, 2, _fileName );
        }

        //
        QStringList args; 
        args << argString;

        //
        pProcess->start( m_fullPath, args );
        ex_log ( "edit %s\n", qPrintable(_fileName) );
        return true;
    }
    return false;
}
