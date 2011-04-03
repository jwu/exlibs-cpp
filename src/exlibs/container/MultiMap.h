// ======================================================================================
// File         : MultiMap.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:30:57 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MULTIMAP_H_1250523061
#define MULTIMAP_H_1250523061
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "Pair.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class MultiMap
// 
// Purpose: improve version of std::multimap
// 
///////////////////////////////////////////////////////////////////////////////
 
template < typename KEY, typename VALUE, typename COMP_FUNC = Less<KEY>, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class MultiMap : protected std::multimap< KEY, VALUE, COMP_FUNC, ContainerAllocator< VALUE, TAllocator_T > >
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    typedef MultiMap< KEY, VALUE, COMP_FUNC, TAllocator_T > self_t;
    typedef std::multimap< KEY, VALUE, COMP_FUNC, ContainerAllocator< VALUE, TAllocator_T > > base_t;

    //
	typedef typename base_t::size_type                  sz_t;
	typedef typename base_t::pointer                    ptr_t;
	typedef typename base_t::const_pointer              const_ptr_t;
	typedef typename base_t::reference                  ref_t;
	typedef typename base_t::const_reference            const_ref_t;
	typedef typename base_t::allocator_type             allocator_t;

    //
    typedef KEY                                         key_t;     
    typedef VALUE                                       value_t;     
    typedef Pair<const KEY, VALUE>                      pair_t;     // same as: typedef typename base_t::value_type pair_t;
    typedef typename base_t::key_compare                key_comp_f;     
    typedef typename base_t::value_compare              value_comp_f;     

    ///////////////////////////////////////////////////////////////////////////////
    // class MultiMapIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class MultiMapIterator : public base_t::iterator
    {
    public:
        typedef MultiMapIterator           iter_self_t;
        typedef typename base_t::iterator   iter_base_t;

    public:
        MultiMapIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
		value_t& operator * () const { return (iter_base_t::operator * ()).second; }
        const key_t& key() const { return (iter_base_t::operator * ()).first; }
    }; // end class MultiMapIterator 

    ///////////////////////////////////////////////////////////////////////////////
    // class MultiMapConstIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class MultiMapConstIterator : public base_t::const_iterator
    {
    public:
        typedef MultiMapConstIterator              iter_self_t;
        typedef typename base_t::const_iterator     iter_base_t;

    public:
        MultiMapConstIterator( const iter_base_t& _base_iter )
            : iter_base_t(_base_iter)
        {
        }

        //
        const value_t& operator * () const { return (iter_base_t::operator * ()).second; }
        const key_t& key() const { return (iter_base_t::operator * ()).first; }
    }; // end class MultiMapConstIterator 

    //
    typedef class MultiMapIterator                      iterator;           
    typedef class MultiMapConstIterator                 c_iterator;      
    typedef std::reverse_iterator<iterator>             r_iterator;
    typedef std::reverse_iterator<c_iterator>           c_r_iterator;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    MultiMap()
        : base_t()
    {
    }

    //
    MultiMap( const pair_t* _pFirst, const pair_t* _pLast )
        : base_t( _pFirst, _pLast )
    {
    }

    //
    MultiMap( c_iterator _first, c_iterator _last )
        : base_t( _first, _last )
    {
    }

    //
    MultiMap( const self_t& _multimap )
        : base_t( _multimap )
    {
    }

    //
    ~MultiMap()
    {
    }

    //
    INLINE self_t& operator = ( const self_t& _multimap ) { base_t::operator = ( _multimap ); return *this; }

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
    INLINE iterator insert( const key_t& _key, const value_t& _val ) { return base_t::insert(pair_t(_key,_val)); } 
    INLINE iterator insert( const pair_t& _pair ) { return base_t::insert(_val); } 
    INLINE iterator insert( iterator _pos, const pair_t& _pair ) { return base_t::insert( _pos, _val ); } 
    INLINE void insert( const pair_t* _pFirst, const pair_t* _pLast ) { base_t::insert( _pFirst, _pLast ); }
    INLINE void insert( c_iterator _first, c_iterator _last ) { base_t::insert( _first, _last ); }

    //
    INLINE sz_t erase( const key_t& _key ) { return base_t::erase(_key); }

    //
    INLINE iterator find( const key_t& _key ) { return base_t::find(_key); }
    INLINE c_iterator find( const key_t& _key ) const { return base_t::find(_key); }
    INLINE sz_t count( const key_t& _key ) const { return base_t::count(_key); }

    //
    INLINE iterator lower_bound( const key_t& _key ) { return base_t::lower_bound(_key);  }
    INLINE c_iterator lower_bound( const key_t& _key ) const { return base_t::lower_bound(_key);  }
    INLINE iterator upper_bound( const key_t& _key ) { return base_t::upper_bound(_key);  }
    INLINE c_iterator upper_bound( const key_t& _key ) const { return base_t::upper_bound(_key); } 
    INLINE Pair<iterator,iterator> equal_range( const key_t& _key ) { return base_t::equal_range(_key); }
    INLINE Pair<c_iterator,c_iterator> equal_range( const key_t& _key ) const { return base_t::equal_range(_key); }

}; // end class MultiMap

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END MULTIMAP_H_1250523061
// #################################################################################
