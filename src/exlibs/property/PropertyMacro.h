// ======================================================================================
// File         : PropertyMacro.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:23:05 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PROPERTYMACRO_H_1250526193
#define PROPERTYMACRO_H_1250526193
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

// ..

///////////////////////////////////////////////////////////////////////////////
// enum property decl/def
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: EX_DECL_ENUM_PROPERTY_BEGIN 
// ------------------------------------------------------------------ 

#define EX_DECL_ENUM_PROPERTY_BEGIN(dll_export,_enumTypeName)  \
template <> class TypeTraits<_enumTypeName> : public _private::TypeTraitsImpl<_enumTypeName> \
{ \
public: \
    static INLINE const string_id_t& type_name () { static const string_id_t strID(#_enumTypeName); return strID; } \
    enum { isEnum = true }; \
}; \
namespace ns_##_enumTypeName { \
    extern dll_export const char* enum_to_str( _enumTypeName _enum ); \
    typedef ::ex::Pair<int,const char*> pair_t; \
    const pair_t list [] = {

// ------------------------------------------------------------------ 
// Desc: EX_DECL_ENUM_PROPERTY_BEGIN_NS 
// ------------------------------------------------------------------ 

#define EX_DECL_ENUM_PROPERTY_BEGIN_NS(dll_export,_enumTypeName)  \
namespace ex { \
    EX_DECL_ENUM_PROPERTY_BEGIN(dll_export,_enumTypeName)

// ------------------------------------------------------------------ 
// Desc: EX_ADD_ENUM
// ------------------------------------------------------------------ 

#define EX_ADD_ENUM(_enum) pair_t(int(_enum),#_enum),

// ------------------------------------------------------------------ 
// Desc: EX_ADD_ENUM_2
// ------------------------------------------------------------------ 

#define EX_ADD_ENUM_2(_enum,_name) pair_t(int(_enum),_name),

// ------------------------------------------------------------------ 
// Desc: EX_DECL_ENUM_PROPERTY_END
// ------------------------------------------------------------------ 

#define EX_DECL_ENUM_PROPERTY_END()                         \
    }; /*end list []*/                                      \
} /*end ns_Enum*/

// ------------------------------------------------------------------ 
// Desc: EX_DECL_ENUM_PROPERTY_END_NS
// ------------------------------------------------------------------ 

#define EX_DECL_ENUM_PROPERTY_END_NS()  \
    EX_DECL_ENUM_PROPERTY_END()         \
} /*end namespace ex*/

// ------------------------------------------------------------------ 
// Desc: EX_DEF_ENUM_PROPERTY
// ------------------------------------------------------------------ 

#define EX_DEF_ENUM_PROPERTY(_enumTypeName)                 \
namespace ns_##_enumTypeName {                              \
    const char* enum_to_str( _enumTypeName _enum )          \
    {                                                       \
        for ( int i = 0; i < EX_ARRAY_COUNT(list); ++i )    \
        {                                                   \
            if ( list[i].first == int(_enum)  )             \
                return list[i].second;                      \
        }                                                   \
        return "unknown";                                   \
    } /*end enum_to_str*/                                   \
} /*end ns_Enum*/

// ------------------------------------------------------------------ 
// Desc: EX_DEF_ENUM_PROPERTY_NS
// ------------------------------------------------------------------ 

#define EX_DEF_ENUM_PROPERTY_NS(_enumTypeName) \
    namespace ex { EX_DEF_ENUM_PROPERTY(_enumTypeName) }

///////////////////////////////////////////////////////////////////////////////
// property instance decl/def
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: EX_DEF_PROPERTY_INSTANCE 
// ------------------------------------------------------------------ 

#define EX_DEF_PROPERTY_INSTANCE(_className)                                                                            \
    template <>                                                                                                         \
    class PropertyInstance<_className> : public ::ex::PropertyInstance< ::ex::PropertyObject >                          \
    {                                                                                                                   \
        typedef ::ex::PropertyInstance< ::ex::PropertyObject > base_t;                                                  \
        typedef PropertyInstance<_className>                   self_t;                                                  \
    public:                                                                                                             \
        PropertyInstance ( PropertyBase* _pProperty, void* _pValue )                                                    \
            : base_t ( _pProperty, _pValue )                                                                            \
        {                                                                                                               \
        }                                                                                                               \
    };

// ------------------------------------------------------------------ 
// Desc: EX_DEF_PROPERTY_INSTANCE_NS 
// ------------------------------------------------------------------ 

#define EX_DEF_PROPERTY_INSTANCE_NS(_className) \
    namespace ex { EX_DEF_PROPERTY_INSTANCE (_className) }

// ------------------------------------------------------------------ 
// Desc: EX_DECL_ENGINE_OBJECT 
// ------------------------------------------------------------------ 

#define EX_DECL_PROPERTY_OBJECT(_selfType,_baseType) \
        EX_DEF_RUNTIME_CLASS(_selfType,_baseType); \
        __EX_DEF_PROPERTY_OBJECT();

// ------------------------------------------------------------------ 
// Desc: __EX_DEF_PROPERTY_OBJECT
// ------------------------------------------------------------------ 

#define __EX_DEF_PROPERTY_OBJECT() \
    public:                                                                                                         \
        static void staticRegisterProperties();                                                                     \
        static const ::ex::PropertiesDescriptor* staticGetDescriptor ()                                             \
        {                                                                                                           \
            ex_assert ( s_initialized, "object should be inited" );                                                 \
            return &(self_t::s_descriptor);                                                                         \
        }                                                                                                           \
        virtual void registerProperties () const { self_t::staticRegisterProperties(); }                            \
        virtual ::ex::PropertiesDescriptor* getDescriptor () { return const_cast< ::ex::PropertiesDescriptor* >(self_t::staticGetDescriptor()); } \
        virtual const ::ex::PropertiesDescriptor* getDescriptor () const { return self_t::staticGetDescriptor(); }  \
    protected:                                                                                                      \
        static bool s_initialized;                                                                                  \
        static ::ex::PropertiesDescriptor s_descriptor;                                                             \
        /* ---------- back to private at the end ---------- */                                                      \
    private:

