// ======================================================================================
// File         : HintLineEdit.h
// Author       : Wu Jie 
// Last Change  : 03/31/2010 | 16:53:24 PM | Wednesday,March
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef HINTLINEEDIT_H_1270025628
#define HINTLINEEDIT_H_1270025628
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// class HintLineEdit 
// 
// Purpose: 
//  A line edit that displays a grayed hintText (like "Type Here to Filter")
//  when not focussed and empty. When connecting to the changed signals and
//  querying text, one has to be aware that the text is set to that hint
//  text if isShowingHintText() returns true (that is, does not contain
//  valid user input). This widget should never have initial focus
//  (ie, be the first widget of a dialog, else, the hint cannot be displayed.
//  For situations, where it is the only focusable control (widget box),
//  there is a special "refuseFocus()" mode, in which it clears the focus
//  policy and focusses explicitly on click (note that setting Qt::ClickFocus
//  is not sufficient for that as an ActivationFocus will occur).
// 
///////////////////////////////////////////////////////////////////////////////

class HintLineEdit : public QLineEdit 
{
    Q_OBJECT

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    explicit HintLineEdit ( QWidget* _pParent = NULL );
    void reset();

    QString hintText() const;
    bool isShowingHintText() const;

    // Convenience for accessing the text that returns "" in case of isShowingHintText().
    QString typedText() const;

    bool refuseFocus() const;
    void setRefuseFocus(bool v);

    ///////////////////////////////////////////////////////////////////////////////
    // public slots
    ///////////////////////////////////////////////////////////////////////////////

public slots:

    void setTypedText( const QString & );
    void setHintText(const QString &);
    void showHintText(bool force = false);
    void hideHintText();

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    bool event( QEvent * );

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void focusInEvent(QFocusEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);
    virtual void keyPressEvent ( QKeyEvent * );

    void setTextColor(const QColor &newColor, QColor *oldColor = 0);

    ///////////////////////////////////////////////////////////////////////////////
    // private member data
    ///////////////////////////////////////////////////////////////////////////////

private:

    const Qt::FocusPolicy m_defaultFocusPolicy;
    const QColor m_hintColor;
    QColor m_textColor;
    bool m_refuseFocus;
    QString m_hintText;
    bool m_showingHintText;

}; // end class HintLineEdit 

// #################################################################################
#endif // END HINTLINEEDIT_H_1270025628
// #################################################################################
