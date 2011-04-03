// ======================================================================================
// File         : PropertyView.h
// Author       : Wu Jie 
// Last Change  : 08/10/2010 | 17:36:13 PM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PROPERTYVIEW_H_1281432975
#define PROPERTYVIEW_H_1281432975
// #################################################################################

#include "qttreepropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qtbuttonpropertybrowser.h"

///////////////////////////////////////////////////////////////////////////////
// class 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class PropertyView : 
    public QtTreePropertyBrowser
    // public QtButtonPropertyBrowser
    // public QtGroupBoxPropertyBrowser
{
    Q_OBJECT

    ///////////////////////////////////////////////////////////////////////////////
    // public
    ///////////////////////////////////////////////////////////////////////////////

public:

    PropertyView ( QWidget* _parent = NULL );
    ~PropertyView ();

    bool init ();
    void deinit ();
    void clear ();
    uint modifiedCount() const { return m_modifiedCount; }
    QTreeWidgetItem* editItem () const { return m_editItem; }

signals:

    void valueChanged ( QTreeWidgetItem* _item );

public slots:

    void showProperty ( QTreeWidgetItem* _item );
    // DISABLE { 
    // void refreshAll ();
    // void reset ();
    // } DISABLE end 

protected slots:

    void valueChanged ( QtProperty* _prop, bool _value );
    void valueChanged ( QtProperty* _prop, double _value );
    void valueChanged ( QtProperty* _prop, int _value );
    void valueChanged ( QtProperty* _prop, const QString& _value );

    ///////////////////////////////////////////////////////////////////////////////
    // protected
    ///////////////////////////////////////////////////////////////////////////////

protected:

    void genPropUIs ( ex::SmartPtr<ex::PropertyObject> _propObj, QList<ex::PropertyInstanceBase::smart_ptr_t>& _propInstList );
    void addPropUI ( QtProperty* _category, ex::PropertyInstanceBase::smart_ptr_t _propInst );
    void setValue ( QtProperty* _prop, ex::PropertyInstanceBase::smart_ptr_t _propInst, void* _value );
    void refresh ( QtBrowserItem* _item );

protected:

    QTreeWidgetItem* m_editItem;

    // property managers
    class QtBoolPropertyManager* m_boolMng;
    class QtDoublePropertyManager* m_doubleMng;
    class QtEnumPropertyManager* m_enumMng;
    class QtGroupPropertyManager* m_groupMng;
    class QtIntPropertyManager* m_intMng;
    class QtStringPropertyManager* m_stringMng;

    // QtProperty to ex::PropertyInstanceBase::smart_ptr_t
    QHash<QtProperty*,ex::PropertyInstanceBase::smart_ptr_t> m_propToInst;

    uint m_modifiedCount;

}; // end class PropertyView

// #################################################################################
#endif // END PROPERTYVIEW_H_1281432975
// #################################################################################


