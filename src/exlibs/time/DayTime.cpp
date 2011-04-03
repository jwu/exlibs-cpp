// ======================================================================================
// File         : DayTime.cpp
// Author       : Wu Jie 
// Last Change  : 03/02/2010 | 21:53:16 PM | Tuesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "DayTime.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// static member defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool DayTime::isValid ( uint _hour, uint _min, uint _secs, uint _ms )
{
    return _hour < 24 && _min < 60 && _secs < 60 && _ms < 1000;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool DayTime::isValid ( uint _milli_sec )
{
    return _milli_sec <= DayTime::msecs_per_day;
}

///////////////////////////////////////////////////////////////////////////////
// DayTime
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DayTime::DayTime ()
    : m_Milliseconds (0)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DayTime::DayTime ( const self_t& _copy )
    : m_Milliseconds (_copy.m_Milliseconds)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DayTime::DayTime ( uint _milli_sec )
    : m_Milliseconds (0)
{
    set (_milli_sec);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DayTime::DayTime ( uint _hour, uint _min, uint _secs, uint _ms )
    : m_Milliseconds (0)
{
    set ( _hour, _min, _secs, _ms );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void DayTime::set ( uint _milli_sec )
{
    if ( !DayTime::isValid(_milli_sec) )
    {
        ex_warning ( "can't set time (%dms). the value is invalid! large than one-day.", _milli_sec );
        return;
    }
    m_Milliseconds = _milli_sec;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void DayTime::set ( uint _hour, uint _min, uint _secs, uint _ms )
{
    if ( !DayTime::isValid( _hour, _min, _secs, _ms ) )
    {
        ex_warning ( "can't set time (%dh,%dm,%ds,%dms). the value is invalid!", _hour, _min, _secs, _ms );
        return;
    }
    m_Milliseconds = (_hour*DayTime::msecs_per_hour + _min*DayTime::msecs_per_min + _secs*DayTime::msecs_per_sec + _ms);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint DayTime::Hours () const
{
    return m_Milliseconds / DayTime::msecs_per_hour;
}


// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint DayTime::Minutes () const
{
    uint mod_hour = m_Milliseconds % DayTime::msecs_per_hour;
    return mod_hour / DayTime::msecs_per_min;
}


// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint DayTime::Seconds () const
{
    uint mod_hour = m_Milliseconds % DayTime::msecs_per_hour;
    uint mod_min = mod_hour % DayTime::msecs_per_min;
    return mod_min / DayTime::msecs_per_sec;
}


// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint DayTime::Milliseconds () const
{
    uint mod_hour = m_Milliseconds % DayTime::msecs_per_hour;
    uint mod_min = mod_hour % DayTime::msecs_per_min;
    uint mod_sec = mod_min % DayTime::msecs_per_sec;
    return mod_sec;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint DayTime::ToMSecs () const
{
    return m_Milliseconds;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint64 DayTime::ToUSecs () const
{
    return m_Milliseconds * 1000;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DayTime DayTime::AddSecs ( int _secs ) const
{
    return AddMSecs(_secs * 1000);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DayTime DayTime::AddMSecs ( int64 _ms ) const
{
    DayTime t;

    int64 msecs = ( m_Milliseconds + _ms ) % DayTime::msecs_per_day;
    msecs = msecs < 0 ? DayTime::msecs_per_day + msecs : msecs;
    t.m_Milliseconds = static_cast<uint>(msecs);

    return t;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DayTime& DayTime::operator += ( const TimeSpan& _span ) 
{
    int64 msecs = ( m_Milliseconds + _span.ToMSecs() ) % DayTime::msecs_per_day;
    msecs = msecs < 0 ? DayTime::msecs_per_day + msecs : msecs;
    m_Milliseconds = static_cast<uint>(msecs);
    return *this;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DayTime& DayTime::operator -= ( const TimeSpan& _span )
{
    int64 msecs = ( m_Milliseconds - _span.ToMSecs() ) % DayTime::msecs_per_day;
    msecs = msecs < 0 ? DayTime::msecs_per_day + msecs : msecs;
    m_Milliseconds = static_cast<uint>(msecs);
    return *this;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TimeSpan DayTime::To ( const self_t& _time_to ) const
{
    if ( _time_to.m_Milliseconds < this->m_Milliseconds )
        return TimeSpan ( int64(_time_to.m_Milliseconds + DayTime::msecs_per_day - this->m_Milliseconds) * 1000 );
    else
        return TimeSpan( int64(_time_to.m_Milliseconds - this->m_Milliseconds) * 1000 ); 
}

// ######################### 
} // end namespace ex 
// ######################### 


