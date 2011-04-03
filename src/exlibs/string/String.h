// ======================================================================================
// File         : String.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:26:33 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef STRING_H_1250526397
#define STRING_H_1250526397
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "gf/encoding.h"
#include "gf/str_op.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class String 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// TODO: change std::basic_string to std::basic_string<uint16> ... 
template < typename T, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class String : public std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >
{
    ///////////////////////////////////////////////////////////////////////////////
    // typdefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    typedef String< T, TAllocator_T > self_t;
    typedef std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> > base_t;

    //
	typedef typename base_t::size_type                  sz_t;          
    typedef typename base_t::value_type                 value_t;       
	typedef typename base_t::pointer                    ptr_t;         
	typedef typename base_t::const_pointer              const_ptr_t;   
	typedef typename base_t::reference                  ref_t;         
	typedef typename base_t::const_reference            const_ref_t;   
	typedef typename base_t::allocator_type             allocator_t;   

    //
    typedef typename base_t::iterator                   iterator;      
    typedef typename base_t::reverse_iterator           r_iterator;     
    typedef typename base_t::const_iterator             c_iterator; 
    typedef typename base_t::const_reverse_iterator     c_r_iterator;

    ///////////////////////////////////////////////////////////////////////////////
    // static members
    ///////////////////////////////////////////////////////////////////////////////

    EX_LIBS_DLL static self_t null;

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    explicit String()
        : base_t( allocator_t() )
    {
    }

    //
    String( const self_t& _string )
        : base_t(_string)
    {
    }

    //
    String( const base_t& _string )
        : base_t(_string)
    {
    }

    //
    String( const self_t& _string, sz_t _pos, sz_t _count = base_t::npos )
        : base_t( _string, _pos, _count )
    {
    }

    //
    String( const T* _c_str, sz_t _count )
        : base_t( _c_str, _count )
    {
    }

    // 
    String( const T* _c_str )
        : base_t( _c_str )
    {
    }

    //
    String( sz_t _count, T _char )
        : base_t( _count, _char )
    {
    }
    
    // 
    String( const T* _pStart, const T* _pEnd )
        : base_t(_pStart, _pEnd)
    {
        ex_assert_slow( ex::str::len(_pStart) >= uint(_pEnd-_pStart), "string end over range" );
        base_t::_M_range_initialize( _pStart, _pEnd );
    }

    // 
    ~String()
    {
    }

public:
    // similar common functions
    INLINE allocator_t get_allocator()                          { return base_t::get_allocator();          }
    INLINE iterator begin()                                     { return base_t::begin();                  }
    INLINE c_iterator begin() const                             { return base_t::begin();                  }
    INLINE iterator end()                                       { return base_t::end();                    }
    INLINE c_iterator end() const                               { return base_t::end();                    }
    INLINE r_iterator rbegin()                                  { return base_t::rbegin();                 }
    INLINE c_r_iterator rbegin() const                          { return base_t::rbegin();                 }
    INLINE r_iterator rend()                                    { return base_t::rend();                   }
    INLINE c_r_iterator rend() const                            { return base_t::rend();                   }
    INLINE bool empty() const                                   { return base_t::empty();                  }
    INLINE sz_t size() const                                    { return base_t::size();                   }
    INLINE sz_t max_size() const                                { return base_t::max_size();               }
    INLINE void clear()                                         { base_t::clear();                         }
    INLINE void swap( self_t& _container )                      { base_t::swap( _container );              }

public:
    //
    INLINE self_t& operator = ( const self_t& _string ) { base_t::operator = (_string); return *this; } 
    INLINE self_t& operator = ( const T* _c_str ) { base_t::operator = (_c_str); return *this; } 
    INLINE self_t& operator = ( const T _char ) { base_t::operator = (_char); return *this; } 

    //
    INLINE void resize( sz_t _count, T _char ) { base_t::resize( _count, _char ); } 
    INLINE void resize( sz_t _count ) { base_t::resize( _count ); } 

    //
    INLINE void reserve( sz_t _count = 0 ) { base_t::reserve(_count); } 

    //
    INLINE sz_t capacity() const { return base_t::capacity(); }

    //
    INLINE ref_t operator [] ( sz_t _idx ) { return base_t::operator [] (_idx); }
    INLINE const_ref_t operator [] ( sz_t _idx ) const { return base_t::operator [] (_idx); }

    //
    INLINE ref_t At ( sz_t _idx ) { return base_t::at(_idx); }
    INLINE const_ref_t At ( sz_t _idx ) const { return base_t::at(_idx); }

    //
    INLINE self_t& operator += ( const self_t& _string ) { base_t::operator += (_string); return *this; } 
    INLINE self_t& operator += ( const T* _c_str ) { base_t::operator += (_c_str); return *this; } 
    INLINE self_t& operator += ( const T _char ) { base_t::operator += (_char); return *this; } 

    //
    INLINE self_t& operator -= ( const self_t& _string ) {
        sz_t idx = this->find( _string );
        if ( idx == ex::IndexNone ) // if not found the sub-string, don't do anything.
            return *this;
        *this = this->substr( 0, idx ) + this->substr( idx + _string.size() );
        return *this; 
    } 
    INLINE self_t& operator -= ( const T* _c_str ) { 
        *this -= self_t(_c_str);
        return *this;
    } 

    //
    INLINE self_t& append( const self_t& _string ) { base_t::append( _string ); return *this; }
    INLINE self_t& append( const self_t& _string, sz_t _pos, sz_t _count ) { base_t::append( _string, _pos, _count ); return *this; }
    INLINE self_t& append( const T* _c_str, sz_t _count ) { base_t::append( _c_str, _count ); return *this; }
    INLINE self_t& append( const T* _c_str ) { base_t::append(_c_str); return *this; }
    INLINE self_t& append( sz_t _count, T _char ) { base_t::append( _count, _char ); return *this; }
    INLINE self_t& append( T _char ) { base_t::append( 1, _char ); return *this; }
    INLINE self_t& append( const T* _pStart, const T* _pEnd ) 
    {
        ex_assert_slow( ex::str::len(_pStart) >= uint(_pEnd-_pStart), "string end over range" );
        base_t::append( _pStart, _pEnd ); 
        return *this;
    }

    //
    INLINE void push_back( T _char ) { base_t::push_back(_char); }
    INLINE void pop_back() { base_t::pop_back(); }

    //
    INLINE self_t& assign( const self_t& _string ) { base_t::assign( _string ); return *this; }
    INLINE self_t& assign( const self_t& _string, sz_t _pos, sz_t _count ) { base_t::assign( _string, _pos, _count ); return *this; }
    INLINE self_t& assign( const T* _c_str, sz_t _count ) { base_t::assign( _c_str, _count ); return *this; }
    INLINE self_t& assign( const T* _c_str ) { base_t::assign( _c_str ); return *this; }
    INLINE self_t& assign( sz_t _count, T _char ) { base_t::assign( _count, _char ); return *this; }
    INLINE self_t& assign( const T* _pStart, const T* _pEnd ) 
    {
        ex_assert_slow( ex::str::len(_pStart) >= uint(_pEnd-_pStart), "string end over range" );
        base_t::assign( _pStart, _pEnd ); 
        return *this;
    }

    //
    INLINE self_t& insert( sz_t _pos, const self_t& _string ) { base_t::insert( _pos, _string ); return *this; }
    INLINE self_t& insert( sz_t _pos, const self_t& _string, sz_t _beg, sz_t _count ) { base_t::insert( _pos, _string, _beg, _count ); return *this; }
    INLINE self_t& insert( sz_t _pos, const T* _c_str, sz_t _count ) { base_t::insert( _pos, _c_str, _count ); return *this; }
    INLINE self_t& insert( sz_t _pos, const T* _c_str ) { base_t::insert( _pos, _c_str ); return *this; }
    INLINE self_t& insert( sz_t _pos, sz_t _count, T _char ) { base_t::insert( _pos, _count, _char ); return *this; }
    INLINE iterator insert( iterator _iter, T _char ) { return base_t::insert( _iter, _char ); }
    INLINE void insert( iterator _iter, sz_t _count, T _char ) { base_t::insert( _iter, _count, _char ); }
    INLINE void insert( iterator _iter, const T* _pStart, const T* _pEnd )
    {
        ex_assert_slow( ex::str::len(_pStart) >= uint(_pEnd-_pStart), "string end over range" );
        base_t::insert( _iter, _pStart, _pEnd ); 
    }

    //
    INLINE self_t& erase( sz_t _pos = 0, sz_t _count = base_t::npos ) { base_t::erase( _pos, _count ); return *this; }
    INLINE iterator erase( iterator _pos ) { return base_t::erase(_pos); }
    INLINE iterator erase( iterator _first, iterator _last ) { return base_t::erase(_first,_last); }

    //
    INLINE self_t& replace( sz_t _pos, sz_t _count, const String& _string ) { base_t::replace( _pos, _count, _string ); return *this; }
    INLINE self_t& replace( sz_t _pos1, sz_t _count1, const String& _string, sz_t _pos2, sz_t _count2 ) { base_t::replace( _pos1, _count1, _string, _pos2, _count2 ); return *this; }
    INLINE self_t& replace( sz_t _pos, sz_t _count1, const T* _c_str, sz_t _count2 ) { base_t::replace( _pos, _count1, _c_str, _count2 ); return *this; }
    INLINE self_t& replace( sz_t _pos, sz_t _count1, const T* _c_str ) { base_t::replace( _pos, _count1, _c_str ); return *this; }
    INLINE self_t& replace( sz_t _pos, sz_t _count1, sz_t _count2, T _char ) { base_t::replace( _pos, _count1, _count2, _char ); return *this; }
    INLINE self_t& replace( iterator _first, iterator _last, const String& _string ) { base_t::replace( _first, _last, _string ); return *this; }
    INLINE self_t& replace( iterator _first, iterator _last, const T* _c_str, sz_t _count ) { base_t::replace( _first, _last, _c_str, _count ); return *this; }
    INLINE self_t& replace( iterator _first, iterator _last, const T* _c_str ) { base_t::replace( _first, _last, _c_str ); return *this; }
    INLINE self_t& replace( iterator _first, iterator _last, const T* _pStart, const T* _pEnd )
    { 
        ex_assert_slow( ex::str::len(_pStart) >= uint(_pEnd-_pStart), "string end over range" );
        base_t::replace( _first, _last, _pStart, _pEnd ); 
        return *this;
    }

    //
    INLINE sz_t Copy( T* _c_str, sz_t _count, sz_t _pos = 0 ) const { return base_t::copy( _c_str, _count, _pos ); }

    //
    INLINE const T* c_str() const { return base_t::c_str(); }
    // just use c_str(), they are the same
    // INLINE const T* Data() const { return base_t::data(); }
    INLINE T* rawData() { return &(base_t::operator [] (0)); }

    //
    INLINE sz_t find( const self_t& _string, sz_t _pos = 0 ) const { return base_t::find( _string, _pos ); }
    INLINE sz_t find( const T* _c_str, sz_t _pos = 0 ) const { return base_t::find( _c_str, _pos ); }
    INLINE sz_t find( const T* _c_str, sz_t _pos, sz_t _count ) const { return base_t::find( _c_str, _pos, _count ); }
    INLINE sz_t find( const T _char, sz_t _pos = 0 ) const { return base_t::find( _char, _pos ); }

    //
    INLINE sz_t rfind( const self_t& _string, sz_t _pos = base_t::npos ) const { return base_t::rfind( _string, _pos ); }
    INLINE sz_t rfind( const T* _c_str, sz_t _pos = base_t::npos ) const { return base_t::rfind( _c_str, _pos ); }
    INLINE sz_t rfind( const T* _c_str, sz_t _pos, sz_t _count ) const { return base_t::rfind( _c_str, _pos, _count ); }
    INLINE sz_t rfind( const T _char, sz_t _pos = base_t::npos ) const { return base_t::rfind( _char, _pos ); }

    //
    INLINE sz_t findFirstOf( const self_t& _string, sz_t _pos = 0 ) const { return base_t::find_first_of( _string, _pos ); }
    INLINE sz_t findFirstOf( const T* _c_str, sz_t _pos = 0 ) const { return base_t::find_first_of( _c_str, _pos ); }
    INLINE sz_t findFirstOf( const T* _c_str, sz_t _pos, sz_t _count ) const { return base_t::find_first_of( _c_str, _pos, _count ); }
    INLINE sz_t findFirstOf( const T _char, sz_t _pos = 0 ) const { return base_t::find_first_of( _char, _pos ); }

    //
    INLINE sz_t findLastOf( const self_t& _string, sz_t _pos = base_t::npos ) const { return base_t::find_last_of( _string, _pos ); }
    INLINE sz_t findLastOf( const T* _c_str, sz_t _pos = base_t::npos ) const { return base_t::find_last_of( _c_str, _pos ); }
    INLINE sz_t findLastOf( const T* _c_str, sz_t _pos, sz_t _count ) const { return base_t::find_last_of( _c_str, _pos, _count ); }
    INLINE sz_t findLastOf( const T _char, sz_t _pos = base_t::npos ) const { return base_t::find_last_of( _char, _pos ); }

    //
    INLINE sz_t findFirstNotOf( const self_t& _string, sz_t _pos = 0 ) const { return base_t::find_first_not_of( _string, _pos ); }
    INLINE sz_t findFirstNotOf( const T* _c_str, sz_t _pos = 0 ) const { return base_t::find_first_not_of( _c_str, _pos ); }
    INLINE sz_t findFirstNotOf( const T* _c_str, sz_t _pos, sz_t _count ) const { return base_t::find_first_not_of( _c_str, _pos, _count ); }
    INLINE sz_t findFirstNotOf( const T _char, sz_t _pos = 0 ) const { return base_t::find_first_not_of( _char, _pos ); }

    //
    INLINE sz_t findLastNotOf( const self_t& _string, sz_t _pos = base_t::npos ) const { return base_t::find_last_not_of( _string, _pos ); }
    INLINE sz_t findLastNotOf( const T* _c_str, sz_t _pos = base_t::npos ) const { return base_t::find_last_not_of( _c_str, _pos ); }
    INLINE sz_t findLastNotOf( const T* _c_str, sz_t _pos, sz_t _count ) const { return base_t::find_last_not_of( _c_str, _pos, _count ); }
    INLINE sz_t findLastNotOf( const T _char, sz_t _pos = base_t::npos ) const { return base_t::find_last_not_of( _char, _pos ); }

    //
    INLINE String substr( sz_t _pos = 0, sz_t _count = base_t::npos ) const { return base_t::substr( _pos, _count ); }

    //
    INLINE int compare( const self_t& _string ) const { return base_t::compare(_string); }
    INLINE int compare( sz_t _pos1, sz_t _count1, const String& _string ) const { return base_t::compare( _pos1, _count1, _string ); }
    INLINE int compare( sz_t _pos1, sz_t _count1, const String& _string, sz_t _pos2, sz_t _count2 ) const { return base_t::compare( _pos1, _count1, _string, _pos2, _count2 ); }
    INLINE int compare( const T* _c_str ) const { return base_t::compare(_c_str); }
    INLINE int compare( sz_t _pos1, sz_t _count1, const T* _c_str ) const { return base_t::compare( _pos1, _count1, _c_str ); }
    INLINE int compare( sz_t _pos1, sz_t _count1, const T* _c_str, sz_t _count2 ) const { return base_t::compare( _pos1, _count1, _c_str, _count2 ); }

    //
    self_t& printf( const T* _fmt, ... )
    {
        int     result = -1;
        int     buffer_count = 1024;
        T*      pBuffer = NULL;

        // keep get va string until success 
        while ( result == -1 )
        {
            pBuffer = (T*)allocator_t().reallocate( pBuffer, buffer_count );
            EX_GET_VA_STRING_WITH_RESULT( pBuffer, buffer_count, _fmt, &result );
            buffer_count *= 2;
        }
        pBuffer[result] = 0;

        // 
        this->assign( pBuffer, result );

        // free the temp buffer
        allocator_t().deallocate( pBuffer, buffer_count );
        return (*this);
    }

    //
    String left( sz_t _count ) const
    {
        return String( this->c_str(), mathop::clamp<sz_t>( _count, 0, this->size() ) );
    }

    //
    String right( sz_t _count ) const
    {
        return String( this->c_str() + mathop::clamp<sz_t>( _count, 0, this->size() ) );
    }

    //
    INLINE void FromString( const T* _c_str )
    {
        this->assign (_c_str);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        return this;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("String");
        return strID;
    }

}; // end class String

