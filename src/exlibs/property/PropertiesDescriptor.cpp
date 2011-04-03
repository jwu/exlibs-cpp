// ======================================================================================
// File         : PropertiesDescriptor.cpp
// Author       : Wu Jie 
// Last Change  : 03/13/2009 | 00:02:12 AM | Friday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// static member functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void PropertiesDescriptor::addProperty ( properties_t* _pInProperties, PropertyBase* _pProperty )
{
    _pInProperties->push_back (_pProperty);
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

PropertiesDescriptor::PropertiesDescriptor ()
    : m_className (NULL)
    , m_parentDesc (NULL)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

PropertiesDescriptor::~PropertiesDescriptor ()
{
    for ( properties_t::c_iterator iter = m_properties.begin(); iter != m_properties.end(); ++iter )
    {
        DestroyProperty< NoManaged<NullType>::TAllocator > ( (*iter) );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t PropertiesDescriptor::serializePropertyObject ( ISerializeNode* _pNode, void* _pObject ) const
{
    result_t eResult = EResult::ok;
    // save/load parent's properties
    if ( m_parentDesc ) {
        m_parentDesc->serializePropertyObject ( _pNode, _pObject );
    }

    // save/load properties
    for ( properties_t::c_iterator iter = m_properties.begin(); iter != m_properties.end(); ++iter )
    {
        if ( serializeProperty( *iter, _pNode, _pObject ) != EResult::ok )
            eResult = EResult::serialize_failed;
    }
    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t PropertiesDescriptor::serializeProperty ( PropertyBase* pProp, ISerializeNode* _pNode, void* _pObject ) const
{
    result_t eResult = pProp->serializeProperty ( _pNode, _pObject );

    // for not-found, we simply warn user, but return OK result to called functions.
    if ( eResult == EResult::not_found ) {
        ex_warning ( "property %s not found", pProp->propName().c_str() );
        return EResult::ok;
    }
    else if ( eResult != EResult::ok ) {
        ex_error( "Failed to serialize property: %s", pProp->propName().c_str() );
    }
    return eResult;
}

// ######################### 
} // end namespace ex 
// ######################### 

