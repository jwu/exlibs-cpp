// ======================================================================================
// File         : conversion.hpp
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 17:20:19 PM | Sunday,August
// Description  : 
// ======================================================================================

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// Late-Inline segment
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Quaternion late-inline functons
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename T >
INLINE void Quaternion<T>::toMatrix( Matrix3<T>* _pResult ) const
{
    //
    T Tx  = T(2)*this->x();
    T Ty  = T(2)*this->y();
    T Tz  = T(2)*this->z();
    T Twx = Tx*this->w();
    T Twy = Ty*this->w();
    T Twz = Tz*this->w();
    T Txx = Tx*this->x();
    T Txy = Ty*this->x();
    T Txz = Tz*this->x();
    T Tyy = Ty*this->y();
    T Tyz = Tz*this->y();
    T Tzz = Tz*this->z();

    //
    _pResult->set( T(1) - ( Tyy + Tzz ),  Txy + Twz,		        Txz - Twy, 
                   Txy - Twz,			  T(1) - ( Txx + Tzz ),     Tyz + Twx,
                   Txz + Twy,			  Tyz - Twx,                T(1) - ( Txx + Tyy ) );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename T >
INLINE void Quaternion<T>::toMatrix( Matrix4<T>* _pResult ) const
{
    //
    T Tx  = T(2)*this->x();
    T Ty  = T(2)*this->y();
    T Tz  = T(2)*this->z();
    T Twx = Tx*this->w();
    T Twy = Ty*this->w();
    T Twz = Tz*this->w();
    T Txx = Tx*this->x();
    T Txy = Ty*this->x();
    T Txz = Tz*this->x();
    T Tyy = Ty*this->y();
    T Tyz = Tz*this->y();
    T Tzz = Tz*this->z();

    //
    _pResult->set( T(1) - ( Tyy + Tzz ),  Txy + Twz,		      Txz - Twy,            T(0), 
                   Txy - Twz,			  T(1) - ( Txx + Tzz ),   Tyz + Twx,            T(0),
                   Txz + Twy,			  Tyz - Twx,              T(1) - ( Txx + Tyy ), T(0),
                   T(0),                  T(0),                   T(0),                 T(1) );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename T >
INLINE void Quaternion<T>::xAxis( Vector3<T>* _pResult ) const
{
    //
    T Tx  = T(2)*this->x();
    T Ty  = T(2)*this->y();
    T Tz  = T(2)*this->z();
    T Twx = Tx*this->w();
    T Twy = Ty*this->w();
    T Twz = Tz*this->w();
    T Txx = Tx*this->x();
    T Txy = Ty*this->x();
    T Txz = Tz*this->x();
    T Tyy = Ty*this->y();
    T Tyz = Tz*this->y();
    T Tzz = Tz*this->z();

    //
    _pResult->set( T(1) - ( Tyy + Tzz ), Txy + Twz,	Txz - Twy );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename T >
INLINE void Quaternion<T>::yAxis( Vector3<T>* _pResult ) const
{
    //
    T Tx  = T(2)*this->x();
    T Ty  = T(2)*this->y();
    T Tz  = T(2)*this->z();
    T Twx = Tx*this->w();
    T Twy = Ty*this->w();
    T Twz = Tz*this->w();
    T Txx = Tx*this->x();
    T Txy = Ty*this->x();
    T Txz = Tz*this->x();
    T Tyy = Ty*this->y();
    T Tyz = Tz*this->y();
    T Tzz = Tz*this->z();

    //
    _pResult->set( Txy - Twz, T(1) - ( Txx + Tzz ), Tyz + Twx );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename T >
INLINE void Quaternion<T>::zAxis( Vector3<T>* _pResult ) const
{
    //
    T Tx  = T(2)*this->x();
    T Ty  = T(2)*this->y();
    T Tz  = T(2)*this->z();
    T Twx = Tx*this->w();
    T Twy = Ty*this->w();
    T Twz = Tz*this->w();
    T Txx = Tx*this->x();
    T Txy = Ty*this->x();
    T Txz = Tz*this->x();
    T Tyy = Ty*this->y();
    T Tyz = Tz*this->y();
    T Tzz = Tz*this->z();

    //
    _pResult->set( Txz + Twy, Tyz - Twx, T(1) - ( Txx + Tyy ) );
}

// #########################
} // end namespace ex 
// #########################

