// ======================================================================================
// File         : Matrix3.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:17:20 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MATRIX3_H_1250525843
#define MATRIX3_H_1250525843
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Matrix3 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class Matrix3
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef Matrix3<T> self_t;

    ///////////////////////////////////////////////////////////////////////////////
    // static const
    ///////////////////////////////////////////////////////////////////////////////

public:

    static const self_t zero;
    static const self_t identity;

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ========================================================
    // constructor & destructor 
    // ========================================================

    //
    Matrix3()
    {
    }

    //
    Matrix3( T _m00, T _m01, T _m02,
              T _m10, T _m11, T _m12,
              T _m20, T _m21, T _m22 )
    {
        this->set( _m00,  _m01,  _m02,
                   _m10,  _m11,  _m12,
                   _m20,  _m21,  _m22 );
    }

    //
    Matrix3( const self_t& _mat )
    {
        this->set(_mat);
    }

    //
    Matrix3( const Matrix2<T>& _mat2 )
    {
        this->set(_mat2);
    }

    //
    Matrix3( const Vector3<T>& _I, const Vector3<T>& _J, const Vector3<T>& _K )
    {
        this->set( _I, _J, _K );
    }

    //
    Matrix3 ( const Angle<T>& _angle )
    {
        this->set(_angle);
    }

    //
    Matrix3( const Rotator<T>& _rot )
    {
        this->set(_rot);
    }

    //
    Matrix3( const Quaternion<T>& _quat )
    {
        this->set(_quat);
    }

    //
    Matrix3 ( const Vector2<T>& _pos, const Vector2<T>& _scale, const Angle<T>& _ang )
    {
        this->set( _pos, _scale, _ang );
    }

    // ========================================================
    // set 
    // ========================================================

    //
    void set( T _m00, T _m01, T _m02,
              T _m10, T _m11, T _m12,
              T _m20, T _m21, T _m22 )
    {
        get(0,0) = _m00; get(0,1) = _m01; get(0,2) = _m02;
        get(1,0) = _m10; get(1,1) = _m11; get(1,2) = _m12;
        get(2,0) = _m20; get(2,1) = _m21; get(2,2) = _m22;
    }

    // set by 3 vector
    void set( const Vector3<T>& _I, const Vector3<T>& _J, const Vector3<T>& _K )
    {
        get(0,0) = _I.x(); get(0,1) = _I.y(); get(0,2) = _I.z();
        get(1,0) = _J.x(); get(1,1) = _J.y(); get(1,2) = _J.z();
        get(2,0) = _K.x(); get(2,1) = _K.y(); get(2,2) = _K.z();
    }

    //
    void set( const angf_t& _ang )
    {
        float cos_a = mathop::cos(_ang);
        float sin_a = mathop::sin(_ang);
        this->set ( cos_a, sin_a, 0.0f,
                   -sin_a, cos_a, 0.0f,
                    0.0f,  0.0f,  1.0f );
    }

    // set by matrix3
    void set( const self_t& _mat )
    {
        get(0,0) = _mat.get(0,0); get(0,1) = _mat.get(0,1); get(0,2) = _mat.get(0,2);
        get(1,0) = _mat.get(1,0); get(1,1) = _mat.get(1,1); get(1,2) = _mat.get(1,2);
        get(2,0) = _mat.get(2,0); get(2,1) = _mat.get(2,1); get(2,2) = _mat.get(2,2);
    }

    // set by matrix2
    void set( const Matrix2<T>& _mat2 )
    {
        this->set( _mat2.get(0,0), _mat2.get(0,1), T(0),
                   _mat2.get(1,0), _mat2.get(1,1), T(0), 
                   T(0),          T(0),          T(1) );
    }

    // set by rotator
    void set( const Rotator<T>& _rot )
    {
        //
        T sin_p = mathop::sin(_rot.pitch());
        T cos_p = mathop::cos(_rot.pitch());
        T sin_y = mathop::sin(_rot.yaw());
        T cos_y = mathop::cos(_rot.yaw());
        T sin_r = mathop::sin(_rot.roll());
        T cos_r = mathop::cos(_rot.roll());
    
        //
        T spsy = sin_p * sin_y;
        T cpsy = cos_p * sin_y;

        // CW rotate
        this->set ( cos_y * cos_r,                cos_y * sin_r,                -sin_y,
                    spsy * cos_r - cos_p * sin_r, spsy * sin_r + cos_p * cos_r,  sin_p * cos_y,
                    cpsy * cos_r + sin_p * sin_r, cpsy * sin_r - sin_p * cos_r,  cos_p * cos_y );

        // XXX: CCW rotate
        // this->set( cos_y*cos_r+sin_y*sin_p*sin_r,   -cos_y*sin_r+sin_y*sin_p*cos_r,  sin_y*cos_p,
        //            sin_r*cos_p,                     cos_r*cos_p,                     -sin_p,
        //            -sin_y*cos_r+cos_y*sin_p*sin_r,  sin_r*sin_y+cos_y*sin_p*cos_r,   cos_y*cos_p );
    }

    // set by pos,scale,rotate for 2d
    void set( const Vector2<T>& _pos, const Vector2<T>& _scale, const Angle<T>& _ang )
    {
        this->set ( _scale.x(), 0.0f,       0.0f,
                    0.0f,       _scale.y(), 0.0f,
                    0.0f,       0.0f,       1.0f );
        float cos_a = mathop::cos(_ang);
        float sin_a = mathop::sin(_ang);
        *this *= Matrix3<T> ( cos_a, sin_a, 0.0f,
                               -sin_a, cos_a, 0.0f, 
                               0.0f,  0.0f,  1.0f );
        this->set_translation( _pos );
    }

    // set by quaternion
    void set( const Quaternion<T>& _quat )
    {
        // TODO: confirm rotate is CW/CCW
        //
        T Tx  = 2.0*_quat.x();
        T Ty  = 2.0*_quat.y();
        T Tz  = 2.0*_quat.z();
        T Twx = Tx*_quat.w();
        T Twy = Ty*_quat.w();
        T Twz = Tz*_quat.w();
        T Txx = Tx*_quat.x();
        T Txy = Ty*_quat.x();
        T Txz = Tz*_quat.x();
        T Tyy = Ty*_quat.y();
        T Tyz = Tz*_quat.y();
        T Tzz = Tz*_quat.z();

        //
        this->set( 1.0 - ( Tyy + Tzz ), Txy + Twz,		     Txz - Twy,
                   Txy - Twz,			1.0 - ( Txx + Tzz ), Tyz + Twx,
                   Txz + Twy,			Tyz - Twx,           1.0 - ( Txx + Tyy ) );
    }

    // ========================================================
    // get 
    // ========================================================

    // get row 
    //  row =============
    Vector3<T> row( uint _row ) const
    {
        ex_assert( _row >= 0 && _row < 3, "out of range" );
        return Vector3<T>( get(_row,0), get(_row,1), get(_row,2) );
    }

    // get col 
    //   col
    //   ||
    //   ||
    //   ||
    //   ||
    Vector3<T> col( uint _col ) const
    {
        ex_assert( _col >= 0 && _col < 3, "out of range" );
        return Vector3<T>( get(0,_col), get(1,_col), get(2,_col) );
    }

    //
    T& get ( uint _row, uint _col )
    {
        ex_assert( _row >= 0 && _row < 3, "out of range" );
        ex_assert( _col >= 0 && _col < 3, "out of range" );
        return m[3*_row+_col]; 
    }

    //
    const T& get ( uint _row, uint _col ) const
    {
        ex_assert( _row >= 0 && _row < 3, "out of range" );
        ex_assert( _col >= 0 && _col < 3, "out of range" );
        return m[3*_row+_col]; 
    }


    //
    INLINE Matrix2<T> rotation() const 
    {
        // TODO: write a assert to make sure the matrix is orthexx??? 
        return Matrix2<T>( get(0,0), get(0,1),
                            get(1,0), get(1,1) ); 
    }
    INLINE Matrix3& set_rotation( const Matrix2<T>& _mat2 ) 
    {
        // TODO: write a assert to make sure the matrix is orthexx??? 
        get(0,0) = _mat2(0,0); get(0,1) = _mat2(0,1);
        get(1,0) = _mat2(1,0); get(1,1) = _mat2(1,1);
        return *this;
    }

    //
    INLINE Vector2<T> translation() const { return Vector2<T>( get(2,0), get(2,1) ); }
    INLINE Matrix3& set_translation( const Vector2<T>& _vec2 ) { get(2,0) = _vec2[0]; get(2,1) = _vec2[1]; get(2,2) = T(1); return *this; }

    //
    T* getPtr() { return (T*)m; }
    const T* getPtr() const { return (T*)m; }

    //
    Rotator<T> to_rotator()
    {
        // TODO: confirm rotate is CW/CCW
        T pitch, yaw, roll;
        T sinp = -get(1,2);

        // Extract pitch from m23, being careful for domain errors with asin(). 
        // We could have values slightly out of range due to floating point arithmetic.
        if ( sinp <= T(-1) )
        {
            pitch = T(-EX_HALF_PI);
        }
        else if ( sinp >= T(1) )
        {
            pitch = T(EX_HALF_PI);
        }
        else
        {
            pitch = mathop::asin( sinp );
        }

        // Check for the Gimbal lock case, giving a slight tolerance for numerical imprecision
        if ( sinp > T(0.9999) ) 
        {
            // we are looking straight up or down. 
            // Slam roll to zero and just set yaw
            roll = T(0);
            yaw = mathop::atan2( -get(2,0), get(0,0) );
        }
        else 
        {
            roll = mathop::atan2(get(1,0), get(1,1));
            yaw = mathop::atan2(get(0,2), get(2,2));
        }
        return Rotator<T>( pitch, yaw, roll );
    }

    //
    Quaternion<T> to_quat()
    {
        // TODO: confirm rotate is CW/CCW
        // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
        // article "Quaternion Calculus and Fast Animation".

        T x,y,z,w;
        T root;
        T trace = get(0,0) + get(1,1) + get(2,2);

        if ( trace > T(0.0) )
        {
            // |w| > 1/2, may as well choose w > 1/2
            root = mathop::sqrt(trace + T(1.0));  // 2w
            w = T(0.5) * root;
            root = T(0.5)/root;  // 1/(4w)
            x = ( get(1,2) - get(2,1) ) * root;
            y = ( get(2,0) - get(0,2) ) * root;
            z = ( get(0,1) - get(1,0) ) * root;
        } // end if
        else
        {
            // diagonal is negative
            int	i = 1;
            if( get(1,1) > get(0,0) ) 
                i = 2;
            if( (i == 1 && get(2,2) > get(0,0)) || (i == 2 && get(2,2) > get(1,1)) ) 
                i = 3;

            switch(i) 
            {
            case 1:
                root = mathop::sqrt( ( get(0,0) - ( get(1,1) + get(2,2) ) ) + T(1.0) );
                x = T(0.5) * root;
                root = T(0.5)/root;
                y = ( get(0,1) + get(1,0) ) * root;
                z = ( get(0,2) + get(2,0) ) * root;
                w = ( get(1,2) - get(2,1) ) * root;
                break;

            case 2:
                root = mathop::sqrt( ( get(1,1) - ( get(2,2) + get(0,0) ) ) + T(1.0) );
                y = T(0.5) * root;
                root = T(0.5)/root;
                x = ( get(0,1) + get(1,0) ) * root;
                z = ( get(1,2) + get(2,1) ) * root;
                w = ( get(2,0) - get(0,2) ) * root;
                break;

            case 3:
                root = mathop::sqrt( ( get(2,2) - ( get(0,0) + get(1,1) ) ) + T(1.0) );
                z = T(0.5) * root;
                root = T(0.5)/root;
                x = ( get(0,2) + get(2,0) ) * root;
                y = ( get(1,2) + get(2,1) ) * root;
                w = ( get(0,1) - get(1,0) ) * root;
                break;
            } // end switch
        } // end else

        return Quaternion<T>( x, y, z, w );
    }

    // ========================================================
    // operator  
    // ========================================================

    // assigment operator
    self_t& operator = ( const self_t& _mat )
    {
        this->set(_mat);
        return *this;
    }

    // Simple operator for directly accessing every element of the matrix.  
    // useful in some codition like for( _row, _col ) .etc
    T& operator () ( uint _row, uint _col )
    {
        return get(_row,_col);
    }

    // Simple operator for directly accessing every element of the matrix.  
    // useful in some codition like for( _row, _col ) .etc
    const T& operator () ( uint _row, uint _col ) const
    {
        return get(_row,_col);
    }

    //
    self_t operator - () const 
    {
        return self_t( -get(0,0), -get(0,1), -get(0,2),
                       -get(1,0), -get(1,1), -get(1,2),
                       -get(2,0), -get(2,1), -get(2,2) );
    }

    //
    self_t& negative()
    {
        get(0,0) = -get(0,0); get(0,1) = -get(0,1); get(0,2) = -get(0,2);
        get(1,0) = -get(1,0); get(1,1) = -get(1,1); get(1,2) = -get(1,2);
        get(2,0) = -get(2,0); get(2,1) = -get(2,1); get(2,2) = -get(2,2);
        return *this;
    }

    //
    self_t& operator += ( const self_t& _mat )
    {
        get(0,0) += get(0,0); get(0,1) += get(0,1); get(0,2) += get(0,2);
        get(1,0) += get(1,0); get(1,1) += get(1,1); get(1,2) += get(1,2);
        get(2,0) += get(2,0); get(2,1) += get(2,1); get(2,2) += get(2,2);
        return *this;
    }

    //
    self_t& operator -= ( const self_t& _mat )
    {
        get(0,0) -= get(0,0); get(0,1) -= get(0,1); get(0,2) -= get(0,2);
        get(1,0) -= get(1,0); get(1,1) -= get(1,1); get(1,2) -= get(1,2);
        get(2,0) -= get(2,0); get(2,1) -= get(2,1); get(2,2) -= get(2,2);
        return *this;
    }

    //
    self_t& operator *= ( const self_t& _mat )
    {
        T m00 = get(0,0);
        T m01 = get(0,1); 
        T m02 = get(0,2); 

        T m10 = get(1,0); 
        T m11 = get(1,1); 
        T m12 = get(1,2); 

        T m20 = get(2,0); 
        T m21 = get(2,1); 
        T m22 = get(2,2); 

        get(0,0) = m00 * _mat.get(0,0) + m01 * _mat.get(1,0) + m02 * _mat.get(2,0);
        get(0,1) = m00 * _mat.get(0,1) + m01 * _mat.get(1,1) + m02 * _mat.get(2,1);
        get(0,2) = m00 * _mat.get(0,2) + m01 * _mat.get(1,2) + m02 * _mat.get(2,2);

        get(1,0) = m10 * _mat.get(0,0) + m11 * _mat.get(1,0) + m12 * _mat.get(2,0);
        get(1,1) = m10 * _mat.get(0,1) + m11 * _mat.get(1,1) + m12 * _mat.get(2,1);
        get(1,2) = m10 * _mat.get(0,2) + m11 * _mat.get(1,2) + m12 * _mat.get(2,2);

        get(2,0) = m20 * _mat.get(0,0) + m21 * _mat.get(1,0) + m22 * _mat.get(2,0);
        get(2,1) = m20 * _mat.get(0,1) + m21 * _mat.get(1,1) + m22 * _mat.get(2,1);
        get(2,2) = m20 * _mat.get(0,2) + m21 * _mat.get(1,2) + m22 * _mat.get(2,2);

        return *this;
    }

    //
    self_t& operator *= ( T _scalar )
    {
        get(0,0) *= _scalar;
        get(0,1) *= _scalar;
        get(0,2) *= _scalar;

        get(1,0) *= _scalar;
        get(1,1) *= _scalar;
        get(1,2) *= _scalar;

        get(2,0) *= _scalar;
        get(2,1) *= _scalar;
        get(2,2) *= _scalar;

        return *this;
    }

    //
    self_t& operator /= ( T _scalar )
    {
        T inv_scalar = T(1) / _scalar;

        get(0,0) *= inv_scalar;
        get(0,1) *= inv_scalar;
        get(0,2) *= inv_scalar;

        get(1,0) *= inv_scalar;
        get(1,1) *= inv_scalar;
        get(1,2) *= inv_scalar;

        get(2,0) *= inv_scalar;
        get(2,1) *= inv_scalar;
        get(2,2) *= inv_scalar;

        return *this;
    }

    //
    void get_transpose( self_t* _pResult ) const
    {
        return _pResult->set( get(0,0), get(1,0), get(2,0),
                              get(0,1), get(1,1), get(2,1),
                              get(0,2), get(1,2), get(2,2) );
    }

    //
    self_t& transpose()
    {
        T swap;

        swap    = get(0,1);
        get(0,1) = get(1,0);
        get(1,0) = swap;

        swap    = get(0,2);
        get(0,2) = get(2,0);
        get(2,0) = swap;

        swap    = get(1,2);
        get(1,2) = get(2,1);
        get(2,1) = swap;

        return *this;
    }

    //
    bool inverse ()
    {
        T m00 = get(1,1) * get(2,2) - get(1,2) * get(2,1);
        T m01 = get(0,2) * get(2,1) - get(0,1) * get(2,2);
        T m02 = get(0,1) * get(1,2) - get(0,2) * get(1,1);
        T m10 = get(1,2) * get(2,0) - get(1,0) * get(2,2);
        T m11 = get(0,0) * get(2,2) - get(0,2) * get(2,0);
        T m12 = get(0,2) * get(1,0) - get(0,0) * get(1,2);
        T m20 = get(1,0) * get(2,1) - get(1,1) * get(2,0);
        T m21 = get(0,1) * get(2,0) - get(0,0) * get(2,1);
        T m22 = get(0,0) * get(1,1) - get(0,1) * get(1,0);

        T det = get(0,0) * m00 + get(0,1) * m10 + get(0,2) * m20;

        if ( mathop::abs(det) < mathop::epsilon<T>() )
        {
            return false;
        }
        T inv = T(1.0) / det;
        set ( m00, m01, m02,
              m10, m11, m12,
              m20, m21, m22 );
        *this *= T(inv);

        return true;

    }

    //
    bool get_inverse( self_t* _pResult ) const
    {
        _pResult->get(0,0) = get(1,1) * get(2,2) - get(1,2) * get(2,1);
        _pResult->get(0,1) = get(0,2) * get(2,1) - get(0,1) * get(2,2);
        _pResult->get(0,2) = get(0,1) * get(1,2) - get(0,2) * get(1,1);
        _pResult->get(1,0) = get(1,2) * get(2,0) - get(1,0) * get(2,2);
        _pResult->get(1,1) = get(0,0) * get(2,2) - get(0,2) * get(2,0);
        _pResult->get(1,2) = get(0,2) * get(1,0) - get(0,0) * get(1,2);
        _pResult->get(2,0) = get(1,0) * get(2,1) - get(1,1) * get(2,0);
        _pResult->get(2,1) = get(0,1) * get(2,0) - get(0,0) * get(2,1);
        _pResult->get(2,2) = get(0,0) * get(1,1) - get(0,1) * get(1,0);

        T det = get(0,0) * _pResult->get(0,0) + get(0,1) * _pResult->get(1,0) + get(0,2) * _pResult->get(2,0);
        if ( mathop::abs(det) < mathop::epsilon<T>() )
        {
            return false;
        }
        T inv = T(1.0) / det;
        (*_pResult) *= T(inv);

        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    T m[9];

}; // end class Matrix3

// #########################
} // end namespace ex 
// #########################

#include "Matrix3.hpp"

// #################################################################################
#endif // END MATRIX3_H_1250525843
// #################################################################################
