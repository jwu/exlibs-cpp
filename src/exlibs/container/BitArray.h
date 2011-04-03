// ======================================================================================
// File         : BitArray.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:08:47 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef BITARRAY_H_1250521715
#define BITARRAY_H_1250521715
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################

// ------------------------------------------------------------------
// Desc: _private::WORD_BIT
// ------------------------------------------------------------------
namespace _private { static const int WordBit = int(CHAR_BIT*sizeof(uint)); } // end namespace _private 

///////////////////////////////////////////////////////////////////////////////
// class BitArray 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class BitArray
{
    ///////////////////////////////////////////////////////////////////////////////
    // internal struct
    ///////////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////////
    // class BitRef 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    struct BitRef 
    {
        uint*   m_p;
        uint    m_mask;

        //
        BitRef( uint* _ptr, uint _mask ) 
            : m_p(_ptr), 
            m_mask(_mask) 
        {
        }

    public:
        BitRef() : m_p(0), m_mask(0) {}

        //
        operator bool() const { return !(!(*m_p & m_mask)); }

        //
        BitRef& operator = ( bool _bit_val )
        {
            if (_bit_val)  *m_p |= m_mask;
            else           *m_p &= ~m_mask;
            return *this;
        }
        BitRef& operator = ( const BitRef& _copy ) { return *this = bool(_copy); }

        //
        bool operator == ( const BitRef& _bitRef ) const { return bool(*this) == bool(_bitRef); }
        bool operator < ( const BitRef& _bitRef ) const { return !bool(*this) && bool(_bitRef); }

        //
        void flip() { *m_p ^= m_mask; }
    }; // end struct BitRef


    ///////////////////////////////////////////////////////////////////////////////
    // class BitIteratorBase 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    struct BitIteratorBase : public std::iterator< std::random_access_iterator_tag, bool, ptrdiff_t, bool*, bool& >
    {
        //
        uint*   m_p;
        uint    m_offset;

        //
        BitIteratorBase( uint* _ptr, uint _offset )
            : m_p(_ptr), 
            m_offset(_offset) 
        {
        }

        //
        void bump_up() 
        {
            if ( m_offset++ == _private::WordBit - 1 )
            {
                m_offset = 0;
                ++m_p;
            }
        }

        //
        void bump_down() {
            if (m_offset-- == 0) {
                m_offset = _private::WordBit - 1;
                --m_p;
            }
        }

        //
        void incr( ptrdiff_t _i ) 
        {
            ptrdiff_t n = _i + m_offset;
            m_p += n / _private::WordBit;
            // TODO: can be change to & ??
            n = n % _private::WordBit;
            if (n < 0) 
            {
                m_offset = (uint) n + _private::WordBit;
                --m_p;
            } 
            else
                m_offset = (uint) n;
        }

        //
        bool operator == ( const BitIteratorBase& _i ) const { return m_p == _i.m_p && m_offset == _i.m_offset;                    }
        bool operator <  ( const BitIteratorBase& _i ) const { return m_p < _i.m_p || (m_p == _i.m_p && m_offset < _i.m_offset);   }
        bool operator != ( const BitIteratorBase& _i ) const { return !(*this == _i);                                              }
        bool operator >  ( const BitIteratorBase& _i ) const { return _i < *this;                                                  }
        bool operator <= ( const BitIteratorBase& _i ) const { return !(_i < *this);                                               }
        bool operator >= ( const BitIteratorBase& _i ) const { return !(*this < _i);                                               }
    }; // end struct BitIteratorBase

    ///////////////////////////////////////////////////////////////////////////////
    // class BitIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    struct BitIterator : public BitIteratorBase
    {
        // the iter_ref_t is different between Iteartor and c_iterator.
        // cause the c_iterator never change the value, it return bool directly.
        // But iterator will return BitRef so the user can modify the exact value.
        typedef BitRef          iter_ref_t;
        typedef BitRef*         iter_ptr_t;
        typedef BitIterator     iter_self_t;
        typedef BitIteratorBase iter_base_t;

        //
        BitIterator() 
            : BitIteratorBase(0, 0) 
        {
        }

        //
        BitIterator( uint* _ptr, uint _offset ) 
            : BitIteratorBase( _ptr, _offset ) 
        {
        }

        //
        iter_ref_t operator*() const { return iter_ref_t( iter_base_t::m_p, 1U << iter_base_t::m_offset ); }

        //
        iter_self_t& operator++() { iter_base_t::bump_up(); return *this; }
        iter_self_t operator++(int) { iter_self_t tmp = *this; iter_base_t::bump_up(); return tmp; }

        //
        iter_self_t& operator--() { iter_base_t::bump_down(); return *this; }
        iter_self_t operator--(int) { iter_self_t tmp = *this; iter_base_t::bump_down(); return tmp; }

        //
        iter_self_t& operator+=( ptrdiff_t _i ) { iter_base_t::incr(_i); return *this; }
        iter_self_t& operator-=( ptrdiff_t _i ) { *this += -_i; return *this; }

        //
        iter_self_t operator+( ptrdiff_t _i ) const { iter_self_t tmp = *this; return tmp += _i; }
        iter_self_t operator-( ptrdiff_t _i ) const { iter_self_t tmp = *this; return tmp -= _i; }

        //
        ptrdiff_t operator-( iter_self_t _iter ) const { return _private::WordBit * (this->m_p - _iter.m_p) + this->m_offset - _iter.m_offset; }

        //
        iter_ref_t operator[]( ptrdiff_t _i ) { return *(*this + _i); }
    }; // end struct BitIterator

    ///////////////////////////////////////////////////////////////////////////////
    // class BitConstIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    struct BitConstIterator : public BitIteratorBase
    {
        typedef bool                iter_ref_t;
        typedef bool                iter_const_ref_t;
        typedef const bool*         iter_ptr_t;
        typedef BitConstIterator   iter_self_t;
        typedef BitIteratorBase    iter_base_t;

        //
        BitConstIterator() 
            : BitIteratorBase(0, 0) 
        {
        }
        
        //
        BitConstIterator( uint* _ptr, uint _offset ) 
            : BitIteratorBase( _ptr, _offset ) 
        {
        }

        //
        BitConstIterator( const BitIterator& _copy ) 
            : BitIteratorBase(_copy.m_p, _copy.m_offset) 
        {
        }

        //
        iter_const_ref_t operator*() const { return BitRef( iter_base_t::m_p, 1U << iter_base_t::m_offset ); }

        //
        iter_self_t& operator++() { iter_base_t::bump_up(); return *this; }
        iter_self_t operator++(int) { iter_self_t tmp = *this; iter_base_t::bump_up(); return tmp; }

        //
        iter_self_t& operator--() { iter_base_t::bump_down(); return *this; }
        iter_self_t operator--(int) { iter_self_t tmp = *this; iter_base_t::bump_down(); return tmp; }

        //
        iter_self_t& operator+=( ptrdiff_t _i ) { iter_base_t::incr(_i); return *this; }
        iter_self_t& operator-=( ptrdiff_t _i ) { *this += -_i; return *this; }

        //
        iter_self_t operator+( ptrdiff_t _i ) const { iter_self_t tmp = *this; return tmp += _i; }
        iter_self_t operator-( ptrdiff_t _i ) const { iter_self_t tmp = *this; return tmp -= _i; }

        //
        ptrdiff_t operator-( iter_self_t _iter ) const { return _private::WordBit * (this->m_p - _iter.m_p) + this->m_offset - _iter.m_offset; }

        //
        iter_const_ref_t operator[]( ptrdiff_t _i ) { return *(*this + _i); }
    }; // end struct BitConstIterator

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    typedef BitArray<TAllocator_T>                      self_t;
    typedef bool                                        value_t;
    typedef size_t                                      sz_t;
    typedef ptrdiff_t                                   diff_t; 
    typedef BitRef                                      ref_t;
    typedef bool                                        const_ref_t;
    typedef BitRef*                                     ptr_t;
    typedef const bool*                                 const_ptr_t;
    typedef ContainerAllocator<uint,TAllocator_T>       allocator_t;

    //
    typedef BitIterator                             iterator;
    typedef BitConstIterator                        c_iterator;
    typedef std::reverse_iterator<iterator>         r_iterator;
    typedef std::reverse_iterator<c_iterator>       c_r_iterator;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

    //
    BitArray()
        : m_start(),
          m_finish(),
          m_endofStorage(NULL)
    {
    }

    //
    BitArray( sz_t _n, bool _value )
        : m_start(),
          m_finish(),
          m_endofStorage(NULL)
    {
        _init(_n);
        ex::iter_fill( m_start.m_p, m_endofStorage, _value ? ~0 : 0 );
    }

    //
    explicit BitArray(sz_t _n)
        : m_start(),
          m_finish(),
          m_endofStorage(NULL)
    {
        _init(_n);
        ex::iter_fill(m_start.m_p, m_endofStorage, 0);
    }

    //
    BitArray( const BitArray& _copy ) 
    {
        _init( _copy.size() );
        ex::iter_copy( _copy.begin(), _copy.end(), m_start );
    }

    //
    BitArray( c_iterator _first, c_iterator _last )
        : m_start(),
          m_finish(),
          m_endofStorage(NULL)
    {
        sz_t count = 0;
        ex::iter_distance( _first, _last, count );
        _init(count);
        ex::iter_copy( _first, _last, m_start );
    }

    //
    BitArray( const bool* _first, const bool* _last )
        : m_start(),
          m_finish(),
          m_endofStorage(NULL)
    {
        sz_t count = 0;
        ex::iter_distance( _first, _last, count );
        _init(count);
        ex::iter_copy( _first, _last, m_start );
    }

    //
    ~BitArray() 
    {
        this->_bit_dealloc();
    }

    //
    BitArray& operator = ( const BitArray& _copy ) 
    {
        if ( &_copy == this ) return *this;
        if ( _copy.size() > capacity() ) 
        {
            _bit_dealloc();
            _init(_copy.size());
        }
        ex::iter_copy(_copy.begin(), _copy.end(), begin());
        m_finish = begin() + diff_t(_copy.size());
        return *this;
    }


    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    iterator begin() { return m_start; }
    c_iterator begin() const { return m_start; }

    //
    iterator end() { return m_finish; }
    c_iterator end() const { return m_finish; }

    //
    r_iterator rbegin() { return r_iterator(end()); }
    c_r_iterator rbegin() const { return c_r_iterator(end()); }

    //
    r_iterator rend() { return r_iterator(begin()); }
    c_r_iterator rend() const { return c_r_iterator(begin()); }

    //
    sz_t size() const { return sz_t(end() - begin()); }
    sz_t max_size() const { return sz_t(-1); }
    sz_t capacity() const { return sz_t(c_iterator(m_endofStorage, 0) - begin()); }
    bool empty() const { return begin() == end(); }
    sz_t index( const iterator& _iter ) { return _iter - begin(); }
    allocator_t get_allocator() const { return allocator_t(); } 

    //
    ref_t operator[] ( sz_t _n ) { return *(begin() + diff_t(_n)); }
    const_ref_t operator[] ( sz_t _n ) const { return *(begin() + diff_t(_n)); }

    //
    void assign( size_t _count, bool _bit_val ) { _fill_assign(_count, _bit_val); }

    // 
    void reserve( sz_t _count ) 
    {
        if ( capacity() < _count )
        {
            uint* pBits = _bit_alloc(_count);
            m_finish = ex::iter_copy(begin(), end(), iterator(pBits, 0));
            _bit_dealloc();
            m_start = iterator(pBits, 0);
            m_endofStorage = pBits + (_count + _private::WordBit - 1)/_private::WordBit;
        }
    }

    //
    ref_t front() { return *begin(); }
    const_ref_t front() const { return *begin(); }

    //
    ref_t back() { return *(end() - 1); }
    const_ref_t back() const { return *(end() - 1); }

    //
    void push_back( bool _bit_val ) 
    {
        if (m_finish.m_p != m_endofStorage)
            *m_finish++ = _bit_val;
        else
            _insert_aux(end(), _bit_val);
    }

    //
    void pop_back () 
    {
        --m_finish; 
    }

    //
    void swap( self_t& _bit_val ) 
    {
        ex::value_swap( m_start, _bit_val.m_start );
        ex::value_swap( m_finish, _bit_val.m_finish );
        ex::value_swap( m_endofStorage, _bit_val.m_endofStorage );
    }

    //
    iterator insert( iterator _pos, bool _bit_val = false ) 
    {
        diff_t count = _pos - begin();
        if ( m_finish.m_p != m_endofStorage && _pos == end() )
            *m_finish++ = _bit_val;
        else
            _insert_aux( _pos, _bit_val );
        return begin() + count;
    }

    //
    void insert( iterator _pos, c_iterator _first, c_iterator _last ) 
    {
        if (_first == _last) 
            return;

        //
        sz_t count = 0;
        ex::iter_distance( _first, _last, count );
        if ( capacity() - size() >= count ) 
        {
            ex::iter_copy_backward(_pos, end(), m_finish + count);
            ex::iter_copy(_first, _last, _pos);
            m_finish += count;
        }
        else 
        {
            sz_t len = size() + mathop::max(size(), count);
            uint* pBits = _bit_alloc(len);
            iterator iter = ex::iter_copy( begin(), _pos, iterator(pBits, 0) );
            iter = ex::iter_copy( _first, _last, iter );
            m_finish = ex::iter_copy( _pos, end(), iter );
            _bit_dealloc();
            m_endofStorage = pBits + (len + _private::WordBit - 1)/_private::WordBit;
            m_start = iterator(pBits, 0);
        }
    }

    void insert( iterator _pos, const bool* _first, const bool* _last ) 
    {
        if (_first == _last) 
            return;

        //
        sz_t count = 0;
        ex::iter_distance(_first, _last, count);
        if ( capacity() - size() >= count ) 
        {
            ex::iter_copy_backward(_pos, end(), m_finish + count);
            ex::iter_copy(_first, _last, _pos);
            m_finish += count;
        }
        else 
        {
            sz_t len = size() + mathop::max(size(), count);
            uint* pBits = _bit_alloc(len);
            iterator iter = ex::iter_copy(begin(), _pos, iterator(pBits, 0));
            iter = ex::iter_copy(_first, _last, iter);
            m_finish = ex::iter_copy(_pos, end(), iter);
            _bit_dealloc();
            m_endofStorage = pBits + (len + _private::WordBit - 1)/_private::WordBit;
            m_start = iterator(pBits, 0);
        }
    }

    //
    void insert( iterator _pos, sz_t _count, bool _bit_val ) 
    {
        _fill_insert( _pos, _count, _bit_val );
    }

    //
    iterator erase( iterator _pos ) 
    {
        if ( _pos + 1 != end() )
            ex::iter_copy(_pos + 1, end(), _pos);
        --m_finish;
        return _pos;
    }

    //
    iterator erase( iterator _first, iterator _last ) 
    {
        m_finish = ex::iter_copy(_last, end(), _first);
        return _first;
    }

    //
    result_t resize( sz_t _new_size, bool _x = false ) 
    {
        if ( _new_size < size() ) 
            erase( begin() + diff_t(_new_size), end() );
        else
            insert( end(), _new_size - size(), _x );
        return EResult::ok;
    }

    //
    void flip() 
    {
        for ( uint* pBits = m_start.m_p; pBits != m_endofStorage; ++pBits )
            *pBits = ~*pBits;
    }

    void clear() { erase(begin(), end()); }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions 
    ///////////////////////////////////////////////////////////////////////////////

protected:
    //
    uint* _bit_alloc ( sz_t _n ) 
    {
        return get_allocator().allocate( (_n + _private::WordBit - 1)/_private::WordBit ); 
    }

    //
    void _bit_dealloc () 
    {
        if ( m_start.m_p )
            get_allocator().deallocate( m_start.m_p, m_endofStorage - m_start.m_p );
    }

    //
    void _init( sz_t _n ) 
    {
        uint* pBits = _bit_alloc(_n);
        m_endofStorage = pBits + (_n + _private::WordBit - 1)/_private::WordBit;
        m_start = iterator(pBits, 0);
        m_finish = m_start + diff_t(_n);
    }

    //
    void _insert_aux( iterator _pos, bool _bit_val ) 
    {
        if ( m_finish.m_p != m_endofStorage ) 
        {
            ex::iter_copy_backward(_pos, m_finish, m_finish + 1);
            *_pos = _bit_val;
            ++m_finish;
        }
        else 
        {
            sz_t len = size() ? 2 * size() : _private::WordBit;
            uint* pBits = _bit_alloc(len);
            iterator _i = ex::iter_copy(begin(), _pos, iterator(pBits, 0));
            *_i++ = _bit_val;
            m_finish = ex::iter_copy(_pos, end(), _i);
            _bit_dealloc();
            m_endofStorage = pBits + (len + _private::WordBit - 1)/_private::WordBit;
            m_start = iterator(pBits, 0);
        }
    }

    //
    void _fill_assign( size_t _count, bool _bit_val ) 
    {
        if ( _count > size() ) 
        {
            ex::iter_fill( m_start.m_p, m_endofStorage, _bit_val ? ~0 : 0 );
            insert( end(), _count - size(), _bit_val );
        }
        else 
        {
            erase( begin() + _count, end() );
            ex::iter_fill( m_start.m_p, m_endofStorage, _bit_val ? ~0 : 0 );
        }
    }

    //
    void _fill_insert(iterator _pos, sz_t count, bool _x) 
    {
        if (count == 0) return;
        if (capacity() - size() >= count) 
        {
            ex::iter_copy_backward(_pos, end(), m_finish + diff_t(count));
            ex::iter_fill(_pos, _pos + diff_t(count), _x);
            m_finish += diff_t(count);
        }
        else 
        {
            sz_t len = size() + mathop::max(size(), count);
            uint* pBits = _bit_alloc(len);
            iterator iter = ex::iter_copy(begin(), _pos, iterator(pBits, 0));
            ex::iter_fill_n(iter, count, _x);
            m_finish = ex::iter_copy(_pos, end(), iter + diff_t(count));
            _bit_dealloc();
            m_endofStorage = pBits + (len + _private::WordBit - 1)/_private::WordBit;
            m_start = iterator(pBits, 0);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:
    //
    iterator m_start;
    iterator m_finish;
    uint* m_endofStorage;

}; // end class BitArray 

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < template <class> class TAllocator_T >
INLINE typename BitArray<TAllocator_T>::BitIterator operator + ( ptrdiff_t _n, const typename BitArray<TAllocator_T>::BitIterator& _iter ) { return _iter + _n; }

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < template <class> class TAllocator_T >
INLINE typename BitArray<TAllocator_T>::BitConstIterator operator + ( ptrdiff_t _n, const typename BitArray<TAllocator_T>::BitConstIterator& _iter ) { return _iter + _n; }

///////////////////////////////////////////////////////////////////////////////
// typedef 
///////////////////////////////////////////////////////////////////////////////

typedef BitArray<> bit_array_t;

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END BITARRAY_H_1250521715
// #################################################################################
