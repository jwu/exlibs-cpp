// ======================================================================================
// File         : StringID.hpp
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:26:56 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef STRINGID_HPP_1250526418
#define STRINGID_HPP_1250526418
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

#define self_t typename StringID<T>::self_t
#define string_set_t typename StringID<T>::string_set_t
#define str_t typename StringID<T>::str_t

///////////////////////////////////////////////////////////////////////////////
// StringID defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
StringID<T>::StringID() 
    : m_ID( uint32(ex::IndexNone) )
#ifdef EX_DEBUG
    , m_DebugString (NULL)
#endif
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
StringID<T>::StringID( const self_t& _copy )
    : m_ID(_copy.m_ID)
#ifdef EX_DEBUG
    , m_DebugString (_copy.m_DebugString)
#endif
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
StringID<T>::StringID( const char* _str )
{
    this->set(_str);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
StringID<T>::StringID( const str_t& _string )
{
    this->set(_string);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
StringID<T>::~StringID() 
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE bool StringID<T>::isValid () const 
{
    return m_ID != uint32(ex::IndexNone); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void StringID<T>::set ( const char* _str )
{
    if ( _str == NULL || ex::str::cmp(_str,"") == 0 )
    {
        m_ID = uint32(ex::IndexNone); 
    }
    else
    {
        Pair< string_set_t::sz_t, result_t > result_pair = StringID<T>::s_pStringSet->insert(_str);
        m_ID = uint32(result_pair.first);

        ex_assert_slow( ex::str::cmp(this->GetString().c_str(),_str) == 0, "raw string is different" );
    }
#ifdef EX_DEBUG
    m_DebugString = this->c_str();
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void StringID<T>::set ( const str_t& _string )
{
    this->set(_string.c_str());
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE void StringID<T>::set ( const self_t& _copy )
{
    m_ID = _copy.m_ID;
#ifdef EX_DEBUG
    m_DebugString = _copy.m_DebugString;
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE const str_t& StringID<T>::GetString() const
{
    if ( isValid() )
        return *(StringID<T>::s_pStringSet->to_iter( m_ID ));
    else
        return String<T>::null;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE const T* StringID<T>::c_str() const 
{
    if ( isValid() )
        return this->GetString().c_str(); 
    else
        return NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE self_t& StringID<T>::operator = ( const T* _str )
{
    this->set(_str);
    return (*this);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE self_t& StringID<T>::operator = ( const str_t& _string )
{
    this->set(_string);
    return (*this);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE self_t& StringID<T>::operator = ( const self_t& _copy )
{
    this->set(_copy);
    return (*this);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE bool StringID<T>::operator == ( const self_t& _string_id ) const
{
    ex_assert_slow( (GetString() == _string_id.GetString()) == (m_ID == _string_id.m_ID), 
                    "The debug string is not the same (%s != %s)", 
                    GetString().c_str(), 
                    _string_id.GetString().c_str() );
    return (this->m_ID == _string_id.m_ID);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
INLINE bool StringID<T>::operator != ( const self_t& _string_id ) const
{
    return !((*this) == _string_id);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
template < uint FLAGS >
INLINE string_t StringID<T>::to_str() const
{
    string_t string;
    string = string + "ID: " + ex::to_str<FLAGS>(m_ID) + "\n";
    string = string + "RawString: " + ex::to_str<FLAGS>(GetString()) + "\n";
    return string;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
const self_t& StringID<T>::type_name()
{
    // KEEPME: static const self_t strID ( (string_t("TStringID_") + TypeTraits<T>::type_name().c_str()).c_str() );
    static const self_t strID ("StringID");
    return strID;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
result_t StringID<T>::resize( uint32 _newSize )
{
    result_t eResult = EResult::ok;

    //
    if ( s_pStringSet->empty() )
    {
        s_pStringSet->resize(_newSize);
    }
    else
    {
        ex_warning( "Can't not resize s_pStringSet with contents, this function can only be call at the initial time" );
        eResult = EResult::failed; 
    }

    //
    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
uint32 StringID<T>::size() 
{
    return s_pStringSet->size(); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
result_t StringID<T>::init( uint32 _size )
{
    ex_assert_return( s_pStringSet == NULL, EResult::init_failed, "The s_pStringSet already init" );
    s_pStringSet = ex_new string_set_t(_size);

    // register static string id.
    StringID<T>::s_folder = StringID<T>("folder");
    StringID<T>::s_config = StringID<T>("config");
    StringID<T>::s___root__   = StringID<T>("__root__");

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
result_t StringID<T>::destroy()
{
    ex_assert_return( s_pStringSet != NULL, EResult::destroy_failed, "The s_pStringSet is NULL, it could be 1: already been destroyed, 2: havn't init" );
    ex_delete(s_pStringSet);
    s_pStringSet = NULL;
    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
const string_set_t& StringID<T>::GetStringTable ()
{
    return *s_pStringSet;
}

#undef self_t
#undef string_set_t
#undef str_t

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END STRINGID_HPP_1250526418
// #################################################################################

