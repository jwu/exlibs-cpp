// ======================================================================================
// File         : PropertyInstanceBase.cpp
// Author       : Wu Jie 
// Last Change  : 01/25/2010 | 09:46:48 AM | Monday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "PropertyBase.h"
#include "PropertyInstanceBase.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

PropertyInstanceBase::PropertyInstanceBase ( PropertyBase* _pProperty, void* _pObject )
    : m_pProperty (_pProperty)
    , m_pObject (_pObject)
    , m_pBasePropertyInstance (NULL)
    , m_originalValue (NULL)
{
    // only atomic value can reset
    // TODO: I think Vector3, Vecotr4 ... can have reset ability, too.
    if ( m_pProperty->isClass() == false ) {
        m_originalValue = ex_malloc ( m_pProperty->typeSize() );
        this->get(m_originalValue);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

PropertyInstanceBase::~PropertyInstanceBase ()
{
    m_subProps.clear();
    ex_safe_delete (m_pProperty);
    ex_safe_free (m_originalValue); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const char* PropertyInstanceBase::typeName () const 
{ 
    return m_pProperty->typeName().c_str(); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const string_id_t& PropertyInstanceBase::typeNameID () const 
{ 
    return m_pProperty->typeName(); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const char* PropertyInstanceBase::propName () const 
{ 
    return m_pProperty->propName().c_str(); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool PropertyInstanceBase::readonly () const 
{ 
    return flags_has(m_pProperty->attributes(),PropAttr::readonly);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool PropertyInstanceBase::visible () const 
{ 
    return !( flags_has(m_pProperty->attributes(),PropAttr::hide) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool PropertyInstanceBase::isModified ()
{
    if ( m_originalValue == NULL ) {
        return false;
    }
    void* curValue = ex_stack_malloc( this->typeSize() );
    this->get(curValue);

    return (m_pProperty->isEqual(curValue,m_originalValue) == false);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyInstanceBase::reset ()
{
    if ( m_originalValue == NULL ) {
        if ( m_subProps.empty() )
            return;
        for ( sub_properties_t::iterator iter = m_subProps.begin(); iter != m_subProps.end(); ++iter ) {
            (*iter)->reset();
        }
        return;
    }
    this->set (m_originalValue);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyInstanceBase::replace ()
{
    if ( m_originalValue == NULL ) {
        if ( m_subProps.empty() )
            return;
        for ( sub_properties_t::iterator iter = m_subProps.begin(); iter != m_subProps.end(); ++iter ) {
            (*iter)->replace();
        }
        return;
    }
    this->get (m_originalValue);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t PropertyInstanceBase::typeSize () const
{
    return m_pProperty->typeSize();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool PropertyInstanceBase::isEnum () const
{
    return m_pProperty->isEnum();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool PropertyInstanceBase::isAtomic () const
{
    return m_pProperty->isAtomic();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool PropertyInstanceBase::isClass () const
{
    return m_pProperty->isClass();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool PropertyInstanceBase::isStandaloneClass () const
{
    return m_pProperty->isStandaloneClass();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool PropertyInstanceBase::isPropertyClass () const
{
    return m_pProperty->isPropertyClass();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

PropertyInstanceBase::enum_infos_t PropertyInstanceBase::enumInfos () const
{
    return m_pProperty->enumInfos();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyInstanceBase::set ( void* _pValue ) 
{ 
    m_pProperty->set(m_pObject,_pValue); 

    // if we are a sub property, and change the value, it is possible that
    // the base property have a callback that will update something else after
    // changes, and this will notify the base classes that the value has been changed
    if ( m_pBasePropertyInstance != NULL )
    {
        m_pBasePropertyInstance->notifyChanged();
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyInstanceBase::get ( void* _pValue )
{ 
    m_pProperty->get(m_pObject,_pValue); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertyInstanceBase::notifyChanged ()
{
    if ( m_pProperty->hasSetCallback() ) // if we have set-callback, call it so that the changed value can be update.
    {
        ex_assert( m_pProperty->getValuePtr(m_pObject), "The ValuePtr can't be NULL unless this is not a property in member class." );
        set ( m_pProperty->getValuePtr(m_pObject) );
    }
    else // NOTE: the Set() function will call notifyChanged, and this protect that if we don't invoke Set
    {
        if ( m_pBasePropertyInstance != NULL )
        {
            m_pBasePropertyInstance->notifyChanged();
        }
    }
}

// ######################### 
} // end namespace ex 
// ######################### 

