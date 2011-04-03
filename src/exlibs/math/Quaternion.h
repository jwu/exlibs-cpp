// ======================================================================================
// File         : Quaternion.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:18:23 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef QUATERNION_H_1250525906
#define QUATERNION_H_1250525906
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Quaternion 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class Quaternion
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    typedef Quaternion<T> self_t;


    ///////////////////////////////////////////////////////////////////////////////
    // static const data 
    ///////////////////////////////////////////////////////////////////////////////

public:
    static const self_t zero;
    static const self_t identity;


    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    Quaternion()
    {
        // T_Zero(m_data);
    }

    //
    Quaternion( const Quaternion& _quat )
    {
        this->set( _quat );
    }

    //
    Quaternion( T _x, T _y, T _z, T _w )
    {
        this->set( _x, _y, _z, _w );
    }

    //
    Quaternion( const Vector3<T>& _axis, T _radian )
    {
        this->set( _axis, _radian );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ========================================================
    // set 
    // ========================================================


    //
    void set( const Quaternion& _quat )
    {
        mathop::set( m_data, _quat.m_data );
    }

    //
    void set( T _x, T _y, T _z, T _w )
    {
        T_Set4( m_data, x, y, z, w );
    }

    //
    void set( const Vector3<T>& _axis, T _radian )
    {
        ex_assert( _axis.is_normalized(), "axis have not been normalized." );

        T half_radian = _radian * 0.5f;

        T_Set4( m_data, 
                _axis.x() * mathop::sin( half_radian ), 
                _axis.y() * mathop::sin( half_radian ),
                _axis.z() * mathop::sin( half_radian ),
                mathop::cos( half_radian ) );
    }

    // ========================================================
    // operator 
    // ========================================================


    //
    self_t& operator = ( const self_t& _quat )
    {
        this->set(_quat);
        return *this;
    }

    //
    self_t operator - () const
    {
        ex_assert(!TypeTraits<T>::isUnsignedInt, "Don't use negative operator for unsigned type\n");

        self_t quat(*this);
        mathop::negative( quat.m_data, quat.m_data );
        return quat;
    }

    //
    void negative()
    {
        mathop::negative( m_data, m_data );
    }

    //
    self_t& operator += ( const self_t& _quat )
    {
        mathop::add( m_data, m_data, _quat.m_data );
        return *this;
    }

    //
    self_t& operator -= ( const self_t& _quat )
    {
        mathop::sub( m_data, m_data, _quat.m_data );
        return *this;
    }

    //
    self_t operator *= ( const self_t& _quat )
    {
#if 1
        T x = x() * _quat.w() + w() * _quat.x() + z() * _quat.y() - y() * _quat.z();
        T y = y() * _quat.w() + w() * _quat.y() + x() * _quat.z() - z() * _quat.x();
        T z = z() * _quat.w() + w() * _quat.z() + y() * _quat.x() - x() * _quat.y();
        T w = w() * _quat.w() - x() * _quat.x() - y() * _quat.y() - z() * _quat.z();
#else
        // TODO: confirm this
        T t0 = ( y() - z() ) * ( _quat.z() - _quat.y() );
        T t1 = ( w() + x() ) * ( _quat.w() + _quat.x() );
        T t2 = ( y() + z() ) * ( _quat.w() - _quat.x() );
        T t3 = ( w() - x() ) * ( _quat.y() + _quat.z() );
        T t4 = ( x() - y() ) * ( _quat.z() - _quat.x() );
        T t5 = ( x() + y() ) * ( _quat.z() + _quat.x() );
        T t6 = ( w() - z() ) * ( _quat.w() + _quat.y() );
        T t7 = ( w() + z() ) * ( _quat.w() - _quat.y() );
        T t8 = t5 + t6 + t7;
        T t9 = 0.5 * ( t4 + t8 );

        //
        T x = t1 + t9 - t8;
        T y = t2 + t9 - t7;
        T z = t3 + t9 - t6;
        T w = t0 + t9 - t5;
#endif
        this->set( x, y, z, w );
        return *this;
    }

    //
    self_t operator *= ( T _scalar ) 
    {
        mathop::mul_scalar( m_data, m_data, _scalar );
        return *this;
    }

    //
    self_t& operator /= ( T _scalar )
    {
        mathop::div_scalar( m_data, m_data, _scalar );
        return *this;
    }

    //
    bool inverse()
    {
        T length_sqr = lengthSQR();
        if ( length_sqr > T(0) )
        {
            T inv_length_sqr = T(1)/length_sqr;
            mathop::mul_scalar( m_data, m_data, inv_length_sqr );
            this->conjugate();
            return true;
        }
        else
        {
            return false;
        }
    }

    //
    void get_inverse( self_t* _pResult ) const
    {
        T length_sqr = lengthSQR();
        if ( length_sqr > T(0) )
        {
            T inv_length_sqr = T(1)/length_sqr;
            mathop::mul_scalar( _pResult->m_data, m_data, inv_length_sqr );
            _pResult->conjugate();
        }
        else
        {
            _pResult->set(self_t::zero);
        }
    }

    //
    void conjugate()
    {
        this->set( -x(), -y(), -z(), w() );
    }

    //
    void get_conjugate( self_t* _pResult ) const
    {
        _pResult->set( -x(), -y(), -z(), w() );
    }

    //
    T length() const
    {
        return mathop::length(m_data);
    }

    //
    T lengthSQR() const
    {
        return mathop::length_sqr(m_data);
    }

    //
    bool is_normalized() const
    {
        return ( mathop::is_equal( lengthSQR(), T(1), mathop::epsilon<T>() ) );
    }

    //
    void get_normalize( self_t* _pResult ) const
    {
        const T length_sqr = lengthSQR();

        if ( mathop::is_equal( length_sqr, T(1), mathop::epsilon<T>() ) )
        {
            _pResult->set(*this);
            return;
        }

        ex_assert( !mathop::is_zero( length_sqr, mathop::epsilon<T>() ), "Can't division zero length" );

        const T inv_length = mathop::inv_sqrt( length_sqr );
        mathop::mul_scalar( _pResult->m_data, m_data, inv_length );
    }

    //
    result_t normalize()
    {
        const T length_sqr = lengthSQR();

        if ( mathop::is_equal( length_sqr, T(1), mathop::epsilon<T>() ) )
            return EResult::ok;

        if( mathop::is_zero( length_sqr, mathop::epsilon<T>() ) )
            return EResult::infinity;

        const T inv_length = mathop::inv_sqrt( length_sqr );
        mathop::mul_scalar( m_data, m_data, inv_length );

        return EResult::ok;
    }

    //
    T dot( const self_t& _quat ) const
    {
        return mathop::dot( m_data, _quat.m_data );
    }

    // 
    INLINE T& x() { return this->get(0); }
    INLINE T& y() { return this->get(1); }
    INLINE T& z() { return this->get(2); }
    INLINE T& w() { return this->get(3); }

    // 
    INLINE const T x() const { return this->get(0); }
    INLINE const T y() const { return this->get(1); }
    INLINE const T z() const { return this->get(2); }
    INLINE const T w() const { return this->get(3); }


    // ========================================================
    // conversion: define in Conversion.h
    // ========================================================

    //
    INLINE void toMatrix( Matrix3<T>* _pResult ) const;
    INLINE void toMatrix( Matrix4<T>* _pResult ) const;

    //
    INLINE void xAxis( Vector3<T>* _pResult ) const;
    INLINE void yAxis( Vector3<T>* _pResult ) const;
    INLINE void zAxis( Vector3<T>* _pResult ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    T& get( int _idx ) { return intri::getref( m_data, _idx ); }
    const T get( int _idx ) const { return intri::get( m_data, _idx ); }


    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    T m_data[4];

}; // end class Quaternion

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// ========================================================
// zero
// ========================================================

template < typename T > 
const Quaternion<T> Quaternion<T>::zero ( T(0), T(0), T(0), T(0) );

// ========================================================
// identity
// ========================================================

template < typename T > 
const Quaternion<T> Quaternion<T>::identity ( T(0), T(0), T(0), T(1) );

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END QUATERNION_H_1250525906
// #################################################################################
