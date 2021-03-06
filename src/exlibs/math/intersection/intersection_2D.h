// ======================================================================================
// File         : intersection_2D.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 17:13:21 PM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef INTERSECTION_2D_H_1281863603
#define INTERSECTION_2D_H_1281863603
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace intersect { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: intersect rect rect 
// ------------------------------------------------------------------ 

// ======================================================== 
// no inter point
// ======================================================== 

template < typename T > bool rect_rect ( T _min_x1, T _min_y1, T _max_x1, T _max_y1, 
                                                    T _min_x2, T _min_y2, T _max_x2, T _max_y2 );
template < typename T > bool rect_rect ( const Rect<T>& _rect1, const Rect<T>& _rect2 );
template < typename T > bool rect_rect ( const AABRect<T>& _rect1, const AABRect<T>& _rect2 );

// ======================================================== 
// inter point 
// ======================================================== 

template < typename T > bool rect_rect ( T _min_x1, T _min_y1, T _max_x1, T _max_y1, 
                                                  T _min_x2, T _min_y2, T _max_x2, T _max_y2, 
                                                  List<Vector2<T> >* _pResult );
template < typename T > bool rect_rect ( const Rect<T>& _rect1, const Rect<T>& _rect2, List<Vector2<T> >* _pResult );
template < typename T > bool rect_rect ( const AABRect<T>& _rect1, const AABRect<T>& _rect2, List<Vector2<T> >* _pResult );

// ######################### 
} // end namespace intersect 
// ######################### 

// ######################### 
} // end namespace ex 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// impl
///////////////////////////////////////////////////////////////////////////////

#include "Intersection_2D.hpp"

// #################################################################################
#endif // END INTERSECTION_2D_H_1281863603
// #################################################################################
