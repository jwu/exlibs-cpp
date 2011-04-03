// ======================================================================================
// File         : DateTime.h
// Author       : Wu Jie 
// Last Change  : 03/03/2010 | 01:01:10 AM | Wednesday,March
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef DATETIME_H_1267549274
#define DATETIME_H_1267549274
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "TimeSpan.h"
#include "Date.h"
#include "DayTime.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class DateTime 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL DateTime
{
    ///////////////////////////////////////////////////////////////////////////////
    // static member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    static DateTime FromJulianDays ( uint _julianDays );
    static DateTime FromMSecsSinceEpoch ( int64 _msecs );
    static DateTime CurrentDateTime ();
    static bool isValid ( uint _year, uint _month, uint _day, 
                          uint _hour, uint _min, uint _sec, uint _msec );

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // constructors
    DateTime (); // NOTE: default constructor. when contruct, it will get current time.
    DateTime ( const DateTime& _copy );
    explicit DateTime ( const date_t& _date, const day_time_t& _time = day_time_t() );
    DateTime ( uint _year, uint _month, uint _day,
            uint _hour = 0, uint _min = 0, uint _sec = 0, uint _msec = 0 );

    //
    void set ( const date_t& _date, const day_time_t& _time = day_time_t() );
    void set ( uint _year, uint _month, uint _day, 
               uint _hour = 0, uint _min = 0, uint _sec = 0, uint _msec = 0 );

    //
    date_t& Date() { return m_Date; }
    const date_t& Date() const { return m_Date; }

    //
    day_time_t& Time() { return m_DayTime; }
    const day_time_t& Time() const { return m_DayTime; }

    //
    uint Day () const           { return Date().Day(); }
    uint Month () const         { return Date().Month(); }
    uint Year () const          { return Date().Year(); }
    uint Hours () const         { return Time().Hours(); }
    uint Minutes () const       { return Time().Minutes(); }
    uint Seconds () const       { return Time().Seconds(); }
    uint Milliseconds () const  { return Time().Milliseconds(); }

    // ======================================================== 
    // operators 
    // ======================================================== 

    //
    INLINE DateTime& operator = ( const DateTime& _time ) 
    {
        m_Date = _time.m_Date;
        m_DayTime = _time.m_DayTime;
        return *this;
    }

    //
    INLINE bool operator == ( const DateTime& _rhs ) const { return !operator!=(_rhs); }
    INLINE bool operator != ( const DateTime& _rhs ) const { return m_Date != _rhs.m_Date || m_DayTime != _rhs.m_DayTime; }

    //
    INLINE bool operator <  ( const DateTime& _rhs ) const 
    { 
        if ( m_Date < _rhs.m_Date )
            return true;
        else if ( m_Date == _rhs.m_Date )
            return m_DayTime < _rhs.m_DayTime;
        return false;
    }
    INLINE bool operator <= ( const DateTime& _rhs ) const 
    { 
        if ( m_Date < _rhs.m_Date )
            return true;
        else if ( m_Date == _rhs.m_Date )
            return m_DayTime <= _rhs.m_DayTime;
        return false;
    }
    INLINE bool operator >  ( const DateTime& _rhs ) const { return !(*this <= _rhs); }
    INLINE bool operator >= ( const DateTime& _rhs ) const { return !(*this < _rhs); }

    //
    DateTime& operator += ( const timespan_t& _span );
    DateTime& operator -= ( const timespan_t& _span );

    //
    friend timespan_t operator - ( const DateTime& _dest, const DateTime& _start )
    {
        int64 dayDiff = int64( _dest.Date().ToJulianDays() ) - int64( _start.Date().ToJulianDays() );
        int64 msDiff = int64( _dest.Time().ToMSecs() ) - int64( _start.Time().ToMSecs() );
        int64 result = (dayDiff * day_time_t::msecs_per_day + msDiff) * 1000;
        return timespan_t(result);
    }
    friend DateTime operator + ( const DateTime& _dateTime, const timespan_t& _span )
    {
        DateTime tmp = _dateTime;
        tmp += _span;
        return tmp;
    }
    friend DateTime operator - ( const DateTime& _dateTime, const timespan_t& _span )
    {
        DateTime tmp = _dateTime;
        tmp -= _span;
        return tmp;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string;
        string = ex::to_str<dec>(m_Date) + " " + ex::to_str<dec>(m_DayTime);
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("date_time_t");
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    date_t      m_Date;
    day_time_t  m_DayTime;

}; // end class DateTime

///////////////////////////////////////////////////////////////////////////////
// typedefs
///////////////////////////////////////////////////////////////////////////////

typedef DateTime date_time_t; // NOTE: avoid the conflict with the c-keyword time_t

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END DATETIME_H_1267549274
// #################################################################################