///////////////////////////////////////////////////////////////////////////////
// Gen_TString 
// NOTE: The purpose of this function is, some times we write string "string"
//       directly in a template. But the template have a T express the character 
//       type, so we have to apply convertor on it. This function help you fulfill 
//       the task.
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <typename T>
INLINE String<T> Gen_TString ( const char* _c_str ) { return String<T>(_c_str); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <>
INLINE String<wchar> Gen_TString ( const char* _c_str ) { 
    wchar wstr[1024];
    ex::mem::zero( wstr, 1024 );
    char_to_wchar<1024> ( _c_str, wstr );
    return String<wchar>(wstr); 
}

///////////////////////////////////////////////////////////////////////////////
// operator +
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: String + String
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator + ( const String<T,TAllocator_T>& _string1, const String<T,TAllocator_T>& _string2 )
{
    return
        (
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string1)) +
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string2))
        );
}

// ------------------------------------------------------------------
// Desc: char_type* + String<char_type>
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator + ( const T* _c_str1, const String<T,TAllocator_T>& _string2 )
{
    return 
        (
         _c_str1 + 
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string2)) 
        );
}

// ------------------------------------------------------------------
// Desc: String<char_type> + char_type*
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator + ( const String<T,TAllocator_T>& _string1, const T* _c_str2 )
{
    return 
        ( 
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string1)) +
         _c_str2 
        ); 
}

