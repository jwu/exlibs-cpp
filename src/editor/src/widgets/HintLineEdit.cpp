// ======================================================================================
// File         : HintLineEdit.cpp
// Author       : Wu Jie 
// Last Change  : 03/31/2010 | 16:55:54 PM | Wednesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "HintLineEdit.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

HintLineEdit::HintLineEdit(QWidget *parent) 
    : QLineEdit(parent)
    , m_defaultFocusPolicy(focusPolicy())
    , m_hintColor(QColor(0xbbbbbb))
    , m_refuseFocus(false)
    , m_showingHintText(false)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HintLineEdit::reset()
{
    if (!this->typedText().isEmpty()) {
        this->hideHintText();
        this->setText(QString());
        emit textEdited(QString());
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool HintLineEdit::refuseFocus() const
{
    return m_refuseFocus;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HintLineEdit::setRefuseFocus(bool v)
{
    if (v == m_refuseFocus)
        return;
    m_refuseFocus = v;
    setFocusPolicy(m_refuseFocus ? Qt::NoFocus : m_defaultFocusPolicy);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HintLineEdit::mousePressEvent(QMouseEvent *e)
{
    // Explicitly focus on click.
    if (m_refuseFocus && !hasFocus())
        setFocus(Qt::OtherFocusReason);
    QLineEdit::mousePressEvent(e);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HintLineEdit::focusInEvent(QFocusEvent *e)
{
    if (m_refuseFocus) {
        // Refuse the focus if the mouse it outside. In addition to the mouse
        // press logic, this prevents a re-focussing which occurs once
        // we actually had focus
        const Qt::FocusReason reason = e->reason();
        if (reason == Qt::ActiveWindowFocusReason || reason == Qt::PopupFocusReason) {
            const QPoint mousePos = mapFromGlobal(QCursor::pos());
            const bool refuse = !geometry().contains(mousePos);
            if (refuse) {
                e->ignore();
                return;
            }
        }
    }

    hideHintText();
    QLineEdit::focusInEvent(e);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HintLineEdit::focusOutEvent(QFocusEvent *e)
{
    // Focus out: Switch to displaying the hint text unless there is user input
    showHintText();
    QLineEdit::focusOutEvent(e);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

QString HintLineEdit::hintText() const
{
    return m_hintText;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HintLineEdit::setTypedText ( const QString& _text )
{
    if ( _text != "" )
    {
        this->hideHintText();
        QLineEdit::setText(_text);
    }
    else
    {
        this->showHintText();
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HintLineEdit::setHintText ( const QString & _ht )
{
    if (_ht == m_hintText)
        return;
    hideHintText();
    m_hintText = _ht;
    if (!hasFocus() && !_ht.isEmpty())
        showHintText();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HintLineEdit::showHintText(bool force)
{
    if (m_showingHintText || m_hintText.isEmpty())
        return;
    if (force || text().isEmpty()) {
        m_showingHintText = true;
        setText(m_hintText);
        setTextColor(m_hintColor, &m_textColor);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HintLineEdit::hideHintText()
{
    if (m_showingHintText && !m_hintText.isEmpty()) {
        m_showingHintText = false;
        setText(QString());
        setTextColor(m_textColor);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool HintLineEdit::isShowingHintText() const
{
    return m_showingHintText;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

QString HintLineEdit::typedText() const
{
    return m_showingHintText ? QString() : text();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HintLineEdit::setTextColor(const QColor &newColor, QColor *oldColor)
{
    QPalette pal = palette();
    if (oldColor)
        *oldColor = pal.color(QPalette::Text);
    pal.setColor(QPalette::Text, newColor);
    setPalette(pal);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HintLineEdit::keyPressEvent ( QKeyEvent* _pEvent )
{
    QLineEdit::keyPressEvent(_pEvent);

    //
    if ( _pEvent->key() == Qt::Key_Escape ) {
        this->reset();
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool HintLineEdit::event( QEvent * e )
{
    bool ret = QLineEdit::event(e);
    
    // the ESC is been add into the action-short list (stop-world). so we must get the event, and accept it.
    if ( e->type() == QEvent::ShortcutOverride ) {
        QKeyEvent* ke = static_cast<QKeyEvent*>(e);
        switch ( ke->key() ) {
        case Qt::Key_Escape:
            ke->accept();
        default:
            break;
        }
    }
    return ret;
}
