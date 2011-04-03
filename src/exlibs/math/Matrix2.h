// ======================================================================================
// File         : Matrix2.h
// Author       : Wu Jie 
// Last Change  : 04/16/2010 | 20:28:01 PM | Friday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MATRIX2_H_1250525832
#define MATRIX2_H_1250525832
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Matrix2
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class Matrix2
{

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef Matrix2<T> self_t;

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

    //
    Matrix2()
    {
    }

    //
    Matrix2( T _m00, T _m01,
              T _m10, T _m11 )
    {
        this->set( _m00, _m01,
                   _m10, _m11 );
    }

    //
    Matrix2( const Angle<T>& _angle )
    {
        this->set(_angle);
    }

    //
    Matrix2( const self_t& _mat )
    {
        this->set(_mat);
    }

    //
    void set( T _m00, T _m01, 
              T _m10, T _m11 )
    {
        get(0,0) = _m00; get(0,1) = _m01;
        get(1,0) = _m10; get(1,1) = _m11;
    }

    //
    void set( const Vector2<T>& _vec1, const Vector2<T>& _vec2 )
    {
        get(0,0) = _vec1.x(); get(0,1) = _vec1.y();
        get(1,0) = _vec2.x(); get(1,1) = _vec2.y();
    }

    //
    void set( const angf_t& _ang )
    {
        float cos_a = mathop::cos(_ang);
        float sin_a = mathop::sin(_ang);
        this->set ( cos_a, sin_a,
                   -sin_a, cos_a );
    }

    //
    void set( const self_t& _mat )
    {
        get(0,0) = _mat.get(0,0); get(0,1) = _mat.get(0,1);
        get(1,0) = _mat.get(1,0); get(1,1) = _mat.get(1,1);
    }

    // get row
    //  row =============
    Vector2<T> row( uint _row ) const
    {
        ex_assert( _row >= 0 && _row < 2, "out of range" );
        return Vector2<T>( get(_row,0), get(_row,1) );
    }

    // get col
    //   col
    //   ||
    //   ||
    //   ||
    //   ||
    Vector2<T> col( uint _col ) const
    {
        ex_assert( _col >= 0 && _col < 2, "out of range" );
        return Vector2<T>( get(0,_col), get(1,_col) );
    }

    // 
    T& get ( uint _row, uint _col )
    {
        ex_assert( _row >= 0 && _row < 2, "out of range" );
        ex_assert( _col >= 0 && _col < 2, "out of range" );
        return m[_row*2+_col]; 
    }

    // 
    const T& get ( uint _row, uint _col ) const
    {
        ex_assert( _row >= 0 && _row < 2, "out of range" );
        ex_assert( _col >= 0 && _col < 2, "out of range" );
        return m[_row*2+_col]; 
    }

    //
    T* getPtr() { return (T*)m; }
    const T* getPtr() const { return (T*)m; }

    //
    self_t& operator = ( const self_t& _mat )
    {
        this->set(_mat);
        return *this;
    }

    // operaotr ()
    //     Simple operator for directly accessing every element of the matrix.  
    //     useful in some codition like for( _row, _col ) .etc
    // 
    T& operator () ( uint _row, uint _col )
    {
        return get(_row,_col);
    }

    // operaotr ()
    //     Simple operator for directly accessing every element of the matrix.  
    //     useful in some codition like for( _row, _col ) .etc
    // 
    const T& operator () ( uint _row, uint _col ) const
    {
        return get(_row,_col);
    }

    // return negative copy, self value will not change
    self_t operator - () const 
    {
        return self_t( -get(0,0), -get(0,1),
                       -get(1,0), -get(1,1) );
    }

    // self negative
    self_t& negative()
    {
        get(0,0) = -get(0,0); get(0,1) = -get(0,1);
        get(1,0) = -get(1,0); get(1,1) = -get(1,1);
        return *this;
    }

    //
    self_t& operator += ( const self_t& _mat )
    {
        get(0,0) += get(0,0); get(0,1) += get(0,1); 
        get(1,0) += get(1,0); get(1,1) += get(1,1); 
        return *this;
    }

    //
    self_t& operator -= ( const self_t& _mat )
    {
        get(0,0) -= get(0,0); get(0,1) -= get(0,1); 
        get(1,0) -= get(1,0); get(1,1) -= get(1,1); 
        return *this;
    }

    //
    self_t& operator *= ( const self_t& _mat )
    {
        T m00 = get(0,0);
        T m01 = get(0,1); 
        T m10 = get(1,0); 
        T m11 = get(1,1); 

        // ----------
        get(0,0) = m00 * _mat.get(0,0) + m01 * _mat.get(1,0);
        get(0,1) = m00 * _mat.get(0,1) + m01 * _mat.get(1,1);
        // ----------
        get(1,0) = m10 * _mat.get(0,0) + m11 * _mat.get(1,0);
        get(1,1) = m10 * _mat.get(0,1) + m11 * _mat.get(1,1);
        // ----------

        return *this;
    }

    //
    self_t& operator *= ( T _scalar )
    {
        // ----------
        get(0,0) *= _scalar;
        get(0,1) *= _scalar;
        // ----------   
        get(1,0) *= _scalar;
        get(1,1) *= _scalar;
        // ----------

        return *this;
    }

    //
    self_t& operator /= ( T _scalar )
    {
        T inv_scalar = T(1) / _scalar;

        // ----------
        get(0,0) *= inv_scalar;
        get(0,1) *= inv_scalar;
        // ----------   
        get(1,0) *= inv_scalar;
        get(1,1) *= inv_scalar;
        // ----------

        return *this;
    }

    //
    void get_transpose( self_t* _pResult ) const
    {
        return _pResult->set( get(0,0), get(1,0),
                              get(0,1), get(1,1) );
    }

    //
    self_t& transpose()
    {
        T swap;
        swap    = get(0,1);
        get(0,1) = get(1,0);
        get(1,0) = swap;
        return *this;
    }

    //
    bool inverse ()
    {
        T det = get(0,0) * get(1,1) - get(1,0) * get(0,1);
        if ( mathop::abs(det) < mathop::epsilon<T>() )
        {
            return false;
        }

        T inv = T(1.0) / det;        
        T m00 = get(1,1) * inv;
        T m01 = get(0,1) * inv;
        T m10 = get(1,0) * inv;
        T m11 = get(0,0) * inv;

        get(0,0) = m00;
        get(0,1) = m01;
        get(1,0) = m10;
        get(1,1) = m11;

        return true;
    }

    //
    bool get_inverse( self_t* _pResult ) const
    {
        T det = get(0,0) * get(1,1) - get(1,0) * get(0,1);
        if ( mathop::abs(det) < mathop::epsilon<T>() )
        {
            return false;
        }

        T inv = T(1.0) / det;        
        _pResult->get(0,0) = get(1,1) * inv;
        _pResult->get(0,1) = get(0,1) * inv;
        _pResult->get(1,0) = get(1,0) * inv;
        _pResult->get(1,1) = get(0,0) * inv;

        return true;
    }

    //
    void get_abs( self_t* _pResult ) const
    {
        return _pResult->set( mathop::abs(get(0,0)), mathop::abs(get(1,0)),
                              mathop::abs(get(0,1)), mathop::abs(get(1,1)) );
    }

    //
    self_t& abs()
    {
        get(0,0) = mathop::abs(get(0,0));
        get(0,1) = mathop::abs(get(0,1));
        get(1,0) = mathop::abs(get(1,0));
        get(1,1) = mathop::abs(get(1,1));
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string;
        string = string + "m00: " + to_str<FLAGS>(this->get(0,0)) + "\n";
        string = string + "m01: " + to_str<FLAGS>(this->get(0,1)) + "\n";
        string = string + "m10: " + to_str<FLAGS>(this->get(1,0)) + "\n";
        string = string + "m11: " + to_str<FLAGS>(this->get(1,1)) + "\n";
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("Matrix2");
        return strID;
    }
    void serialize ( ISerializeNode* _pNode );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    T m[4];

}; // end class Matrix2

// #########################
} // end namespace ex 
// #########################

#include "Matrix2.hpp"

// #################################################################################
#endif // END MATRIX2_H_1250525832
// #################################################################################
