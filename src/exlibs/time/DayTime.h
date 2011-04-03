// ======================================================================================
// File         : DayTime.h
// Author       : Wu Jie 
// Last Change  : 03/02/2010 | 21:53:04 PM | Tuesday,March
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef DAYTIME_H_1267537986
#define DAYTIME_H_1267537986
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "Date.h"
#include "TimeSpan.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class DayTime 
// 
// Purpose: This is time to express one-day 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL DayTime
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

    typedef DayTime self_t;

    ///////////////////////////////////////////////////////////////////////////////
    // static member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    static const uint msecs_per_sec  = 1000;
    static const uint msecs_per_min  = msecs_per_sec  * 60;
    static const uint msecs_per_hour = msecs_per_min  * 60;
    static const uint msecs_per_day  = msecs_per_hour * 24;

    static bool isValid ( uint _milli_sec );
    static bool isValid ( uint _hour, uint _min, uint _secs, uint _ms );

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // constructors
    DayTime ();
    DayTime ( const self_t& _copy );
    explicit DayTime ( uint _milli_sec );
    DayTime ( uint _hour, uint _min, uint _secs = 0, uint _ms = 0 );

    //
    void set ( uint _milli_sec );
    void set ( uint _hour, uint _min, uint _secs = 0, uint _ms = 0 );

    //
    uint Hours () const;
    uint Minutes () const;
    uint Seconds () const;
    uint Milliseconds () const;

    //
    uint   ToMSecs () const;
    uint64 ToUSecs () const;

    //
    TimeSpan To ( const self_t& _time_to ) const;

    // ======================================================== 
    // operations 
    // ======================================================== 

    INLINE self_t& operator = ( const self_t& _other ) { m_Milliseconds = _other.m_Milliseconds; return *this; }

    INLINE bool operator == ( const self_t& _other ) const { return m_Milliseconds == _other.m_Milliseconds; }
    INLINE bool operator != ( const self_t& _other ) const { return m_Milliseconds != _other.m_Milliseconds; }
    INLINE bool operator <  ( const self_t& _other ) const { return m_Milliseconds <  _other.m_Milliseconds; }
    INLINE bool operator <= ( const self_t& _other ) const { return m_Milliseconds <= _other.m_Milliseconds; }
    INLINE bool operator >  ( const self_t& _other ) const { return m_Milliseconds >  _other.m_Milliseconds; }
    INLINE bool operator >= ( const self_t& _other ) const { return m_Milliseconds >= _other.m_Milliseconds; }

    self_t& operator += ( const TimeSpan& _span ); 
    self_t& operator -= ( const TimeSpan& _span );

    friend INLINE self_t operator + ( const self_t& _time, const TimeSpan& _span ) { return _time.AddMSecs(  _span.ToMSecs() ); }
    friend INLINE self_t operator - ( const self_t& _time, const TimeSpan& _span ) { return _time.AddMSecs( -_span.ToMSecs() ); }
    friend INLINE TimeSpan operator - ( const self_t& _a /*dest*/, const self_t& _b /*start*/ ) { return _b.To(_a); }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    DayTime AddSecs ( int _secs ) const;
    DayTime AddMSecs ( int64 _ms ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string;
        string = ex::to_str<dec>(Hours()) + "h:" +
                 ex::to_str<dec>(Minutes())  + "m:" +
                 ex::to_str<dec>(Seconds())  + "s:" +
                 ex::to_str<dec>(Milliseconds()) + "ms";
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("day_time_t");
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // private member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    uint m_Milliseconds;

}; // end class DayTime

///////////////////////////////////////////////////////////////////////////////
// typedef
///////////////////////////////////////////////////////////////////////////////

typedef DayTime day_time_t;

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END DAYTIME_H_1267537986
// #################################################################################

