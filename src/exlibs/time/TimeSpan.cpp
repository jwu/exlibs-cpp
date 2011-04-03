// ======================================================================================
// File         : TimeSpan.cpp
// Author       : Wu Jie 
// Last Change  : 03/02/2010 | 13:39:59 PM | Tuesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "TimeSpan.h"

// ######################### 
namespace ex { 
// ######################### 

// KEEPME: code to set day,hour,min by secons { 
// // set min, day, month, years,
// uint32 int_sec = (uint32)_secs;

// uint32 mod_day = int_sec % _private::sec_in_one_day;
// uint32 mod_hour = mod_day % _private::sec_in_one_hour;
// uint32 mod_min = mod_hour % _private::sec_in_one_min;

// this->day = int_sec / _private::sec_in_one_day;
// this->hour = mod_day / _private::sec_in_one_hour;
// this->min = mod_hour / _private::sec_in_one_min;
// this->sec = mod_min;
// } KEEPME end 

///////////////////////////////////////////////////////////////////////////////
// static defines
///////////////////////////////////////////////////////////////////////////////

TimeSpan TimeSpan::INF = TimeSpan(EX_INT64_MAX);

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TimeSpan::TimeSpan ()
    : m_Microseconds (0)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TimeSpan::TimeSpan ( const self_t& _copy )
    : m_Microseconds (_copy.m_Microseconds)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TimeSpan::TimeSpan( int64 _microSeconds )
    : m_Microseconds (0)
{
    set (_microSeconds);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TimeSpan::TimeSpan ( int _seconds, int _milliseconds )
    : m_Microseconds (0)
{
    set (_seconds,_milliseconds);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TimeSpan::TimeSpan ( int _days, int _hours, int _miniutes, int _seconds, int _milliseconds )
{
    set( _days, _hours, _miniutes, _seconds, _milliseconds );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimeSpan::set ( int64 _microSeconds )
{
    m_Microseconds = _microSeconds;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimeSpan::set ( int _seconds, int _milliseconds )
{
    m_Microseconds = _seconds * TimeSpan::usecs_per_sec +
                     _milliseconds * TimeSpan::usecs_per_msec;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimeSpan::set ( int _days, int _hours, int _miniutes, int _seconds, int _milliseconds )
{
    m_Microseconds = _days * TimeSpan::usecs_per_day +
                     _hours * TimeSpan::usecs_per_hour +
                     _miniutes * TimeSpan::usecs_per_min +
                     _seconds * TimeSpan::usecs_per_sec +
                     _milliseconds * TimeSpan::usecs_per_msec;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimeSpan::SetSeconds_f32 ( float _secs )
{
    int64 int_sec = (int64)mathop::trunc(_secs);
    float f_ms = (_secs - int_sec) * 1000.0f;
    int64 int_ms = (int64)mathop::trunc(f_ms);
    int64 int_us = (int64)mathop::round((f_ms - int_ms) * 1000.0f);

    m_Microseconds = int_sec * TimeSpan::usecs_per_sec + 
                     int_ms  * TimeSpan::usecs_per_msec +
                     int_us;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimeSpan::SetSeconds_f64 ( double _secs )
{
    int64 int_sec = (int64)mathop::trunc(_secs);
    double f_ms = (_secs - int_sec) * 1000.0;
    int64 int_ms = (int64)mathop::trunc(f_ms);
    int64 int_us = (int64)mathop::round((f_ms - int_ms) * 1000.0);

    m_Microseconds = int_sec * TimeSpan::usecs_per_sec + 
                     int_ms  * TimeSpan::usecs_per_msec +
                     int_us;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimeSpan::SetMilliseconds_f32 ( float _ms )
{
    int64 int_ms = (int64)mathop::trunc(_ms);
    m_Microseconds = int_ms * TimeSpan::usecs_per_msec + int64( mathop::round((_ms - int_ms) * 1000.0f) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void TimeSpan::SetMilliseconds_f64 ( double _ms )
{
    int64 int_ms = (int64)mathop::trunc(_ms);
    m_Microseconds = int_ms * TimeSpan::usecs_per_msec + int64( mathop::round((_ms - int_ms) * 1000.0) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

double TimeSpan::TotalDays () const
{
    return (double)m_Microseconds / (double)TimeSpan::usecs_per_day;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

double TimeSpan::TotalHours () const
{
    return (double)m_Microseconds / (double)TimeSpan::usecs_per_hour;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

double TimeSpan::TotalMinutes () const
{
    return (double)m_Microseconds / (double)TimeSpan::usecs_per_min;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

double TimeSpan::TotalSeconds () const
{
    return (double)m_Microseconds / (double)TimeSpan::usecs_per_sec;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

double TimeSpan::TotalMilliseconds () const
{
	return (double)m_Microseconds / (double)TimeSpan::usecs_per_msec;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int64 TimeSpan::ToSecs () const
{
    return (int64)mathop::round(TotalSeconds());
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int64 TimeSpan::ToMSecs () const
{
    return (int64)mathop::round(TotalMilliseconds());
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int64 TimeSpan::ToUSecs () const
{
    return m_Microseconds;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int TimeSpan::Days () const
{
    return int(m_Microseconds / TimeSpan::usecs_per_day);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int TimeSpan::Hours () const
{
    int64 mod_day = m_Microseconds % TimeSpan::usecs_per_day;
    return int(mod_day / TimeSpan::usecs_per_hour);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int TimeSpan::Minutes () const
{
    int64 mod_day = m_Microseconds % TimeSpan::usecs_per_day;
    int64 mod_hour = mod_day % TimeSpan::usecs_per_hour;
    return int(mod_hour / TimeSpan::usecs_per_min);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int TimeSpan::Seconds () const
{
    int64 mod_day = m_Microseconds % TimeSpan::usecs_per_day;
    int64 mod_hour = mod_day % TimeSpan::usecs_per_hour;
    int64 mod_min = mod_hour % TimeSpan::usecs_per_min;
    return int(mod_min / TimeSpan::usecs_per_sec);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int TimeSpan::Milliseconds () const
{
    int64 mod_day = m_Microseconds % TimeSpan::usecs_per_day;
    int64 mod_hour = mod_day % TimeSpan::usecs_per_hour;
    int64 mod_min = mod_hour % TimeSpan::usecs_per_min;
    int64 mod_sec = mod_min % TimeSpan::usecs_per_sec;
    return int(mod_sec / TimeSpan::usecs_per_msec);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int TimeSpan::Microseconds () const
{
    int64 mod_day = m_Microseconds % TimeSpan::usecs_per_day;
    int64 mod_hour = mod_day % TimeSpan::usecs_per_hour;
    int64 mod_min = mod_hour % TimeSpan::usecs_per_min;
    int64 mod_sec = mod_min % TimeSpan::usecs_per_sec;
    int64 mod_msec = mod_sec % TimeSpan::usecs_per_msec;
    return int(mod_msec);
}

// ######################### 
} // end namespace ex 
// ######################### 

