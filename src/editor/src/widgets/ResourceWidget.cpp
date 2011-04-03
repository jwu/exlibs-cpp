// ======================================================================================
// File         : ResourceWidget.cpp
// Author       : Wu Jie 
// Last Change  : 04/04/2010 | 15:04:33 PM | Sunday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "ResourceWidget.h"
#include "EditorMain.h"

using namespace ex;

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ResourceWidget::ResourceWidget ( QWidget* _pParent )
    : QWidget (_pParent)
{
    setupUi(this);

    filter->setHint(tr("<Search>"));

    // signal slot
    connect( filter, SIGNAL(filterChanged(const QString&)), this, SLOT(applyFilter(const QString&)) );

    // setup sync action
    refreshButton->setDefaultAction(action_Refresh);
    action_Refresh->setEnabled(false);
    connect( action_Refresh, SIGNAL(triggered()), this, SLOT(refresh()) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ResourceWidget::~ResourceWidget ()
{
    this->deinit ();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ResourceWidget::init ()
{
    ex_log ("init ResourceWidget.\n");

    // TODO: resView->init();
    // TODO: add resource types.
    return true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ResourceWidget::deinit ()
{
    ex_log ("deinit ResourceWidget.\n");

    // TODO: resView->deinit();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ResourceWidget::explore ( const QString& _path )
{
    QFileSystemModel* model = new QFileSystemModel;
    model->setRootPath(_path);
    resView->setModel(model);
    resView->setRootIndex(model->index(_path));
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ResourceWidget::refresh()
{
    // TODO:
    ex_log_func();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ResourceWidget::applyFilter ( const QString& _pattern )
{
    Q_UNUSED (_pattern);
    // TODO { 
    // resView->setUpdatesEnabled(false);
    // for ( int i = 0; i < resView->topLevelItemCount(); ++i )
    // {
    //     CResourceItem* pItem = static_cast<CResourceItem*>(resView->topLevelItem(i));
    //     this->doFilter(pItem,_pattern);
    // }
    // resView->setUpdatesEnabled(true);
    // } TODO end 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// TODO { 
// void ResourceWidget::doFilter ( CResourceItem* _pItem, const QString& _pattern )
// {
//     const bool matchAll = _pattern.isEmpty();
//     for ( int c = 0; c < _pItem->childCount(); ++c )
//     {
//         CResourceItem* pResItem = _pItem->child(c);
//         if ( pResItem->isFolder() ) // always show folders
//         {
//             pResItem->setHidden(false);
//         }
//         else
//         {
//             const QString propertyName = pResItem->text(0);
//             const bool showProperty = matchAll || propertyName.contains(_pattern, Qt::CaseInsensitive);
//             pResItem->setHidden( showProperty == false );
//         }
//         this->doFilter(pResItem,_pattern);
//     }
// }
// } TODO end 