// ------------------------------------------------------------------
// Desc: char_type + String<char_type>
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator + ( const T _char1, const String<T,TAllocator_T>& _string2 )
{
    return  
        (
         _char1 + 
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string2)) 
        );
}

// ------------------------------------------------------------------
// Desc: String<char_type> + char_type
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator + ( const String<T,TAllocator_T>& _string1, const T _char2 )
{
    return 
        (
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string1)) +
         _char2
        ); 
}


///////////////////////////////////////////////////////////////////////////////
// operator -
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: String + String
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator - ( const String<T,TAllocator_T>& _string1, const String<T,TAllocator_T>& _string2 )
{
    typename String<T,TAllocator_T>::sz_t idx = _string1.find( _string2 );
    if ( idx == ex::IndexNone ) // if not found the sub-string, don't do anything.
        return _string1;
    return _string1.substr( 0, idx ) + _string1.substr( idx + _string2.size() );
}

// ------------------------------------------------------------------
// Desc: char_type* + String<char_type>
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator - ( const T* _c_str1, const String<T,TAllocator_T>& _string2 )
{
    return String<T,TAllocator_T>(_c_str1) - _string2;
}

// ------------------------------------------------------------------
// Desc: String<char_type> + char_type*
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator - ( const String<T,TAllocator_T>& _string1, const T* _c_str2 )
{
    return _string1 - String<T,TAllocator_T>(_c_str2);
}

