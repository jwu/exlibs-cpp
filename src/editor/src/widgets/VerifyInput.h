// ======================================================================================
// File         : VerifyInput.h
// Author       : Wu Jie 
// Last Change  : 04/09/2010 | 18:17:51 PM | Friday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef VERIFYINPUT_H_1270808274
#define VERIFYINPUT_H_1270808274
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "ui_VerifyInput.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class VerifyInput.h 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class VerifyInput : public QWidget, private Ui::VerifyInput
{
    Q_OBJECT

    ///////////////////////////////////////////////////////////////////////////////
    // public mebmer functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    VerifyInput ( QWidget* _pParent = NULL );
    ~VerifyInput ();

    const QString& text() const { return m_text; }
    bool isValid () const { return m_isValid; }

    void setInputLabelText ( const QString& _text ) { inputLabel->setText(_text); }
    void setHintText ( const QString& _hintText ) { lineEdit->setHintText(_hintText); }
    void setText ( const QString& _text ) { lineEdit->setTypedText(_text); }
    void reset () { lineEdit->reset(); }

    void setInvalidInputs ( const QStringList& _invalidInputs ) { m_invalidInputs = _invalidInputs; }
    void setCurrentPath ( const QString& _dirName ) { m_currentPath = _dirName; }
    void setExtFilters ( const QStringList& _exts ) { m_extFilters = _exts; }
    void setConflictCheck ( bool _enable ) { m_checkConflict = _enable; }
    void setExistsCheck ( bool _enable ) { m_checkExists = _enable; }

    void setFocus() { lineEdit->setFocus(); }
    void installEventFilterForLineEdit ( QWidget* _pWidget );

    ///////////////////////////////////////////////////////////////////////////////
    // protected slots
    ///////////////////////////////////////////////////////////////////////////////

protected slots:

    void inputChanged ( const QString& _text );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    void updateStatus(); 
    bool checkInvalid ( const QString& _text ) const;
    bool checkConflict ( const QString& _text ) const;
    bool checkExists ( const QString& _text ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    QStringList m_invalidInputs;
    QStringList m_extFilters;
    bool m_checkConflict;
    bool m_checkExists;

    QString m_currentPath;
    QString m_text;
    bool m_isValid;

}; // end class VerifyInput

// #################################################################################
#endif // END VERIFYINPUT_H_1270808274
// #################################################################################
