// ======================================================================================
// File         : EditorMain.h
// Author       : Wu Jie 
// Last Change  : 08/06/2010 | 10:02:44 AM | Friday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef EDITORMAIN_H_1250528046
#define EDITORMAIN_H_1250528046
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>
#include "ui_EditorMain.h"

#include "../misc/ExternalTool.h"

///////////////////////////////////////////////////////////////////////////////
// fwd-decls
///////////////////////////////////////////////////////////////////////////////

class View3D;

///////////////////////////////////////////////////////////////////////////////
// class EditorMain 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EditorMain : public QMainWindow, private Ui::EditorMain 
{
    Q_OBJECT
    EX_DECL_SINGLETON( EditorMain ); 

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    EditorMain ( QWidget* _pParent = NULL );
    ~EditorMain ();

    //
    bool init ();
    void deinit ();

    // this will open the native explorer to explore specifi directory
    void explore ( const QString& _path );
    void editText ( const QString& _file );
    void editImage ( const QString& _file );

    //
    void startTick ();
    void stopTick ();

    //
    void saveSettings ();
    void readSettings ();

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    // editor settings
    QByteArray saveEditor ();
    bool restoreEditor ( const QByteArray& _info );

    // events
    void closeEvent ( QCloseEvent* _event );

    ///////////////////////////////////////////////////////////////////////////////
    // slots
    ///////////////////////////////////////////////////////////////////////////////

protected slots:

    // file operations
    void onOpenActionData();
    void onCloseFile();
    void onSaveFile();

    // resource operations
    void onBrowseResource();
    void onCloseResource();

    //
    void tick ();
    void updateTitle();
    void updateMenu();

    // external tools
    void setupTextEditor();
    void setupImageEditor();

    //
    // TEST { 
    void rapidTest ();
    // } TEST end 

    ///////////////////////////////////////////////////////////////////////////////
    // protected members
    ///////////////////////////////////////////////////////////////////////////////

protected:

    // status bar widgets
    QLabel* m_labelFps;
    QTimer* m_tickTimer; 
    View3D* m_view3D;

    //
    typedef QHash<QString,ExternalTool> externals_t; 
    externals_t m_externals;

    // editor settings
    QString m_lastEditPath;

}; // end class EditorMain 

// #################################################################################
#endif // END EDITORMAIN_H_1250528046
// #################################################################################