///////////////////////////////////////////////////////////////////////////////
// operator ==
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: String == String 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator == ( const String<T,TAllocator_T>& _string1, const String<T,TAllocator_T>& _string2 )
{
    return 
        (
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string1)) ==
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string2))
        ); 
}

// ------------------------------------------------------------------
// Desc: char_type* == String<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator == ( const T* _c_str1, const String<T,TAllocator_T>& _string2 )
{
    return
        ( 
         _c_str1 == 
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string2))
        ); 
}

// ------------------------------------------------------------------
// Desc: String<char_type> == char_type* 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator == ( const String<T,TAllocator_T>& _string1, const T* _c_str2 )
{
    return 
        (
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string1)) ==
         _c_str2 
        ); 
}

///////////////////////////////////////////////////////////////////////////////
// operator !=
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: String != String 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator != ( const String<T,TAllocator_T>& _string1, const String<T,TAllocator_T>& _string2 )
{
    return !(_string1 == _string2); 
}

// ------------------------------------------------------------------
// Desc: char_type* != String<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator != ( const T* _c_str1, const String<T,TAllocator_T>& _string2 )
{
    return !(_c_str1 == _string2); 
}

// ------------------------------------------------------------------
// Desc: String<char_type> != char_type* 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator != ( const String<T,TAllocator_T>& _string1, const T* _c_str2 )
{
    return !(_string1 == _c_str2); 
}

