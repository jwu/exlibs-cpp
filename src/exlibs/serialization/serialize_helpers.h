// ======================================================================================
// File         : serialize_helpers.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 15:40:06 PM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef SERIALIZE_HELPERS_H_1281858007
#define SERIALIZE_HELPERS_H_1281858007
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// fwd-decl
///////////////////////////////////////////////////////////////////////////////

template < typename T > class SerializeHelper;
template < typename T, uint SIZE > class SerializeHelper <T[SIZE]>;

///////////////////////////////////////////////////////////////////////////////
// T_ObjSerialize function defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace _private { 
// ######################### 

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    // 0: atomic
    template < typename T >
    result_t SerializeSelector( ISerializeNode* _pNode, const char* _propertyName, T* _pValue, intToType<0> )
    {
        if ( _pNode->isLoading () )
        {
            return _pNode->getAttr ( _propertyName, _pValue );
        }
        else
        {
            _pNode->setAttr ( _propertyName, *_pValue );
            return EResult::ok;
        }
    }

    // 1: enums
    template < typename T >
    result_t SerializeSelector( ISerializeNode* _pNode, const char* _propertyName, T* _pValue, intToType<1> )
    {
        if ( _pNode->isLoading () )
        {
            return _pNode->getAttr ( _propertyName, (int*)_pValue );
        }
        else
        {
            _pNode->setAttr ( _propertyName, int(*_pValue) );
            return EResult::ok;
        }
    }

    // 2: classes
    template < typename T >
    result_t SerializeSelector( ISerializeNode* _pNode, const char* _propertyName, T* _pValue, intToType<2> )
    {
        ISerializeNode* pChildNode = NULL;

        //
        if ( _pNode->isLoading () )
        {
            pChildNode = _pNode->nextChild(_propertyName);
            if ( pChildNode == NULL )
                return EResult::not_found;
        }
        else
        {
            pChildNode = _pNode->newChild(_propertyName);
            ex_assert_slow ( pChildNode, "Failed create %s child node", _propertyName );
            if ( pChildNode == NULL )
                return EResult::create_failed;
        }

        //
        _pValue->serialize ( pChildNode );
        return EResult::ok;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    // isAtomic == true
    template < typename T, uint SIZE >
    result_t SerializeArraySelector( ISerializeNode* _pNode, const char* _propertyName, T(*_pValue)[SIZE] )
    {
        ISerializeNode* pChildNode = NULL;

        //
        if ( _pNode->isLoading () )
        {
            pChildNode = _pNode->nextChild(_propertyName);
            if ( pChildNode == NULL )
                return EResult::not_found;
        }
        else
        {
            pChildNode = _pNode->newChild(_propertyName);
            ex_assert_slow ( pChildNode, "Failed create %s child node", _propertyName );
            if ( pChildNode == NULL )
                return EResult::create_failed;
        }

        //
        for ( uint i = 0; i < SIZE; ++i ) {
            ex_check ( SerializeHelper<T>::serialize ( pChildNode, ("idx_"+to_str<dec>(i)).c_str(), (*_pValue)+i ) == EResult::ok, "failed to serialize element %d", i );
        }

        return EResult::ok;
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    static result_t SerializeBuffer ( ISerializeNode* _pNode, const char* _propertyName, void** _ppValue, uint _bytes )
    {
        if ( _pNode->isLoading () )
        {
            return _pNode->getAttr ( _propertyName, _ppValue, _bytes );
        }
        else
        {
            _pNode->setAttr ( _propertyName, *_ppValue, _bytes );
            return EResult::ok;
        }
    }

// ######################### 
} // end namespace _private 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class SerializeHelper<T> 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class SerializeHelper
{
public:

    enum { Sel = (TypeTraits<T>::isAtomic || TypeTraits<T>::isString) ? 0 : (TypeTraits<T>::isEnum ? 1 : 2) };

    INLINE static result_t serialize ( ISerializeNode* _pNode, const char* _propertyName, T* _pValue )
    {
        // static const int sel = (TypeTraits<T>::isAtomic || TypeTraits<T>::isString) ? 0 : (TypeTraits<T>::isEnum ? 1 : 2);
        return _private::SerializeSelector <T> ( _pNode, _propertyName, _pValue, intToType<Sel> () );
    }

}; // end class SerializeHelper 

///////////////////////////////////////////////////////////////////////////////
// class SerializeHelper <T[SIZE]> 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, uint SIZE >
class SerializeHelper <T[SIZE]>
{
public:

    INLINE static result_t serialize ( ISerializeNode* _pNode, const char* _propertyName, T(*_pValue)[SIZE] )
    {
        return _private::SerializeArraySelector <T,SIZE> ( _pNode, _propertyName, _pValue );
    }

}; // end class SerializeHelper 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE static result_t Serialize ( ISerializeNode* _pNode, const char* _propertyName, T* _pValue )
{
    return SerializeHelper<T>::serialize ( _pNode, _propertyName, _pValue );
}

// ######################### 
} // end namespace ex 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define EX_SERIALIZE( _pSerializeNode, _propertyName, _value ) \
        ex_check( ::ex::Serialize ( _pSerializeNode, _propertyName, &(_value) ) == ::ex::EResult::ok, "Failed to load property: %s", _propertyName );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define EX_SERIALIZE_BUFFER( _pSerializeNode, _propertyName, _pBuffer, _bytes ) \
        ex_check( ::ex::_private::SerializeBuffer ( _pSerializeNode, _propertyName, &(_pBuffer), _bytes ) == ::ex::EResult::ok, "Failed to load property: %s", _propertyName );

// #################################################################################
#endif // END SERIALIZE_HELPERS_H_1281858007
// #################################################################################
