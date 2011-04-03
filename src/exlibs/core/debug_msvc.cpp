// ======================================================================================
// File         : debug_msvc.cpp
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 09:57:57 AM | Saturday,August
// Description  : refs: http://msinilo.pl/blog/?p=571
// ======================================================================================

// USAGE:
// void Hero::Regenerate()  
// {  
//     ex::SetDataBreakpoint(m_VitalityPoints, eDBT_None); // Disable  
//     m_VitalityPoints += m_RegenerationPerTick;  
//     ex::SetDataBreakpoint(m_VitalityPoints, eDBT_Write); // Enable again  
// }  

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"

///////////////////////////////////////////////////////////////////////////////
// defiens
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace _private { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int FindBreakpointIndexForAddress(const void* address, CONTEXT& ctx, DWORD** retDebugReg)
{
    int dataIndex(-1);
    *retDebugReg = 0;
    if (ctx.Dr0 == (size_t)address)
    {
        dataIndex = 0;
        *retDebugReg = &ctx.Dr0;
    }
    else if (ctx.Dr1 == (size_t)address)
    {
        dataIndex = 1;
        *retDebugReg = &ctx.Dr1;
    }
    else if (ctx.Dr2 == (size_t)address)
    {
        dataIndex = 2;
        *retDebugReg = &ctx.Dr2;
    }
    else if (ctx.Dr3 == (size_t)address)
    {
        dataIndex = 3;
        *retDebugReg = &ctx.Dr3;
    }
    return dataIndex;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int FindFreeBreakpointIndex(CONTEXT& ctx, DWORD** retDebugReg)
{
	return FindBreakpointIndexForAddress(NULL, ctx, retDebugReg);
}

// ------------------------------------------------------------------ 
// Desc: Indexed with EDataBreakpointType
// ------------------------------------------------------------------ 

const uint32 s_triggerMasks[] =
{
	0xFFFFFFFF, // NONE
	1,			// WRITE
	3,			// READWRITE
	0,			// EXECUTE
};

// ------------------------------------------------------------------ 
// Desc: Indexed with EDataBreakpointSize
// ------------------------------------------------------------------ 

const uint32 s_sizeMasks[] =
{
	0, 1, 3, 2,
};

// ######################### 
} // end namespace _private 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: SetDataBreakpoint
// ------------------------------------------------------------------ 

bool SetDataBreakpoint ( const void* _addr, int _accessType, int _dataSize )
{
    CONTEXT threadContext;
    threadContext.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    const HANDLE currentThread = ::GetCurrentThread();
    if (!::GetThreadContext(currentThread, &threadContext))
        return false;

    DWORD* dataDebugReg(0);
    int dataIndex = _private::FindBreakpointIndexForAddress(_addr, threadContext, &dataDebugReg);
    bool success(false);
    // clear data breakpoint
    if (_accessType == DATA_BREAKPOINT_NONE)
    {
        if (dataIndex >= 0)
        {
            threadContext.Dr7 &= ~(3 << (dataIndex * 2));
            *dataDebugReg = 0; // clear _addr
            success = true;
        }
    }
    else // set/change data breakpoint
    {
        if (dataIndex < 0)
            dataIndex = _private::FindFreeBreakpointIndex(threadContext, &dataDebugReg);

        if (dataIndex >= 0)
        {
            // Enable breakpoint.
            threadContext.Dr7 &= ~(3 << (dataIndex * 2));
            threadContext.Dr7 |= 3 << (dataIndex * 2); // local & global

            // Set trigger mode.
            // (starts at bit 16, 2 bits per entry).
            const uint32 triggerMask = _private::s_triggerMasks[_accessType];
            threadContext.Dr7 &= ~(3 << ((dataIndex * 2) + 16)); // clear old mask
            threadContext.Dr7 |= triggerMask << ((dataIndex * 2) + 16);

            // Set data size
            // (starts at bit 24, 2 bits per entry).
            threadContext.Dr7 &= ~(3 << ((dataIndex * 2) + 24)); // clear old mask
            const uint32 sizeMask = _private::s_sizeMasks[_dataSize];
            threadContext.Dr7 |= sizeMask << ((dataIndex * 2) + 24);

            *dataDebugReg = (DWORD)((size_t)_addr);

            success = true;
        }
    }

    //
    if (success)
    {
        success = (::SetThreadContext(currentThread, &threadContext) != 0);
    }

    return success;
}

// ######################### 
} // end namespace ex 
// ######################### 

