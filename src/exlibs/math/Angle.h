// ======================================================================================
// File         : Angle.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:16:15 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ANGLE_H_1250525778
#define ANGLE_H_1250525778
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////


// #########################
namespace ex { 
// #########################

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// enum
namespace AngleType {
    enum Enum {
        radians = 0,
        degrees
    }; // end EType
}

///////////////////////////////////////////////////////////////////////////////
// class Angle 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class Angle
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    typedef Angle<T> self_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    Angle ()
        : m_radians(0)
    {
    }

    //
    Angle ( const self_t& _copy )
        : m_radians(_copy.m_radians)
    {
    }

    //
    explicit Angle ( T _value, AngleType::Enum _eType = AngleType::radians ) 
    {
        if ( _eType == AngleType::radians )
            setRadians(_value);
        else if ( _eType == AngleType::degrees )
            setDegrees(_value);
    }

    // operator =
    INLINE self_t& operator = ( const self_t& _copy ) { setRadians(_copy.toRadians()); return *this; } 

    // operator T
    INLINE operator T () { return m_radians; }
    INLINE operator const T& () const { return m_radians; }


    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // set
    INLINE void setRadians ( T _radians ) { 
        if ( m_radians >= T(0) )
            m_radians = mathop::fmod(_radians,T(EX_TWO_PI)); 
        else
            m_radians = T(EX_TWO_PI) + mathop::fmod(_radians,T(EX_TWO_PI)); 
        verifyIsFinite(); 
    }
    INLINE void setDegrees ( T _degrees ) { setRadians( T(EX_DEG_TO_RAD) * _degrees ); }

    // cast to
    INLINE T toRadians () const { verifyIsFinite(); return m_radians; }
    INLINE T toDegrees180 () const { verifyIsFinite(); return m_radians >= T(EX_PI) ? T(EX_RAD_TO_DEG*m_radians) - 360 : T(EX_RAD_TO_DEG*m_radians); } // from -180 to 180
    INLINE T toDegrees360 () const { verifyIsFinite(); return T(EX_RAD_TO_DEG*m_radians); } // from 0 to 360

    // operator 
    INLINE self_t operator - () const { return Angle( -toRadians(), AngleType::radians ); } 
    self_t& negative() { setRadians( -toRadians() ); return *this; }

    INLINE self_t& operator *= ( const self_t& _angle ) { setRadians( toRadians() * _angle.toRadians() ); return *this; }
    INLINE self_t& operator *= ( const T& _scale )      { setRadians( toRadians() * _scale ); return *this; }
    INLINE self_t& operator /= ( const self_t& _angle ) { setRadians( toRadians() / _angle.toRadians() ); return *this; }
    INLINE self_t& operator /= ( const T& _scale )      { setRadians( toRadians() / _scale ); return *this; }
    INLINE self_t& operator += ( const self_t& _angle ) { setRadians( toRadians() + _angle.toRadians() ); return *this; }
    INLINE self_t& operator -= ( const self_t& _angle ) { setRadians( toRadians() - _angle.toRadians() ); return *this; }

    INLINE bool operator < ( const self_t& _angle )  const { return toRadians() <  _angle.toRadians(); }
    INLINE bool operator <= ( const self_t& _angle ) const { return toRadians() <= _angle.toRadians(); }
    INLINE bool operator > ( const self_t& _angle )  const { return toRadians() >  _angle.toRadians(); }
    INLINE bool operator >= ( const self_t& _angle ) const { return toRadians() >= _angle.toRadians(); }
    INLINE bool operator == ( const self_t& _angle ) const { return mathop::is_equal( toRadians(), _angle.toRadians(), mathop::epsilon<T>() ); }
    INLINE bool operator != ( const self_t& _angle ) const { return !(*this == _angle); }
    INLINE bool isZero () const { return mathop::is_zero( toRadians(), mathop::epsilon<T>() ); }

    ///////////////////////////////////////////////////////////////////////////////
    // static public member functions 
    ///////////////////////////////////////////////////////////////////////////////

    static self_t degrees ( T _degrees ) { return Angle( _degrees, AngleType::degrees ); }
    static self_t radians ( T _radians ) { return Angle( _radians, AngleType::radians ); }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    INLINE void verifyIsFinite () const { ex_assert( !mathop::isNaN<T>(m_radians), "error: NaN value" ); }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string = to_str<FLAGS>(m_radians);
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID = string_id_t( string_t("Angle<") + TypeTraits<T>::type_name().c_str() + ">" );
        return strID;
    }
    void serialize ( ISerializeNode* _pNode );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    T m_radians;

}; // end class Angle
    

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END ANGLE_H_1250525778
// #################################################################################
