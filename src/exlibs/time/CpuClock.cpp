// ======================================================================================
// File         : CpuClock.cpp
// Author       : Wu Jie 
// Last Change  : 03/03/2010 | 09:24:45 AM | Wednesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "CpuClock.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// static member functions 
///////////////////////////////////////////////////////////////////////////////

uint64 CpuClock::s_CpuFrequency = 0;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t CpuClock::init ()
{
    CpuClock::s_CpuFrequency = cpu_freq();

    // TODO: can get more cpu info.
    // TODO: may be we need class separatly for cpu-info.

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint32 CpuClock::GetCurrentMSecs ()
{
    // TODO: timeGetTime() looks like hacky...
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

CpuClock::CpuClock ()
    : m_StartCouter (0)
    , m_StopCouter (0)
    , m_LastCouter (0)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void CpuClock::start ()
{
    m_StartCouter = cpu_cycle ();
    m_LastCouter = m_StartCouter;
}

// ------------------------------------------------------------------ 
// Desc: 
// count will count the time from start to now.
// ------------------------------------------------------------------ 

timespan_t CpuClock::Elapsed ()
{
    //
    uint64 curCounter = cpu_cycle ();
    uint64 deltaCycle = curCounter - m_StartCouter;

    //
    return GetTimeSpan(deltaCycle);
}

// ------------------------------------------------------------------ 
// Desc: 
// count-last will count the time from last-cout to now.
// ------------------------------------------------------------------ 

timespan_t CpuClock::count ()
{
    //
    uint64 curCounter = cpu_cycle ();
    uint64 deltaCycle = curCounter - m_LastCouter;
    m_LastCouter = curCounter;

    //
    return GetTimeSpan(deltaCycle);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

timespan_t CpuClock::Stop ()
{
    //
    m_StopCouter = cpu_cycle ();
    uint64 deltaCycle = m_StopCouter - m_StartCouter;

    // reset the couter
    m_StartCouter = 0;
    m_StopCouter = 0;
    m_LastCouter = 0;

    //
    return GetTimeSpan(deltaCycle);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

timespan_t CpuClock::GetTimeSpan ( uint64 _deltaCycle )
{
    double deltaTime = (double)_deltaCycle/(double)CpuClock::Frequency();
    timespan_t timeSpan;
    timeSpan.SetSeconds_f64 (deltaTime);
    return timeSpan;
}

// ######################### 
} // end namespace ex 
// ######################### 

