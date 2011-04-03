// ======================================================================================
// File         : Rotator.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:18:35 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ROTATOR_H_1250525921
#define ROTATOR_H_1250525921
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Rotator 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class Rotator
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef Rotator<T> self_t;

    ///////////////////////////////////////////////////////////////////////////////
    // static member data 
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
    Rotator()
    {
        // T_Zero(m_data);
    }

    //
    Rotator( const Rotator& _rot )
    {
        this->set( _rot );
    }

    //
    Rotator( T _pitch, T _yaw, T _roll )
    {
        this->set( _pitch, _yaw, _roll );
    }

    // ========================================================
    // set functions
    // ========================================================

    //
    void set( const Rotator& _rot )
    {
        mathop::set( m_data, _rot.m_data );
    }

    //
    void set( T _pitch, T _yaw, T _roll )
    {
        T_Set3( m_data, _pitch, _yaw, _roll );
    }

    // pitch - looking up & down
    INLINE T& pitch() { return intri::getref( m_data, 0 ); }
    INLINE const T pitch() const { return intri::get( m_data, 0 ); }

    // yaw - looking left & right
    INLINE T& yaw() { return intri::getref( m_data, 1 ); }
    INLINE const T yaw() const { return intri::get( m_data, 1 ); }

    // roll - circle by look-at axis
    INLINE T& roll() { return intri::getref( m_data, 2 ); }
    INLINE const T roll() const { return intri::get( m_data, 2 ); }

    // ========================================================
    // operator functions
    // ========================================================

    //
    self_t& operator = ( const self_t& _rot )
    {
        this->set(_rot);
        return *this;
    }

    //
    self_t operator - () const
    {
        ex_assert(!TypeTraits<T>::isUnsignedInt, "Don't use negative operator for unsigned type\n");

        self_t rot(*this);
        mathop::negative( rot.m_data, rot.m_data );
        return rot;
    }

    //
    void negative()
    {
        mathop::negative( m_data, m_data );
    }

    //
    self_t& operator += ( const self_t& _rot )
    {
        mathop::add( m_data, m_data, _rot.m_data );
        return *this;
    }

    //
    self_t& operator -= ( const self_t& _rot )
    {
        mathop::sub( m_data, m_data, _rot.m_data );
        return *this;
    }

    //
    self_t operator *= ( const self_t& _rot )
    {
        mathop::mul( m_data, m_data, _rot.m_data );
        return *this;
    }

    //
    self_t operator *= ( T _scalar ) 
    {
        mathop::mul_scalar( m_data, m_data, _scalar );
        return *this;
    }

    //
    self_t operator /= ( const self_t& _rot )
    {
        mathop::div( m_data, m_data, _rot.m_data );
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
        // TODO: inverse
        return true;
    }

    //
    void get_inverse( self_t* _pResult ) const
    {
        // TODO: inverse
        return ;
    }

    //
    bool is_normalized() const
    {
        // TODO: nomalized
        return true;
    }

    //
    void get_normalize( self_t* _pResult ) const
    {
        // TODO: nomalized
        return ;
    }

    //
    result_t normalize()
    {
        // TODO: nomalized
        return EResult::ok;
    }

protected:

    T m_data[3];

}; // end class Rotator

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// ========================================================
// zero
// ========================================================

template < typename T > 
const Rotator<T> Rotator<T>::zero ( T(0), T(0), T(0) );

// ========================================================
// identity
// ========================================================

template < typename T > 
const Rotator<T> Rotator<T>::identity ( T(0), T(0), T(0) );

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END ROTATOR_H_1250525921
// #################################################################################
