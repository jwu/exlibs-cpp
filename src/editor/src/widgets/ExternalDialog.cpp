// ======================================================================================
// File         : ExternalDialog.cpp
// Author       : Wu Jie 
// Last Change  : 04/22/2010 | 09:55:03 AM | Thursday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "ExternalDialog.h"
#include "../misc/ExternalTool.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ExternalDialog::ExternalDialog ( const ExternalTool& _extTool, QWidget* _pParent )
    : QDialog (_pParent)
    , m_currentFocus (NULL)
{
    this->setupUi(this);
    // this->setWindowFlags(Qt::Popup);

    // path
    pathLine->setInputLabelText ("full path: ");
    pathLine->installEventFilterForLineEdit(this); // capture lineEdit's event to pre-process ESC key.
    pathLine->setExistsCheck(true);
    if ( _extTool.fullPath() != "" ) {
        pathLine->setText(_extTool.fullPath());
    }
    else {
        pathLine->setHintText(tr("<enter the path of the external tool>"));
    }

    // args
    argsLine->setInputLabelText ("args ($1 represent the first file): ");
    argsLine->installEventFilterForLineEdit(this); // capture lineEdit's event to pre-process ESC key.
    if ( _extTool.args() != "" ) {
        argsLine->setText(_extTool.args());
    }
    else {
        argsLine->setText("$1");
    }

    //
    this->setFocus();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ExternalDialog::~ExternalDialog ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ExternalDialog::eventFilter( QObject* object, QEvent* event ) 
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        if ( ke->key() == Qt::Key_Escape ||
             ke->key() == Qt::Key_Return ) 
        {
            HintLineEdit* pCurObj = qobject_cast<HintLineEdit*>(object);
            if ( pCurObj )
                m_currentFocus = (VerifyInput*)(pCurObj->parent());
            else
                m_currentFocus = NULL;

            keyPressEvent (ke);
            return true;
        }
    }
    return QDialog::eventFilter(object, event);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ExternalDialog::keyPressEvent ( QKeyEvent * _pEvent )
{
    switch ( _pEvent->key() )
    {
    case Qt::Key_Escape:
        {
            if ( m_currentFocus ) {
                if ( m_currentFocus->text().isEmpty() ) {
                    this->reject();
                }
                else {
                    m_currentFocus->reset();
                }
            }
            else {
                this->reject();
            }
        }
        break;

    case Qt::Key_Return:
        {
            if ( pathLine->isValid() && argsLine->isValid() ) {
                this->accept();
            }
        }
        break;
    }
}