// ------------------------------------------------------------------ 
// Desc: EX_DEF_PROPERTIES_BEGIN
// ------------------------------------------------------------------ 

#define EX_DEF_PROPERTIES_BEGIN(_className)                         \
    EX_DEF_PROPERTY_INSTANCE(_className)                            \
    __EX_DEF_PROPERTIES_BEGIN(_className)

// ------------------------------------------------------------------ 
// Desc: EX_DEF_PROPERTIES_BEGIN_NS
// NOTE: this is for those class defined outside the ex namespace.
// ------------------------------------------------------------------ 

#define EX_DEF_PROPERTIES_BEGIN_NS(_className)                      \
    EX_DEF_PROPERTY_INSTANCE_NS(_className)                         \
    __EX_DEF_PROPERTIES_BEGIN(_className)

// ------------------------------------------------------------------ 
// Desc: __EX_DEF_PROPERTIES_BEGIN
// ------------------------------------------------------------------ 

#define __EX_DEF_PROPERTIES_BEGIN(_className)                       \
    ::ex::PropertiesDescriptor _className::s_descriptor;            \
    bool _className::s_initialized(false);                          \
    void _className::staticRegisterProperties()                     \
    {                                                               \
        if (s_initialized)                                          \
            return;                                                 \
                                                                    \
        base_t::staticRegisterProperties();                         \
        typedef _className object_t;                                \
        s_descriptor.setClassName ( _className::className() );      \
        s_initialized = true;


// ------------------------------------------------------------------ 
// Desc: EX_DEF_PROPERTIES_END
// ------------------------------------------------------------------ 

#define EX_DEF_PROPERTIES_END()                                     \
        s_descriptor.setParentDescriptor( &base_t::s_descriptor );  \
    }

// NOTE: if needed, we can have EX_REGISTER_VALUE_PROPERTY which use CreateValueProperty for those non-member values.

///////////////////////////////////////////////////////////////////////////////
// property register
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: EX_REGISTER_PROPERTY
// ------------------------------------------------------------------ 

#define EX_REGISTER_PROPERTY( _prop_name, _member ) \
{ \
    ::ex::PropertyBase* pProperty = ::ex::CreateMemberProperty< ::ex::NoManaged< ::ex::NullType>::TAllocator > ( #_member, _prop_name, &object_t::_member ); \
    ::ex::PropertiesDescriptor::addProperty( &(s_descriptor.properties()), pProperty ); \
}

// ------------------------------------------------------------------ 
// Desc: EX_REGISTER_PROPERTY_ATTRS
// ------------------------------------------------------------------ 

#define EX_REGISTER_PROPERTY_ATTRS( _prop_name, _member, _attr_flags ) \
{ \
    ::ex::PropertyBase* pProperty = ::ex::CreateMemberProperty< ::ex::NoManaged< ::ex::NullType>::TAllocator > ( #_member, _prop_name, &object_t::_member, _attr_flags ); \
    ::ex::PropertiesDescriptor::addProperty( &(s_descriptor.properties()), pProperty ); \
}

// ------------------------------------------------------------------ 
// Desc: EX_REGISTER_PROPERTY_GET_SET
// ------------------------------------------------------------------ 

#define EX_REGISTER_PROPERTY_GET_SET( _prop_name, _member, _attr_flags, _fpn_get, _fpn_set ) \
{ \
    ::ex::PropertyBase* pProperty = ::ex::CreateMemberProperty< ::ex::NoManaged< ::ex::NullType>::TAllocator > ( #_member, _prop_name, &object_t::_member, _attr_flags, _fpn_get, _fpn_set ); \
    ::ex::PropertiesDescriptor::addProperty( &(s_descriptor.properties()), pProperty ); \
}

// KEEPME: it is dangerous to use pure get/set in property with gui. 
//         because the gui can't hold the return value (a local value) unless it is a member-ptr can hold in somewhere long enough { 
// TODO: it is possible to use pure get/set if we allocate a membory to store value from get/set.
// // ------------------------------------------------------------------ 
// // Desc: EX_REGISTER_PROPERTY_TYPE_GET_SET
// // ------------------------------------------------------------------ 

#if 0
#define EX_REGISTER_PROPERTY_TYPE_GET_SET( _prop_name, _type, _attr_flags, _fpn_get, _fpn_set ) \
{ \
    uint32 attr = _attr_flags; \
    if ( _fpn_get == NULL ) \
    { \
        ex_warning( "can't register type-only property with NULL get-function-ptr" ); \
        return; \
    } \
    else if ( _fpn_set == NULL ) \
    { \
        attr |= PropAttr::readonly; \
    } \
    ::ex::PropertyBase* pProperty = ::ex::CreateMemberProperty< ::ex::NoManaged<::ex::NullType>::TAllocator, \
                                                                   object_t, \
                                                                   _type > ( _prop_name, NULL, attr, _fpn_get, _fpn_set ); \
    ::ex::PropertiesDescriptor::addProperty( &(s_descriptor.properties()), pProperty ); \
}
#endif
// } KEEPME end 

// #################################################################################
#endif // END PROPERTYMACRO_H_1250526193
// #################################################################################
