// ======================================================================================
// File         : Queue.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:34:46 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef QUEUE_H_1250523290
#define QUEUE_H_1250523290
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "Deque.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Queue
// 
// Purpose: improve version of std::queue
// 
///////////////////////////////////////////////////////////////////////////////
 
template < typename T, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class Queue : protected std::queue< T, std::deque< T, ContainerAllocator<T,TAllocator_T> > >
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    typedef Queue< T, TAllocator_T >                                               self_t;
	typedef std::queue< T, std::deque< T, ContainerAllocator<T,TAllocator_T> > >    base_t;
	typedef std::deque< T, ContainerAllocator<T,TAllocator_T> >                     container_t;

    typedef typename container_t::size_type          sz_t;
    typedef typename container_t::value_type         value_t;
    typedef typename container_t::reference          ref_t;
    typedef typename container_t::const_reference    const_ref_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    Queue()
        : base_t()
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    bool empty() const { return base_t::empty(); }
    sz_t size() const { return base_t::size(); }

    //
    ref_t front() { return base_t::front(); }
    const_ref_t front() const { return base_t::front(); }

    //
    ref_t back() { return base_t::back(); }
    const_ref_t back() const { return base_t::back(); }

    // 
    void push( const value_t& _val ) { base_t::push(_val); }
    void pop() { base_t::pop(); }
    value_t get_pop() 
    {
        value_t copy(front());
        base_t::pop(); 
        return copy;
    }

    //
    void clear()
    {
        while ( !this->empty() )
            this->pop();
    }

}; // end class Queue 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END QUEUE_H_1250523290
// #################################################################################