///////////////////////////////////////////////////////////////////////////////
// operator <
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: String < String 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator < ( const String<T,TAllocator_T>& _string1, const String<T,TAllocator_T>& _string2 )
{
    return ( 
            *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string1)) <
            *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string2))
           ); 
}

// ------------------------------------------------------------------
// Desc: char_type* < String<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator < ( const T* _c_str1, const String<T,TAllocator_T>& _string2 )
{
    return (
            _c_str1 < 
            *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string2)) 
           );
}

// ------------------------------------------------------------------
// Desc: String<char_type> < char_type* 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator < ( const String<T,TAllocator_T>& _string1, const T* _c_str2 )
{
    return ( 
            *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string1)) <
            _c_str2 
           ); 
}

///////////////////////////////////////////////////////////////////////////////
// operator <=
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: String <= String 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator <= ( const String<T,TAllocator_T>& _string1, const String<T,TAllocator_T>& _string2 )
{
    return !(_string2 < _string1); 
}

// ------------------------------------------------------------------
// Desc: char_type* <= String<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator <= ( const T* _c_str1, const String<T,TAllocator_T>& _string2 )
{
    return !(_string2 < _c_str1); 
}

// ------------------------------------------------------------------
// Desc: String<char_type> <= char_type* 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator <= ( const String<T,TAllocator_T>& _string1, const T* _c_str2 )
{
    return !(_c_str2 < _string1); 
}

