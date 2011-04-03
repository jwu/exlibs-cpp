// ======================================================================================
// File         : Rect.h
// Author       : Wu Jie 
// Last Change  : 10/31/2009 | 23:31:35 PM | Saturday,October
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef RECT_H_1257003101
#define RECT_H_1257003101
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// fwd-decls
///////////////////////////////////////////////////////////////////////////////

template < typename T > class Rect;
template < typename T > class AABRect;
template < typename T > class OBRect;

///////////////////////////////////////////////////////////////////////////////
// class Rect 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class Rect
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef Vector2<T> vector2_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    Rect ( T _left = T(0), T _top = T(0), T _right = T(1), T _bot = T(1) )
        : m_top (_top)
        , m_left (_left)
        , m_bot (_bot)
        , m_right (_right)
    {
    }

    //
    Rect ( const vector2_t& _topleft, const vector2_t& _botright )
        : m_top (_topleft.y())
        , m_left (_topleft.x())
        , m_bot (_botright.y())
        , m_right (_botright.x())
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    INLINE void set ( T _left, T _top, T _right, T _bot )
    {
        m_top = _top;
        m_left = _left;
        m_bot = _bot;
        m_right = _right;
    }

    INLINE void set ( const vector2_t& _topleft, const vector2_t& _botright )
    {
        m_top = _topleft.y();
        m_left = _topleft.x();
        m_bot = _botright.y();
        m_right = _botright.x();
    }

    //
    INLINE void setInScreen ( T _x1, T _y1, T _x2, T _y2 )
    {
        //
        if ( _x1 <= _x2 )
        {
            m_left = _x1;
            m_right = _x2;
        }
        else
        {
            m_left = _x2;
            m_right = _x1;
        }

        //
        if ( _y1 <= _y2 )
        {
            m_top = _y1;
            m_bot = _y2;
        }
        else
        {
            m_top = _y2;
            m_bot = _y1;
        }
    }

    //
    INLINE T width () const { return mathop::abs(m_left-m_right); }
    INLINE T height () const { return mathop::abs(m_top-m_bot); }

    //
    INLINE const T center_x() const { return (m_left + m_right)/T(2); }
    INLINE const T center_y() const { return (m_top + m_bot)/T(2); }

    //
    INLINE T& left() { return m_left; }
    INLINE const T& left() const { return m_left; }

    INLINE T& right() { return m_right; }
    INLINE const T& right() const { return m_right; }

    INLINE T& top() { return m_top; }
    INLINE const T& top() const { return m_top; }

    INLINE T& bot() { return m_bot; }
    INLINE const T& bot() const { return m_bot; }

    //
    INLINE const vector2_t top_left () const { return vector2_t( left(), top() ); }
    INLINE const vector2_t top_right () const { return vector2_t( right(), top() ); }
    INLINE const vector2_t bot_left () const { return vector2_t( left(), bot() ); }
    INLINE const vector2_t bot_right () const { return vector2_t( right(), bot() ); }
    INLINE const vector2_t center () const { return vector2_t( center_x(), center_y() ); }

    //
    INLINE T area () const { return width() * height(); }

    AABRect<T> toAABRect () const;

    //
    // NOTE: viewport space only
    INLINE bool contains ( const vector2_t& _pt ) const
    {
        return ( left() <= _pt.x() && 
                 right() >= _pt.x() &&
                 top() <= _pt.y() &&
                 bot() >= _pt.y() );
    }

    //
    // NOTE: viewport space only, not detect min, max for left,right,top,bot. 
    INLINE bool contains ( const Rect<T>& _rect ) const
    {
        return ( left() <= _rect.left() && 
                 right() >= _rect.right() &&
                 top() <= _rect.top() &&
                 bot() >= _rect.bot() );
    }

    //
    INLINE Rect<int> to_recti_t () const { return Rect<int> ( (int)m_left, (int)m_top, (int)m_right, (int)m_bot ); }
    INLINE Rect<float> to_rectf_t () const { return Rect<float> ( (float)m_left, (float)m_top, (float)m_right, (float)m_bot ); }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string;
        string = string + "top: " + ex::to_str<FLAGS>(m_top) + "\n";
        string = string + "left: " + ex::to_str<FLAGS>(m_left) + "\n";
        string = string + "bot: " + ex::to_str<FLAGS>(m_bot) + "\n";
        string = string + "right: " + ex::to_str<FLAGS>(m_right) + "\n";
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("Rect");
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    T m_top;
    T m_left;
    T m_bot;
    T m_right;

}; // end class Rect

