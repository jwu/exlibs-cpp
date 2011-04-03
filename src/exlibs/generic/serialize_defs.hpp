// ======================================================================================
// File         : GenericTypeSerialize.hpp
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:25:27 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef GENERICTYPESERIALIZE_HPP_1250526329
#define GENERICTYPESERIALIZE_HPP_1250526329
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// Color3u
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE void Color3u::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "r", r );
    EX_SERIALIZE ( _pNode, "g", g );
    EX_SERIALIZE ( _pNode, "b", b );
}

///////////////////////////////////////////////////////////////////////////////
// Color4u
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE void Color4u::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "r", r );
    EX_SERIALIZE ( _pNode, "g", g );
    EX_SERIALIZE ( _pNode, "b", b );
    EX_SERIALIZE ( _pNode, "a", a );
}

///////////////////////////////////////////////////////////////////////////////
// Color3f
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE void Color3f::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "r", r );
    EX_SERIALIZE ( _pNode, "g", g );
    EX_SERIALIZE ( _pNode, "b", b );
}

///////////////////////////////////////////////////////////////////////////////
// Color4f
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE void Color4f::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "r", r );
    EX_SERIALIZE ( _pNode, "g", g );
    EX_SERIALIZE ( _pNode, "b", b );
    EX_SERIALIZE ( _pNode, "a", a );
}

///////////////////////////////////////////////////////////////////////////////
// Vector2
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void Vector2<T>::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "x", x() );
    EX_SERIALIZE ( _pNode, "y", y() );
}

///////////////////////////////////////////////////////////////////////////////
// Vector3
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void Vector3<T>::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "x", x() );
    EX_SERIALIZE ( _pNode, "y", y() );
    EX_SERIALIZE ( _pNode, "z", z() );
}

///////////////////////////////////////////////////////////////////////////////
// Matrix2
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void Matrix2<T>::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "m00", get(0,0) );
    EX_SERIALIZE ( _pNode, "m01", get(0,1) );
    EX_SERIALIZE ( _pNode, "m10", get(1,0) );
    EX_SERIALIZE ( _pNode, "m11", get(1,1) );
}

///////////////////////////////////////////////////////////////////////////////
// Matrix4
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void Matrix4<T>::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "m00", m00 );
    EX_SERIALIZE ( _pNode, "m01", m01 );
    EX_SERIALIZE ( _pNode, "m02", m02 );
    EX_SERIALIZE ( _pNode, "m03", m03 );
    EX_SERIALIZE ( _pNode, "m10", m10 );
    EX_SERIALIZE ( _pNode, "m11", m11 );
    EX_SERIALIZE ( _pNode, "m12", m12 );
    EX_SERIALIZE ( _pNode, "m13", m13 );
    EX_SERIALIZE ( _pNode, "m20", m20 );
    EX_SERIALIZE ( _pNode, "m21", m21 );
    EX_SERIALIZE ( _pNode, "m22", m22 );
    EX_SERIALIZE ( _pNode, "m23", m23 );
    EX_SERIALIZE ( _pNode, "m30", m30 );
    EX_SERIALIZE ( _pNode, "m31", m31 );
    EX_SERIALIZE ( _pNode, "m32", m32 );
    EX_SERIALIZE ( _pNode, "m33", m33 );
}

///////////////////////////////////////////////////////////////////////////////
// Angle
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void Angle<T>::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "radians", m_radians );
}

///////////////////////////////////////////////////////////////////////////////
// Pair
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T1, typename T2 >
INLINE void Pair<T1,T2>::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "first", first );
    EX_SERIALIZE ( _pNode, "second", second );
}

