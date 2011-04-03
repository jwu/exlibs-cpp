// ======================================================================================
// File         : Deque.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:09:30 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef DEQUE_H_1250521768
#define DEQUE_H_1250521768
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Deque
// 
// Purpose: improve version of std::deque
// 
///////////////////////////////////////////////////////////////////////////////
 
template < typename T, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class Deque : protected std::deque< T, ContainerAllocator<T,TAllocator_T> >
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    typedef Deque< T, TAllocator_T > self_t;
	typedef std::deque< T, ContainerAllocator<T,TAllocator_T> > base_t;

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
    explicit Deque()
        : base_t( allocator_t() ) 
    {
    }

    //
    Deque( const self_t& _copy )
        : base_t( _copy )
    {
    }

    //
    Deque( const value_t* _pFirst, const value_t* _pLast )
        : base_t( _pFirst, _pLast, allocator_t() )
    {
    }

    //
    Deque( c_iterator _first, c_iterator _last )
        : base_t( _first, _last, allocator_t() )
    {
    }

    //
    ~Deque()
    {
    }

    //
    INLINE Deque& operator = ( const Deque& _deque ) { self_t::operator = ( _deque ); return *this; }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // similar common functions
    INLINE allocator_t get_allocator()                        { return base_t::get_allocator();          }
    INLINE iterator begin()                                  { return base_t::begin();                  }
    INLINE c_iterator begin() const                       { return base_t::begin();                  }
    INLINE iterator end()                                    { return base_t::end();                    }
    INLINE c_iterator end() const                         { return base_t::end();                    }
    INLINE r_iterator rbegin()                                { return base_t::rbegin();                 }
    INLINE c_r_iterator rbegin() const                     { return base_t::rbegin();                 }
    INLINE r_iterator rend()                                  { return base_t::rend();                   }
    INLINE c_r_iterator rend() const                       { return base_t::rend();                   }
    INLINE bool empty() const                                { return base_t::empty();                  }
    INLINE sz_t size() const                                 { return base_t::size();                   }
    INLINE sz_t max_size() const                              { return base_t::max_size();               }
    INLINE iterator erase( iterator _pos )                   { return base_t::erase( _pos );            }
    INLINE iterator erase( iterator _first, iterator _last ) { return base_t::erase( _first, _last );   }
    INLINE void clear()                                      { base_t::clear();                         }
    INLINE void swap( self_t& _container )                   { base_t::swap( _container );              }

    //
    INLINE ref_t operator [] ( sz_t _idx ) { return base_t::operator [] (_idx); }
    INLINE const_ref_t operator [] ( sz_t _idx ) const { return base_t::operator [] (_idx); }

    //
    INLINE ref_t front() { return base_t::front(); }
    INLINE ref_t back() { return base_t::back(); }
    INLINE const_ref_t front() const { return base_t::front(); }
    INLINE const_ref_t back() const { return base_t::back(); }

    //
    INLINE void assign( sz_t _idx, const T& _val ) { return base_t::assign( _idx, _val ); }

    //
    INLINE void push_back( const T& _val ) { base_t::push_back(_val); }
    INLINE void push_back() { base_t::push_back(); }
    INLINE void push_front( const T& _val ) { base_t::push_front(_val); }
    INLINE void push_front() { base_t::push_front(); }

    //
    INLINE void pop_back() { base_t::pop_back(); }
    INLINE void pop_front() { base_t::pop_front(); }

    //
    INLINE value_t get_pop_back() 
    {
        value_t copy(back());
        base_t::pop_back();
        return copy;
    }
    INLINE value_t get_pop_front() 
    {
        value_t copy(front());
        base_t::pop_front();
        return copy;
    }

    //
    INLINE iterator insert( iterator _pos, const T& _val ) { base_t::insert( _pos, _val ); }
    INLINE iterator insert( iterator _pos ) { base_t::insert( _pos ); }
    INLINE void insert( iterator _pos, sz_t _count, const T& _val ) { base_t::insert( _pos, _count, _val ); }
    INLINE void insert( iterator _pos, const T* _pFirst, const T* _pLast ) { base_t::insert( _pos, _pFirst, _pLast ); }
    INLINE void insert( iterator _pos, c_iterator _first, c_iterator _last ) { base_t::insert( _pos, _first, _last ); }

    //
    INLINE result_t resize( sz_t _new_size, const T& _val ) { base_t::resize( _new_size, _val ); return EResult::ok; }

}; // end class deque

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END DEQUE_H_1250521768
// #################################################################################
