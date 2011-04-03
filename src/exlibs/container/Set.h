// ======================================================================================
// File         : Set.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:35:00 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef SET_H_1250523303
#define SET_H_1250523303
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "Pair.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Set
// 
// Purpose: improve version of std::set
// 
///////////////////////////////////////////////////////////////////////////////
 
template < typename KEY, typename COMP_FUNC = Less<KEY>, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class Set : protected std::set< KEY, COMP_FUNC, ContainerAllocator< KEY, TAllocator_T > >
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    typedef Set< KEY, COMP_FUNC, TAllocator_T > self_t;
    typedef std::set< KEY, COMP_FUNC, ContainerAllocator< KEY, TAllocator_T > > base_t;

    //
	typedef typename base_t::size_type                  sz_t;
	typedef typename base_t::pointer                    ptr_t;
	typedef typename base_t::const_pointer              const_ptr_t;
	typedef typename base_t::reference                  ref_t;
	typedef typename base_t::const_reference            const_ref_t;
	typedef typename base_t::allocator_type             allocator_t;

    //
    typedef KEY key_t;     
    typedef KEY value_t;     // same as: typedef typename base_t::value_type value_t;
    typedef typename base_t::key_compare      key_comp_f;     
    typedef typename base_t::value_compare    value_comp_f;     

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
    Set( const value_t* _pFirst, const value_t* _pLast ) 
        : base_t( _pFirst, _pLast ) 
    {
    }

    //
    Set( c_iterator _first, c_iterator _last )
        : base_t( _first, _last ) 
    {
    }

    //
    Set( const self_t& _set ) 
        : base_t( _set ) 
    {
    }

    //
    ~Set()
    {
    }

    //
    INLINE self_t& operator = ( const self_t& _set ) { base_t::operator = (_set); return *this; }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
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
    INLINE void erase( iterator _pos )                          { base_t::erase( _pos );                   }
    INLINE void erase( iterator _first, iterator _last )        { base_t::erase( _first, _last );          }
    INLINE void clear()                                         { base_t::clear();                         }
    INLINE void swap( self_t& _container )                      { base_t::swap( _container );              }

    //
    INLINE key_comp_f key_comp() const { return base_t::key_comp(); } 
    INLINE value_comp_f value_comp() const { return base_t::value_comp(); } 

    //
    INLINE Pair<iterator,result_t> insert( const value_t& _val )
    {
        std::pair<typename base_t::iterator,bool> res_pair = base_t::insert(_val); 
        if (res_pair.second)
            return Pair<iterator,result_t>(res_pair.first,EResult::ok);
        else
            return Pair<iterator,result_t>(res_pair.first,EResult::not_found);
    }
    INLINE iterator insert( iterator _pos, const value_t& _val ) { return base_t::insert(_val); }
    INLINE void insert( const value_t* _pFirst, const value_t* _pLast ) { return base_t::insert( _pFirst, _pLast ); }
    INLINE void insert( c_iterator _first, c_iterator _last ) { return base_t::insert( _first, _last ); }

    //
    INLINE sz_t erase( const key_t& _key ) { return base_t::erase(_key); }

    //
    INLINE c_iterator find( const key_t& _key ) const { return base_t::find(_key); }
    INLINE sz_t count( const key_t& _key ) const { return base_t::count(_key); }

    //
    INLINE iterator lower_bound( const key_t& _key ) { return base_t::lower_bound(_key);  }
    INLINE iterator upper_bound( const key_t& _key ) { return base_t::upper_bound(_key);  }
    INLINE Pair<iterator,iterator> equal_range( const key_t& _key ) { return base_t::equal_range(_key); }

}; // end class Set

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END SET_H_1250523303
// #################################################################################
