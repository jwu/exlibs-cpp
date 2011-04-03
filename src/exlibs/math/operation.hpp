// ======================================================================================
// File         : operation.hpp
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 17:20:13 PM | Sunday,August
// Description  : 
// ======================================================================================

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// Late-Inline segment
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Vector2
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: vec2 *= mat2 
// ------------------------------------------------------------------

template < typename T >
Vector2<T>& Vector2<T>::operator *= ( const Matrix2<T>& _mat2 ) 
{
    T list[2] = { this->dot( _mat2.col(0) ) ,  
                  this->dot( _mat2.col(1) ) };
    this->set(list);
    return *this;
}

// ------------------------------------------------------------------
// Desc: vec2 + vec2
// ------------------------------------------------------------------

template < typename T >
Vector2<T> operator + ( const Vector2<T>& _vec1, const Vector2<T>& _vec2 )
{
    Vector2<T> vec_result;
    mathop::add( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------
// Desc: vec2 - vec2
// ------------------------------------------------------------------

template < typename T >
Vector2<T> operator - ( const Vector2<T>& _vec1, const Vector2<T>& _vec2 )
{
    Vector2<T> vec_result;
    mathop::sub( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------
// Desc: vec2 * vec2
// ------------------------------------------------------------------

template < typename T >
Vector2<T> operator * ( const Vector2<T>& _vec1, const Vector2<T>& _vec2 )
{
    Vector2<T> vec_result;
    mathop::mul( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: vec2 * scalar 
// ------------------------------------------------------------------ 

template < typename T >
Vector2<T> operator * ( const Vector2<T>& _vec, T _scalar )
{
    Vector2<T> vec_result;
    mathop::mul_scalar( vec_result.m_data, _vec.m_data, _scalar );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: scalar * vec2 
// ------------------------------------------------------------------ 

template < typename T >
Vector2<T> operator * ( T _scalar, const Vector2<T>& _vec )
{
    Vector2<T> vec_result;
    mathop::mul_scalar( vec_result.m_data, _vec.m_data, _scalar );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: vec2 * mat2 
// ------------------------------------------------------------------ 

template < typename T >
Vector2<T> operator * ( const Vector2<T>& _vec, const Matrix2<T>& _mat2 )
{
    return Vector2<T>( _vec.dot( _mat2.col(0) ),  
                        _vec.dot( _mat2.col(1) ) );
}

// ------------------------------------------------------------------ 
// Desc: vec2 * mat2 const ver. 
// ------------------------------------------------------------------ 

template < typename T >
Vector2<T> Vector2<T>::operator * ( const Matrix2<T>& _mat2 ) const
{
    return Vector2<T>( this->dot( _mat2.col(0) ),  
                        this->dot( _mat2.col(1) ) );
}

// ------------------------------------------------------------------ 
// Desc: mat2 * vec2 
// ------------------------------------------------------------------ 

template < typename T >
Vector2<T> operator * ( const Matrix2<T>& _mat2, const Vector2<T>& _vec )
{
    return Vector2<T>( _vec.dot( _mat2.row(0) ),  
                        _vec.dot( _mat2.row(1) ) );
}

// ------------------------------------------------------------------
// Desc: vec2 / vec2
// ------------------------------------------------------------------

template < typename T >
Vector2<T> operator / ( const Vector2<T>& _vec1, const Vector2<T>& _vec2 )
{
    Vector2<T> vec_result;
    mathop::div( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: vec2 / scalar 
// ------------------------------------------------------------------ 

template < typename T >
Vector2<T> operator / ( const Vector2<T>& _vec, T _scalar )
{
    Vector2<T> vec_result;
    mathop::div_scalar( vec_result.m_data, _vec.m_data, _scalar );
    return vec_result;
}

// TODO: implement scalar_div
// ========================================================
// scalar / vec2 
// ========================================================

// template < typename T, uint COUNT >
// Vector2<T> operator / ( T _scalar, const Vector2<T>& _vec )
// {
//     Vector2<T> vec_result;
//     mathop::scalar_div( vec_result.m_data, _scalar, _vec.m_data );
//     return vec_result;
// }

///////////////////////////////////////////////////////////////////////////////
// Vector3
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: vec3 *= mat3 
// ------------------------------------------------------------------

template < typename T >
Vector3<T>& Vector3<T>::operator *= ( const Matrix3<T>& _mat3 ) 
{
    T list[3] = { this->dot( _mat3.col(0) ),
                  this->dot( _mat3.col(1) ),
                  this->dot( _mat3.col(2) ) };
    this->set(list);
    return *this;
}

// ------------------------------------------------------------------
// Desc: vec3 + vec3
// ------------------------------------------------------------------

template < typename T >
Vector3<T> operator + ( const Vector3<T>& _vec1, const Vector3<T>& _vec2 )
{
    Vector3<T> vec_result;
    mathop::add( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------
// Desc: vec3 - vec3
// ------------------------------------------------------------------

template < typename T >
Vector3<T> operator - ( const Vector3<T>& _vec1, const Vector3<T>& _vec2 )
{
    Vector3<T> vec_result;
    mathop::sub( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------
// Desc: vec3 * vec3
// ------------------------------------------------------------------

template < typename T >
Vector3<T> operator * ( const Vector3<T>& _vec1, const Vector3<T>& _vec2 )
{
    Vector3<T> vec_result;
    mathop::mul( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: vec3 * scalar 
// ------------------------------------------------------------------ 

template < typename T >
Vector3<T> operator * ( const Vector3<T>& _vec, T _scalar )
{
    Vector3<T> vec_result;
    mathop::mul_scalar( vec_result.m_data, _vec.m_data, _scalar );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: scalar * vec3 
// ------------------------------------------------------------------ 

template < typename T >
Vector3<T> operator * ( T _scalar, const Vector3<T>& _vec )
{
    Vector3<T> vec_result;
    mathop::mul_scalar( vec_result.m_data, _vec.m_data, _scalar );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: vec3 * mat3 
// ------------------------------------------------------------------ 

template < typename T >
Vector3<T> operator * ( const Vector3<T>& _vec, const Matrix3<T>& _mat3 )
{
    return Vector3<T>( _vec.dot( _mat3.col(0) ),  
                        _vec.dot( _mat3.col(1) ),
                        _vec.dot( _mat3.col(2) ) );
}

// ------------------------------------------------------------------ 
// Desc: vec3 * mat3 const ver. 
// ------------------------------------------------------------------ 

template < typename T >
Vector3<T> Vector3<T>::operator * ( const Matrix3<T>& _mat3 ) const
{
    return Vector3<T>( this->dot( _mat3.col(0) ),  
                        this->dot( _mat3.col(1) ),
                        this->dot( _mat3.col(2) ) );
}

// ------------------------------------------------------------------ 
// Desc: mat3 * vec3 
// ------------------------------------------------------------------ 

template < typename T >
Vector3<T> operator * ( const Matrix3<T>& _mat3, const Vector3<T>& _vec )
{
    return Vector3<T>( _vec.dot( _mat3.row(0) ),  
                        _vec.dot( _mat3.row(1) ),
                        _vec.dot( _mat3.row(2) ));
}

// ------------------------------------------------------------------
// Desc: vec3 / vec3
// ------------------------------------------------------------------

template < typename T >
Vector3<T> operator / ( const Vector3<T>& _vec1, const Vector3<T>& _vec2 )
{
    Vector3<T> vec_result;
    mathop::div( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: vec3 / scalar 
// ------------------------------------------------------------------ 

template < typename T >
Vector3<T> operator / ( const Vector3<T>& _vec, T _scalar )
{
    Vector3<T> vec_result;
    mathop::div_scalar( vec_result.m_data, _vec.m_data, _scalar );
    return vec_result;
}

// TODO: implement scalar_div
// ========================================================
// scalar / vec3 
// ========================================================

// template < typename T, uint COUNT >
// Vector3<T> operator / ( T _scalar, const Vector3<T>& _vec )
// {
//     Vector3<T> vec_result;
//     mathop::scalar_div( vec_result.m_data, _scalar, _vec.m_data );
//     return vec_result;
// }

///////////////////////////////////////////////////////////////////////////////
// Vector4
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: vec4 *= mat4 
// ------------------------------------------------------------------

template < typename T >
Vector4<T>& Vector4<T>::operator *= ( const Matrix4<T>& _mat4 ) 
{
    T list[3] = { this->dot( _mat4.col(0) ),
                  this->dot( _mat4.col(1) ),
                  this->dot( _mat4.col(2) ),
                  this->dot( _mat4.col(3) ) };
    this->set(list);
    return *this;
}

// ------------------------------------------------------------------
// Desc: vec4 + vec4
// ------------------------------------------------------------------

template < typename T >
Vector4<T> operator + ( const Vector4<T>& _vec1, const Vector4<T>& _vec2 )
{
    Vector4<T> vec_result;
    mathop::add( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------
// Desc: vec4 - vec4
// ------------------------------------------------------------------

template < typename T >
Vector4<T> operator - ( const Vector4<T>& _vec1, const Vector4<T>& _vec2 )
{
    Vector4<T> vec_result;
    mathop::sub( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------
// Desc: vec4 * vec4
// ------------------------------------------------------------------

template < typename T >
Vector4<T> operator * ( const Vector4<T>& _vec1, const Vector4<T>& _vec2 )
{
    Vector4<T> vec_result;
    mathop::mul( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: vec4 * scalar 
// ------------------------------------------------------------------ 

template < typename T >
Vector4<T> operator * ( const Vector4<T>& _vec, T _scalar )
{
    Vector4<T> vec_result;
    mathop::mul_scalar( vec_result.m_data, _vec.m_data, _scalar );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: scalar * vec4 
// ------------------------------------------------------------------ 

template < typename T >
Vector4<T> operator * ( T _scalar, const Vector4<T>& _vec )
{
    Vector4<T> vec_result;
    mathop::mul_scalar( vec_result.m_data, _vec.m_data, _scalar );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: vec4 * mat3 
// ------------------------------------------------------------------ 

template < typename T >
Vector4<T> operator * ( const Vector4<T>& _vec, const Matrix4<T>& _mat4 )
{
    return Vector4<T>( _vec.dot( _mat4.col(0) ),  
                        _vec.dot( _mat4.col(1) ),
                        _vec.dot( _mat4.col(2) ),
                        _vec.dot( _mat4.col(3) ) );
}

// ------------------------------------------------------------------ 
// Desc: vec4 * mat3 const ver. 
// ------------------------------------------------------------------ 

template < typename T >
Vector4<T> Vector4<T>::operator * ( const Matrix4<T>& _mat4 ) const
{
    return Vector4<T>( this->dot( _mat4.col(0) ),  
                        this->dot( _mat4.col(1) ),
                        this->dot( _mat4.col(2) ),
                        this->dot( _mat4.col(3) ) );
}

// ------------------------------------------------------------------ 
// Desc: mat3 * vec4 
// ------------------------------------------------------------------ 

template < typename T >
Vector4<T> operator * ( const Matrix4<T>& _mat4, const Vector4<T>& _vec )
{
    return Vector4<T>( _vec.dot( _mat4.row(0) ),  
                        _vec.dot( _mat4.row(1) ),
                        _vec.dot( _mat4.row(2) ),
                        _vec.dot( _mat4.row(3) ) );
}

// ------------------------------------------------------------------
// Desc: vec4 / vec4
// ------------------------------------------------------------------

template < typename T >
Vector4<T> operator / ( const Vector4<T>& _vec1, const Vector4<T>& _vec2 )
{
    Vector4<T> vec_result;
    mathop::div( vec_result.m_data, _vec1.m_data, _vec2.m_data );
    return vec_result;
}

// ------------------------------------------------------------------ 
// Desc: vec4 / scalar 
// ------------------------------------------------------------------ 

template < typename T >
Vector4<T> operator / ( const Vector4<T>& _vec, T _scalar )
{
    Vector4<T> vec_result;
    mathop::div_scalar( vec_result.m_data, _vec.m_data, _scalar );
    return vec_result;
}

// TODO: implement scalar_div
// ========================================================
// scalar / vec4 
// ========================================================

// template < typename T, uint COUNT >
// Vector4<T> operator / ( T _scalar, const Vector4<T>& _vec )
// {
//     Vector4<T> vec_result;
//     mathop::scalar_div( vec_result.m_data, _scalar, _vec.m_data );
//     return vec_result;
// }

///////////////////////////////////////////////////////////////////////////////
// Matrix2
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Add +
// ------------------------------------------------------------------

template < typename T >
Matrix2<T> operator + ( const Matrix2<T>& _mat1, const Matrix2<T>& _mat2 )
{
    return Matrix2<T>( _mat1(0,0)+_mat2(0,0),_mat1(0,1)+_mat2(0,1),
                        _mat1(1,0)+_mat2(1,0),_mat1(1,1)+_mat2(1,1) );
}

// ------------------------------------------------------------------
// Desc: Sub -
// ------------------------------------------------------------------

template < typename T >
Matrix2<T> operator - ( const Matrix2<T>& _mat1, const Matrix2<T>& _mat2 )
{
    return Matrix2<T>( _mat1(0,0)-_mat2(0,0),_mat1(0,1)-_mat2(0,1),
                        _mat1(1,0)-_mat2(1,0),_mat1(1,1)-_mat2(1,1) );
}

// ------------------------------------------------------------------
// Desc: Mul *
// ------------------------------------------------------------------

// ========================================================
// mat * mat 
// ========================================================

template < typename T >
Matrix2<T> operator * ( const Matrix2<T>& _mat1, const Matrix2<T>& _mat2 )
{
    return Matrix2<T>( _mat1(0,0) * _mat2(0,0) +_mat1(0,1) * _mat2(1,0),_mat1(0,0) * _mat2(0,1) +_mat1(0,1) * _mat2(1,1), 
                        _mat1(1,0) * _mat2(0,0) +_mat1(1,1) * _mat2(1,0),_mat1(1,0) * _mat2(0,1) +_mat1(1,1) * _mat2(1,1) );
}

// ========================================================
// mat * scalar 
// ========================================================

template < typename T >
Matrix2<T> operator * ( const Matrix2<T>& _mat, T _scalar )
{
    return Matrix2<T>( _mat(0,0) * _scalar, _mat(0,1) * _scalar,
                        _mat(1,0) * _scalar, _mat(1,1) * _scalar );
}

// ========================================================
// scalar * mat 
// ========================================================

template < typename T >
Matrix2<T> operator * ( T _scalar, const Matrix2<T>& _mat )
{
    return Matrix2<T>( _mat(0,0) * _scalar, _mat(0,1) * _scalar,
                        _mat(1,0) * _scalar, _mat(1,1) * _scalar );
}

// ------------------------------------------------------------------
// Desc: Div / 
// ------------------------------------------------------------------

// ========================================================
// mat / scalar
// ========================================================

template < typename T >
Matrix2<T> operator / ( const Matrix2<T>& _mat, T _scalar )
{
    T inv_scalar = T(1) / _scalar;
    return Matrix2<T>( _mat(0,0) * inv_scalar, _mat(0,1) * inv_scalar,
                        _mat(1,0) * inv_scalar, _mat(1,1) * inv_scalar );
}

// ========================================================
// scalar / mat 
// ========================================================

template < typename T >
Matrix2<T> operator / ( T _scalar, const Matrix2<T>& _mat )
{
    return Matrix2<T>( _scalar / _mat(0,0), _scalar / _mat(0,1),
                        _scalar / _mat(1,0), _scalar / _mat(1,1) );
}

///////////////////////////////////////////////////////////////////////////////
// Matrix3
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Add +
// ------------------------------------------------------------------

template < typename T >
Matrix3<T> operator + ( const Matrix3<T>& _mat1, const Matrix3<T>& _mat2 )
{
    return Matrix3<T>( _mat1(0,0)+_mat2(0,0),_mat1(0,1)+_mat2(0,1),_mat1(0,2)+_mat2(0,2),
                        _mat1(1,0)+_mat2(1,0),_mat1(1,1)+_mat2(1,1),_mat1(1,2)+_mat2(1,2),
                        _mat1(2,0)+_mat2(2,0),_mat1(2,1)+_mat2(2,1),_mat1(2,2)+_mat2(2,2) );
}


// ------------------------------------------------------------------
// Desc: Sub - 
// ------------------------------------------------------------------

template < typename T >
Matrix3<T> operator - ( const Matrix3<T>& _mat1, const Matrix3<T>& _mat2 )
{
    return Matrix3<T>( _mat1(0,0)-_mat2(0,0),_mat1(0,1)-_mat2(0,1),_mat1(0,2)-_mat2(0,2),
                        _mat1(1,0)-_mat2(1,0),_mat1(1,1)-_mat2(1,1),_mat1(1,2)-_mat2(1,2),
                        _mat1(2,0)-_mat2(2,0),_mat1(2,1)-_mat2(2,1),_mat1(2,2)-_mat2(2,2) );
}

// ------------------------------------------------------------------
// Desc: Mul * 
// ------------------------------------------------------------------

// ========================================================
// mat * mat
// ========================================================

template < typename T >
Matrix3<T> operator * ( const Matrix3<T>& _mat1, const Matrix3<T>& _mat2 )
{
    Matrix3<T> result;

    result(0,0) = _mat1(0,0) * _mat2(0,0) + _mat1(0,1) * _mat2(1,0) + _mat1(0,2) * _mat2(2,0);
    result(0,1) = _mat1(0,0) * _mat2(0,1) + _mat1(0,1) * _mat2(1,1) + _mat1(0,2) * _mat2(2,1);
    result(0,2) = _mat1(0,0) * _mat2(0,2) + _mat1(0,1) * _mat2(1,2) + _mat1(0,2) * _mat2(2,2);

    result(1,0) = _mat1(1,0) * _mat2(0,0) + _mat1(1,1) * _mat2(1,0) + _mat1(1,2) * _mat2(2,0);
    result(1,1) = _mat1(1,0) * _mat2(0,1) + _mat1(1,1) * _mat2(1,1) + _mat1(1,2) * _mat2(2,1);
    result(1,2) = _mat1(1,0) * _mat2(0,2) + _mat1(1,1) * _mat2(1,2) + _mat1(1,2) * _mat2(2,2);

    result(2,0) = _mat1(2,0) * _mat2(0,0) + _mat1(2,1) * _mat2(1,0) + _mat1(2,2) * _mat2(2,0);
    result(2,1) = _mat1(2,0) * _mat2(0,1) + _mat1(2,1) * _mat2(1,1) + _mat1(2,2) * _mat2(2,1);
    result(2,2) = _mat1(2,0) * _mat2(0,2) + _mat1(2,1) * _mat2(1,2) + _mat1(2,2) * _mat2(2,2);

    return result;
}

// ========================================================
// mat * scalar 
// ========================================================

template < typename T >
Matrix3<T> operator * ( const Matrix3<T>& _mat, T _scalar )
{
    return Matrix3<T>( _mat(0,0) * _scalar, _mat(0,1) * _scalar, _mat(0,2) * _scalar,
                        _mat(1,0) * _scalar, _mat(1,1) * _scalar, _mat(1,2) * _scalar,
                        _mat(2,0) * _scalar, _mat(2,1) * _scalar, _mat(2,2) * _scalar );
}

// ========================================================
// scalar * mat 
// ========================================================

template < typename T >
Matrix3<T> operator * ( T _scalar, const Matrix3<T>& _mat )
{
    return Matrix3<T>( _mat(0,0) * _scalar, _mat(0,1) * _scalar, _mat(0,2) * _scalar,
                        _mat(1,0) * _scalar, _mat(1,1) * _scalar, _mat(1,2) * _scalar,
                        _mat(2,0) * _scalar, _mat(2,1) * _scalar, _mat(2,2) * _scalar );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// ========================================================
// mat / scalar
// ========================================================

template < typename T >
Matrix3<T> operator / ( const Matrix3<T>& _mat, T _scalar )
{
    T inv_scalar = T(1) / _scalar;
    return Matrix3<T>( _mat(0,0) * inv_scalar, _mat(0,1) * inv_scalar, _mat(0,2) * inv_scalar,
                        _mat(1,0) * inv_scalar, _mat(1,1) * inv_scalar, _mat(1,2) * inv_scalar,
                        _mat(2,0) * inv_scalar, _mat(2,1) * inv_scalar, _mat(2,2) * inv_scalar );
}

// ========================================================
// scalar / mat 
// ========================================================

template < typename T >
Matrix3<T> operator / ( T _scalar, const Matrix3<T>& _mat )
{
    return Matrix3<T>( _scalar/_mat(0,0), _scalar/_mat(0,1), _scalar/_mat(0,2),
                        _scalar/_mat(1,0), _scalar/_mat(1,1), _scalar/_mat(1,2),
                        _scalar/_mat(2,0), _scalar/_mat(2,1), _scalar/_mat(2,2) );
}

///////////////////////////////////////////////////////////////////////////////
// Matrix4
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Add + 
// ------------------------------------------------------------------

template < typename T > 
Matrix4<T> operator + ( const Matrix4<T>& _mat1, const Matrix4<T>& _mat2 )
{
    return Matrix4<T>( _mat1(0,0)+_mat2(0,0),_mat1(0,1)+_mat2(0,1),_mat1(0,2)+_mat2(0,2),_mat1(0,3)+_mat2(0,3),
                        _mat1(1,0)+_mat2(1,0),_mat1(1,1)+_mat2(1,1),_mat1(1,2)+_mat2(1,2),_mat1(1,3)+_mat2(1,3),
                        _mat1(2,0)+_mat2(2,0),_mat1(2,1)+_mat2(2,1),_mat1(2,2)+_mat2(2,2),_mat1(2,3)+_mat2(2,3),
                        _mat1(3,0)+_mat2(3,0),_mat1(3,1)+_mat2(3,1),_mat1(3,2)+_mat2(3,2),_mat1(3,3)+_mat2(3,3) );
}

// ------------------------------------------------------------------
// Desc: Sub - 
// ------------------------------------------------------------------

template < typename T > 
Matrix4<T> operator - ( const Matrix4<T>& _mat1, const Matrix4<T>& _mat2 )
{
    return Matrix4<T>( _mat1(0,0)-_mat2(0,0),_mat1(0,1)-_mat2(0,1),_mat1(0,2)-_mat2(0,2),_mat1(0,3)-_mat2(0,3),
                        _mat1(1,0)-_mat2(1,0),_mat1(1,1)-_mat2(1,1),_mat1(1,2)-_mat2(1,2),_mat1(1,3)-_mat2(1,3),
                        _mat1(2,0)-_mat2(2,0),_mat1(2,1)-_mat2(2,1),_mat1(2,2)-_mat2(2,2),_mat1(2,3)-_mat2(2,3),
                        _mat1(3,0)-_mat2(3,0),_mat1(3,1)-_mat2(3,1),_mat1(3,2)-_mat2(3,2),_mat1(3,3)-_mat2(3,3) );
}

// ------------------------------------------------------------------
// Desc: Mul * 
// ------------------------------------------------------------------

// ========================================================
// mat * mat
// ========================================================

template < typename T > 
Matrix4<T> operator * ( const Matrix4<T>& _mat1, const Matrix4<T>& _mat2 )
{
    Matrix4<T> result;

    result(0,0) =_mat1(0,0) * _mat2(0,0) +_mat1(0,1) * _mat2(1,0) +_mat1(0,2) * _mat2(2,0) +_mat1(0,3) * _mat2(3,0);
    result(0,1) =_mat1(0,0) * _mat2(0,1) +_mat1(0,1) * _mat2(1,1) +_mat1(0,2) * _mat2(2,1) +_mat1(0,3) * _mat2(3,1);
    result(0,2) =_mat1(0,0) * _mat2(0,2) +_mat1(0,1) * _mat2(1,2) +_mat1(0,2) * _mat2(2,2) +_mat1(0,3) * _mat2(3,2);
    result(0,3) =_mat1(0,0) * _mat2(0,3) +_mat1(0,1) * _mat2(1,3) +_mat1(0,2) * _mat2(2,3) +_mat1(0,3) * _mat2(3,3);

    result(1,0) =_mat1(1,0) * _mat2(0,0) +_mat1(1,1) * _mat2(1,0) +_mat1(1,2) * _mat2(2,0) +_mat1(1,3) * _mat2(3,0);
    result(1,1) =_mat1(1,0) * _mat2(0,1) +_mat1(1,1) * _mat2(1,1) +_mat1(1,2) * _mat2(2,1) +_mat1(1,3) * _mat2(3,1);
    result(1,2) =_mat1(1,0) * _mat2(0,2) +_mat1(1,1) * _mat2(1,2) +_mat1(1,2) * _mat2(2,2) +_mat1(1,3) * _mat2(3,2);
    result(1,3) =_mat1(1,0) * _mat2(0,3) +_mat1(1,1) * _mat2(1,3) +_mat1(1,2) * _mat2(2,3) +_mat1(1,3) * _mat2(3,3);

    result(2,0) =_mat1(2,0) * _mat2(0,0) +_mat1(2,1) * _mat2(1,0) +_mat1(2,2) * _mat2(2,0) +_mat1(2,3) * _mat2(3,0);
    result(2,1) =_mat1(2,0) * _mat2(0,1) +_mat1(2,1) * _mat2(1,1) +_mat1(2,2) * _mat2(2,1) +_mat1(2,3) * _mat2(3,1);
    result(2,2) =_mat1(2,0) * _mat2(0,2) +_mat1(2,1) * _mat2(1,2) +_mat1(2,2) * _mat2(2,2) +_mat1(2,3) * _mat2(3,2);
    result(2,3) =_mat1(2,0) * _mat2(0,3) +_mat1(2,1) * _mat2(1,3) +_mat1(2,2) * _mat2(2,3) +_mat1(2,3) * _mat2(3,3);

    result(3,0) =_mat1(3,0) * _mat2(0,0) +_mat1(3,1) * _mat2(1,0) +_mat1(3,2) * _mat2(2,0) +_mat1(3,3) * _mat2(3,0);
    result(3,1) =_mat1(3,0) * _mat2(0,1) +_mat1(3,1) * _mat2(1,1) +_mat1(3,2) * _mat2(2,1) +_mat1(3,3) * _mat2(3,1);
    result(3,2) =_mat1(3,0) * _mat2(0,2) +_mat1(3,1) * _mat2(1,2) +_mat1(3,2) * _mat2(2,2) +_mat1(3,3) * _mat2(3,2);
    result(3,3) =_mat1(3,0) * _mat2(0,3) +_mat1(3,1) * _mat2(1,3) +_mat1(3,2) * _mat2(2,3) +_mat1(3,3) * _mat2(3,3);

    return result;
}

// ========================================================
// mat * scalar 
// ========================================================

template < typename T > 
Matrix4<T> operator * ( const Matrix4<T>& _mat, T _scalar )
{
    return Matrix4<T>(_mat(0,0) * _scalar,_mat(0,1) * _scalar,_mat(0,2) * _scalar,_mat(0,3) * _scalar,
                       _mat(1,0) * _scalar,_mat(1,1) * _scalar,_mat(1,2) * _scalar,_mat(1,3) * _scalar,
                       _mat(2,0) * _scalar,_mat(2,1) * _scalar,_mat(2,2) * _scalar,_mat(2,3) * _scalar,
                       _mat(3,0) * _scalar,_mat(3,1) * _scalar,_mat(3,2) * _scalar,_mat(3,3) * _scalar );
}

// ========================================================
// scalar * mat 
// ========================================================

template < typename T > 
Matrix4<T> operator * ( T _scalar, const Matrix4<T>& _mat )
{
    return Matrix4<T>(_mat(0,0) * _scalar,_mat(0,1) * _scalar,_mat(0,2) * _scalar,_mat(0,3) * _scalar,
                       _mat(1,0) * _scalar,_mat(1,1) * _scalar,_mat(1,2) * _scalar,_mat(1,3) * _scalar,
                       _mat(2,0) * _scalar,_mat(2,1) * _scalar,_mat(2,2) * _scalar,_mat(2,3) * _scalar,
                       _mat(3,0) * _scalar,_mat(3,1) * _scalar,_mat(3,2) * _scalar,_mat(3,3) * _scalar );
}

// ------------------------------------------------------------------
// Desc: DIV /
// ------------------------------------------------------------------

// ========================================================
// mat / scalar 
// ========================================================

template < typename T > 
Matrix4<T> operator / ( const Matrix4<T>& _mat, T _scalar )
{
    T inv_scalar = T(1) / _scalar;
    return Matrix4<T>( _mat(0,0) * inv_scalar,_mat(0,1) * inv_scalar,_mat(0,2) * inv_scalar,_mat(0,3) * inv_scalar,
                        _mat(1,0) * inv_scalar,_mat(1,1) * inv_scalar,_mat(1,2) * inv_scalar,_mat(1,3) * inv_scalar,
                        _mat(2,0) * inv_scalar,_mat(2,1) * inv_scalar,_mat(2,2) * inv_scalar,_mat(2,3) * inv_scalar,
                        _mat(3,0) * inv_scalar,_mat(3,1) * inv_scalar,_mat(3,2) * inv_scalar,_mat(3,3) * inv_scalar );
}

// ========================================================
// scalar / mat 
// ========================================================

template < typename T > 
Matrix4<T> operator / ( T _scalar, const Matrix4<T>& _mat )
{
    return Matrix4<T>( _scalar/_mat(0,0),_scalar/_mat(0,1),_scalar/_mat(0,2),_scalar/_mat(0,3),
                        _scalar/_mat(1,0),_scalar/_mat(1,1),_scalar/_mat(1,2),_scalar/_mat(1,3),
                        _scalar/_mat(2,0),_scalar/_mat(2,1),_scalar/_mat(2,2),_scalar/_mat(2,3),
                        _scalar/_mat(3,0),_scalar/_mat(3,1),_scalar/_mat(3,2),_scalar/_mat(3,3) );
}

///////////////////////////////////////////////////////////////////////////////
// Quaternion
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Add + 
// ------------------------------------------------------------------

template < typename T > 
Quaternion<T> operator + ( const Quaternion<T>& _quat1, const Quaternion<T>& _quat2 )
{
    Quaternion<T> quat_result;
    mathop::add( quat_result.m_Components.Data, _quat1.m_Components.Data, _quat2.m_Components.Data );
    return quat_result;
}

// ------------------------------------------------------------------
// Desc: Sub - 
// ------------------------------------------------------------------

template < typename T > 
Quaternion<T> operator - ( const Quaternion<T>& _quat1, const Quaternion<T>& _quat2 )
{
    Quaternion<T> quat_result;
    mathop::sub( quat_result.m_Components.Data, _quat1.m_Components.Data, _quat2.m_Components.Data );
    return quat_result;
}

// ------------------------------------------------------------------
// Desc: Mul * 
// ------------------------------------------------------------------

// ========================================================
// quat * quat
// ========================================================

template < typename T > 
Quaternion<T> operator * ( const Quaternion<T>& _quat1, const Quaternion<T>& _quat2 )
{
    Quaternion<T> quat_result;
#if 1
    quat_result.set(
                    _quat1.x() * _quat2.w() + _quat1.w() * _quat2.x() + _quat1.z() * _quat2.y() - _quat1.y() * _quat2.z(), /* x */
                    _quat1.y() * _quat2.w() + _quat1.w() * _quat2.y() + _quat1.x() * _quat2.z() - _quat1.z() * _quat2.x(), /* y */
                    _quat1.z() * _quat2.w() + _quat1.w() * _quat2.z() + _quat1.y() * _quat2.x() - _quat1.x() * _quat2.y(), /* z */
                    _quat1.w() * _quat2.w() - _quat1.x() * _quat2.x() - _quat1.y() * _quat2.y() - _quat1.z() * _quat2.z()  /* w */
                   );
#else
    // TODO: confirm this
    T t0 = (_quat1.y() - _quat1.z() ) * ( _quat2.z() - _quat2.y() );
    T t1 = (_quat1.w() + _quat1.x() ) * ( _quat2.w() + _quat2.x() );
    T t2 = (_quat1.y() + _quat1.z() ) * ( _quat2.w() - _quat2.x() );
    T t3 = (_quat1.w() - _quat1.x() ) * ( _quat2.y() + _quat2.z() );
    T t4 = (_quat1.x() - _quat1.y() ) * ( _quat2.z() - _quat2.x() );
    T t5 = (_quat1.x() + _quat1.y() ) * ( _quat2.z() + _quat2.x() );
    T t6 = (_quat1.w() - _quat1.z() ) * ( _quat2.w() + _quat2.y() );
    T t7 = (_quat1.w() + _quat1.z() ) * ( _quat2.w() - _quat2.y() );
    T t8 = t5 + t6 + t7;
    T t9 = 0.5 * ( t4 + t8 );

    quat_result.set( 
                    t1 + t9 - t8, /* x */
                    t2 + t9 - t7, /* y */
                    t3 + t9 - t6, /* z */
                    t0 + t9 - t5  /* w */
                   );
#endif
    return quat_result;
}

// ========================================================
// quat * scalar
// ========================================================

template < typename T > 
Quaternion<T> operator * ( const Quaternion<T>& _quat, T _scalar )
{
    Quaternion<T> quat_result;
    mathop::mul_scalar( quat_result.m_Components.Data, _quat.m_Components.Data, _scalar );
    return quat_result;
}

// ========================================================
// scalar * quat
// ========================================================

template < typename T > 
Quaternion<T> operator * ( T _scalar, const Quaternion<T>& _quat )
{
    Quaternion<T> quat_result;
    mathop::mul_scalar( quat_result.m_Components.Data, _quat.m_Components.Data, _scalar );
    return quat_result;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// ========================================================
// quat / scalar
// ========================================================

template < typename T >
Quaternion<T> operator / ( const Quaternion<T>& _quat, T _scalar )
{
    Quaternion<T> quat_result;
    mathop::div_scalar( quat_result.m_Components.Data, _quat.m_Components.Data, _scalar );
    return quat_result;
}

///////////////////////////////////////////////////////////////////////////////
// Angle 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Add + 
// ------------------------------------------------------------------

template < typename T >
Angle<T> operator + ( const Angle<T>& _angle1, const Angle<T>& _angle2 )
{
    return Angle<T>( T(_angle1) + T(_angle2), AngleType::radians );
}

// ------------------------------------------------------------------
// Desc: Sub - 
// ------------------------------------------------------------------

template < typename T >
Angle<T> operator - ( const Angle<T>& _angle1, const Angle<T>& _angle2 )
{
    return Angle<T>( T(_angle1) - T(_angle2), AngleType::radians );
}

// ------------------------------------------------------------------
// Desc: Mul * 
// ------------------------------------------------------------------

// ========================================================
// angle * angle
// ========================================================

template < typename T >
Angle<T> operator * ( const Angle<T>& _angle1, const Angle<T>& _angle2 )
{
    return Angle<T>( T(_angle1) * T(_angle2), AngleType::radians );
}

// ========================================================
// angle * scalar
// ========================================================

template < typename T >
Angle<T> operator * ( const Angle<T>& _angle, T _scalar )
{
    return Angle<T>( T(_angle) * _scalar, AngleType::radians );
}

// ========================================================
// scalar * angle
// ========================================================

template < typename T >
Angle<T> operator * ( T _scalar, const Angle<T>& _angle )
{
    return Angle<T>( T(_angle) * _scalar, AngleType::radians );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// ========================================================
// angle1 / angle2
// ========================================================

template < typename T >
Angle<T> operator / ( const Angle<T>& _angle1, const Angle<T>& _angle2 )
{
    return Angle<T>( T(_angle1) / T(_angle2), AngleType::radians );
}

// ========================================================
// angle / scalar
// ========================================================

template < typename T >
Angle<T> operator / ( const Angle<T>& _angle1, T _scalar )
{
    return Angle<T>( T(_angle1) / _scalar, AngleType::radians );
}

///////////////////////////////////////////////////////////////////////////////
// Rotator
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Add + 
// ------------------------------------------------------------------

template < typename T >
Rotator<T> operator + ( const Rotator<T>& _rot1, const Rotator<T>& _rot2 )
{
    Rotator<T> rot_result;
    mathop::add( rot_result.m_Components.Data, _rot1.m_Components.Data, _rot2.m_Components.Data );
    return rot_result;
}

// ------------------------------------------------------------------
// Desc: Sub - 
// ------------------------------------------------------------------

template < typename T >
Rotator<T> operator - ( const Rotator<T>& _rot1, const Rotator<T>& _rot2 )
{
    Rotator<T> rot_result;
    mathop::sub( rot_result.m_Components.Data, _rot1.m_Components.Data, _rot2.m_Components.Data );
    return rot_result;
}

// ------------------------------------------------------------------
// Desc: Mul * 
// ------------------------------------------------------------------

// ========================================================
// rot * rot
// ========================================================

template < typename T >
Rotator<T> operator * ( const Rotator<T>& _rot1, const Rotator<T>& _rot2 )
{
    Rotator<T> rot_result;
    mathop::mul( rot_result.m_Components.Data, _rot1.m_Components.Data, _rot2.m_Components.Data );
    return rot_result;
}

// ========================================================
// rot * scalar
// ========================================================

template < typename T >
Rotator<T> operator * ( const Rotator<T>& _rot, T _scalar )
{
    Rotator<T> rot_result;
    mathop::mul_scalar( rot_result.m_Components.Data, _rot.m_Components.Data, _scalar );
    return rot_result;
}

// ========================================================
// scalar * rot
// ========================================================

template < typename T >
Rotator<T> operator * ( T _scalar, const Rotator<T>& _rot )
{
    Rotator<T> rot_result;
    mathop::mul_scalar( rot_result.m_Components.Data, _rot.m_Components.Data, _scalar );
    return rot_result;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// ========================================================
// rot1 / rot2
// ========================================================

template < typename T >
Rotator<T> operator / ( const Rotator<T>& _rot1, const Rotator<T>& _rot2 )
{
    Rotator<T> rot_result;
    mathop::div( rot_result.m_Components.Data, _rot1.m_Components.Data, _rot2.m_Components.Data );
    return rot_result;
}

// ========================================================
// rot / scalar
// ========================================================

template < typename T >
Rotator<T> operator / ( const Rotator<T>& _rot1, T _scalar )
{
    Rotator<T> rot_result;
    mathop::div_scalar( rot_result.m_Components.Data, _rot1.m_Components.Data, _scalar );
    return rot_result;
}

///////////////////////////////////////////////////////////////////////////////
// Color3u
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Add + 
// ------------------------------------------------------------------

INLINE Color3u operator + ( const Color3u& _clr1, const Color3u& _clr2 )
{ 
    return Color3u( _clr1.r+_clr2.r, _clr1.g+_clr2.g, _clr1.b+_clr2.b ); 
} 

// ------------------------------------------------------------------
// Desc: Sub - 
// ------------------------------------------------------------------

INLINE Color3u operator - ( const Color3u& _clr1, const Color3u& _clr2 )
{
    return Color3u( _clr1.r-_clr2.r, _clr1.g-_clr2.g, _clr1.b-_clr2.b ); 
}

// ------------------------------------------------------------------
// Desc: Mul * 
// ------------------------------------------------------------------

// ========================================================
// col3u * col3u
// ========================================================

INLINE Color3u operator * ( const Color3u& _clr1, const Color3u& _clr2 )
{
    return Color3u( _clr1.r*_clr2.r, _clr1.g*_clr2.g, _clr1.b*_clr2.b ); 
}

// ========================================================
// scalar * col3u 
// ========================================================

INLINE Color3u operator * ( float _scalar, const Color3u& _color )
{
    return Color3u( uint8(_scalar*_color.r), uint8(_scalar*_color.g), uint8(_scalar*_color.b) );
}

// ========================================================
// col3u * scalar
// ========================================================

INLINE Color3u operator * ( const Color3u& _color, float _scalar )
{
    return Color3u( uint8(_scalar*_color.r), uint8(_scalar*_color.g), uint8(_scalar*_color.b) );
}

// ------------------------------------------------------------------
// Desc: Div / 
// ------------------------------------------------------------------

// ======================================================== 
// col3u / col3u 
// ======================================================== 

INLINE Color3u operator / ( const Color3u& _clr1, const Color3u& _clr2 )
{
    return Color3u( uint8(_clr1.r/_clr2.r), uint8(_clr1.g/_clr2.g), uint8(_clr1.b/_clr2.b) );
}

// ======================================================== 
// scalar / col3u
// ======================================================== 

INLINE Color3u operator / ( float _scalar, const Color3u& _color )
{
    return Color3u( uint8(_scalar/_color.r), uint8(_scalar/_color.g), uint8(_scalar/_color.b) );
}

// ======================================================== 
// col3u / scalar 
// ======================================================== 

INLINE Color3u operator / ( const Color3u& _color, float _scalar )
{
    float inv_scalar = 1.0f / _scalar;
    return Color3u( uint8(_color.r*inv_scalar), uint8(_color.g*inv_scalar), uint8(_color.b*inv_scalar) );
}

///////////////////////////////////////////////////////////////////////////////
// Color4u
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Add + 
// ------------------------------------------------------------------

INLINE Color4u operator + ( const Color4u& _clr1, const Color4u& _clr2 )
{ 
    return Color4u( _clr1.r+_clr2.r, _clr1.g+_clr2.g, _clr1.b+_clr2.b, _clr1.a+_clr2.a ); 
} 

// ------------------------------------------------------------------
// Desc: Sub - 
// ------------------------------------------------------------------

INLINE Color4u operator - ( const Color4u& _clr1, const Color4u& _clr2 )
{
    return Color4u( _clr1.r-_clr2.r, _clr1.g-_clr2.g, _clr1.b-_clr2.b, _clr1.a-_clr2.a ); 
}

// ------------------------------------------------------------------
// Desc: Mul * 
// ------------------------------------------------------------------

// ========================================================
// col4u * col4u
// ========================================================

INLINE Color4u operator * ( const Color4u& _clr1, const Color4u& _clr2 )
{
    return Color4u( _clr1.r*_clr2.r, _clr1.g*_clr2.g, _clr1.b*_clr2.b, _clr1.a*_clr2.a ); 
}

// ========================================================
// scalar * col4u 
// ========================================================

INLINE Color4u operator * ( float _scalar, const Color4u& _color )
{
    return Color4u( uint8(_scalar*_color.r), uint8(_scalar*_color.g), uint8(_scalar*_color.b), uint8(_scalar*_color.a) );
}

// ========================================================
// col4u * scalar
// ========================================================

INLINE Color4u operator * ( const Color4u& _color, float _scalar )
{
    return Color4u( uint8(_scalar*_color.r), uint8(_scalar*_color.g), uint8(_scalar*_color.b), uint8(_scalar*_color.a) );
}

// ------------------------------------------------------------------
// Desc: Div / 
// ------------------------------------------------------------------

// ======================================================== 
// col4u / col4u 
// ======================================================== 

INLINE Color4u operator / ( const Color4u& _clr1, const Color4u& _clr2 )
{
    return Color4u( uint8(_clr1.r/_clr2.r), uint8(_clr1.g/_clr2.g), uint8(_clr1.b/_clr2.b), uint8(_clr1.a/_clr2.a) );
}

// ======================================================== 
// scalar / col4u
// ======================================================== 

INLINE Color4u operator / ( float _scalar, const Color4u& _color )
{
    return Color4u( uint8(_scalar/_color.r), uint8(_scalar/_color.g), uint8(_scalar/_color.b), uint8(_scalar/_color.a) );
}

// ======================================================== 
// col4u / scalar 
// ======================================================== 

INLINE Color4u operator / ( const Color4u& _color, float _scalar )
{
    float inv_scalar = 1.0f / _scalar;
    return Color4u( uint8(_color.r*inv_scalar), uint8(_color.g*inv_scalar), uint8(_color.b*inv_scalar), uint8(_color.a*inv_scalar) );
}

///////////////////////////////////////////////////////////////////////////////
// Color3f
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Add + 
// ------------------------------------------------------------------

INLINE Color3f operator + ( const Color3f& _clr1, const Color3f& _clr2 )
{ 
    return Color3f( _clr1.r+_clr2.r, _clr1.g+_clr2.g, _clr1.b+_clr2.b ); 
} 

// ------------------------------------------------------------------
// Desc: Sub - 
// ------------------------------------------------------------------

INLINE Color3f operator - ( const Color3f& _clr1, const Color3f& _clr2 )
{
    return Color3f( _clr1.r-_clr2.r, _clr1.g-_clr2.g, _clr1.b-_clr2.b ); 
}

// ------------------------------------------------------------------
// Desc: Mul * 
// ------------------------------------------------------------------

// ========================================================
// col3f * col3f
// ========================================================

INLINE Color3f operator * ( const Color3f& _clr1, const Color3f& _clr2 )
{
    return Color3f( _clr1.r*_clr2.r, _clr1.g*_clr2.g, _clr1.b*_clr2.b ); 
}

// ========================================================
// scalar * col3f 
// ========================================================

INLINE Color3f operator * ( float _scalar, const Color3f& _color )
{
    return Color3f( _scalar*_color.r, _scalar*_color.g, _scalar*_color.b );
}

// ========================================================
// col3f * scalar
// ========================================================

INLINE Color3f operator * ( const Color3f& _color, float _scalar )
{
    return Color3f( _scalar*_color.r, _scalar*_color.g, _scalar*_color.b );
}

// ------------------------------------------------------------------
// Desc: Div / 
// ------------------------------------------------------------------

// ======================================================== 
// col3f / col3f 
// ======================================================== 

INLINE Color3f operator / ( const Color3f& _clr1, const Color3f& _clr2 )
{
    return Color3f( _clr1.r/_clr2.r, _clr1.g/_clr2.g, _clr1.b/_clr2.b );
}

// ======================================================== 
// scalar / col3f
// ======================================================== 

INLINE Color3f operator / ( float _scalar, const Color3f& _color )
{
    return Color3f( _scalar/_color.r, _scalar/_color.g, _scalar/_color.b );
}

// ======================================================== 
// col3f / scalar 
// ======================================================== 

INLINE Color3f operator / ( const Color3f& _color, float _scalar )
{
    float inv_scalar = 1.0f / _scalar;
    return Color3f( _color.r*inv_scalar, _color.g*inv_scalar, _color.b*inv_scalar );
}

///////////////////////////////////////////////////////////////////////////////
// Color4f
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Add + 
// ------------------------------------------------------------------

INLINE Color4f operator + ( const Color4f& _clr1, const Color4f& _clr2 )
{ 
    return Color4f( _clr1.r+_clr2.r, _clr1.g+_clr2.g, _clr1.b+_clr2.b, _clr1.a+_clr2.a ); 
} 

// ------------------------------------------------------------------
// Desc: Sub - 
// ------------------------------------------------------------------

INLINE Color4f operator - ( const Color4f& _clr1, const Color4f& _clr2 )
{
    return Color4f( _clr1.r-_clr2.r, _clr1.g-_clr2.g, _clr1.b-_clr2.b, _clr1.a-_clr2.a ); 
}

// ------------------------------------------------------------------
// Desc: Mul * 
// ------------------------------------------------------------------

// ========================================================
// col4f * col4f
// ========================================================

INLINE Color4f operator * ( const Color4f& _clr1, const Color4f& _clr2 )
{
    return Color4f( _clr1.r*_clr2.r, _clr1.g*_clr2.g, _clr1.b*_clr2.b, _clr1.a*_clr2.a ); 
}

// ========================================================
// scalar * col4f 
// ========================================================

INLINE Color4f operator * ( float _scalar, const Color4f& _color )
{
    return Color4f( _scalar*_color.r, _scalar*_color.g, _scalar*_color.b, _scalar*_color.a );
}

// ========================================================
// col4f * scalar
// ========================================================

INLINE Color4f operator * ( const Color4f& _color, float _scalar )
{
    return Color4f( _scalar*_color.r, _scalar*_color.g, _scalar*_color.b, _scalar*_color.a );
}

// ------------------------------------------------------------------
// Desc: Div / 
// ------------------------------------------------------------------

// ======================================================== 
// col4f / col4f 
// ======================================================== 

INLINE Color4f operator / ( const Color4f& _clr1, const Color4f& _clr2 )
{
    return Color4f( _clr1.r/_clr2.r, _clr1.g/_clr2.g, _clr1.b/_clr2.b, _clr1.a/_clr2.a );
}

// ======================================================== 
// scalar / col4f
// ======================================================== 

INLINE Color4f operator / ( float _scalar, const Color4f& _color )
{
    return Color4f( _scalar/_color.r, _scalar/_color.g, _scalar/_color.b, _scalar/_color.a );
}

// ======================================================== 
// col4u / scalar 
// ======================================================== 

INLINE Color4f operator / ( const Color4f& _color, float _scalar )
{
    float inv_scalar = 1.0f / _scalar;
    return Color4f( _color.r*inv_scalar, _color.g*inv_scalar, _color.b*inv_scalar, _color.a*inv_scalar );
}

// #########################
} // end namespace ex 
// #########################

