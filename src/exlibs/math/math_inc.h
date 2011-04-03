// ======================================================================================
// File         : math_inc.h
// Author       : Wu Jie 
// Last Change  : 03/23/2010 | 17:48:26 PM | Tuesday,March
// Description  : Base-Libaray Math
// ======================================================================================

// #################################################################################
#ifndef MATH_INC_H_1269337709
#define MATH_INC_H_1269337709
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
//  config macros
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
//  EX_MATRIX_ROW_MAJOR (each row of the matrix is stored in a single constant register)
//  the row major matrix can multiply by row easily, as r1 * vec
//
//   layer out for register pack           layer out for geometry meanning
//
//                                               I  J  K  T
//                                               -- -- -- --
//      r1 | 11 12 13 14 |                       11 12 13 14  
//      r2 | 21 22 23 24 |                       21 22 23 24  
//      r3 | 31 32 33 34 |                       31 32 33 34  
//      r4 | 41 42 43 44 |                       41 42 43 44  
//                                               -- -- -- --
//      
//   multiply vector:
//      mat2 * mat1 * vec 
//
//  EX_MATRIX_COLUMN_MAJOR (each row of the matrix is stored in a single constant register)
//  the column major matrix can multiply by column easily, as vec * r1
//
//   layer out for register pack           layer out for geometry meanning
//
//      r1 r2 r3 r4
//      -- -- -- --                            
//      11 21 31 41                            I | 11 21 31 41 |
//      12 22 32 42                            J | 12 22 32 42 |
//      13 23 33 43                            K | 13 23 33 43 |
//      14 24 34 44                            T | 14 24 34 44 |
//      -- -- -- --
//
//   multiply vector:
//      vec * mat1 * mat2
//
//  Warning:
//      Don't modify this macro, currently the engine just support column major calculate
// ------------------------------------------------------------------

#define EX_MATRIX_COLUMN_MAJOR 1
#define EX_MATRIX_ROW_MAJOR    2

#define EX_MATRIX_ORDER EX_MATRIX_COLUMN_MAJOR

// ------------------------------------------------------------------
// Desc: 
// EX_MULTIPLY_LEFT_TO_RIGHT
//     vRot = vec * mat1 * mat2 * mat3 * ...
//     vRot = vec * quad1 * quad2 * quad3 * ...
//
//     vector express:
//         vec = [ v1, v2, v3, v4, ... ]
//
// EX_MULTIPLY_RIGHT_TO_LEFT
//     vRot = ... * mat3 * mat2 * mat1 * vec
//     vRot = ... * quad3 * quad2 * quad1 * vec
//
//     vector express:
//         vec = [ v1, 
//                 v2, 
//                 v3, 
//                 v4,
//                 ... ]
// ------------------------------------------------------------------

#define EX_MULTIPLY_LEFT_TO_RIGHT 1
#define EX_MULTIPLY_RIGHT_TO_LEFT 2

#if ( EX_MATRIX_ORDER == EX_MATRIX_COLUMN_MAJOR )
    #define EX_MULTIPLY_ORDER EX_MULTIPLY_LEFT_TO_RIGHT
#elif ( EX_MATRIX_ORDER == EX_MATRIX_ROW_MAJOR ) 
    #define EX_MULTIPLY_ORDER EX_MULTIPLY_RIGHT_TO_LEFT
#endif

// ------------------------------------------------------------------
// Desc: 
// EX_COORDINATE_LEFT_HANDED
//    
//          Y 
//           ^   Z
//           | / 
//           |/
//            -----> X      
//
// EX_COORDINATE_RIGHT_HANDED
//
//          Y 
//           ^   
//           |  
//           |
//          / -----> X      
//         /
//       Z
//
// ------------------------------------------------------------------

#define EX_COORDINATE_LEFT_HANDED  1
#define EX_COORDINATE_RIGHT_HANDED 2

#define EX_COORDINATE_SYSTEM EX_COORDINATE_LEFT_HANDED

