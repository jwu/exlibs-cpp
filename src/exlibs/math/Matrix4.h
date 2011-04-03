// ======================================================================================
// File         : Matrix4.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:17:30 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MATRIX4_H_1250525858
#define MATRIX4_H_1250525858
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Matrix4
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class Matrix4
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:
    typedef Matrix4<T> self_t;


    ///////////////////////////////////////////////////////////////////////////////
    // static const values 
    ///////////////////////////////////////////////////////////////////////////////

public:
    static const self_t zero;
    static const self_t identity;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    Matrix4()
    {
    }

    //
    Matrix4( T _m00, T _m01, T _m02, T _m03,
              T _m10, T _m11, T _m12, T _m13,
              T _m20, T _m21, T _m22, T _m23,
              T _m30, T _m31, T _m32, T _m33 )
    {
        this->set( _m00,  _m01,  _m02,  _m03,
                   _m10,  _m11,  _m12,  _m13,
                   _m20,  _m21,  _m22,  _m23,
                   _m30,  _m31,  _m32,  _m33 );
    }

    //
    Matrix4( const self_t& _mat )
    {
        this->set(_mat);
    }

    // rotation, position
    Matrix4( const Rotator<T>& _rot, const Vector3<T>& _pos )
    {
        this->set( _rot, _pos );
    }

    // matrix3==rotation, position
    Matrix4( const Matrix3<T>& _mat3, const Vector3<T>& _pos )
    {
        this->set( _mat3, _pos );
    }

    // quaternion==rotation, position
    Matrix4( const Quaternion<T>& _quat, const Vector3<T>& _pos )
    {
        this->set( _quat, _pos );
    }

    // rotation,position,scale
    Matrix4( const Rotator<T>& _rot, const Vector3<T>& _pos, const Vector3<T>& _scale )
    {
        this->set( _rot, _pos, _scale );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ========================================================
    // set functions
    // ========================================================

    // 
    void set( T _m00, T _m01, T _m02, T _m03,
              T _m10, T _m11, T _m12, T _m13,
              T _m20, T _m21, T _m22, T _m23,
              T _m30, T _m31, T _m32, T _m33 )
    {
        get(0,0) = _m00; get(0,1) = _m01; get(0,2) = _m02; get(0,3) = _m03;
        get(1,0) = _m10; get(1,1) = _m11; get(1,2) = _m12; get(1,3) = _m13;
        get(2,0) = _m20; get(2,1) = _m21; get(2,2) = _m22; get(2,3) = _m23;
        get(3,0) = _m30; get(3,1) = _m31; get(3,2) = _m32; get(3,3) = _m33;
    }

    //
    void set( const Vector4<T>& _I, const Vector4<T>& _J, const Vector4<T>& _K, const Vector4<T>& _T )
    {
        get(0,0) = _I.x(); get(0,1) = _I.y(); get(0,2) = _I.z(); get(0,3) = _I.w();
        get(1,0) = _J.x(); get(1,1) = _J.y(); get(1,2) = _J.z(); get(1,3) = _J.w();
        get(2,0) = _K.x(); get(2,1) = _K.y(); get(2,2) = _K.z(); get(2,3) = _K.w();
        get(3,0) = _T.x(); get(3,1) = _T.y(); get(3,2) = _T.z(); get(3,3) = _T.w();
    }

    //
    void set( const self_t& _mat )
    {
        get(0,0) = _mat.get(0,0); get(0,1) = _mat.get(0,1); get(0,2) = _mat.get(0,2); get(0,3) = _mat.get(0,3);
        get(1,0) = _mat.get(1,0); get(1,1) = _mat.get(1,1); get(1,2) = _mat.get(1,2); get(1,3) = _mat.get(1,3);
        get(2,0) = _mat.get(2,0); get(2,1) = _mat.get(2,1); get(2,2) = _mat.get(2,2); get(2,3) = _mat.get(2,3);
        get(3,0) = _mat.get(3,0); get(3,1) = _mat.get(3,1); get(3,2) = _mat.get(3,2); get(3,3) = _mat.get(3,3);
    }

    //
    void set( const Matrix3<T>& _mat3, const Vector3<T>& _pos )
    {
        this->set( _mat3(0,0), _mat3(0,1), _mat3(0,2), T(0),
                   _mat3(1,0), _mat3(1,1), _mat3(1,2), T(0),
                   _mat3(2,0), _mat3(2,1), _mat3(2,2), T(0),
                   _pos.x(),   _pos.y(),   _pos.z(),   T(1) );
    }

    //
    void set( const Rotator<T>& _rot, const Vector3<T>& _pos )
    {
        this->set( Matrix3<T>(_rot), _pos );
    }

    //
    void set( const Quaternion<T>& _quat, const Vector3<T>& _pos )
    {
        this->set( Matrix3<T>(_quat), _pos );
    }

    //
    void set( const Rotator<T>& _rot, const Vector3<T>& _position, const Vector3<T>& _scale )
    {
        // TODO:
    }

    // ========================================================
    // get & set partial data
    // TODO: get/set row/col can be optimize by col_major or row_majow
    // ========================================================

    //  row =============

    // get row 
    Vector4<T> row( uint _row ) const
    {
		ex_assert( _row >= 0 && _row < 4, "out of range" );
        return Vector4<T>( get(_row,0), get(_row,1), get(_row,2), get(_row,3) );
    }

    // set row
    void set_row( uint _row, const Vector4<T>& _vec )
    {
		ex_assert( _row >= 0 && _row < 4, "out of range" );
        get(_row,0) = _vec.x(); get(_row,1) = _vec.y(); get(_row,2) = _vec.z(); get(_row,3) = _vec.w();
    }

    //   col
    //   ||
    //   ||
    //   ||
    //   ||

    // get col 
    Vector4<T> col( uint _col ) const
    {
		ex_assert( _col >= 0 && _col < 4, "out of range" );
        return Vector4<T>( get(0,_col), get(1,_col), get(2,_col), get(3,_col) );
    }

    // set col
    void set_col( uint _col, const Vector4<T>& _vec )
    {
		ex_assert( _col >= 0 && _col < 4, "out of range" );
        get(0,_col) = _vec.x(); get(1,_col) = _vec.y(); get(2,_col) = _vec.z(); get(3,_col) =  _vec.w();
    }

    // 
    T& get ( uint _row, uint _col )
    {
		ex_assert( _row >= 0 && _row < 4, "out of range" );
		ex_assert( _col >= 0 && _col < 4, "out of range" );
		return m[_row*4+_col]; 
    }

    // 
    const T& get ( uint _row, uint _col ) const
    {
		ex_assert( _row >= 0 && _row < 4, "out of range" );
		ex_assert( _col >= 0 && _col < 4, "out of range" );
		return m[_row*4+_col]; 
    }

    //
    INLINE Matrix3<T> rotation() const 
    {
        // TODO: write a assert to make sure the matrix is orthexx??? 
        return Matrix3<T>( get(0,0), get(0,1), get(0,2),
                            get(1,0), get(1,1), get(1,2),
                            get(2,0), get(2,1), get(2,2) ); 
    }
    INLINE void set_rotation( const Matrix3<T>& _mat3 ) 
    {
        // TODO: write a assert to make sure the matrix is orthexx??? 
        get(0,0) = _mat3(0,0); get(0,1) = _mat3(0,1); get(0,2) = _mat3(0,2);
        get(1,0) = _mat3(1,0); get(1,1) = _mat3(1,1); get(1,2) = _mat3(1,2);
        get(2,0) = _mat3(2,0); get(2,1) = _mat3(2,1); get(2,2) = _mat3(2,2); 
    }

    //
    INLINE Vector3<T> translation() const { return Vector3<T>( get(3,0), get(3,1), get(3,2) ); }
    INLINE void set_translation( const Vector3<T>& _vec3 ) { get(3,0) = _vec3[0]; get(3,1) = _vec3[1]; get(3,2) = _vec3[2]; }

    //
    T* getPtr() { return (T*)m; }
    const T* getPtr() const { return (T*)m; }

    // ========================================================
    // element operations
    // ========================================================

    //
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
        return self_t( -get(0,0), -get(0,1), -get(0,2), -get(0,3),
                       -get(1,0), -get(1,1), -get(1,2), -get(1,3),
                       -get(2,0), -get(2,1), -get(2,2), -get(2,3),
                       -get(3,0), -get(3,1), -get(3,2), -get(3,3) );
    }

    //
    self_t& negative()
    {
        get(0,0) = -get(0,0); get(0,1) = -get(0,1); get(0,2) = -get(0,2); get(0,3) = -get(0,3);
        get(1,0) = -get(1,0); get(1,1) = -get(1,1); get(1,2) = -get(1,2); get(1,3) = -get(1,3);
        get(2,0) = -get(2,0); get(2,1) = -get(2,1); get(2,2) = -get(2,2); get(2,3) = -get(2,3);
        get(3,0) = -get(3,0); get(3,1) = -get(3,1); get(3,2) = -get(3,2); get(3,3) = -get(3,3);
        return *this;
    }

    // ========================================================
    // cacluation operations 
    // ========================================================

    //
    self_t& operator += ( const self_t& _mat )
    {
        get(0,0) += get(0,0); get(0,1) += get(0,1); get(0,2) += get(0,2); get(0,3) += get(0,3);
        get(1,0) += get(1,0); get(1,1) += get(1,1); get(1,2) += get(1,2); get(1,3) += get(1,3);
        get(2,0) += get(2,0); get(2,1) += get(2,1); get(2,2) += get(2,2); get(2,3) += get(2,3);
        get(3,0) += get(3,0); get(3,1) += get(3,1); get(3,2) += get(3,2); get(3,3) += get(3,3);
        return *this;
    }

    //
    self_t& operator -= ( const self_t& _mat )
    {
        get(0,0) -= get(0,0); get(0,1) -= get(0,1); get(0,2) -= get(0,2); get(0,3) -= get(0,3);
        get(1,0) -= get(1,0); get(1,1) -= get(1,1); get(1,2) -= get(1,2); get(1,3) -= get(1,3);
        get(2,0) -= get(2,0); get(2,1) -= get(2,1); get(2,2) -= get(2,2); get(2,3) -= get(2,3);
        get(3,0) -= get(3,0); get(3,1) -= get(3,1); get(3,2) -= get(3,2); get(3,3) -= get(3,3);
        return *this;
    }

    //
    self_t& operator *= ( const self_t& _mat )
    {
        T m00 = get(0,0);  T m10 = get(1,0);  T m20 = get(2,0);  T m30 = get(3,0);
        T m01 = get(0,1);  T m11 = get(1,1);  T m21 = get(2,1);  T m31 = get(3,1);
        T m02 = get(0,2);  T m12 = get(1,2);  T m22 = get(2,2);  T m32 = get(3,2);
        T m03 = get(0,3);  T m13 = get(1,3);  T m23 = get(2,3);  T m33 = get(3,3);

        get(0,0) = m00 * _mat.get(0,0) + m01 * _mat.get(1,0) + m02 * _mat.get(2,0) + m03 * _mat.get(3,0);
        get(0,1) = m00 * _mat.get(0,1) + m01 * _mat.get(1,1) + m02 * _mat.get(2,1) + m03 * _mat.get(3,1);
        get(0,2) = m00 * _mat.get(0,2) + m01 * _mat.get(1,2) + m02 * _mat.get(2,2) + m03 * _mat.get(3,2);
        get(0,3) = m00 * _mat.get(0,3) + m01 * _mat.get(1,3) + m02 * _mat.get(2,3) + m03 * _mat.get(3,3);

        get(1,0) = m10 * _mat.get(0,0) + m11 * _mat.get(1,0) + m12 * _mat.get(2,0) + m13 * _mat.get(3,0);
        get(1,1) = m10 * _mat.get(0,1) + m11 * _mat.get(1,1) + m12 * _mat.get(2,1) + m13 * _mat.get(3,1);
        get(1,2) = m10 * _mat.get(0,2) + m11 * _mat.get(1,2) + m12 * _mat.get(2,2) + m13 * _mat.get(3,2);
        get(1,3) = m10 * _mat.get(0,3) + m11 * _mat.get(1,3) + m12 * _mat.get(2,3) + m13 * _mat.get(3,3);

        get(2,0) = m20 * _mat.get(0,0) + m21 * _mat.get(1,0) + m22 * _mat.get(2,0) + m23 * _mat.get(3,0);
        get(2,1) = m20 * _mat.get(0,1) + m21 * _mat.get(1,1) + m22 * _mat.get(2,1) + m23 * _mat.get(3,1);
        get(2,2) = m20 * _mat.get(0,2) + m21 * _mat.get(1,2) + m22 * _mat.get(2,2) + m23 * _mat.get(3,2);
        get(2,3) = m20 * _mat.get(0,3) + m21 * _mat.get(1,3) + m22 * _mat.get(2,3) + m23 * _mat.get(3,3);

        get(3,0) = m30 * _mat.get(0,0) + m31 * _mat.get(1,0) + m32 * _mat.get(2,0) + m33 * _mat.get(3,0);
        get(3,1) = m30 * _mat.get(0,1) + m31 * _mat.get(1,1) + m32 * _mat.get(2,1) + m33 * _mat.get(3,1);
        get(3,2) = m30 * _mat.get(0,2) + m31 * _mat.get(1,2) + m32 * _mat.get(2,2) + m33 * _mat.get(3,2);
        get(3,3) = m30 * _mat.get(0,3) + m31 * _mat.get(1,3) + m32 * _mat.get(2,3) + m33 * _mat.get(3,3);

        return *this;
    }

    //
    self_t& operator *= ( T _scalar )
    {
        get(0,0) *= _scalar;
        get(0,1) *= _scalar;
        get(0,2) *= _scalar;
        get(0,3) *= _scalar;

        get(1,0) *= _scalar;
        get(1,1) *= _scalar;
        get(1,2) *= _scalar;
        get(1,3) *= _scalar;

        get(2,0) *= _scalar;
        get(2,1) *= _scalar;
        get(2,2) *= _scalar;
        get(2,3) *= _scalar;

        get(3,0) *= _scalar;
        get(3,1) *= _scalar;
        get(3,2) *= _scalar;
        get(3,3) *= _scalar;

        return *this;
    }

    //
    self_t& operator /= ( T _scalar )
    {
        T inv_scalar = T(1) / _scalar;

        get(0,0) *= inv_scalar;
        get(0,1) *= inv_scalar;
        get(0,2) *= inv_scalar;
        get(0,3) *= inv_scalar;

        get(1,0) *= inv_scalar;
        get(1,1) *= inv_scalar;
        get(1,2) *= inv_scalar;
        get(1,3) *= inv_scalar;

        get(2,0) *= inv_scalar;
        get(2,1) *= inv_scalar;
        get(2,2) *= inv_scalar;
        get(2,3) *= inv_scalar;

        get(3,0) *= inv_scalar;
        get(3,1) *= inv_scalar;
        get(3,2) *= inv_scalar;
        get(3,3) *= inv_scalar;

        return *this;
    }

    //
    void get_transpose( self_t* _pResult ) const
    {
        return _pResult->set( get(0,0), get(1,0), get(2,0), get(3,0),
                              get(0,1), get(1,1), get(2,1), get(3,1),
                              get(0,2), get(1,2), get(2,2), get(3,2),
                              get(0,3), get(1,3), get(2,3), get(3,3) );
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
		
		swap    = get(0,3);
		get(0,3) = get(3,0);
		get(3,0) = swap;

		swap    = get(1,3);
		get(1,3) = get(3,1);
		get(3,1) = swap;

		swap    = get(2,3);
		get(2,3) = get(3,2);
		get(3,2) = swap;

		return *this;
    }

    //
    T determinant () const
    {
		T t11 = get(2,2)*(get(3,3)*get(4,4)-get(3,4)*get(4,3))+get(2,3)*(get(3,4)*get(4,2)-get(3,2)*get(4,4))+get(2,4)*(get(3,2)*get(4,3)-get(3,3)*get(4,2));
		T t12 = get(2,1)*(get(3,4)*get(4,3)-get(3,3)*get(4,4))+get(2,3)*(get(3,4)*get(4,1)-get(3,1)*get(4,4))+get(2,4)*(get(3,1)*get(4,3)-get(3,3)*get(4,1));
		T t13 = get(2,1)*(get(3,4)*get(4,2)-get(3,2)*get(4,4))+get(2,2)*(get(3,1)*get(4,4)-get(3,4)*get(4,1))+get(2,4)*(get(3,1)*get(4,2)-get(3,2)*get(4,1));
		T t14 = get(2,1)*(get(3,3)*get(4,2)-get(3,2)*get(4,3))+get(2,2)*(get(3,1)*get(4,3)-get(3,3)*get(4,1))+get(2,3)*(get(3,2)*get(4,1)-get(3,1)*get(4,2));

		return ( get(1,1)*t11 + get(1,2)*t12 + get(1,3)*t13 + get(1,4)*t14 );
    }

    //
    void inverse ()
    {
        T tmp[12];
        self_t mat = *this;

        // calculate pairs for first 8 elements (cofactors)
        tmp[0] = mat.get(2,2) * mat.get(3,3);
        tmp[1] = mat.get(2,3) * mat.get(3,2);
        tmp[2] = mat.get(2,1) * mat.get(3,3);
        tmp[3] = mat.get(2,3) * mat.get(3,1);
        tmp[4] = mat.get(2,1) * mat.get(3,2);
        tmp[5] = mat.get(2,2) * mat.get(3,1);
        tmp[6] = mat.get(2,0) * mat.get(3,3);
        tmp[7] = mat.get(2,3) * mat.get(3,0);
        tmp[8] = mat.get(2,0) * mat.get(3,2);
        tmp[9] = mat.get(2,2) * mat.get(3,0);
        tmp[10]= mat.get(2,0) * mat.get(3,1);
        tmp[11]= mat.get(2,1) * mat.get(3,0);

        // calculate first 8 elements (cofactors)
        this->get(0,0) = tmp[0]*mat.get(1,1) + tmp[3]*mat.get(1,2) + tmp[ 4]*mat.get(1,3);
        this->get(0,0)-= tmp[1]*mat.get(1,1) + tmp[2]*mat.get(1,2) + tmp[ 5]*mat.get(1,3);
        this->get(1,0) = tmp[1]*mat.get(1,0) + tmp[6]*mat.get(1,2) + tmp[ 9]*mat.get(1,3);
        this->get(1,0)-= tmp[0]*mat.get(1,0) + tmp[7]*mat.get(1,2) + tmp[ 8]*mat.get(1,3);
        this->get(2,0) = tmp[2]*mat.get(1,0) + tmp[7]*mat.get(1,1) + tmp[10]*mat.get(1,3);
        this->get(2,0)-= tmp[3]*mat.get(1,0) + tmp[6]*mat.get(1,1) + tmp[11]*mat.get(1,3);
        this->get(3,0) = tmp[5]*mat.get(1,0) + tmp[8]*mat.get(1,1) + tmp[11]*mat.get(1,2);
        this->get(3,0)-= tmp[4]*mat.get(1,0) + tmp[9]*mat.get(1,1) + tmp[10]*mat.get(1,2);
        this->get(0,1) = tmp[1]*mat.get(0,1) + tmp[2]*mat.get(0,2) + tmp[ 5]*mat.get(0,3);
        this->get(0,1)-= tmp[0]*mat.get(0,1) + tmp[3]*mat.get(0,2) + tmp[ 4]*mat.get(0,3);
        this->get(1,1) = tmp[0]*mat.get(0,0) + tmp[7]*mat.get(0,2) + tmp[ 8]*mat.get(0,3);
        this->get(1,1)-= tmp[1]*mat.get(0,0) + tmp[6]*mat.get(0,2) + tmp[ 9]*mat.get(0,3);
        this->get(2,1) = tmp[3]*mat.get(0,0) + tmp[6]*mat.get(0,1) + tmp[11]*mat.get(0,3);
        this->get(2,1)-= tmp[2]*mat.get(0,0) + tmp[7]*mat.get(0,1) + tmp[10]*mat.get(0,3);
        this->get(3,1) = tmp[4]*mat.get(0,0) + tmp[9]*mat.get(0,1) + tmp[10]*mat.get(0,2);
        this->get(3,1)-= tmp[5]*mat.get(0,0) + tmp[8]*mat.get(0,1) + tmp[11]*mat.get(0,2);

        // calculate pairs for second 8 elements (cofactors)
        tmp[ 0] = mat.get(0,2)*mat.get(1,3);
        tmp[ 1] = mat.get(0,3)*mat.get(1,2);
        tmp[ 2] = mat.get(0,1)*mat.get(1,3);
        tmp[ 3] = mat.get(0,3)*mat.get(1,1);
        tmp[ 4] = mat.get(0,1)*mat.get(1,2);
        tmp[ 5] = mat.get(0,2)*mat.get(1,1);
        tmp[ 6] = mat.get(0,0)*mat.get(1,3);
        tmp[ 7] = mat.get(0,3)*mat.get(1,0);
        tmp[ 8] = mat.get(0,0)*mat.get(1,2);
        tmp[ 9] = mat.get(0,2)*mat.get(1,0);
        tmp[10] = mat.get(0,0)*mat.get(1,1);
        tmp[11] = mat.get(0,1)*mat.get(1,0);

        // calculate second 8 elements (cofactors)
        this->get(0,2) = tmp[ 0]*mat.get(3,1) + tmp[ 3]*mat.get(3,2) + tmp[ 4]*mat.get(3,3);
        this->get(0,2)-= tmp[ 1]*mat.get(3,1) + tmp[ 2]*mat.get(3,2) + tmp[ 5]*mat.get(3,3);
        this->get(1,2) = tmp[ 1]*mat.get(3,0) + tmp[ 6]*mat.get(3,2) + tmp[ 9]*mat.get(3,3);
        this->get(1,2)-= tmp[ 0]*mat.get(3,0) + tmp[ 7]*mat.get(3,2) + tmp[ 8]*mat.get(3,3);
        this->get(2,2) = tmp[ 2]*mat.get(3,0) + tmp[ 7]*mat.get(3,1) + tmp[10]*mat.get(3,3);
        this->get(2,2)-= tmp[ 3]*mat.get(3,0) + tmp[ 6]*mat.get(3,1) + tmp[11]*mat.get(3,3);
        this->get(3,2) = tmp[ 5]*mat.get(3,0) + tmp[ 8]*mat.get(3,1) + tmp[11]*mat.get(3,2);
        this->get(3,2)-= tmp[ 4]*mat.get(3,0) + tmp[ 9]*mat.get(3,1) + tmp[10]*mat.get(3,2);
        this->get(0,3) = tmp[ 2]*mat.get(2,2) + tmp[ 5]*mat.get(2,3) + tmp[ 1]*mat.get(2,1);
        this->get(0,3)-= tmp[ 4]*mat.get(2,3) + tmp[ 0]*mat.get(2,1) + tmp[ 3]*mat.get(2,2);
        this->get(1,3) = tmp[ 8]*mat.get(2,3) + tmp[ 0]*mat.get(2,0) + tmp[ 7]*mat.get(2,2);
        this->get(1,3)-= tmp[ 6]*mat.get(2,2) + tmp[ 9]*mat.get(2,3) + tmp[ 1]*mat.get(2,0);
        this->get(2,3) = tmp[ 6]*mat.get(2,1) + tmp[11]*mat.get(2,3) + tmp[ 3]*mat.get(2,0);
        this->get(2,3)-= tmp[10]*mat.get(2,3) + tmp[ 2]*mat.get(2,0) + tmp[ 7]*mat.get(2,1);
        this->get(3,3) = tmp[10]*mat.get(2,2) + tmp[ 4]*mat.get(2,0) + tmp[ 9]*mat.get(2,1);
        this->get(3,3)-= tmp[ 8]*mat.get(2,1) + tmp[11]*mat.get(2,2) + tmp[ 5]*mat.get(2,0);

        // calculate determinant
        T det=( mat.get(0,0)*this->get(0,0) + mat.get(0,1)*this->get(1,0) + mat.get(0,2)*this->get(2,0) + mat.get(0,3)*this->get(3,0) );

        //devide the cofactor-matrix by the determinat
        T idet=(T)1.0/det;
        this->get(0,0)*=idet; this->get(1,0)*=idet; this->get(2,0)*=idet; this->get(3,0)*=idet;
        this->get(0,1)*=idet; this->get(1,1)*=idet; this->get(2,1)*=idet; this->get(3,1)*=idet;
        this->get(0,2)*=idet; this->get(1,2)*=idet; this->get(2,2)*=idet; this->get(3,2)*=idet;
        this->get(0,3)*=idet; this->get(1,3)*=idet; this->get(2,3)*=idet; this->get(3,3)*=idet;
    }

    //
    void get_inverse( self_t* _pResult ) const
    {
        T tmp[12];

        // calculate pairs for first 8 elements (cofactors)
        tmp[0] = this->get(2,2) * this->get(3,3);
        tmp[1] = this->get(2,3) * this->get(3,2);
        tmp[2] = this->get(2,1) * this->get(3,3);
        tmp[3] = this->get(2,3) * this->get(3,1);
        tmp[4] = this->get(2,1) * this->get(3,2);
        tmp[5] = this->get(2,2) * this->get(3,1);
        tmp[6] = this->get(2,0) * this->get(3,3);
        tmp[7] = this->get(2,3) * this->get(3,0);
        tmp[8] = this->get(2,0) * this->get(3,2);
        tmp[9] = this->get(2,2) * this->get(3,0);
        tmp[10]= this->get(2,0) * this->get(3,1);
        tmp[11]= this->get(2,1) * this->get(3,0);

        // calculate first 8 elements (cofactors)
        _pResult->get(0,0) = tmp[0]*this->get(1,1) + tmp[3]*this->get(1,2) + tmp[ 4]*this->get(1,3);
        _pResult->get(0,0)-= tmp[1]*this->get(1,1) + tmp[2]*this->get(1,2) + tmp[ 5]*this->get(1,3);
        _pResult->get(1,0) = tmp[1]*this->get(1,0) + tmp[6]*this->get(1,2) + tmp[ 9]*this->get(1,3);
        _pResult->get(1,0)-= tmp[0]*this->get(1,0) + tmp[7]*this->get(1,2) + tmp[ 8]*this->get(1,3);
        _pResult->get(2,0) = tmp[2]*this->get(1,0) + tmp[7]*this->get(1,1) + tmp[10]*this->get(1,3);
        _pResult->get(2,0)-= tmp[3]*this->get(1,0) + tmp[6]*this->get(1,1) + tmp[11]*this->get(1,3);
        _pResult->get(3,0) = tmp[5]*this->get(1,0) + tmp[8]*this->get(1,1) + tmp[11]*this->get(1,2);
        _pResult->get(3,0)-= tmp[4]*this->get(1,0) + tmp[9]*this->get(1,1) + tmp[10]*this->get(1,2);
        _pResult->get(0,1) = tmp[1]*this->get(0,1) + tmp[2]*this->get(0,2) + tmp[ 5]*this->get(0,3);
        _pResult->get(0,1)-= tmp[0]*this->get(0,1) + tmp[3]*this->get(0,2) + tmp[ 4]*this->get(0,3);
        _pResult->get(1,1) = tmp[0]*this->get(0,0) + tmp[7]*this->get(0,2) + tmp[ 8]*this->get(0,3);
        _pResult->get(1,1)-= tmp[1]*this->get(0,0) + tmp[6]*this->get(0,2) + tmp[ 9]*this->get(0,3);
        _pResult->get(2,1) = tmp[3]*this->get(0,0) + tmp[6]*this->get(0,1) + tmp[11]*this->get(0,3);
        _pResult->get(2,1)-= tmp[2]*this->get(0,0) + tmp[7]*this->get(0,1) + tmp[10]*this->get(0,3);
        _pResult->get(3,1) = tmp[4]*this->get(0,0) + tmp[9]*this->get(0,1) + tmp[10]*this->get(0,2);
        _pResult->get(3,1)-= tmp[5]*this->get(0,0) + tmp[8]*this->get(0,1) + tmp[11]*this->get(0,2);

        // calculate pairs for second 8 elements (cofactors)
        tmp[ 0] = this->get(0,2)*this->get(1,3);
        tmp[ 1] = this->get(0,3)*this->get(1,2);
        tmp[ 2] = this->get(0,1)*this->get(1,3);
        tmp[ 3] = this->get(0,3)*this->get(1,1);
        tmp[ 4] = this->get(0,1)*this->get(1,2);
        tmp[ 5] = this->get(0,2)*this->get(1,1);
        tmp[ 6] = this->get(0,0)*this->get(1,3);
        tmp[ 7] = this->get(0,3)*this->get(1,0);
        tmp[ 8] = this->get(0,0)*this->get(1,2);
        tmp[ 9] = this->get(0,2)*this->get(1,0);
        tmp[10] = this->get(0,0)*this->get(1,1);
        tmp[11] = this->get(0,1)*this->get(1,0);

        // calculate second 8 elements (cofactors)
        _pResult->get(0,2) = tmp[ 0]*this->get(3,1) + tmp[ 3]*this->get(3,2) + tmp[ 4]*this->get(3,3);
        _pResult->get(0,2)-= tmp[ 1]*this->get(3,1) + tmp[ 2]*this->get(3,2) + tmp[ 5]*this->get(3,3);
        _pResult->get(1,2) = tmp[ 1]*this->get(3,0) + tmp[ 6]*this->get(3,2) + tmp[ 9]*this->get(3,3);
        _pResult->get(1,2)-= tmp[ 0]*this->get(3,0) + tmp[ 7]*this->get(3,2) + tmp[ 8]*this->get(3,3);
        _pResult->get(2,2) = tmp[ 2]*this->get(3,0) + tmp[ 7]*this->get(3,1) + tmp[10]*this->get(3,3);
        _pResult->get(2,2)-= tmp[ 3]*this->get(3,0) + tmp[ 6]*this->get(3,1) + tmp[11]*this->get(3,3);
        _pResult->get(3,2) = tmp[ 5]*this->get(3,0) + tmp[ 8]*this->get(3,1) + tmp[11]*this->get(3,2);
        _pResult->get(3,2)-= tmp[ 4]*this->get(3,0) + tmp[ 9]*this->get(3,1) + tmp[10]*this->get(3,2);
        _pResult->get(0,3) = tmp[ 2]*this->get(2,2) + tmp[ 5]*this->get(2,3) + tmp[ 1]*this->get(2,1);
        _pResult->get(0,3)-= tmp[ 4]*this->get(2,3) + tmp[ 0]*this->get(2,1) + tmp[ 3]*this->get(2,2);
        _pResult->get(1,3) = tmp[ 8]*this->get(2,3) + tmp[ 0]*this->get(2,0) + tmp[ 7]*this->get(2,2);
        _pResult->get(1,3)-= tmp[ 6]*this->get(2,2) + tmp[ 9]*this->get(2,3) + tmp[ 1]*this->get(2,0);
        _pResult->get(2,3) = tmp[ 6]*this->get(2,1) + tmp[11]*this->get(2,3) + tmp[ 3]*this->get(2,0);
        _pResult->get(2,3)-= tmp[10]*this->get(2,3) + tmp[ 2]*this->get(2,0) + tmp[ 7]*this->get(2,1);
        _pResult->get(3,3) = tmp[10]*this->get(2,2) + tmp[ 4]*this->get(2,0) + tmp[ 9]*this->get(2,1);
        _pResult->get(3,3)-= tmp[ 8]*this->get(2,1) + tmp[11]*this->get(2,2) + tmp[ 5]*this->get(2,0);

        // calculate determinant
        T det=( this->get(0,0)*_pResult->get(0,0) + this->get(0,1)*_pResult->get(1,0) + this->get(0,2)*_pResult->get(2,0) + this->get(0,3)*_pResult->get(3,0) );

        //devide the cofactor-matrix by the determinat
        T idet=(T)1.0/det;
        _pResult->get(0,0)*=idet; _pResult->get(1,0)*=idet; _pResult->get(2,0)*=idet; _pResult->get(3,0)*=idet;
        _pResult->get(0,1)*=idet; _pResult->get(1,1)*=idet; _pResult->get(2,1)*=idet; _pResult->get(3,1)*=idet;
        _pResult->get(0,2)*=idet; _pResult->get(1,2)*=idet; _pResult->get(2,2)*=idet; _pResult->get(3,2)*=idet;
        _pResult->get(0,3)*=idet; _pResult->get(1,3)*=idet; _pResult->get(2,3)*=idet; _pResult->get(3,3)*=idet;
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:
    // TODO: find a way to use this, and optimize the code like this
#ifdef __USE_VECTOR_OPT__
    Vector4<T> m[4];
#else
    EX_ALIGN(16) union
    {
        struct 
        {
            T m00, m01, m02, m03;
            T m10, m11, m12, m13;
            T m20, m21, m22, m23;
            T m30, m31, m32, m33;
        }; // end struct
        T m[16];
    }; // end union
#endif

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string;
        string = string + "m00: " + to_str<FLAGS>(m00) + "\n";
        string = string + "m01: " + to_str<FLAGS>(m01) + "\n";
        string = string + "m02: " + to_str<FLAGS>(m02) + "\n";
        string = string + "m03: " + to_str<FLAGS>(m03) + "\n";
        string = string + "m10: " + to_str<FLAGS>(m10) + "\n";
        string = string + "m11: " + to_str<FLAGS>(m11) + "\n";
        string = string + "m12: " + to_str<FLAGS>(m12) + "\n";
        string = string + "m13: " + to_str<FLAGS>(m13) + "\n";
        string = string + "m20: " + to_str<FLAGS>(m20) + "\n";
        string = string + "m21: " + to_str<FLAGS>(m21) + "\n";
        string = string + "m22: " + to_str<FLAGS>(m22) + "\n";
        string = string + "m23: " + to_str<FLAGS>(m23) + "\n";
        string = string + "m30: " + to_str<FLAGS>(m30) + "\n";
        string = string + "m31: " + to_str<FLAGS>(m31) + "\n";
        string = string + "m32: " + to_str<FLAGS>(m32) + "\n";
        string = string + "m33: " + to_str<FLAGS>(m33) + "\n";
        return string;
    }

    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("Matrix4");
        return strID;
    }

    // TODO: we should define second atomic classes. ----- molecular
    void serialize ( ISerializeNode* _pNode );

}; // end class Matrix4

// #########################
} // end namespace ex 
// #########################

#include "Matrix4.hpp"

// #################################################################################
#endif // END MATRIX4_H_1250525858
// #################################################################################
