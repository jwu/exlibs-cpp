// ======================================================================================
// File         : Plane.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:18:12 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PLANE_H_1250525895
#define PLANE_H_1250525895
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Plane 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class Plane
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    typedef Plane self_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destrucotor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    Plane()
        : m_Normal( Vector3<float>::zero ),
          m_Distance(0.0f)
    {
    }

    //
    Plane( const self_t& _copy )
        : m_Normal(_copy.m_Normal),
          m_Distance(_copy.m_Distance)
    {
    }

    //
    Plane( const Vector3<float>& _normal, float _distance )
        : m_Normal(_normal),
          m_Distance(_distance)
    {
    }

    //
    Plane( const Vector3<float>& _normal, const Vector3<float>& _point )
    {
        this->set( _normal, _point );
    }

    //
    Plane( const Vector3<float>& _p1, const Vector3<float>& _p2, const Vector3<float>& _p3 )
    {
        this->set( _p1, _p2, _p3 );
    }

    //
    ~Plane() {}

    //
    INLINE self_t& operator = ( const self_t& _copy )
    {
        this->set(_copy);
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    INLINE void set ( const self_t& _other ) { m_Normal = _other.m_Normal; m_Distance = _other.m_Distance; }
    INLINE void set ( const Vector3<float>& _normal, float _distance ) { m_Normal = _normal; m_Distance = _distance; }
    INLINE void set ( const Vector3<float>& _normal, const Vector3<float>& _point )
    {
        m_Normal = _normal;
        m_Distance = (float)-1.0f * ( m_Normal.dot(_point) );
    }
    INLINE void set ( const Vector3<float>& _p1, const Vector3<float>& _p2, const Vector3<float>& _p3 )
    {
        m_Normal = (_p2-_p1).cross(_p3-_p2);
        ex_check( m_Normal.normalize() == EResult::ok, "failed to normalize m_Normal" );
        m_Distance = (float)-1.0f * ( m_Normal.dot(_p1) );
    }

    //
    INLINE bool operator == ( const self_t& _plane ) { return ( (m_Normal == _plane.m_Normal) && mathop::is_equal( m_Distance, _plane.m_Distance, float(EX_FLOAT_EPS) ) ); }
    INLINE bool operator != ( const self_t& _plane ) { return !( (*this) == _plane ); }

    //
    void get_normalize( self_t* _pResult ) const
    {
        _pResult->set(*this);
        if ( _pResult->normalize() == EResult::infinity )
            _pResult->set( Vector3<float>( 0.0f, 0.0f, 0.0f ), 0.0f ); 
    }
    result_t normalize() 
    {
        float len = m_Normal.length();
        if ( mathop::is_zero( len, float(EX_FLOAT_EPS) ) )
            return EResult::infinity;
        m_Normal /= len;
        m_Distance /= len;
        return EResult::ok;
    }

    //
    INLINE const Vector3<float>& normal() const { return m_Normal; }
    INLINE Vector3<float>& normal() { return m_Normal; }

    //
    INLINE const float d() const { return m_Distance; }
    INLINE float& d() { return m_Distance; }


    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    Vector3<float>     m_Normal;
    float               m_Distance;

}; // end class Plane 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END PLANE_H_1250525895
// #################################################################################
