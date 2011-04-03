// ======================================================================================
// File         : StackAllocator.cpp
// Author       : Wu Jie 
// Description  : 
// ======================================================================================


///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "StackAllocator.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// defines 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

StackAllocator::StackAllocator()
{
    ex::mem::zero( m_stackPool, EX_MAX_STACK_POOL );
    m_stackPoint = m_stackPool + (EX_MAX_STACK_POOL-1); 
}


// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

StackAllocator::~StackAllocator()
{
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void* StackAllocator::alloc( size_t _size )
{
    ex_assert( uint32(m_stackPoint-m_stackPool) >= _size, "Can't alloc %d size memory, stack has overflowed", _size );
    m_stackPoint -= _size;
    return m_stackPoint;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void* StackAllocator::allocAligned( size_t _size, uint _alignment )
{
    ex_assert( uint32(m_stackPoint-m_stackPool) >= _size, "Can't alloc %d size memory, stack has overflowed", _size );

    // TODO: implement it
    return NULL;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void StackAllocator::free( size_t _size )
{
    ex_assert( m_stackPoint + _size <= m_stackPool + (EX_MAX_STACK_POOL-1), "Can't free %d size memory, stack has overflowed", _size );
    m_stackPoint += _size;
}

// #########################
} // end namespace ex 
// #########################

