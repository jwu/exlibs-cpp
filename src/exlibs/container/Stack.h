// ======================================================================================
// File         : Stack.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:35:11 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef STACK_H_1250523315
#define STACK_H_1250523315
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "Deque.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Stack
// 
// Purpose: improve version of std::stack
// 
///////////////////////////////////////////////////////////////////////////////
 
template < typename T, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class Stack : public std::stack< T, std::deque< T, ContainerAllocator<T,TAllocator_T> > >
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    typedef Stack< T, TAllocator_T >                                               self_t;
	typedef std::stack< T, std::deque< T, ContainerAllocator<T,TAllocator_T> > >   base_t;
	typedef std::deque< T, ContainerAllocator<T,TAllocator_T> >                    container_t;

    typedef typename container_t::size_type          sz_t;
    typedef typename container_t::value_type         value_t;
    typedef typename container_t::reference          ref_t;
    typedef typename container_t::const_reference    const_ref_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor  
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    Stack()
        : base_t()
    {
    }

    //
    ~Stack()
    {
        clear();
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    bool empty() const { return base_t::empty(); }
    sz_t size() const { return base_t::size(); }

    //
    ref_t top() { return base_t::top(); }
    const_ref_t top() const { return base_t::top(); }
    
    //
    void push( const value_t& _val ) { base_t::push(_val); } 
    void pop() { base_t::pop(); } 
    value_t get_pop() {
        value_t copy(top());
        base_t::pop(); 
        return copy;
    }

    //
    void clear() {
        while ( !this->empty() )
            this->pop();
    }

}; // end class Stack

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END STACK_H_1250523315
// #################################################################################