///////////////////////////////////////////////////////////////////////////////
// operator >
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: String > String 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator > ( const String<T,TAllocator_T>& _string1, const String<T,TAllocator_T>& _string2 )
{
    return (_string2 < _string1); 
}

// ------------------------------------------------------------------
// Desc: char_type* > String<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator > ( const T* _c_str1, const String<T,TAllocator_T>& _string2 )
{
    return ( _string2 < _c_str1 ); 
}

// ------------------------------------------------------------------
// Desc: String<char_type> > char_type* 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator > ( const String<T,TAllocator_T>& _string1, const T* _c_str2 )
{
    return ( _c_str2 < _string1 ); 
}

///////////////////////////////////////////////////////////////////////////////
// operator >=
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: String >= String 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator >= ( const String<T,TAllocator_T>& _string1, const String<T,TAllocator_T>& _string2 )
{
    return !(_string1 < _string2); 
}

// ------------------------------------------------------------------
// Desc: char_type* >= String<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator >= ( const T* _c_str1, const String<T,TAllocator_T>& _string2 )
{
    return !(_c_str1 < _string2); 
}

// ------------------------------------------------------------------
// Desc: String<char_type> >= char_type* 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator >= ( const String<T,TAllocator_T>& _string1, const T* _c_str2 )
{
    return !(_string1 < _c_str2); 
}

///////////////////////////////////////////////////////////////////////////////
// operator ^=
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: String ^= String 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator ^= ( const String<T,TAllocator_T>& _string1, const String<T,TAllocator_T>& _string2 )
{
    return (ex::str::icmp( _string1.c_str(), _string2.c_str() ) == 0);
}

// ------------------------------------------------------------------
// Desc: char_type* ^= String<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator ^= ( const T* _c_str1, const String<T,TAllocator_T>& _string2 )
{
    return (ex::str::icmp( _c_str1, _string2.c_str() ) == 0);
}

// ------------------------------------------------------------------
// Desc: String<char_type> ^= char_type* 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator ^= ( const String<T,TAllocator_T>& _string1, const T* _c_str2 )
{
    return (ex::str::icmp( _string1.c_str(), _c_str2 ) == 0);
}

///////////////////////////////////////////////////////////////////////////////
// define includes
///////////////////////////////////////////////////////////////////////////////

#include "to_str.hpp"
#include "from_str.hpp"

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END STRING_H_1250526397
// #################################################################################
