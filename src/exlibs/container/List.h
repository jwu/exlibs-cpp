// ======================================================================================
// File         : List.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:29:22 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef LIST_H_1250522966
#define LIST_H_1250522966
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////


// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class List
// 
// Purpose: improve version of std::list
// 
///////////////////////////////////////////////////////////////////////////////
 
template < typename T, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class List : protected std::list< T, ContainerAllocator<T,TAllocator_T> >
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    typedef List< T, TAllocator_T > self_t;
	typedef std::list< T, ContainerAllocator<T,TAllocator_T> > base_t;

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
    List()
        : base_t( allocator_t() )
    {
    }

    //
    List( sz_t _n, const T& _val )
        : base_t( _n, _val, allocator_t() )
    {
    }

    //
    explicit List( sz_t _n )
        : base_t( _n )
    {
    }

    // 
    List( const T* _pFirst, const T* _pLast )
        : base_t( _pFirst, _pLast )
    {
    }

    //
    List( c_iterator _first, c_iterator _last )
        : base_t( _first, _last, allocator_t() )
    {
    }

    // copy
    List( const self_t& _copy )
        : base_t(_copy)
    {
    }

    //
    ~List() 
    {
        clear();
    }

    //
    INLINE self_t& operator = ( const self_t& _list ) { base_t::operator = (_list); return *this; }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functons 
    ///////////////////////////////////////////////////////////////////////////////

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

    //
    INLINE iterator erase( iterator _pos )
    { 
        ex_assert ( _pos != end(), "invalid input! try to remove iterator end()" );
        return base_t::erase( _pos );            
    }
    INLINE iterator erase( iterator _first, iterator _last ) 
    { 
        ex_assert ( _last >= _first, "invalid input!" );
        ex_assert ( _first != end(), "invalid input! param 1 is end()" );
        ex_assert ( _last != end(), "invalid input! param 2 is end()" );
        return base_t::erase( _first, _last );   
    }

    //
    INLINE iterator safe_erase( iterator _pos )
    { 
        if ( _pos == end() )
            return end();
        return base_t::erase( _pos );            
    }
    INLINE iterator safe_erase( iterator _first, iterator _last ) 
    {
        if ( _last < _first || _first == end() || _last == end() )
            return end();
        return base_t::erase( _first, _last );   
    }

    // 
    INLINE ref_t front() { return base_t::front(); }
    INLINE const_ref_t front() const { return base_t::front(); }
    INLINE ref_t back() { return base_t::back(); }
    INLINE const_ref_t back() const { return base_t::back(); }

    //
    INLINE iterator find ( const_ref_t _val )                { return find( begin(), end(), _val );    }
    INLINE c_iterator find ( const_ref_t _val ) const     { return find( begin(), end(), _val );    }

    //
    INLINE void assign( sz_t _count, const T& _val ) { base_t::assign( _count, _val ); }

    //
    INLINE iterator insert( iterator _pos, const T& _val ) { return base_t::insert( _pos, _val ); }
    // TODO: implement it in win32
    // INLINE iterator insert( iterator _pos ) { return base_t::insert( _pos ); }

    //
    INLINE void insert( iterator _pos, const T* _pFirst, const T* _pLast ) { base_t::insert( _pos, _pFirst, _pLast ); }
    INLINE void insert( iterator _pos, c_iterator _first, c_iterator _last ) { base_t::insert( _pos, _first, _last ); }

    //
    INLINE void push_front( const T& _val ) { base_t::push_front(_val); }
    INLINE void push_front() { base_t::push_front(); }
    INLINE void push_front_unique( const value_t& _val ) 
    { 
        if ( find (_val ) == end() )
            base_t::push_front(_val); 
    }

    INLINE void push_back( const T& _val ) { base_t::push_back(_val); }
    // TODO: implement it in win32
    // INLINE void push_back() { base_t::push_back(); }
    INLINE result_t push_back_unique( const value_t& _val ) 
    { 
        result_t eResult = EResult::already_existed;
        if ( find (_val ) == end() ) {
            base_t::push_back(_val); 
            eResult = EResult::ok;
        }
        return eResult;
    }

    //
    INLINE result_t resize( sz_t _new_size, const T& _val ) { base_t::resize( _new_size, _val ); return EResult::ok; }
    INLINE result_t resize( sz_t _new_size ) { base_t::resize( _new_size ); return EResult::ok; }

    // 
    INLINE void pop_front() { base_t::pop_front(); }
    INLINE void pop_back()  { base_t::pop_back(); } 

    // 
    INLINE void splice( iterator _pos, self_t& _list ) { base_t::splice( _pos, _list ); }
    INLINE void splice( iterator _pos, self_t& _list, iterator _iter ) { base_t::splice( _pos, _list, _iter ); }

    //
    INLINE void remove( const T& _val ) { base_t::remove(_val); }
    INLINE void unique() { base_t::unique(); }
    INLINE void merge( self_t& _list ) { base_t::merge(_list); }
    INLINE void reverse() { base_t::reverse(); }
    INLINE void sort() { base_t::sort(); }
    template < class StrictWeakOrdering_T > INLINE void sort( StrictWeakOrdering_T _strictWeakOrdering ) { base_t::sort(_strictWeakOrdering); }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string;
        c_iterator iter       = this->begin();
        c_iterator iterEnd    = this->end();
        for ( ; iter != iterEnd; ++iter )
        {
            string = string + ex::to_str<FLAGS>((*iter)) + "\n";
        }
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("List");
        return strID;
    }

}; // end class List 

// #########################
} // end namespace ex 
// #########################

// TODO: make it work 
#if 0
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
INLINE void* operator new ( size_t _size, ex::List<T,TAllocator_T>& _list )
{
    _list.push_back();
    return &(_list.back());
}

// ========================================================
// placement new for insert
// ========================================================

template<  typename T, template <class> class TAllocator_T >
INLINE void* operator new ( size_t _size, ex::List<T,TAllocator_T>& _list, typename ex::List<T,TAllocator_T>::iterator _pos )
{
    return &(*(_list.insert( _pos )));
}

// ------------------------------------------------------------------
// Desc: 
// this is dummy function
// ------------------------------------------------------------------
// {
template< typename T, template <class> class TAllocator_T >
INLINE void operator delete ( void* _ptr, ex::List<T,TAllocator_T>& _list ) {}

template< typename T, template <class> class TAllocator_T >
INLINE void operator delete ( void* _ptr, ex::List<T,TAllocator_T>& _list, typename ex::List<T,TAllocator_T>::iterator _pos ) {}
// }
#endif

// #################################################################################
#endif // END LIST_H_1250522966
// #################################################################################