// ------------------------------------------------------------------
// Desc: 
//  EX_ANGLE_RADIANS
//      [ 0.0 - 2pi ]
//
//  EX_ANGLE_DEGREE
//      [ 0.0 - 360.0 ]
//
//  NOTE:
//      cause most c/cpp math function like sinf,cosf... use radians as input value. 
//      if we use the degree, then we need one more calculation to transform the input.
// ------------------------------------------------------------------

#define EX_ANGLE_RADIANS 1
#define EX_ANGLE_DEGREE  2

#define EX_ANGLE_UNIT EX_ANGLE_RADIANS

// ------------------------------------------------------------------
// Desc: 
//  EX_ROTATE_CW
//      Angles are measured clockwise when looking along the rotation axis toward the "origin".
//      As know as Left-Hand Rotate ( use thumb as axis, other finger as rotation )
//
//  EX_ROTATE_CCW
//      Angles are measured counter clockwise when looking along the rotation axis toward the "origin".
//      As know as Right-Hand Rotate ( use thumb as axis, other finger as rotation )
//
// ------------------------------------------------------------------

#define EX_ROTATE_CW   1
#define EX_ROTATE_CCW  2

#define EX_ROTATE_METHOD EX_ROTATE_CW

// ------------------------------------------------------------------
//            Operation       |  Result
//   -------------------------+------------
//             n / +-infinity |     0
//              +-nonzero / 0 | +-infinity
//    +-infinity * +-infinity | +-infinity
//        infinity + infinity |   infinity
//        infinity - infinity |    NaN
//    +-infinity / +-infinity |    NaN
//             +-infinity * 0 |    NaN
//                  +-0 / +-0 |    NaN
// ------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////
//  value defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: values about PI 
// ------------------------------------------------------------------

#define EX_PI               (3.1415926535897932)
#define EX_INV_PI			(0.31830988618)
#define EX_TWO_PI           (6.2831853071795864)
#define EX_HALF_PI			(1.57079632679)

// ------------------------------------------------------------------
// Desc: degree/radius convertor 
// ------------------------------------------------------------------

#define EX_DEG_TO_RAD       (0.017453292519943296) /* pi/180.0 */
#define EX_RAD_TO_DEG       (57.29577951308232158) /* 180.0/pi */

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// type defines 
///////////////////////////////////////////////////////////////////////////////

// algebra
typedef Vector2<float>     vec2f_t;
typedef Vector3<float>     vec3f_t;
typedef Vector4<float>     vec4f_t;
typedef Matrix2<float>     mat2f_t;
typedef Matrix3<float>     mat3f_t;
typedef Matrix4<float>     mat4f_t;
typedef Quaternion<float>  quatf_t;
typedef Angle<float>       angf_t;
typedef Rotator<float>     rotf_t;

typedef Vector2<int>       vec2i_t;
typedef Vector3<int>       vec3i_t;
typedef Vector4<int>       vec4i_t;

// colors
typedef Color3u            color3u_t;
typedef Color4u            color4u_t;
typedef Color3f            color3f_t;
typedef Color4f            color4f_t;

// shapes
typedef Line2D<float>  line2f_t;
typedef Rect<float>    rectf_t;
typedef AABRect<float> aab_rectf_t;
typedef OBRect<float> ob_rectf_t;

typedef Line2D<int>    line2i_t;
typedef Rect<int>      recti_t;
typedef AABRect<int>   aab_recti_t;

// #########################
} // end namespace ex 
// #########################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

// api
#include "math_op.h"
#include "random.h"
#include "curve.h"

// base math template
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Vector.hpp"
#include "Quaternion.h"
#include "Angle.h"
#include "Rotator.h" // deps on angle
#include "Matrix2.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Color.h"

// base graphics structure
#include "Line.h"
#include "Rect.h"
#include "Plane.h"

// base math algorithm after typedefs
#include "matrix_op.h"
#include "intersection/intersection_2D.h"

///////////////////////////////////////////////////////////////////////////////
// late-inlines
///////////////////////////////////////////////////////////////////////////////

#include "operation.hpp"
#include "conversion.hpp"

// #################################################################################
#endif // END MATH_INC_H_1269337709
// #################################################################################

