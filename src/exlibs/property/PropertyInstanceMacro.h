// ======================================================================================
// File         : PropertyInstanceMacro.h
// Author       : Wu Jie 
// Last Change  : 02/23/2010 | 11:12:04 AM | Tuesday,February
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PROPERTYINSTANCEMACRO_H_1266894764
#define PROPERTYINSTANCEMACRO_H_1266894764
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE PropertyInstanceBase* CreateValuePropertyInstance ( const char* _propertyName,  
                                                              T* _pValue, 
                                                              uint32 _attributes,
                                                              T* _pMin = NULL, 
                                                              T* _pMax = NULL,
                                                              typename ValueProperty<T>::pfn_get_t _pfnGet = NULL,
                                                              typename ValueProperty<T>::pfn_set_t _pfnSet = NULL )
{
    ValueProperty<T>* pProp = ex_new ValueProperty<T>();
    pProp->setPropID(_propertyName); // NOTE: the sub-property doesn't care about ID.
    pProp->setPropName(_propertyName);
    pProp->setAttributes(_attributes);
    pProp->setValuePtr(_pValue);
    pProp->setFnGet(_pfnGet);
    pProp->setFnSet(_pfnSet);
    pProp->setMin(_pMin);
    pProp->setMax(_pMax);
    return ex_new PropertyInstance<T> ( pProp, (void*)(_pValue) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename CLASS_T, typename MEMBER_T >
INLINE PropertyInstanceBase* CreateMemberPropertyInstance ( const char* _propertyName, 
                                                               CLASS_T* _pClass, 
                                                               MEMBER_T CLASS_T::* _memberPtr, 
                                                               uint32 _attributes,
                                                               typename MemberProperty<CLASS_T,MEMBER_T>::pfn_get_t _pfnGet = NULL,
                                                               typename MemberProperty<CLASS_T,MEMBER_T>::pfn_set_t _pfnSet = NULL )
{
    MemberProperty <CLASS_T,MEMBER_T>* pProp = ex_new MemberProperty <CLASS_T,MEMBER_T>();
    pProp->setPropID(_propertyName); // NOTE: the sub-property doesn't care about ID.
    pProp->setPropName(_propertyName);
    pProp->setAttributes(_attributes);
    pProp->setMemberPtr(_memberPtr);
    pProp->setFnGet(_pfnGet);
    pProp->setFnSet(_pfnSet);
    return ex_new PropertyInstance<MEMBER_T> ( pProp, (void*)(_pClass) );
}

// ------------------------------------------------------------------ 
// Desc: EX_DEF_PROPERTY_INSTANCE_BEGIN
// ------------------------------------------------------------------ 

#define EX_DEF_PROPERTY_INSTANCE_BEGIN(_className) \
    EX_PROPERTY_INSTANCE_TYPEDEFS(_className) \
public: \
    PropertyInstance ( PropertyBase* _pProperty, void* _pObject ) \
        : base_t ( _pProperty, _pObject ) \
    { \
        class_t* pClass = reinterpret_cast<class_t*>(_pProperty->getValuePtr(_pObject));

// ------------------------------------------------------------------ 
// Desc: EX_DEF_PROPERTY_INSTANCE_END
// ------------------------------------------------------------------ 

#define EX_DEF_PROPERTY_INSTANCE_END() \
    }

// ------------------------------------------------------------------ 
// Desc: EX_PROPERTY_INSTANCE_TYPEDEFS 
// ------------------------------------------------------------------ 

#define EX_PROPERTY_INSTANCE_TYPEDEFS(_className) \
    typedef _className class_t; \
    typedef PropertyInstanceBase base_t; \
    typedef PropertyInstance<class_t> self_t; \
    /* ---------- back to private at the end ---------- */ \
private:

// ------------------------------------------------------------------ 
// Desc: EX_REGISTER_SUB_PROPERTY_VALUE_PTR  
// ------------------------------------------------------------------ 

#define EX_REGISTER_SUB_PROPERTY_VALUE_PTR( _NAME, _VALUE_PTR, _ATTRS ) \
    {\
        PropertyInstanceBase* pPropInstance = CreateValuePropertyInstance( _NAME, _VALUE_PTR, _ATTRS | _pProperty->attributes() ); \
        pPropInstance->setBase(this); \
        m_subProps.push_back ( PropertyInstanceBase::smart_ptr_t ( pPropInstance ) ); \
    }

// ------------------------------------------------------------------ 
// Desc: EX_REGISTER_SUB_PROPERTY_VALUE_PTR_MIN_MAX  
// ------------------------------------------------------------------ 

#define EX_REGISTER_SUB_PROPERTY_VALUE_PTR_MIN_MAX( _NAME, _VALUE_PTR, _ATTRS, _TYPE, _MIN, _MAX ) \
    {\
        static _TYPE min = _MIN; \
        static _TYPE max = _MAX; \
        PropertyInstanceBase* pPropInstance = CreateValuePropertyInstance( _NAME, _VALUE_PTR, _ATTRS | _pProperty->attributes(), &min, &max ); \
        pPropInstance->setBase(this); \
        m_subProps.push_back ( PropertyInstanceBase::smart_ptr_t ( pPropInstance ) ); \
    }

// ------------------------------------------------------------------ 
// Desc: EX_REGISTER_SUB_PROPERTY_MEMBER_PTR  
// regiter sub-property that the member type is deduce by member_ptr.
// you can't provide NULL member_ptr or the member type can't be deduced.
// you can provide NULL get/set function pointer because the member_ptr will do reset of the things 
// ------------------------------------------------------------------ 

#define EX_REGISTER_SUB_PROPERTY_MEMBER_PTR( _NAME, _MB_PTR, _ATTRS, _FPN_GET, _FPN_SET ) \
    {\
        PropertyInstanceBase* pPropInstance = CreateMemberPropertyInstance<class_t>( _NAME, pClass, _MB_PTR, _ATTRS | _pProperty->attributes(), _FPN_GET, _FPN_SET ); \
        pPropInstance->setBase(this); \
        m_subProps.push_back ( PropertyInstanceBase::smart_ptr_t ( pPropInstance ) ); \
    }

// KEEPME: it is dangerous to use pure get/set in property with gui. 
//         because the gui can't hold the return value (a local value) unless it is a member-ptr can hold in somewhere long enough { 
// TODO: it is possible to use pure get/set if we allocate a membory to store value from get/set.
// // ------------------------------------------------------------------ 
// // Desc: EX_REGISTER_SUB_PROPERTY_TYPE_GET_SET  
// // regiter sub-property by specific member type
// // you can provide NULL member_ptr, the get/set function will help access data. 
// // if you provide NULL set function and your member_ptr is NULL, the property will be readonly by add readonly-attribute.
// // if you provide NULL get function and your member_ptr is NULL, it will report and error, and prevent you register this property
// // ------------------------------------------------------------------ 

#if 0
#define EX_REGISTER_SUB_PROPERTY_TYPE_GET_SET( _NAME, _TYPE, _ATTRS, _FPN_GET, _FPN_SET ) \
    {\
        uint32 attr = _ATTRS; \
        if ( _FPN_GET == NULL ) \
        { \
            ex_warning( "can't register type-only property with NULL get-function-ptr" ); \
            return; \
        } \
        else if ( _FPN_SET == NULL ) \
        { \
            attr |= PropAttr::readonly; \
        } \
        PropertyInstanceBase* pPropInstance = CreateValuePropertyInstance<_TYPE>( _NAME, NULL, attr | _pProperty->attributes(), _FPN_GET, _FPN_SET ); \
        pPropInstance->setBase(this); \
        m_subProps.push_back ( PropertyInstanceBase::smart_ptr_t ( pPropInstance ) ); \
    }
#endif
// } KEEPME end 

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END PROPERTYINSTANCEMACRO_H_1266894764
// #################################################################################

