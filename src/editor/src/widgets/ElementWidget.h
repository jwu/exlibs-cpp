// ======================================================================================
// File         : ElementWidget.h
// Author       : Wu Jie 
// Last Change  : 08/10/2010 | 09:03:46 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ELEMENTWIDGET_H_1281402228
#define ELEMENTWIDGET_H_1281402228
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "ui_ElementWidget.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class ParseThread
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class ParseThread : public QThread
{
    ///////////////////////////////////////////////////////////////////////////////
    // public
    ///////////////////////////////////////////////////////////////////////////////

public:

    ParseThread ( QObject* _parent = NULL );
    ~ParseThread ();

    void init ( QTreeWidget* _treeWidget );
    void run();
    void abort () { m_abort = true; }

    void parse ( const QString& _dataType, const QString& _dirPath );

    ///////////////////////////////////////////////////////////////////////////////
    // protected
    ///////////////////////////////////////////////////////////////////////////////

protected:

    int parseFile ( const QString& _filepath );
    int parseAction ( const QString& _filepath );

    ///////////////////////////////////////////////////////////////////////////////
    // protected
    ///////////////////////////////////////////////////////////////////////////////

protected:

    QMutex m_mutex;
    bool m_abort;

    bool m_needParse;
    QString m_dirToParse;
    QString m_parseType;
    QTreeWidget* m_treeWidget;

}; // end class CPendingItemsThread

///////////////////////////////////////////////////////////////////////////////
// class ElementItem 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class ElementItem : public QTreeWidgetItem 
{
    ///////////////////////////////////////////////////////////////////////////////
    // public
    ///////////////////////////////////////////////////////////////////////////////

public:

    ElementItem ();

    void setDomElement( const QDomElement& _element ) { m_element = _element; }
    QDomElement& domElement () { return m_element; }
    const QDomElement& domElement () const { return m_element; }

    void setFilepath ( const QString& _filepath ) { m_filepath = _filepath; }
    const QString& filepath () const { return m_filepath; }

    void setPropObj ( ex::SmartPtr<ex::PropertyObject> _propObj ) { m_propObj = _propObj; m_regen = true; } 
    ex::SmartPtr<ex::PropertyObject> propObj () const { return m_propObj; } 

    // the functions will check if regenerate the property instance list first, 
    // then return the generated list.
    QList<ex::PropertyInstanceBase::smart_ptr_t>& propInstList ();

    //
    void setDirty ( bool _isDirty ) { m_dirty = _isDirty; }
    bool isDirty () const { return m_dirty; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected
    ///////////////////////////////////////////////////////////////////////////////

protected:

    void addPropInst_recursively( const ex::PropertiesDescriptor* _desc );

protected:

    QDomElement m_element;
    QString m_filepath;
    ex::SmartPtr<ex::PropertyObject> m_propObj;

    bool m_regen;
    bool m_dirty;
    QList<ex::PropertyInstanceBase::smart_ptr_t> m_propInstList;

}; // end class ElementItem

///////////////////////////////////////////////////////////////////////////////
// class ElementWidget 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class ElementWidget : public QWidget, private Ui::ElementWidget
{
    Q_OBJECT

    ///////////////////////////////////////////////////////////////////////////////
    // public mebmer functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    ElementWidget ( QWidget* _pParent = NULL );
    ~ElementWidget ();

    //
    bool init ();
    void deinit ();

    //
    void explore ( const QString& _dataType, const QString& _dirPath );

    // TEMP TEST { 
    void doLuaFilter ();
    // } TEMP TEST end 

    ///////////////////////////////////////////////////////////////////////////////
    // signals
    ///////////////////////////////////////////////////////////////////////////////

signals:

    void currentItemChanged ( QTreeWidgetItem* cur, QTreeWidgetItem* prev );
    void currentItemReseted ( QTreeWidgetItem* cur );
    void currentItemReplaced ( QTreeWidgetItem* cur );
    void currentItemSaved ( QTreeWidgetItem* cur );

    ///////////////////////////////////////////////////////////////////////////////
    // slots 
    ///////////////////////////////////////////////////////////////////////////////

public slots:

    void checkReset ( QTreeWidgetItem* _item, int _column );
    void onSave ();
    void onSaveAll ();
    void saveItem ( QTreeWidgetItem* _item );
    void updateItem ( QTreeWidgetItem* _item );

protected slots:

    void applyFilter ( const QString& _pattern );

protected:

    void reset ( QTreeWidgetItem* _item );
    void replace ( QTreeWidgetItem* _item );

    ///////////////////////////////////////////////////////////////////////////////
    // protected
    ///////////////////////////////////////////////////////////////////////////////

protected:

    ParseThread m_parseThread;
    QString m_editDir;

}; // end class ElementWidget

// #################################################################################
#endif // END ELEMENTWIDGET_H_1281402228
// #################################################################################
