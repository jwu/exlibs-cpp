// ======================================================================================
// File         : PropertyView.cpp
// Author       : Wu Jie 
// Last Change  : 08/10/2010 | 17:36:18 PM | Tuesday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "PropertyView.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

PropertyView::PropertyView ( QWidget* _parent )
    : QtTreePropertyBrowser (_parent)
    , m_modifiedCount (0)
    // : QtButtonPropertyBrowser (_parent)
    // : QtGroupBoxPropertyBrowser (_parent)
{
    this->setPropertiesWithoutValueMarked(true);
    this->setRootIsDecorated(true);
    this->setAlternatingRowColors(true);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

PropertyView::~PropertyView ()
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool PropertyView::init ()
{
    ex_log ("init PropertyView.\n");

    // create property manager
    m_boolMng = new QtBoolPropertyManager(this);
    m_doubleMng = new QtDoublePropertyManager(this);
    m_enumMng = new QtEnumPropertyManager(this);
    m_groupMng = new QtGroupPropertyManager(this);
    m_intMng = new QtIntPropertyManager(this);
    m_stringMng = new QtStringPropertyManager(this);

    // setup factory for each manager
    this->setFactoryForManager(m_boolMng,   new QtCheckBoxFactory(this));
    this->setFactoryForManager(m_doubleMng, new QtDoubleSpinBoxFactory(this));
    this->setFactoryForManager(m_enumMng,   new QtEnumEditorFactory(this));
    this->setFactoryForManager(m_intMng,    new QtSpinBoxFactory(this));
    this->setFactoryForManager(m_stringMng, new QtLineEditFactory(this));

    return true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyView::deinit ()
{
    this->clear ();
    ex_log ("deinit PropertyView.\n");
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyView::clear ()
{
    m_modifiedCount = 0;
    QtTreePropertyBrowser::clear();
    m_editItem = NULL;
    m_propToInst.clear();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyView::showProperty ( QTreeWidgetItem* _item )
{
    this->setUpdatesEnabled(false);
    this->clear();
    if ( _item ) {
        m_editItem = _item;
        ElementItem* elItem = static_cast<ElementItem*>(m_editItem);
        this->genPropUIs(elItem->propObj(), elItem->propInstList() );
    }
    this->setUpdatesEnabled(true);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyView::addPropUI ( QtProperty* _category, ex::PropertyInstanceBase::smart_ptr_t _propInst )
{
    using namespace ex;

    // don't add hided property
    if ( _propInst->visible() == false )
        return;

    QtProperty* qt_prop = NULL;
    QString propName = QString::fromLocal8Bit(_propInst->propName()); 

    if ( _propInst->typeNameID() == TypeTraits<int8>::type_name() )
    {
        qt_prop = m_intMng->addProperty(propName);
        int8 value;
        _propInst->get(&value);
        m_intMng->setValue( qt_prop, value );
        // TODO: setup min/max for the item { 
        // if ( _propInst->typeNameID() == TypeTraits<int8>::type_name() ) {
        // }
        // } TODO end 
    }
    else if ( _propInst->typeNameID() == TypeTraits<int16>::type_name() )
    {
        qt_prop = m_intMng->addProperty(propName);
        int16 value;
        _propInst->get(&value);
        m_intMng->setValue( qt_prop, value );
    }
    else if ( _propInst->typeNameID() == TypeTraits<int32>::type_name() )
    {
        qt_prop = m_intMng->addProperty(propName);
        int32 value;
        _propInst->get(&value);
        m_intMng->setValue( qt_prop, value );
    }
    else if ( _propInst->typeNameID() == TypeTraits<int64>::type_name() )
    {
        qt_prop = m_intMng->addProperty(propName);
        int64 value;
        _propInst->get(&value);
        m_intMng->setValue( qt_prop, value );
    }
    else if ( _propInst->typeNameID() == TypeTraits<uint8>::type_name() )
    {
        qt_prop = m_intMng->addProperty(propName);
        uint8 value;
        _propInst->get(&value);
        m_intMng->setValue( qt_prop, value );
    }
    else if ( _propInst->typeNameID() == TypeTraits<uint16>::type_name() )
    {
        qt_prop = m_intMng->addProperty(propName);
        uint16 value;
        _propInst->get(&value);
        m_intMng->setValue( qt_prop, value );
    }
    else if ( _propInst->typeNameID() == TypeTraits<uint32>::type_name() )
    {
        qt_prop = m_intMng->addProperty(propName);
        uint32 value;
        _propInst->get(&value);
        m_intMng->setValue( qt_prop, value );
    }
    else if ( _propInst->typeNameID() == TypeTraits<uint64>::type_name() )
    {
        qt_prop = m_intMng->addProperty(propName);
        uint64 value;
        _propInst->get(&value);
        m_intMng->setValue( qt_prop, value );
    }
    else if ( _propInst->typeNameID() == TypeTraits<bool>::type_name() )
    {
        qt_prop = m_boolMng->addProperty(propName);
        bool value;
        _propInst->get(&value);
        m_boolMng->setValue( qt_prop, value );
    }
    else if ( _propInst->typeNameID() == TypeTraits<float>::type_name() )
    {
        qt_prop = m_doubleMng->addProperty(propName);
        float value;
        _propInst->get(&value);
        m_doubleMng->setValue( qt_prop, value );
    }
    else if ( _propInst->typeNameID() == TypeTraits<double>::type_name() )
    {
        qt_prop = m_doubleMng->addProperty(propName);
        double value;
        _propInst->get(&value);
        m_doubleMng->setValue( qt_prop, value );
    }
    else if ( _propInst->typeNameID() == TypeTraits<const char*>::type_name() )
    {
        qt_prop = m_stringMng->addProperty(propName);
        const char* value = NULL;
        _propInst->get(&value);
        m_stringMng->setValue( qt_prop, QString::fromUtf8(value) );
    }
    else if ( _propInst->typeNameID() == TypeTraits<string_t>::type_name() )
    {
        qt_prop = m_stringMng->addProperty(propName);
        string_t value;
        _propInst->get(&value);
        m_stringMng->setValue( qt_prop, QString::fromUtf8(value.c_str()) );
    }
    else if ( _propInst->isEnum() )
    {
        qt_prop = m_enumMng->addProperty(propName);
        PropertyInstanceBase::enum_infos_t enumInfos = _propInst->enumInfos();
        QStringList strList;
        for ( PropertyInstanceBase::enum_infos_t::iterator iter = enumInfos.begin(); iter != enumInfos.end(); ++iter ) {
            strList.push_back((*iter).second);
        }
        m_enumMng->setEnumNames( qt_prop, strList );
        int value;
        _propInst->get(&value);
        m_enumMng->setValue( qt_prop, value );
    }
    else // there is not matched atomic type, maybe it have sub-properties 
    {
        if ( _propInst->subProperties().empty() == false ) {
            qt_prop = m_groupMng->addProperty(propName);
            PropertyInstanceBase::sub_properties_t& sub_props = _propInst->subProperties();

            typedef PropertyInstanceBase::sub_properties_t::iterator prop_iterator; 
            for ( prop_iterator iter = sub_props.begin(); iter != sub_props.end(); ++iter ) {
                this->addPropUI( qt_prop, *iter );
            }
        }
    }

    if ( qt_prop ) {
        qt_prop->setEnabled( _propInst->readonly() == false );
        bool isModified = _propInst->isModified();
        qt_prop->setModified (isModified);
        if ( isModified ) {
            m_modifiedCount += 1;
            qt_prop->setPropertyName( _propInst->propName() + QString(" *") );
        }
        else {
            qt_prop->setPropertyName( _propInst->propName() );
        }
        _category->addSubProperty(qt_prop);

        // add QtProperty to ex::PropertyInstanceBase::smart_ptr_t map.
        ex_assert( m_propToInst.contains(qt_prop) == false, "the QtProperty alreayd exists!" );
        m_propToInst[qt_prop] = _propInst;
    }
    else {
        ex_warning ("can't add property name: %s typename: %s.", qPrintable(propName), _propInst->typeNameID().c_str() );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyView::genPropUIs ( ex::SmartPtr<ex::PropertyObject> _propObj, QList<ex::PropertyInstanceBase::smart_ptr_t>& _propInstList )
{
    // disconnect all property manager valueChanged signal
    disconnect ( m_boolMng,    SIGNAL(valueChanged(QtProperty*, bool)),            this, SLOT(valueChanged(QtProperty*, bool)) );
    disconnect ( m_doubleMng,  SIGNAL(valueChanged(QtProperty*, double)),          this, SLOT(valueChanged(QtProperty*, double)) );
    disconnect ( m_enumMng,    SIGNAL(valueChanged(QtProperty*, int)),             this, SLOT(valueChanged(QtProperty*, int)) );
    disconnect ( m_intMng,     SIGNAL(valueChanged(QtProperty*, int)),             this, SLOT(valueChanged(QtProperty*, int)) );
    disconnect ( m_stringMng,  SIGNAL(valueChanged(QtProperty*, const QString&)),  this, SLOT(valueChanged(QtProperty*, const QString&)) );

    // we always create a basic group to include all properties.
    QtProperty* qt_category = m_groupMng->addProperty( _propObj->getClassName() );
    for ( QList<ex::PropertyInstanceBase::smart_ptr_t>::iterator iter = _propInstList.begin(); iter != _propInstList.end(); ++iter ) {
        this->addPropUI( qt_category, *iter );
    }
    QtBrowserItem* item = this->addProperty(qt_category);
    this->setBackgroundColor( item, QColor(255, 230, 191) );
    // TODO { 
    // m_colors.push_back(QColor(255, 230, 191));
    // m_colors.push_back(QColor(255, 255, 191));
    // m_colors.push_back(QColor(191, 255, 191));
    // m_colors.push_back(QColor(199, 255, 255));
    // m_colors.push_back(QColor(234, 191, 255));
    // m_colors.push_back(QColor(255, 191, 239));
    // m_colors.push_back(QColor(191, 207, 255));
    // m_colors.push_back(QColor(255, 191, 191));
    // } TODO end 

    // NOTE: we don't want the first time value changed signal, 
    // by connecting signal after property show up can avoid this problem.
    // setup property signal slot
    connect ( m_boolMng,    SIGNAL(valueChanged(QtProperty*, bool)),            this, SLOT(valueChanged(QtProperty*, bool)) );
    connect ( m_doubleMng,  SIGNAL(valueChanged(QtProperty*, double)),          this, SLOT(valueChanged(QtProperty*, double)) );
    connect ( m_enumMng,    SIGNAL(valueChanged(QtProperty*, int)),             this, SLOT(valueChanged(QtProperty*, int)) );
    connect ( m_intMng,     SIGNAL(valueChanged(QtProperty*, int)),             this, SLOT(valueChanged(QtProperty*, int)) );
    connect ( m_stringMng,  SIGNAL(valueChanged(QtProperty*, const QString&)),  this, SLOT(valueChanged(QtProperty*, const QString&)) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyView::setValue ( QtProperty* _prop, ex::PropertyInstanceBase::smart_ptr_t _propInst, void* _value )
{
    //
    bool isAlreadyModified = _propInst->isModified();
    _propInst->set(_value);
    bool isModified = _propInst->isModified();

    //
    bool itemNeedChange = false;
    if ( isAlreadyModified && !isModified ) {
        m_modifiedCount -= 1;
        if ( m_modifiedCount == 0 )
            itemNeedChange = true;
    }
    else if ( !isAlreadyModified && isModified ) {
        m_modifiedCount += 1;
        if ( m_modifiedCount == 1 )
            itemNeedChange = true;
    }

    //
    _prop->setModified (isModified);
    if ( isModified )
        _prop->setPropertyName( _propInst->propName() + QString(" *") );
    else
        _prop->setPropertyName( _propInst->propName() );
    
    // DISABLE { 
    // if ( itemNeedChange ) {
    //     if ( m_modifiedCount > 0 ) {
    //         m_editItem->setText( 1, m_editItem->text(1) + QString(" *") );
    //         QStyleOptionViewItemV3 opt;
    //         opt.font.setBold(true);
    //         m_editItem->setFont( 1, opt.font );
    //     }
    //     else {
    //         m_editItem->setText( 1, m_editItem->text(1) );
    //         QStyleOptionViewItemV3 opt;
    //         opt.font.setBold(false);
    //         m_editItem->setFont( 1, opt.font );
    //     }
    // }
    // if ( itemNeedChange ) {
    //     // NOTE: this can avoid reduntantly calling checkReset() --> reset() function...
    //     m_editItem->treeWidget()->blockSignals(true);
    //     if ( m_modifiedCount > 0 ) {
    //         m_editItem->setCheckState ( 0, Qt::Checked ); 
    //         m_editItem->setFlags ( m_editItem->flags() | Qt::ItemIsUserCheckable ); 
    //     }
    //     else {
    //         m_editItem->setCheckState ( 0, Qt::Unchecked ); 
    //         m_editItem->setFlags ( m_editItem->flags() & ~Qt::ItemIsUserCheckable ); 
    //     }
    //     m_editItem->treeWidget()->blockSignals(false);
    // }
    // } DISABLE end 
    ElementItem* item = static_cast<ElementItem*>(m_editItem);
    item->setDirty( m_modifiedCount > 0 );
    emit valueChanged (m_editItem);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyView::valueChanged ( QtProperty* _prop, bool _value ) 
{
    ex_assert_return( m_propToInst.contains(_prop), /*void*/, "can't find the property %s in m_propToInst map", qPrintable(_prop->propertyName()) );
    this->setValue( _prop, m_propToInst[_prop], &_value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyView::valueChanged ( QtProperty* _prop, double _value )
{
    ex_assert_return( m_propToInst.contains(_prop), /*void*/, "can't find the property %s in m_propToInst map", qPrintable(_prop->propertyName()) );
    this->setValue( _prop, m_propToInst[_prop], &_value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyView::valueChanged ( QtProperty* _prop, int _value )
{
    ex_assert_return( m_propToInst.contains(_prop), /*void*/, "can't find the property %s in m_propToInst map", qPrintable(_prop->propertyName()) );
    this->setValue( _prop, m_propToInst[_prop], &_value );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyView::valueChanged ( QtProperty* _prop, const QString& _value )
{
    ex_assert_return( m_propToInst.contains(_prop), /*void*/, "can't find the property %s in m_propToInst map", qPrintable(_prop->propertyName()) );

    // NOTE: don't use const char* value = _value.toUtf8().constData(), 
    // this will loose the data because QByteArray will be destroyed after toUtf8() out of its scope . 
    QByteArray byteArray = _value.toUtf8();
    const char* value = byteArray.constData();
    this->setValue( _prop, m_propToInst[_prop], &value );
}

// DISABLE { 
// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// void PropertyView::reset () 
// {
//     m_modifiedCount = 0;
//     refreshAll ();

//     // now reset the edit item in element widget
//     m_editItem->treeWidget()->blockSignals(true);
//     m_editItem->setCheckState ( 0, Qt::Unchecked ); 
//     m_editItem->setFlags ( m_editItem->flags() & ~Qt::ItemIsUserCheckable ); 
//     m_editItem->treeWidget()->blockSignals(false);
// }

// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// void PropertyView::refreshAll ()
// {
//     QList<QtBrowserItem*> categories = this->topLevelItems();
//     for ( QList<QtBrowserItem*>::iterator it_cate = categories.begin(); it_cate < categories.end(); ++it_cate ) {
//         QList<QtBrowserItem*> items = (*it_cate)->children();
//         for ( QList<QtBrowserItem*>::iterator it = items.begin(); it < items.end(); ++it ) {
//             this->refresh( *it );
//         }
//     }
// }

// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// void PropertyView::refresh ( QtBrowserItem* _item )
// {
//     using namespace ex;

//     QList<QtBrowserItem*> items = _item->children();
//     for ( QList<QtBrowserItem*>::iterator it = items.begin(); it < items.end(); ++it ) {
//         this->refresh(*it);
//     }
//     QtProperty* qt_prop = _item->property();
//     ex::PropertyInstanceBase::smart_ptr_t propInst = m_propToInst[qt_prop];

//     if ( propInst->typeNameID() == TypeTraits<int8>::type_name() 
//          || propInst->typeNameID() == TypeTraits<int16>::type_name()
//          || propInst->typeNameID() == TypeTraits<int32>::type_name()
//          || propInst->typeNameID() == TypeTraits<int64>::type_name()
//          || propInst->typeNameID() == TypeTraits<uint8>::type_name()
//          || propInst->typeNameID() == TypeTraits<uint16>::type_name()
//          || propInst->typeNameID() == TypeTraits<uint32>::type_name()
//          || propInst->typeNameID() == TypeTraits<uint64>::type_name()
//        )
//     {
//         int value;
//         propInst->get(&value);
//         m_intMng->setValue( qt_prop, value );
//     }
//     else if ( propInst->typeNameID() == TypeTraits<bool>::type_name() )
//     {
//         bool value;
//         propInst->get(&value);
//         m_boolMng->setValue( qt_prop, value );
//     }
//     else if ( propInst->typeNameID() == TypeTraits<float>::type_name() 
//               || propInst->typeNameID() == TypeTraits<double>::type_name()
//             )
//     {
//         double value;
//         propInst->get(&value);
//         m_doubleMng->setValue( qt_prop, value );
//     }
//     else if ( propInst->typeNameID() == TypeTraits<const char*>::type_name() 
//               || propInst->typeNameID() == TypeTraits<string_t>::type_name()
//             )
//     {
//         const char* value = NULL;
//         propInst->get(&value);
//         m_stringMng->setValue( qt_prop, QString::fromUtf8(value) );
//     }
//     else if ( propInst->isEnum() )
//     {
//         int value;
//         propInst->get(&value);
//         m_enumMng->setValue( qt_prop, value );
//     }
// }
// } DISABLE end 
