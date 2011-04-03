// ======================================================================================
// File         : PropertyBase.h
// Author       : Wu Jie 
// Last Change  : 01/25/2010 | 00:44:38 AM | Monday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PROPERTYBASE_H_1264351485
#define PROPERTYBASE_H_1264351485
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// include
///////////////////////////////////////////////////////////////////////////////

#include "PropertyInstanceBase.h"

// TODO:
// Consider CDebug class for debugging

// ######################### 
namespace ex { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

namespace PropAttr {
    enum Enum {
        none            = 0,
        readonly        = 1 << 0,
        hide            = 1 << 1,
        no_serialize    = 1 << 2,
        editor_only     = 1 << 3,
    }; // end Enum
} // end namespace

///////////////////////////////////////////////////////////////////////////////
// class PropertyBase 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL PropertyBase
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef PropertyBase self_t; 
    typedef String<char,NoManaged<NullType>::TAllocator> string_nomng_t;
    typedef List<Pair<int,const char*> > enum_infos_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    PropertyBase ()
        : m_propID ()
        , m_propName ()
        , m_attrFlags (PropAttr::none)
        , m_pMin (NULL)
        , m_pMax (NULL)
    {
    }

    PropertyBase ( const PropertyBase& _property )
        : m_propID (_property.m_propID)
        , m_propName (_property.m_propName)
        , m_attrFlags (_property.m_attrFlags)
        , m_pMin (_property.m_pMin)
        , m_pMax (_property.m_pMax)
    {
    }

    virtual ~PropertyBase ()
    {
    }

    // init member
    void setPropID ( const char* _propertyID ) { m_propID.assign(_propertyID); }
    void setPropName ( const char* _propertyName ) { m_propName.assign(_propertyName); }
    void setAttributes ( uint32 _attrFlags ) { m_attrFlags = _attrFlags; }
    void setMin ( void* _pMin ) { m_pMin = _pMin; }
    void setMax ( void* _pMax ) { m_pMax = _pMax; }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ======================================================== 
    // non-virtual 
    // ======================================================== 

    //
    INLINE PropertyInstanceBase::smart_ptr_t createPropertyInstance_sp ( void* _pObject ) const 
    { 
        return PropertyInstanceBase::smart_ptr_t ( createPropertyInstance(_pObject) ); 
    }

    //
    INLINE const string_nomng_t& propID () const { return m_propID; }
    INLINE const string_nomng_t& propName () const { return m_propName; }
    INLINE uint32 attributes () const { return m_attrFlags; }

    // ======================================================== 
    // virtual  
    // ======================================================== 

    //
    virtual result_t serializeProperty ( ISerializeNode* _pNode, void* _pObject ) { return EResult::ok; }
    virtual PropertyInstanceBase* createPropertyInstance ( void* _pObject ) const { return NULL; }

    // value op
    virtual const string_id_t& typeName () const { static string_id_t sid("unknown"); return sid; }
    virtual void* getValuePtr ( void* _pObject ) { return NULL; }
    virtual void get ( void* _pObject, void* _pValueOut ) { ex_warning( "can't call base function get" ); }
    virtual void set ( void* _pObject, void* _pValueIn ) { ex_warning( "can't call base function set" ); }
    virtual bool hasSetCallback () const { return false; } 
    virtual bool hasGetCallback () const { return false; } 

    // original value op 
    virtual bool isEqual ( void* _lhs, void* _rhs ) const { ex_warning( "can't call base function isEqual" ); return false; }

    // type op
    virtual size_t typeSize () const { return 0; } 
    virtual bool isEnum () const { return false; } 
    virtual bool isAtomic () const { return false; }
    virtual bool isClass () const { return false; } 
    virtual bool isStandaloneClass () const { return false; } 
    virtual bool isPropertyClass () const { return false; } 

    virtual enum_infos_t enumInfos () const { return enum_infos_t(); } 

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    // NOTE: the PropertyBase is mainly handled in NoManaged scope except clone one in PropertyInstance,
    string_nomng_t  m_propID; // NOTE: because XmlNode's getAttr algorithm, we use string_t instead of string_id_t here. 
    string_nomng_t  m_propName;
    uint32          m_attrFlags;
    void*           m_pMin;
    void*           m_pMax;

}; // end class PropertyBase

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END PROPERTYBASE_H_1264351485
// #################################################################################


