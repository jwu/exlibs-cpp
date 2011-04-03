// ======================================================================================
// File         : PropertyWidget.cpp
// Author       : Wu Jie 
// Last Change  : 08/09/2010 | 15:05:01 PM | Monday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "PropertyWidget.h"
#include "ElementWidget.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

PropertyWidget::PropertyWidget ( QWidget* _pParent )
    : QWidget (_pParent)
{
    setupUi(this);

    // signal slot
    connect( filter, SIGNAL(filterChanged(const QString&)), this, SLOT(applyFilter(const QString&)) );
    connect( propView, SIGNAL(valueChanged(QTreeWidgetItem*)), this, SIGNAL(valueChanged(QTreeWidgetItem*)) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

PropertyWidget::~PropertyWidget ()
{
    this->clear();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool PropertyWidget::init ()
{
    ex_log ("init PropertyWidget\n");
    ex_check_return ( propView->init(), false, "failed to init property view" );
    return true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyWidget::deinit ()
{
    ex_log ("deinit PropertyWidget\n");
    propView->deinit();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyWidget::refresh()
{
    // TODO need better algorithm: propView->refreshAll();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyWidget::clear()
{
    propView->clear();
    filter->reset();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyWidget::showProperty ( QTreeWidgetItem* _item )
{
    // store the filter-text before we clear the widget.
    QString filterText = filter->text();
    this->clear();

    // show property
    // DEBUG: ex_log ( "showProperty: %s\n",  qPrintable( _item->text(1) ) );
    propView->showProperty(_item);

    // 
    if ( filterText != "" )
        filter->setText(filterText);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyWidget::applyFilter ( const QString& _pattern )
{
    propView->setUpdatesEnabled(false);
    const bool matchAll = _pattern.isEmpty();
    QList<QtBrowserItem*> categories = propView->topLevelItems();
    for ( QList<QtBrowserItem*>::iterator it_category = categories.begin(); it_category < categories.end(); ++it_category ) {
        QList<QtBrowserItem*> browserItems = (*it_category)->children();
        for ( QList<QtBrowserItem*>::iterator it_brow = browserItems.begin(); it_brow < browserItems.end(); ++it_brow ) {
            QtProperty* prop = (*it_brow)->property();
            const bool show = matchAll || prop->propertyName().contains(_pattern, Qt::CaseInsensitive);
            propView->setItemVisible( *it_brow, show );
        }
    }
    propView->setUpdatesEnabled(true);
}

