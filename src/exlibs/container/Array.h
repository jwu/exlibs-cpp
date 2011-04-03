// ======================================================================================
// File         : Array.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:08:01 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ARRAY_H_1250521685
#define ARRAY_H_1250521685
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Array
// 
// Purpose: improve version of std::list
// 
///////////////////////////////////////////////////////////////////////////////
 
template < typename T, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class Array : protected std::vector< T, ContainerAllocator<T,TAllocator_T> >
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    typedef Array< T, TAllocator_T > self_t;
    typedef std::vector< T, ContainerAllocator<T,TAllocator_T> > base_t;

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
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    explicit Array()
        : base_t( allocator_t() ) 
    {
    }

    //
    explicit Array( sz_t _count )
        : base_t( _count )
    {
    }

    //
    Array( const self_t& _copy )
        : base_t( _copy )
    {
    }

    // 
    Array( sz_t _count, const value_t& _val )
        : base_t( _count, _val, allocator_t() )
    {
    }

    //
    Array( const value_t* _pFirst, const value_t* _pLast )
        : base_t( _pFirst, _pLast, allocator_t() )
    {
    }

    //
    ~Array()
    {
        clear();
    }

    //
    INLINE self_t& operator = ( const self_t& _array ) { base_t::operator = (_array); return *this; }

    //
    INLINE bool operator == ( const self_t& _array ) 
    {
        if ( size() != _array.size() )
            return false;

        for ( sz_t i = 0; i < size(); ++i )
        {
            if ( (*this)[i] != _array[i] )
                return false;
        }

        return true;
    }

    //
    INLINE bool operator != ( const self_t& _array ) { return !( *this == _array ); }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:
    // similar common functions
    INLINE allocator_t get_allocator()                          { return base_t::get_allocator();           }
    INLINE iterator begin()                                     { return base_t::begin();                   }
    INLINE c_iterator begin() const                             { return base_t::begin();                   }
    INLINE iterator end()                                       { return base_t::end();                     }
    INLINE c_iterator end() const                               { return base_t::end();                     }
    INLINE r_iterator rbegin()                                  { return base_t::rbegin();                  }
    INLINE c_r_iterator rbegin() const                          { return base_t::rbegin();                  }
    INLINE r_iterator rend()                                    { return base_t::rend();                    }
    INLINE c_r_iterator rend() const                            { return base_t::rend();                    }
    INLINE bool empty() const                                   { return base_t::empty();                   }
    INLINE sz_t size() const                                    { return base_t::size();                    }
    INLINE sz_t max_size() const                                { return base_t::max_size();                }
    INLINE iterator erase( iterator _pos )                      { return base_t::erase( _pos );             }
    INLINE iterator erase( iterator _first, iterator _last )    { return base_t::erase( _first, _last );    }
    INLINE void clear()                                         { base_t::clear();                          }
    INLINE void swap( self_t& _container )                      { base_t::swap( _container );               }

    //
    INLINE sz_t index( iterator& _pos )                         { return (_pos - begin());                  }
    INLINE sz_t index( c_iterator& _pos ) const                 { return (_pos - begin());                  }

    //
    INLINE iterator find ( const_ref_t _val )                   { return ex::find( begin(), end(), _val );    }
    INLINE c_iterator find ( const_ref_t _val ) const           { return ex::find( begin(), end(), _val );    }

    //
    INLINE void reserve( sz_t _count ) { return base_t::reserve(_count); }
    INLINE sz_t capacity () const { return base_t::capacity(); }

    //
    INLINE ref_t operator [] ( sz_t _idx ) 
    {
        ex_assert( _idx < size() && _idx >= 0, "index out of range." ); 
        return base_t::operator[](_idx); 
    }
    INLINE const_ref_t operator [] ( sz_t _idx ) const 
    {
        ex_assert( _idx < size() && _idx >= 0, "index out of range." );
        return base_t::operator[](_idx); 
    }

    //
    INLINE ref_t front () 
    {
        ex_assert( size() >= 0, "working on a zero count array!" );
        return base_t::front();
    }
    INLINE const_ref_t front () const 
    {
        ex_assert( size() >= 0, "working on a zero count array!" );
        return base_t::front();
    }
    INLINE ref_t back () 
    {
        ex_assert( size() >= 0, "working on a zero count array!" );
        return base_t::back();
    }
    INLINE const_ref_t back () const 
    {
        ex_assert( size() >= 0, "working on a zero count array!" );
        return base_t::back();
    }

    //
    INLINE void assign( sz_t _count, const T& _val ) { base_t::assign( _count, _val ); }

    // don't use this, we already have operator [], they are the same
    // ref_t At( sz_t _idx ) { return (*this)[_idx]; }
    // const_ref_t At( sz_t _idx ) const  { return (*this)[_idx]; }

    //
    INLINE void push_back_unique( const value_t& _val ) 
    { 
        if ( find (_val ) == end() )
            base_t::push_back(_val); 
    }

    //
    INLINE void push_back( const value_t& _val ) { base_t::push_back(_val); }
    INLINE void push_back() 
    {
        // TODO: can we use stl-v3.3 so that we can just write code as:
        // base_t::push_back(); 

        // if the array haven't allocated, allocate then return
        if ( size() == 0 )
        {
            reserve( EX_DEFAULT_ALIGNMENT );
        }

        //
        if ( capacity() < size() + 1 )
        {
            sz_t cap = max_size() - capacity() / 2 < capacity() ? 0 : capacity() + capacity() / 2;	// try to grow by 50%
            if ( cap < size() + 1 )
                cap = size() + 1;
            reserve(cap);
        }
#if (EX_COMPILER == EX_MSVC)
        ++base_t::_Mylast;
#elif (EX_COMPILER == EX_GCC)
        ++this->_M_impl._M_finish;
#endif
    }

    template < template <class> class TAllocator_OTHER_T >
    INLINE void push_back( const Array<T,TAllocator_OTHER_T>& _array ) { insert ( end(), _array.begin(), _array.end() ); }

    //
    INLINE iterator insert( iterator _pos, const value_t& _val ) { return base_t::insert( _pos, _val ); }
    INLINE iterator insert( iterator _pos ) { return base_t::insert( _pos ); }
    INLINE void insert( iterator _pos, c_iterator _first, c_iterator _last ) { base_t::insert( _pos, _first, _last ); }
    INLINE void insert( iterator _pos, sz_t _count, const value_t& _val ) { base_t::insert( _pos, _count, _val ); }

    //
    INLINE iterator insert_at( sz_t _idx, const value_t& _val ) 
    {
        ex_assert(_idx < size() && _idx >= 0, "index out of range" ); 
        return base_t::insert( begin()+_idx, _val ); 
    }
    INLINE iterator insert_at( sz_t _idx ) 
    {
        ex_assert(_idx < size() && _idx >= 0, "index out of range" ); 
        return base_t::insert( begin()+_idx ); 
    }
    INLINE void insert_at( sz_t _idx, c_iterator _first, c_iterator _last ) 
    {
        ex_assert(_idx < size() && _idx >= 0, "index out of range" ); 
        base_t::insert( begin()+_idx, _first, _last ); 
    }
    INLINE void insert_at( sz_t _idx, sz_t _count, const value_t& _val ) 
    {
        ex_assert(_idx < size() && _idx >= 0, "index out of range" ); 
        base_t::insert( begin()+_idx, _count, _val ); 
    }

    // 
    INLINE void pop_back() { base_t::pop_back(); }

    //
    INLINE iterator erase_at( sz_t _idx ) 
    {
        ex_assert(_idx < size() && _idx >= 0, "index out of range" ); 
        return base_t::erase(begin()+_idx); 
    }

    //
    INLINE result_t resize( sz_t _new_size, const value_t& _val ) { base_t::resize( _new_size, _val ); return EResult::ok; }
    INLINE result_t resize( sz_t _new_size ) { base_t::resize( _new_size ); return EResult::ok; }

    //
    INLINE T* ptr ( sz_t _idx ) 
    {
        ex_assert(_idx < size() && _idx >= 0, "index out of range" ); 
        return &(*(begin()+_idx));
    }

    //
    INLINE const T* ptr ( sz_t _idx ) const 
    {
        ex_assert(_idx < size() && _idx >= 0, "index out of range" ); 
        return &(*(begin()+_idx));
    }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string;
        for ( c_iterator iter = this->begin(); iter != this->end(); ++iter )
        {
            string = string + "[" + ex::to_str<FLAGS>(uint32(index(iter))) + "]: " + ex::to_str<FLAGS>((*iter)) + "\n";
        }
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("Array");
        return strID;
    }

}; // end class Array