///////////////////////////////////////////////////////////////////////////////
// class AABRect 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class AABRect
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef Vector2<T> vector2_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    AABRect ( T _center_x = T(0), T _center_y = T(0), T _width = T(1), T _height = T(1) )
        : m_lowerBound ( _center_x - _width/T(2), _center_y - _height/T(2) )
        , m_upperBound ( _center_x + _width/T(2), _center_y + _height/T(2) )
    {
    }

    AABRect ( const vector2_t& _lowerBound, const vector2_t& _upperBound )
        : m_lowerBound (_lowerBound)
        , m_upperBound (_upperBound)
    {
        ex_assert ( isValid(), "the value in aab_rect is invalid. pls check it!" );
    }

    AABRect ( const Rect<T>& _rect )
    {
        set ( _rect.center_x(), _rect.center_y(), _rect.width(), _rect.height() );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    INLINE void set ( T _center_x, T _center_y, T _width, T _height )
    {
        m_lowerBound = vector2_t( _center_x - _width/T(2), _center_y - _height/T(2) );
        m_upperBound = vector2_t( _center_x + _width/T(2), _center_y + _height/T(2) );
    }

    //
    INLINE void set ( const vector2_t& _lowerBound, const vector2_t& _upperBound )
    {
        m_lowerBound = _lowerBound;
        m_upperBound = _upperBound;
    }

    //
    INLINE void set ( const Rect<T>& _rect )
    {
        set ( _rect.center_x(), _rect.center_y(), _rect.width(), _rect.height() );
    }

    INLINE bool isValid() const
    {
        vector2_t d = m_upperBound - m_lowerBound;
        bool valid = d.x() >= 0.0f && d.y() >= 0.0f;
        return valid;
    }

    //
    INLINE const T center_x() const { return (m_upperBound.x()+m_lowerBound.x())/T(2); }
    INLINE const T center_y() const { return (m_upperBound.y()+m_lowerBound.y())/T(2); }

    INLINE const T width () const { return m_upperBound.x() - m_lowerBound.x(); }
    INLINE const T height () const { return m_upperBound.y() - m_lowerBound.y(); }

    //
    INLINE const T left() const { return m_lowerBound.x(); }
    INLINE const T right() const { return m_upperBound.x(); }
    INLINE const T top() const { return m_upperBound.y(); }
    INLINE const T bot() const { return m_lowerBound.y(); }

    //
    INLINE const vector2_t top_left () const { return vector2_t( left(), top() ); }
    INLINE const vector2_t top_right () const { return vector2_t( right(), top() ); }
    INLINE const vector2_t bot_left () const { return vector2_t( left(), bot() ); }
    INLINE const vector2_t bot_right () const { return vector2_t( right(), bot() ); }
    INLINE const vector2_t center () const { return vector2_t( center_x(), center_y() ); }

    //
    INLINE vector2_t& lower_bound () { return m_lowerBound; }
    INLINE const vector2_t& lower_bound () const { return m_lowerBound; }
    INLINE vector2_t& upper_bound () { return m_upperBound; }
    INLINE const vector2_t& upper_bound () const { return m_upperBound; }

    //
    INLINE T area () const { return width() * height(); }

    //
    INLINE Rect<T> toRect () const { return Rect<T>( left(), top(), right(), bot() ); }

    //
    // NOTE: world space only, not detect min, max for left,right,top,bot. 
    INLINE bool contains ( const AABRect<T>& _rect ) const
    {
        return ( left() <= _rect.left() && 
                 right() >= _rect.right() &&
                 top() >= _rect.top() &&
                 bot() <= _rect.bot() );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string = ex::to_str<FLAGS>(m_lowerBound) + ";" +
                          ex::to_str<FLAGS>(m_upperBound)
                          ;
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID = string_id_t( string_t("AABRect<") + TypeTraits<T>::type_name().c_str() + ">" );
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    vector2_t m_lowerBound;
    vector2_t m_upperBound;

}; // end class AABRect

///////////////////////////////////////////////////////////////////////////////
// class OBRect 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class OBRect
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef Vector2<T> vector2_t;
    typedef Angle<T> angle_t;
    typedef Matrix2<T> matrix2_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    OBRect ( T _center_x = T(0), T _center_y = T(0), T _width = T(1), T _height = T(1), angle_t _ang = angle_t(0) )
    {
        ex_static_assert( TypeTraits<T>::isFloat, "T must be float/double type" );
        set( _center_x, _center_y, _width, _height, _ang );
    }

    OBRect ( const vector2_t& _center, const vector2_t& _extents, const matrix2_t _rot )
    {
        ex_static_assert( TypeTraits<T>::isFloat, "T must be float/double type" );
        set ( _center, _extents, _rot );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    INLINE void set ( T _center_x, T _center_y, T _width, T _height, angle_t _ang )
    {
        float cos_a = mathop::cos(_ang);
        float sin_a = mathop::sin(_ang);
        set ( vector2_t( _center_x, _center_y ),
              vector2_t( _width/T(2), _height/T(2) ), 
              matrix2_t ( cos_a, sin_a, -sin_a, cos_a ) );
    }

    //
    INLINE void set ( const vector2_t& _center, const vector2_t& _extents, const matrix2_t _rot )
    {
        m_center = _center;
        m_extents = _extents;
        m_rot = _rot;
    }

    //
    INLINE const T center_x() const { return m_center.x(); }
    INLINE const T center_y() const { return m_center.y(); }

    INLINE const T width () const { return T(2) * m_extents.x(); }
    INLINE const T height () const { return T(2) * m_extents.y(); }

    //
    INLINE const T left() const { return top_left().x(); }
    INLINE const T right() const { return bot_right().x(); }
    INLINE const T top() const { return top_left().y(); }
    INLINE const T bot() const { return bot_right().y(); }

    //
    INLINE const vector2_t top_left () const { return vector2_t( -m_extents.x(), m_extents.y() ) * m_rot + m_center; }
    INLINE const vector2_t top_right () const { return vector2_t( m_extents.x(), m_extents.y() ) * m_rot + m_center; }
    INLINE const vector2_t bot_left () const { return vector2_t( -m_extents.x(), -m_extents.y() ) * m_rot + m_center; }
    INLINE const vector2_t bot_right () const { return vector2_t( m_extents.x(), -m_extents.y() ) * m_rot + m_center; }

    //
    INLINE const matrix2_t& rot () const { return m_rot; }
    INLINE const vector2_t& center () const { return m_center; }
    INLINE const vector2_t& extents () const { return m_extents; }

    //
    INLINE T area () const { return width() * height(); }

    //
    INLINE AABRect<T> toAABRect () const 
    { 
        matrix2_t absRot;
        m_rot.get_abs(&absRot);
        vector2_t h = m_extents * absRot;
        return AABRect<T>( -h + m_center, h + m_center ); 
    }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string;
        string = string + "Rot: " + ex::to_str<FLAGS>(m_rot) + "\n";
        string = string + "Center: " + ex::to_str<FLAGS>(m_center) + "\n";
        string = string + "Extents: " + ex::to_str<FLAGS>(m_extents) + "\n";
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("OBRect");
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    matrix2_t   m_rot;
    vector2_t   m_center;
    vector2_t   m_extents;

}; // end class OBRect

///////////////////////////////////////////////////////////////////////////////
// late-inline
///////////////////////////////////////////////////////////////////////////////

template < typename T >
INLINE AABRect<T> Rect<T>::toAABRect () const { return AABRect<T>( center_x(), center_y(), width(), height() ); }

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END RECT_H_1257003101
// #################################################################################


