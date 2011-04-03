// ======================================================================================
// File         : DataHolder.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:13:53 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef DATAHOLDER_H_1250525636
#define DATAHOLDER_H_1250525636
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class DataHolder 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class DataHolder : public RefCounted<void>
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

    typedef void* ptr_t;
    typedef const void* const_ptr_t;
    typedef ptr_t& ptr_ref_t; // T* &
    typedef const ptr_t& const_ptr_ref_t; // T* const &, not miss understand as const T* const &
    typedef RefCounted<void> ref_counted_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    DataHolder()
        : m_data(NULL),
          m_size(0)
    {
    }

    //
    DataHolder( const DataHolder& _copy )
        : ref_counted_t(_copy),
          m_size(_copy.m_size)
    {
        m_data = ref_counted_t::clone( _copy.ptr_ref() );
    }

    //
    DataHolder( void* _pData, uint32 _size )
    {
        assign( _pData, _size );
    }

    // operator = 
    DataHolder& operator = ( const DataHolder& _copy )
    {
        DataHolder temp(_copy);
        temp.swap(*this);
        return *this;
    }

    //
    ~DataHolder()
    {
        if ( ref_counted_t::release(this->ptr_ref()) )
        {
            if ( m_data )
            {
                ex_free ( m_data );
                m_data = NULL;
                m_size = 0;
            }
            ex_assert( m_size == 0, "Data Lost!" );
        }
    }

    //
    void swap( DataHolder& _rhs )
    {
        ex::value_swap( m_data, _rhs.m_data );
        ex::value_swap( m_size, _rhs.m_size );
        ref_counted_t::swap(_rhs);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

    //
    void*  data() const { return m_data; }
    size_t size() const { return m_size; }
    bool   is_empty() const { return m_size == 0; }

    // NOTE: borrowed data never respond for de-allocate.
    void borrow ( void* _pData, size_t _size )
    {
        free();
        m_data = _pData;
        m_size = _size;
        incRef (); // we simply inc the ref-count so that it never release.
    }

    //
    void alloc ( size_t _size ) 
    {
        free();
        m_data = ex_malloc ( _size );
        m_size = _size;
    }

    //
    void alloc ( void* _pData, size_t _size )
    {
        free();
        m_data = ex_malloc ( _size );
        ex::mem::cpy( m_data, _pData, _size );
        m_size = _size;
    }

    //
    void realloc ( size_t _size )
    {
        m_data = ex_realloc( m_data, _size );
        m_size = _size;
    }

    //
    void free ()
    {
        (*this) = DataHolder();
    }

    //
    void assign ( void* _pData, size_t _size )
    {
        free();
        m_data = _pData;
        m_size = _size;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    // get ptr_ref
    INLINE ptr_ref_t ptr_ref() { return m_data; }
    INLINE const_ptr_ref_t ptr_ref() const { return m_data; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    void*   m_data;
    size_t  m_size;

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // TODO: we should define second atomic classes. ----- molecular
    void serialize ( ISerializeNode* _pNode );

}; // end class DataHolder

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END DATAHOLDER_H_1250525636
// #################################################################################
