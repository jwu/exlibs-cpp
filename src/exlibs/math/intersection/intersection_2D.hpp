// ======================================================================================
// File         : intersection_2D.hpp
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 17:13:34 PM | Sunday,August
// Description  : 
// ======================================================================================

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace intersect { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T > 
INLINE bool rect_rect ( T _min_x1, T _min_y1, T _max_x1, T _max_y1, 
                                   T _min_x2, T _min_y2, T _max_x2, T _max_y2 )
{
    return ( (_min_x1 <= _max_x2) && 
             (_max_x1 >= _min_x2) && 
             (_min_y1 <= _max_y2) && 
             (_max_y1 >= _min_y2) );
}

// ------------------------------------------------------------------ 
// Desc: rect rect 
// NOTE: this is for viewport space, the intersect not detect min,max for rect
// ------------------------------------------------------------------ 

template < typename T > 
INLINE bool rect_rect ( const Rect<T>& _rect1, const Rect<T>& _rect2 )
{
    return rect_rect( _rect1.left(), _rect1.top(), _rect1.right(), _rect1.bot(),
                                 _rect2.left(), _rect2.top(), _rect2.right(), _rect2.bot() );
}

// ------------------------------------------------------------------ 
// Desc: 
// NOTE: this is for world space, the intersect not detect min,max for rect
// ------------------------------------------------------------------ 

template < typename T > 
INLINE bool rect_rect ( const AABRect<T>& _rect1, const AABRect<T>& _rect2 )
{
    return rect_rect( _rect1.left(), _rect1.bot(), _rect1.right(), _rect1.top(),
                                 _rect2.left(), _rect2.bot(), _rect2.right(), _rect2.top() );
}

// ######################### 
} // end namespace intersect 
// ######################### 

// ######################### 
} // end namespace ex 
// ######################### 


