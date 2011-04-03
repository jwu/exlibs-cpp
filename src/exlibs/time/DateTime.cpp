// ======================================================================================
// File         : DateTime.cpp
// Author       : Wu Jie 
// Last Change  : 03/02/2010 | 21:52:32 PM | Tuesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "DateTime.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// static member functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DateTime DateTime::CurrentDateTime ()
{
    return DateTime();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DateTime DateTime::FromJulianDays ( uint _julianDays )
{
    DateTime dateTime = DateTime ( date_t(_julianDays) );
    return dateTime;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DateTime DateTime::FromMSecsSinceEpoch ( int64 _msecs )
{
    static const DateTime dateTime( 1970, 1, 1 );
    timespan_t span ( _msecs * 1000 );
    return dateTime + span;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool isValid ( uint _year, uint _month, uint _day, 
               uint _hour, uint _min, uint _sec, uint _msec )
{
    return date_t::isValid(_year, _month, _day) && day_time_t::isValid(_hour, _min, _sec, _msec);
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DateTime::DateTime ()
{
#if (EX_PLATFORM == EX_WIN32)
    SYSTEMTIME time;
    GetLocalTime(&time);
    set ( time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds );
#else
    time_t now = time(NULL);
    tm* ts = localtime(&now);
    set ( ts->tm_year, ts->tm_mon, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec );
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DateTime::DateTime ( const DateTime& _copy )
    : m_Date (_copy.m_Date)
    , m_DayTime (_copy.m_DayTime)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DateTime::DateTime ( const date_t& _date, const day_time_t& _time )
{
    set ( _date, _time );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DateTime::DateTime ( uint _year, uint _month, uint _day, 
                       uint _hour, uint _min, uint _sec, uint _msec )
{
    set ( _year, _month, _day, _hour, _min, _sec, _msec );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void DateTime::set ( const date_t& _date, const day_time_t& _time )
{
    m_Date = _date;
    m_DayTime = _time;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void DateTime::set ( uint _year, uint _month, uint _day, uint _hour, uint _min, uint _sec, uint _msec )
{
    m_Date.set ( _year, _month, _day );
    m_DayTime.set ( _hour, _min, _sec, _msec );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DateTime& DateTime::operator += ( const timespan_t& _span )
{
    int64 totalMSecs = _span.ToMSecs();
    int64 days = totalMSecs / day_time_t::msecs_per_day;
    int64 overrun = totalMSecs % day_time_t::msecs_per_day;

    if ( (-overrun) > m_DayTime.ToMSecs()  )
    {
        days -= 1;
    }
    else if (  overrun + m_DayTime.ToMSecs() > day_time_t::msecs_per_day )
    {
        days += 1;
    }

    m_Date += static_cast<int>(days);
    m_DayTime += timespan_t(overrun * 1000);
    return *this;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

DateTime& DateTime::operator -= ( const timespan_t& _span )
{
    int64 totalMSecs = _span.ToMSecs();
    int64 days = totalMSecs / day_time_t::msecs_per_day;
    int64 overrun = totalMSecs % day_time_t::msecs_per_day;

    if( overrun > m_DayTime.ToMSecs() )
    {
        days += 1;
    }
    else if(m_DayTime.ToMSecs() - overrun > day_time_t::msecs_per_day)
    {
        days -= 1;
    }

    m_Date -= static_cast<int>(days);
    m_DayTime -= timespan_t( overrun * 1000 );
    return *this;
}


// ######################### 
} // end namespace ex 
// ######################### 