// #########################
} // end namespace ex 
// #########################

// ------------------------------------------------------------------
// Desc: 
//  If the T_NeedConstruct<T>::Result is true, 
//  it is recomment to use this new function to do add/insert
//  instead of adding/inserting by member function. 
//  Because you will call constructor then copy-constructor.
// ------------------------------------------------------------------

// ========================================================
// placement new for push back
// ========================================================

template<  typename T, template <class> class TAllocator_T >
INLINE void* operator new ( size_t _size, ex::Array<T,TAllocator_T>& _array )
{
    _array.push_back();
    return &(_array.back());
}

// ========================================================
// placement new for insert
// ========================================================

template<  typename T, template <class> class TAllocator_T >
INLINE void* operator new ( size_t _size, ex::Array<T,TAllocator_T>& _array, int _idx )
{
    return &(*(_array.insert_at( _idx )));
}

// ------------------------------------------------------------------
// Desc: 
// this is dummy function
// ------------------------------------------------------------------
// {
template< typename T, template <class> class TAllocator_T >
INLINE void operator delete ( void* _ptr, ex::Array<T,TAllocator_T>& _array ) {}

template< typename T, template <class> class TAllocator_T >
INLINE void operator delete ( void* _ptr, ex::Array<T,TAllocator_T>& _array, int _idx ) {}
// }

// #################################################################################
#endif // END ARRAY_H_1250521685
// #################################################################################
