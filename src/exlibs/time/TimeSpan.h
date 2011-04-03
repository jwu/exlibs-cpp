// ======================================================================================
// File         : TimeSpan.h
// Author       : Wu Jie 
// Last Change  : 03/02/2010 | 13:36:33 PM | Tuesday,March
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef TIMESPAN_H_1267508204
#define TIMESPAN_H_1267508204
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// defiens 
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class TimeSpan 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL TimeSpan
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

    typedef TimeSpan self_t;

    ///////////////////////////////////////////////////////////////////////////////
    // static public functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    static const int64 usecs_per_msec = 1000;
    static const int64 usecs_per_sec  = usecs_per_msec * 1000;
    static const int64 usecs_per_min  = usecs_per_sec  * 60;
    static const int64 usecs_per_hour = usecs_per_min  * 60;
    static const int64 usecs_per_day  = usecs_per_hour * 24;

    static TimeSpan INF; // NOTE: INFINITY has been used as gcc-compiler builtin keyword.

public:

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

    // constructors
    TimeSpan ();
    TimeSpan ( const self_t& _copy );
    explicit TimeSpan ( int64 _microSeconds );
    TimeSpan ( int _seconds, int _milliseconds = 0 );
    TimeSpan ( int _days, int _hours, int _miniutes, int _seconds = 0, int _milliseconds = 0 );

    //
    void set ( int64 _microSeconds );
    void set ( int _seconds, int _milliseconds = 0 );
    void set ( int _days, int _hours, int _miniutes, int _seconds = 0, int _milliseconds = 0 );

    //
    void SetSeconds_f32 ( float _secs );
    void SetSeconds_f64 ( double _secs );

    //
    void SetMilliseconds_f32 ( float _ms );
    void SetMilliseconds_f64 ( double _ms );

    //
    double TotalDays () const;
    double TotalHours () const;
    double TotalMinutes () const;
    double TotalSeconds () const;
    double TotalMilliseconds () const;

    int64  ToSecs () const; // total seconds
    int64  ToMSecs () const; // total milliseconds
    int64  ToUSecs () const; // total microseconds

    //
    int Days () const;
    int Hours () const;
    int Minutes () const;
    int Seconds () const;
    int Milliseconds () const;
    int Microseconds () const;

    // ======================================================== 
    // operations 
    // ======================================================== 

    INLINE self_t& operator = ( const self_t& _span ) { m_Microseconds = _span.m_Microseconds; return *this; }
    INLINE self_t& operator = ( int64 _micro_sec )    { m_Microseconds = _micro_sec; return *this; }

    INLINE bool operator == ( const self_t& _span ) const { return m_Microseconds == _span.m_Microseconds; }
    INLINE bool operator != ( const self_t& _span ) const { return m_Microseconds != _span.m_Microseconds; }
    INLINE bool operator >  ( const self_t& _span ) const { return m_Microseconds >  _span.m_Microseconds; }
    INLINE bool operator >= ( const self_t& _span ) const { return m_Microseconds >= _span.m_Microseconds; }
    INLINE bool operator <  ( const self_t& _span ) const { return m_Microseconds <  _span.m_Microseconds; }
    INLINE bool operator <= ( const self_t& _span ) const { return m_Microseconds <= _span.m_Microseconds; }

    INLINE bool operator == ( int64 _micro_sec ) const { return m_Microseconds == _micro_sec; }
    INLINE bool operator != ( int64 _micro_sec ) const { return m_Microseconds != _micro_sec; }
    INLINE bool operator >  ( int64 _micro_sec ) const { return m_Microseconds >  _micro_sec; }
    INLINE bool operator >= ( int64 _micro_sec ) const { return m_Microseconds >= _micro_sec; }
    INLINE bool operator <  ( int64 _micro_sec ) const { return m_Microseconds <  _micro_sec; }
    INLINE bool operator <= ( int64 _micro_sec ) const { return m_Microseconds <= _micro_sec; }

    INLINE self_t  operator +  ( const self_t& _span ) const { return TimeSpan( m_Microseconds + _span.m_Microseconds ); }
    INLINE self_t  operator -  ( const self_t& _span ) const { return TimeSpan( m_Microseconds - _span.m_Microseconds ); }
    INLINE self_t& operator += ( const self_t& _span )       { m_Microseconds += _span.m_Microseconds; return *this; }
    INLINE self_t& operator -= ( const self_t& _span )       { m_Microseconds -= _span.m_Microseconds; return *this; }

    INLINE self_t  operator +  ( int64 _micro_sec ) const { return TimeSpan( m_Microseconds + _micro_sec ); }
    INLINE self_t  operator -  ( int64 _micro_sec ) const { return TimeSpan( m_Microseconds - _micro_sec ); }
    INLINE self_t& operator += ( int64 _micro_sec )       { m_Microseconds += _micro_sec; return *this; }     
    INLINE self_t& operator -= ( int64 _micro_sec )       { m_Microseconds -= _micro_sec; return *this; }     

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string;
        string = ex::to_str<dec>(Days())  + "d:" +
                 ex::to_str<dec>(Hours()) + "h:" +
                 ex::to_str<dec>(Minutes())  + "m:" +
                 ex::to_str<dec>(Seconds())  + "s:" +
                 ex::to_str<dec>(Milliseconds()) + "ms:" +
                 ex::to_str<dec>(Microseconds()) + "us";
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("time_span_t");
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // private member data
    ///////////////////////////////////////////////////////////////////////////////

private:

    int64 m_Microseconds;

}; // end class TimeSpan

///////////////////////////////////////////////////////////////////////////////
// typedefs
///////////////////////////////////////////////////////////////////////////////

typedef TimeSpan timespan_t;

// ######################### 
} // end namespace ex 
// ######################### 



// #################################################################################
#endif // END TIMESPAN_H_1267508204
// #################################################################################

