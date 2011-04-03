// ======================================================================================
// File         : MemberProperty.h
// Author       : Wu Jie 
// Last Change  : 02/23/2010 | 21:04:53 PM | Tuesday,February
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MEMBERPROPERTY_H_1266930297
#define MEMBERPROPERTY_H_1266930297
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
// class MemberProperty 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename CLASS_T, typename MEMBER_T >
class MemberProperty : public PropertyBase
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef PropertyBase                               base_t;
    typedef MemberProperty<CLASS_T,MEMBER_T>           self_t;
    typedef MEMBER_T CLASS_T::*                        member_ptr_t;             
    typedef void (CLASS_T::*pfn_get_t)(MEMBER_T*);
    typedef void (CLASS_T::*pfn_set_t)(const MEMBER_T&);
    typedef Functor<void,Seq<MEMBER_T*> >         get_functor_t; 
    typedef Functor<void,Seq<const MEMBER_T&> >   set_functor_t; 

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ------------------------------------------------------------------ 
    // Desc: default constructor
    // ------------------------------------------------------------------ 

    MemberProperty ()
        : base_t ()
        , m_memberPtr (NULL)
        , m_fnGet ()
        , m_fnSet ()
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: copy constructor
    // ------------------------------------------------------------------ 

    MemberProperty ( const MemberProperty& _property )
        : base_t (_property)
        , m_memberPtr (_property.m_memberPtr)
        , m_fnGet (_property.m_fnGet)
        , m_fnSet (_property.m_fnSet)
    {
    }

    // ------------------------------------------------------------------ 
    // Desc: init member
    // ------------------------------------------------------------------ 

    void setMemberPtr ( member_ptr_t _memberPtr ) { m_memberPtr = _memberPtr; }
    void setFnGet ( pfn_get_t _pfnGet ) { if ( _pfnGet != NULL ) m_fnGet.set ( (CLASS_T*)NULL, _pfnGet, true ); }
    void setFnSet ( pfn_set_t _pfnSet ) { if ( _pfnSet != NULL ) m_fnSet.set ( (CLASS_T*)NULL, _pfnSet, true ); }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ------------------------------------------------------------------ 
    // Desc: 
    // NOTE: can't "serialize ( void* _v, int _length )" like UE3, cause 
    //       the serialize in UE3 don't need to provide type when loading.
    //       the advance for UE3's serialize method is it unify the loading 
    //       and saving in the code, in NOMAD, this can be done by have 
    //       same Descriptor with Load&Save functions. 
    // ------------------------------------------------------------------ 

    virtual result_t serializeProperty ( ISerializeNode* _pNode, void* _pObject ) 
    {
        result_t eResult = EResult::ok;

        // if the property have the attribute no-serialize, just skip it when save/load
        if ( flags_has (m_attrFlags, PropAttr::no_serialize) )
            return eResult;

        // if the property have the attribute editor-only, and the serialize node is BinarySerializeNode, skip it when save/load
        if ( flags_has (m_attrFlags, PropAttr::editor_only) ) {
            if ( _pNode->isA( BinarySerializeNode::classID() ) )
                return EResult::ok;
        }

        // NOTE: the get/set would be really danger if the object operate behind get/set is
        //       not created! so make sure you have the right object to opearte before serialize.
        // PS: the object above is not the _pObject. it is some object that you wrap in get/set function. 

        // if we have set function and we are loading the node
        // load the value and use set function to set it.
        if ( _pNode->isLoading() && m_fnSet.isValid() )
        {
            MEMBER_T value;
            eResult = SerializeHelper<MEMBER_T>::serialize ( _pNode, base_t::propID().c_str(), &value );
            m_fnSet.set_object((CLASS_T*)_pObject);
            m_fnSet( value );
            return eResult;
        }
        // if we have get function and we are saving the node
        // use get function to get the value and save it.
        else if ( _pNode->isSaving() && m_fnGet.isValid() )
        {
            MEMBER_T value;
            m_fnGet.set_object((CLASS_T*)_pObject);
            m_fnGet( &value );
            eResult = SerializeHelper<MEMBER_T>::serialize ( _pNode, base_t::propID().c_str(), &value );
            return eResult;
        }

        //
        return SerializeHelper<MEMBER_T>::serialize ( _pNode, base_t::propID().c_str(), &(((CLASS_T*)_pObject)->*m_memberPtr) );
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual PropertyInstanceBase* createPropertyInstance ( void* _pObject ) const 
    {
        return ex_new PropertyInstance<MEMBER_T> ( ex_new MemberProperty <CLASS_T,MEMBER_T>(*this),
                                                   _pObject );
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual const string_id_t& typeName () const { 
        return TypeTraits<MEMBER_T>::type_name();
    } 

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual void* getValuePtr ( void* _pObject ) 
    { 
        // NOTE: the TYPE_GET_SET member-property will have NULL member-ptr. 
        if ( m_memberPtr == NULL )
            return _pObject;
        return &(((CLASS_T*)_pObject)->*m_memberPtr); 
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual void get ( void* _pObject, void* _pValueOut )
    { 
        if ( m_fnGet.isValid() ) {
            m_fnGet.set_object((CLASS_T*)_pObject);
            m_fnGet((MEMBER_T*)_pValueOut);
        }
        else {
            PropertyGetSet<MEMBER_T>()( reinterpret_cast<MEMBER_T*>(_pValueOut), &(((CLASS_T*)_pObject)->*m_memberPtr) );
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual void set ( void* _pObject, void* _pValueIn ) 
    { 
        if ( m_fnSet.isValid() ) {
            m_fnSet.set_object((CLASS_T*)_pObject);
            m_fnSet( *reinterpret_cast<MEMBER_T*>(_pValueIn) );
        }
        else {
            PropertyGetSet<MEMBER_T>()( &(((CLASS_T*)_pObject)->*m_memberPtr), reinterpret_cast<MEMBER_T*>(_pValueIn) );
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
        return PropertyEqualSelector<MEMBER_T>( reinterpret_cast<MEMBER_T*>(_lhs), 
                                                reinterpret_cast<MEMBER_T*>(_rhs), 
                                                intToType< TypeTraits<MEMBER_T>::isAtomic || TypeTraits<MEMBER_T>::isString || TypeTraits<MEMBER_T>::isEnum >() );
    } 

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    virtual size_t typeSize () const { return sizeof(MEMBER_T); } 
    virtual bool isEnum () const { return TypeTraits<MEMBER_T>::isEnum; } 
    virtual bool isAtomic () const { return TypeTraits<MEMBER_T>::isAtomic; } 
    virtual bool isClass () const { return !TypeTraits<MEMBER_T>::isArith && !TypeTraits<MEMBER_T>::isString && !TypeTraits<MEMBER_T>::isEnum; } 
    virtual bool isStandaloneClass () const { return isClass() && !isPropertyClass(); } 
    virtual bool isPropertyClass () const { return typeop::IsSuperSubClass<PropertyObject,MEMBER_T>::Result; } 

    virtual enum_infos_t enumInfos () const { 
        enum_infos_t info;
        enum_info_list ( TypeTraits<MEMBER_T>::type_name(), &info );
        return info;
    } 

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    member_ptr_t    m_memberPtr;
    get_functor_t   m_fnGet;
    set_functor_t   m_fnSet;

}; // end class MemberProperty 

///////////////////////////////////////////////////////////////////////////////
// helper functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: CreateMemberProperty
// NOTE: the template non-parameter instanciation can only be used in template function, 
//       no way to write MemberProperty ( xxx, xxx ) without parameter declaration, that's 
//       why we have a wrapper function here.
// NOTE: usally the function been called by static member data, and free the allocated memory
//       in destructor. But unfortunately static member's destructor is right after MemMng, 
//       so if static data use this, it can only use NoManaged<xxxAllocator>::TAllocator
// ------------------------------------------------------------------ 

template < template <class> class TAllocator_T, typename CLASS_T, typename MEMBER_T >
INLINE PropertyBase* CreateMemberProperty ( const char* _propertyID,
                                            const char* _propertyName, 
                                            MEMBER_T CLASS_T::* _memberPtr, 
                                            uint32 _flags = PropAttr::none, 
                                            typename MemberProperty<CLASS_T,MEMBER_T>::pfn_get_t _pfnGet = NULL, 
                                            typename MemberProperty<CLASS_T,MEMBER_T>::pfn_set_t _pfnSet = NULL ) 
{
    typedef MemberProperty <CLASS_T,MEMBER_T> property_t;
    property_t* pProperty = TAllocator_T<property_t>::Malloc (1);
    ex_new_in (pProperty) property_t ();
    pProperty->setPropID(_propertyID);
    pProperty->setPropName(_propertyName);
    pProperty->setAttributes(_flags);
    pProperty->setMemberPtr(_memberPtr);
    pProperty->setFnGet(_pfnGet);
    pProperty->setFnSet(_pfnSet);
    return pProperty;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < template <class> class TAllocator_T >
INLINE void DestroyProperty ( PropertyBase* _pProperty ) 
{
    _pProperty->~PropertyBase(); // call destroy class first.
    TAllocator_T<PropertyBase>::Free (_pProperty);
}

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END MEMBERPROPERTY_H_1266930297
// #################################################################################


