// ======================================================================================
// File         : Date.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 15:27:08 PM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef DATE_H_1267508061
#define DATE_H_1267508061
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class Date 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

struct EX_LIBS_DLL Date
{
    ///////////////////////////////////////////////////////////////////////////////
    // static member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    static const char* WeekDayName ( uint _wday );
    static const char* MonthName ( uint _month );

    static bool isValid     ( uint _year, uint _month, uint _day );
    static bool IsLeapYear  ( uint _year );
    static void greg2jul    ( uint* _pJul_out, int _year, int _month, int _day ); // NOTE: the input y,m,d must be int
    static void jul2greg    ( uint _jul, int* _pYear_out, int* _pMonth_out, int* _pDay_out ); // NOTE: the input y,m,d must be int

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    Date ();
    Date ( const Date& _date );
    explicit Date ( uint _julianDays );
    Date ( uint _year, uint _month, uint _day );

    //
    void set ( uint _julian );
    void set ( uint _year, uint _month, uint _day );

    //
    uint ToJulianDays () const { return m_Julian; }

    //
    uint Day () const;
    uint Month () const;
    uint Year () const;

    //
    uint DayOfWeek () const;
    uint DayOfYear () const;
    uint DaysInMonth () const;

    //
    bool IsLeapYear() const;

    //
    INLINE Date& operator =  ( const Date& _date ) { m_Julian = _date.m_Julian; return *this; }
    INLINE Date& operator += ( int _days ) { m_Julian += _days; return *this; }
    INLINE Date& operator -= ( int _days ) { m_Julian -= _days; return *this; }
    INLINE Date& operator ++ () { ++m_Julian; return *this; }
    INLINE Date& operator -- () { --m_Julian; return *this; }

    INLINE bool operator == ( const Date& _date ) const { return m_Julian == _date.m_Julian; }
    INLINE bool operator != ( const Date& _date ) const { return m_Julian != _date.m_Julian; }
    INLINE bool operator <  ( const Date& _date ) const { return m_Julian <  _date.m_Julian; }
    INLINE bool operator <= ( const Date& _date ) const { return m_Julian <= _date.m_Julian; }
    INLINE bool operator >  ( const Date& _date ) const { return m_Julian >  _date.m_Julian; }
    INLINE bool operator >= ( const Date& _date ) const { return m_Julian >= _date.m_Julian; }

    friend INLINE Date operator + ( const Date& _date, int _days ) { return Date(_date.m_Julian+_days); }
    friend INLINE Date operator + ( int _days, const Date& _date ) { return _date + _days; }
    friend INLINE Date operator - ( const Date& _date, int _days ) { return _date + -_days; }
    friend INLINE int operator - ( const Date& _a, const Date& _b ) { return _a.m_Julian - _b.m_Julian; }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string;
        string = ex::to_str<dec>(Year()) + "-" +
                 ex::to_str<dec>(Month())  + "-" +
                 ex::to_str<dec>(Day());
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("date_t");
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // private member
    ///////////////////////////////////////////////////////////////////////////////

protected:

    uint m_Julian;

}; // end struct Date

///////////////////////////////////////////////////////////////////////////////
// typedefs
///////////////////////////////////////////////////////////////////////////////

typedef Date date_t;

// ######################### 
} // end namespace ex 
// ######################### 


// #################################################################################
#endif // END DATE_H_1267508061
// #################################################################################


