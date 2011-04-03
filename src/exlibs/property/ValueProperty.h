// ======================================================================================
// File         : ValueProperty.h
// Author       : Wu Jie 
// Last Change  : 02/23/2010 | 21:10:58 PM | Tuesday,February
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef VALUEPROPERTY_H_1266930667
#define VALUEPROPERTY_H_1266930667
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// include
///////////////////////////////////////////////////////////////////////////////

#include "serialization/serialize_helpers.h"
#include "property_helpers.h"
#include "PropertyBase.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class ValueProperty 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class ValueProperty : public PropertyBase
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef PropertyBase                    base_t;
    typedef ValueProperty<T>                self_t;
    typedef T*                              value_ptr_t;             
    typedef void (*pfn_get_t)(T*);
    typedef void (*pfn_set_t)(const T&);
    typedef Functor<void,Seq<T*> >          get_functor_t; 
    typedef Functor<void,Seq<const T&> >    set_functor_t; 

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ------------------------------------------------------------------ 
    // Desc: default constructor
    // ------------------------------------------------------------------ 

    ValueProperty ()
        : base_t ()
        , m_pValue (NULL)
        , m_fnGet ()
        , m_fnSet ()
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: copy constructor
    // ------------------------------------------------------------------ 

    ValueProperty ( const ValueProperty& _property )
        : base_t (_property)
        , m_pValue (_property.m_pValue)
        , m_fnGet (_property.m_fnGet)
        , m_fnSet (_property.m_fnSet)
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: init member
    // ------------------------------------------------------------------ 

    void setValuePtr ( value_ptr_t _valuePtr ) { m_pValue = _valuePtr; }
    void setFnGet ( pfn_get_t _pfnGet ) { if ( _pfnGet != NULL ) m_fnGet.set ( _pfnGet ); }
    void setFnSet ( pfn_set_t _pfnSet ) { if ( _pfnSet != NULL ) m_fnSet.set ( _pfnSet ); }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ------------------------------------------------------------------ 
    // Desc: 
    // NOTE: in value property, this function seldom be invoked.
    //       cause value-property usually used in sub-property. the parent 
    //       of those property have their own serialize function.  
    // NOTE: since there is no RegisterProperty been called for these non-property-object
    //       class, it make it hard to use the ValueProperty for serialization 
    // ------------------------------------------------------------------ 

    virtual result_t serializeProperty ( ISerializeNode* _pNode, void* _pObject ) 
    {
        // if the property have the attribute no-serialize, just skip it when save/load
        if ( flags_has (m_attrFlags, PropAttr::no_serialize) )
            return EResult::ok;

        // if the property have the attribute editor-only, and the serialize node is BinarySerializeNode, skip it when save/load
        if ( flags_has (m_attrFlags, PropAttr::editor_only) ) {
            if ( _pNode->isA( BinarySerializeNode::classID() ) )
                return EResult::ok;
        }

        return SerializeHelper<T>::serialize ( _pNode, base_t::propID().c_str(), m_pValue );
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual PropertyInstanceBase* createPropertyInstance ( void* _pObject ) const 
    {
        return ex_new PropertyInstance<T> ( ex_new ValueProperty <T>(*this),
                                            _pObject );
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual const string_id_t& typeName () const { 
        return TypeTraits<T>::type_name();
    } 

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual void* getValuePtr ( void* _pObject ) 
    { 
        return _pObject;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual void get ( void* _pObject, void* _pValueOut )
    { 
        if ( m_fnGet.isValid() ) {
            m_fnGet((T*)_pValueOut);
        }
        else {
            PropertyGetSet<T>()( reinterpret_cast<T*>(_pValueOut), reinterpret_cast<T*>(_pObject) );
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual void set ( void* _pObject, void* _pValueIn ) 
    { 
        T* pValue = reinterpret_cast<T*>(_pValueIn);
        PropertyMinMax<T>()( &pValue, 
                             reinterpret_cast<T*>(_pValueIn), 
                             reinterpret_cast<T*>(m_pMin), 
                             reinterpret_cast<T*>(m_pMax) );

        //
        if ( m_fnSet.isValid() ) {
            m_fnSet( *reinterpret_cast<T*>(pValue) );
        }
        else {
            PropertyGetSet<T>()( reinterpret_cast<T*>(_pObject), reinterpret_cast<T*>(pValue) );
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual bool hasSetCallback () const { return m_fnSet.isValid(); } 

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual bool hasGetCallback () const { return m_fnGet.isValid(); } 

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual bool isEqual ( void* _lhs, void* _rhs ) const { 
        return PropertyEqualSelector<T>( reinterpret_cast<T*>(_lhs), 
                                         reinterpret_cast<T*>(_rhs), 
                                         intToType< TypeTraits<T>::isAtomic || TypeTraits<T>::isString || TypeTraits<T>::isEnum >() );
    } 

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual size_t typeSize () const { return sizeof(T); } 
    virtual bool isEnum () const { return TypeTraits<T>::isEnum; } 
    virtual bool isAtomic () const { return TypeTraits<T>::isAtomic; } 
    virtual bool isClass () const { return !TypeTraits<T>::isArith && !TypeTraits<T>::isString && !TypeTraits<T>::isEnum; } 
    virtual bool isStandaloneClass () const { return isClass() && !isPropertyClass(); } 
    virtual bool isPropertyClass () const { return typeop::IsSuperSubClass<PropertyObject,T>::Result; } 

    virtual enum_infos_t enumInfos () const { 
        enum_infos_t info;
        enum_info_list ( TypeTraits<T>::type_name(), &info );
        return info;
    } 

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    value_ptr_t     m_pValue;
    get_functor_t   m_fnGet;
    set_functor_t   m_fnSet;

}; // end class ValueProperty 

///////////////////////////////////////////////////////////////////////////////
// helper functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: CreateValueProperty
// ------------------------------------------------------------------ 

template < template <class> class TAllocator_T, typename T >
INLINE PropertyBase* CreateValueProperty ( const char* _propertyID, 
                                           const char* _propertyName, 
                                           T* _valuePtr, 
                                           uint32 _flags = PropAttr::none, 
                                           typename ValueProperty<T>::pfn_get_t _pfnGet = NULL, 
                                           typename ValueProperty<T>::pfn_set_t _pfnSet = NULL ) 
{
    typedef ValueProperty <T> property_t;
    property_t* pProp = TAllocator_T<property_t>::Malloc (1);
    ex_new_in (pProp) property_t ();
    pProp->setPropID(_propertyID);
    pProp->setPropName(_propertyName);
    pProp->setAttributes(_flags);
    pProp->setValuePtr(_valuePtr);
    pProp->setFnGet(_pfnGet);
    pProp->setFnSet(_pfnSet);
    // pProp->setMin(_pMin);
    // pProp->setMax(_pMax);
    return pProp;
}

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END VALUEPROPERTY_H_1266930667
// #################################################################################

