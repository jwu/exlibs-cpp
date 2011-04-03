// ======================================================================================
// File         : VerifyInput.cpp
// Author       : Wu Jie 
// Last Change  : 04/09/2010 | 18:19:04 PM | Friday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "VerifyInput.h"

#include "EditorMain.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

VerifyInput::VerifyInput ( QWidget* _pParent )
    : QWidget (_pParent)
    , m_checkConflict (false)
    , m_checkExists (false)
    , m_isValid (false)
{
    setupUi(this);

    lineEdit->setHintText(tr("<enter a new name>"));
    connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(inputChanged(const QString&)));

    this->updateStatus();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

VerifyInput::~VerifyInput ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void VerifyInput::inputChanged ( const QString& _text )
{
    Q_UNUSED(_text);
    m_text = lineEdit->typedText();
    this->updateStatus ();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void VerifyInput::installEventFilterForLineEdit ( QWidget* _pWidget )
{
    lineEdit->installEventFilter (_pWidget);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void VerifyInput::updateStatus() 
{
    if ( m_text.isEmpty() ) {
        status->setText("<font color=#ff00ff>waiting for input...</font>");
        m_isValid = false;
    }
    else if ( this->checkInvalid(m_text) ) 
    {
        QString invalid_text;
        foreach ( QString invalid_input, m_invalidInputs ) {
            invalid_text = invalid_text + "\"" + invalid_input + "\", ";
        }
        QString reason = "the input can't include characters: " + invalid_text;
        status->setText ( "<font color=#ff0000>invalid: " + reason + "</font>" );
        m_isValid = false;
    }
    else if ( this->checkConflict(m_text) )
    {
        QString reason = "the input already exists";
        status->setText ( "<font color=#ff0000>conflict: " + reason + "</font>" );
        m_isValid = false;
    }
    else if ( this->checkExists(m_text) == false )
    {
        QString reason = "can't find the input";
        status->setText ( "<font color=#ff0000>file not exists: " + reason + "</font>" );
        m_isValid = false;
    }
    else
    {
        status->setText ( "<font color=#215E21>ok</font>" );
        m_isValid = true;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool VerifyInput::checkInvalid ( const QString& _text ) const
{
    foreach ( QString invalid_input, m_invalidInputs )
    {
        if ( _text.contains(invalid_input) )
        {
            return true;
        }
    }
    return false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool VerifyInput::checkConflict ( const QString& _text ) const
{
    if ( m_checkConflict == false )
        return false;

    if ( m_extFilters.isEmpty() )
    {
        QFileInfo fileInfo(m_currentPath + "/" + _text);
        if ( fileInfo.exists() )
            return true;
    }
    else
    {
        foreach ( QString ext, m_extFilters )
        {
            QFileInfo fileInfo(m_currentPath + "/" + _text + "." + ext );
            if ( fileInfo.exists() )
                return true;
        }
    }

    return false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool VerifyInput::checkExists ( const QString& _text ) const
{
    if ( m_checkExists == false )
        return true;

    QString fullPath = m_currentPath == "" ? _text : m_currentPath + "/" + _text; 
    QFileInfo fileInfo(fullPath);
    if ( fileInfo.exists() )
        return true;
    return false;
}
