// ======================================================================================
// File         : ExternalTool.h
// Author       : Wu Jie 
// Last Change  : 04/22/2010 | 09:05:25 AM | Thursday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef EXTERNALTOOL_H_1271898328
#define EXTERNALTOOL_H_1271898328
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class ExternalTool 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class ExternalTool
{
    friend QDataStream &operator<<(QDataStream &, const ExternalTool &);
    friend QDataStream &operator>>(QDataStream &, ExternalTool &);

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    ExternalTool ();
    ExternalTool ( const QString& _fullPath, const QString& _args );
    ExternalTool ( const ExternalTool& _cpy );
    ~ExternalTool ();

    //
    void setFullPath ( const QString& _fullPath ) { m_fullPath = _fullPath; }
    const QString& fullPath () const { return m_fullPath; }

    //
    void setArgs ( const QString& _args ) { m_args = _args; }
    const QString& args () const { return m_args; }

    //
    bool exec ( const QString& _fileName );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    QString m_fullPath;
    QString m_args;

}; // end class ExternalTool

QDataStream &operator<<(QDataStream &, const ExternalTool &);
QDataStream &operator>>(QDataStream &, ExternalTool &);

// #################################################################################
#endif // END EXTERNALTOOL_H_1271898328
// #################################################################################


