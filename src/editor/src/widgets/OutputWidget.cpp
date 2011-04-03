// ======================================================================================
// File         : OutputWidget.cpp
// Author       : Wu Jie 
// Last Change  : 03/17/2010 | 00:04:36 AM | Wednesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "OutputWidget.h"

using namespace ex;

///////////////////////////////////////////////////////////////////////////////
// static member 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void OutputWidget::LogMsg ( void* _pObject, const char* _str )
{
    static_cast<OutputWidget*>(_pObject)->LogMsg( QString::fromLocal8Bit(_str) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void OutputWidget::LogMsg ( void* _pObject, const ex::wchar* _str )
{
    static_cast<OutputWidget*>(_pObject)->LogMsg( QString::fromUtf16(_str) );
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

OutputWidget::OutputWidget ( QWidget* _pParent )
    : QWidget (_pParent)
{
    setupUi(this);

    //
    LogObjectCallback::pfn_char_t pfn = OutputWidget::LogMsg;
    EX_GP(Log)->hookMethod ( "qt_log_callback", new LogObjectCallback(this,pfn) );

    LogObjectCallback::pfn_wchar_t pfn_w = OutputWidget::LogMsg;
    EX_GP(Log)->hookMethod ( "qt_log_callbackw", new LogObjectCallback(this,pfn_w) );

    QTimer* tickTimer = new QTimer (this);
    connect ( tickTimer, SIGNAL(timeout()), this, SLOT(flush()) );
    tickTimer->start(500);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

OutputWidget::~OutputWidget ()
{
    EX_GP(Log)->unhookMethod ( "qt_log_callback" );
    EX_GP(Log)->unhookMethod ( "qt_log_callbackw" );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void OutputWidget::LogMsg ( QString _str )
{
    QMutexLocker locker(&m_mutex);
    m_pendingLogs.enqueue(_str);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void OutputWidget::flush ()
{
    QMutexLocker locker(&m_mutex);
    while ( !m_pendingLogs.isEmpty() ) {
        // move the cursor to the end of the document
        plainTextEdit->moveCursor ( QTextCursor::End );
        plainTextEdit->insertPlainText (m_pendingLogs.dequeue());
        plainTextEdit->centerCursor ();
        plainTextEdit->repaint ();
    }
}