///////////////////////////////////////////////////////////////////////////////
// Array
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, template <class> class TAllocator_T >
void Array<T,TAllocator_T>::serialize ( ISerializeNode* _pNode )
{
    //
    uint size = uint( this->size() );
    EX_SERIALIZE ( _pNode, "size", size );

    //
    if ( _pNode->isLoading() )
    {
        this->clear();
        this->resize (size);
    }

    //
    for ( uint idx = 0; idx < uint(this->size()); ++idx )
    {
        EX_SERIALIZE ( _pNode, ("idx_"+ex::to_str<dec>(idx)).c_str(), (*this)[idx] );
    }
}

///////////////////////////////////////////////////////////////////////////////
// List
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, template <class> class TAllocator_T >
void List<T,TAllocator_T>::serialize ( ISerializeNode* _pNode )
{
    uint size = uint( this->size() );
    EX_SERIALIZE ( _pNode, "size", size );

    //
    if ( _pNode->isLoading() )
    {
        this->clear();
        for ( uint idx = 0; idx < size; ++idx )
        {
            T value;
            EX_SERIALIZE ( _pNode, ("idx_"+ex::to_str<dec>(idx)).c_str(), value );
            this->push_back(value);
        }
    }
    else
    {
        uint idx = 0;
        for ( iterator iter = begin(); iter != end(); ++iter, ++idx )
        {
            EX_SERIALIZE ( _pNode, ("idx_"+ex::to_str<dec>(idx)).c_str(), *iter );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Pool
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, template <class> class TAllocator_T >
void Pool<T,TAllocator_T>::serialize ( ISerializeNode* _pNode )
{
    uint size = uint( this->size() );
    EX_SERIALIZE ( _pNode, "size", size );

    //
    if ( _pNode->isLoading() )
    {
        this->clear();
        for ( uint idx = 0; idx < size; ++idx )
        {
            sz_t pool_index;
            T value;
            EX_SERIALIZE ( _pNode, ("idx_"+ex::to_str<dec>(idx)).c_str(), pool_index );
            EX_SERIALIZE ( _pNode, ("value_"+ex::to_str<dec>(idx)).c_str(), value );
            this->push_at( pool_index, value );
        }
    }
    else
    {
        uint idx = 0;
        for ( iterator iter = begin(); iter != end(); ++iter, ++idx )
        {
            sz_t pool_index = index ( iter );
            EX_SERIALIZE ( _pNode, ("idx_"+ex::to_str<dec>(idx)).c_str(), pool_index );
            EX_SERIALIZE ( _pNode, ("value_"+ex::to_str<dec>(idx)).c_str(), *iter );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// HashMap
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename KEY, 
           typename VALUE, 
           typename HASH_FUNC,
           typename EQUAL_KEY,
           template <class> class TAllocator_T >
void HashMap<KEY,VALUE,HASH_FUNC,EQUAL_KEY,TAllocator_T>::serialize ( ISerializeNode* _pNode )
{
    uint size = uint( this->size() );
    EX_SERIALIZE ( _pNode, "size", size );

    //
    typedef Pair<KEY,VALUE> pair_t;
    if ( _pNode->isLoading() )
    {
        this->clear();
        this->resize(mathop::ceilpow2(size));
        for ( uint idx = 0; idx < size; ++idx )
        {
            pair_t pair;
            EX_SERIALIZE ( _pNode, ("pair_"+ex::to_str<dec>(idx)).c_str(), pair );
            this->insert( pair.first, pair.second );
        }
    }
    else
    {
        // NOTE: the HashMapPool store the early item at the end. save the early
        // item first will help load in right order
        uint idx = 0;
        for ( iterator iter = begin(); iter != end(); ++iter, ++idx )
        {
            pair_t pair( iter.key(), *iter );
            EX_SERIALIZE ( _pNode, ("pair_"+ex::to_str<dec>(idx)).c_str(), pair );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// HashPool
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename KEY, 
           typename VALUE,
           typename HASH_FUNC, 
           typename GET_KEY_FUNC, 
           typename EQUAL_KEY_FUNC,
           template <class> class TAllocator_T >
void HashPool<KEY,VALUE,HASH_FUNC,GET_KEY_FUNC,EQUAL_KEY_FUNC,TAllocator_T>::serialize ( ISerializeNode* _pNode )
{
    // TODO:
}

///////////////////////////////////////////////////////////////////////////////
// HashPool::HashNode
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename KEY, 
           typename VALUE,
           typename HASH_FUNC, 
           typename GET_KEY_FUNC, 
           typename EQUAL_KEY_FUNC,
           template <class> class TAllocator_T >
void HashPool<KEY,VALUE,HASH_FUNC,GET_KEY_FUNC,EQUAL_KEY_FUNC,TAllocator_T>::HashNode::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE( _pNode, "value", value );
    EX_SERIALIZE( _pNode, "hash_next", hash_next );
    EX_SERIALIZE( _pNode, "hash_prev", hash_prev );
}

///////////////////////////////////////////////////////////////////////////////
// String
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, template <class> class TAllocator_T >
INLINE void String<T,TAllocator_T>::serialize ( ISerializeNode* _pNode )
{
    const T* c_str = this->c_str();
    EX_SERIALIZE ( _pNode, "c_str", c_str );
    if ( _pNode->isLoading() ) {
        this->assign( c_str );
    }
}

///////////////////////////////////////////////////////////////////////////////
// StringID
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void StringID<T>::serialize ( ISerializeNode* _pNode )
{
    if ( _pNode->isLoading() ) {
        const char* c_str;
        EX_SERIALIZE ( _pNode, "c_str", c_str );
        this->set( c_str );
    }
    else {
        const char* c_str = this->c_str();
        if ( *this == string_id_t::null )
            c_str = "";
        EX_SERIALIZE ( _pNode, "c_str", c_str );
    }
}

///////////////////////////////////////////////////////////////////////////////
// Path
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, template <class> class TAllocator_T >
INLINE void Path<T,TAllocator_T>::serialize ( ISerializeNode* _pNode )
{
    const char* c_str = this->c_str();
    EX_SERIALIZE ( _pNode, "c_str", c_str );

    //
    if ( _pNode->isLoading() ) {
        this->formatSet( c_str );
    }
}

///////////////////////////////////////////////////////////////////////////////
// ResPath
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T, template <class> class TAllocator_T >
INLINE void ResPath<T,TAllocator_T>::serialize ( ISerializeNode* _pNode )
{
    const char* c_str = this->c_str();
    EX_SERIALIZE ( _pNode, "c_str", c_str );

    //
    if ( _pNode->isLoading() ) {
        this->formatSet( c_str );
    }
}

///////////////////////////////////////////////////////////////////////////////
// DataHolder
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE void DataHolder::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "size", m_size );

    //
    if ( _pNode->isLoading() ) {
        ex_assert_return ( m_data == NULL, /*void*/, "Can't not serialize a DataHolder that already allocated." );
        m_data = ex_malloc ( m_size );
    }
    EX_SERIALIZE_BUFFER ( _pNode, "data", m_data, m_size );
}

///////////////////////////////////////////////////////////////////////////////
// Rect
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void Rect<T>::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "top", m_top );
    EX_SERIALIZE ( _pNode, "left", m_left );
    EX_SERIALIZE ( _pNode, "bot", m_bot );
    EX_SERIALIZE ( _pNode, "right", m_right );
}

///////////////////////////////////////////////////////////////////////////////
// AABRect
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void AABRect<T>::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "lowerBound", m_lowerBound );
    EX_SERIALIZE ( _pNode, "upperBound", m_upperBound );
}

///////////////////////////////////////////////////////////////////////////////
// OBRect
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void OBRect<T>::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "rot", m_rot );
    EX_SERIALIZE ( _pNode, "center", m_center );
    EX_SERIALIZE ( _pNode, "extents", m_extents );
}

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END GENERICTYPESERIALIZE_HPP_1250526329
// #################################################################################

