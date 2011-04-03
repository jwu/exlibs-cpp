// ======================================================================================
// File         : FilterWidget.cpp
// Author       : Wu Jie 
// Last Change  : 03/31/2010 | 17:50:10 PM | Wednesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "FilterWidget.h"

///////////////////////////////////////////////////////////////////////////////
// IconButton
///////////////////////////////////////////////////////////////////////////////

#define ICONBUTTON_SIZE 12

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

IconButton::IconButton(QWidget *parent)
    : QToolButton(parent)
{
    setCursor(Qt::ArrowCursor);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void IconButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // Note isDown should really use the active state but in most styles
    // this has no proper feedback
    QIcon::Mode state = QIcon::Disabled;
    if (isEnabled())
        state = isDown() ? QIcon::Selected : QIcon::Normal;
    QPixmap iconpixmap = icon().pixmap(QSize(ICONBUTTON_SIZE, ICONBUTTON_SIZE),
                                       state, QIcon::Off);
    QRect pixmapRect = QRect(0, 0, iconpixmap.width(), iconpixmap.height());
    pixmapRect.moveCenter(rect().center());
    painter.setOpacity(m_fader);
    painter.drawPixmap(pixmapRect, iconpixmap);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void IconButton::animateShow(bool visible)
{
    if (visible) {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
        animation->setDuration(160);
        animation->setEndValue(1.0);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    } else {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
        animation->setDuration(160);
        animation->setEndValue(0.0);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

///////////////////////////////////////////////////////////////////////////////
// FilterWidget
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

FilterWidget::FilterWidget ( QWidget* _pParent )
    : QWidget (_pParent)
    , m_resetButton (NULL)
{
    setupUi(this);

    // ======================================================== 
    // hintLine 
    // ======================================================== 

    hintLine->setHintText(tr("<Filter>"));

    // Let the style determine minimum height for our widget
    QSize size(ICONBUTTON_SIZE + 6, ICONBUTTON_SIZE + 2);

    // Note KDE does not reserve space for the highlight color
    if (style()->inherits("OxygenStyle")) {
        size = size.expandedTo(QSize(24, 0));
    }

    // Make room for clear icon
    QMargins margins = hintLine->textMargins();
    if (layoutDirection() == Qt::LeftToRight)
        margins.setRight(size.width());
    else
        margins.setLeft(size.width());

    hintLine->setTextMargins(margins);

    connect(hintLine, SIGNAL(textEdited(const QString&)), this, SIGNAL(filterChanged(const QString&)));

    // ======================================================== 
    // button 
    // ======================================================== 

    // KDE has custom icons for this. Notice that icon namings are counter intuitive
    // If these icons are not avaiable we use the freedesktop standard name before
    // falling back to a bundled resource
    // QIcon icon = QIcon::fromTheme(layoutDirection() == Qt::LeftToRight ?
    //                  QLatin1String("edit-clear-locationbar-rtl") :
    //                  QLatin1String("edit-clear-locationbar-ltr"),
    //                  QIcon::fromTheme("edit-clear", createIconSet(QLatin1String("cleartext.png"))));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icons/res/icons/editdelete.png"), QSize(), QIcon::Normal, QIcon::Off);

    m_resetButton = new IconButton(hintLine);
    m_resetButton->setIcon(icon);
    m_resetButton->setToolTip(tr("Clear text"));
    m_resetButton->setDisabled(true);
    connect(m_resetButton, SIGNAL(clicked()), this, SLOT(reset()));
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

FilterWidget::~FilterWidget ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

QString FilterWidget::text() const
{
    return hintLine->typedText();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void FilterWidget::setText( const QString & _text )
{
    hintLine->setTypedText(_text);
    emit filterChanged(_text);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void FilterWidget::setHint ( const QString & _hint )
{
    hintLine->setHintText(_hint);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void FilterWidget::checkButton(const QString &)
{
    if ( m_resetButton ) {
        m_resetButton->setEnabled(!text().isEmpty());
        m_resetButton->animateShow(!text().isEmpty());
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void FilterWidget::reset()
{
    if (!text().isEmpty()) {
        // DISABLE: we now use m_resetButton instead of resetButton { 
        // Editor has lost focus once this is pressed
        // hintLine->showHintText(true);
        // } DISABLE end 
        hintLine->reset();
        emit filterChanged(QString());
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool FilterWidget::refuseFocus() const
{
    return hintLine->refuseFocus();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void FilterWidget::setRefuseFocus ( bool v )
{
    hintLine->setRefuseFocus(v);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void FilterWidget::resizeEvent(QResizeEvent *)
{
    QRect contentRect = hintLine->rect();
    if (layoutDirection() == Qt::LeftToRight) {
        const int iconoffset = hintLine->textMargins().right() + 4;
        m_resetButton->setGeometry(contentRect.adjusted(hintLine->width() - iconoffset, 0, 0, 0));
    } else {
        const int iconoffset = hintLine->textMargins().left() + 4;
        m_resetButton->setGeometry(contentRect.adjusted(0, 0, -hintLine->width() + iconoffset, 0));
    }
}
