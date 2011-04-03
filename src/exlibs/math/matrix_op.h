// ======================================================================================
// File         : matrix_op.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 17:14:46 PM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MATRIX_OP_H_1281863689
#define MATRIX_OP_H_1281863689
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INLINE void make_mat4f ( mat4f_t* _pResult, const mat3f_t& _mat2D )
{
    _pResult->set ( _mat2D(0,0), _mat2D(0,1), 0.0f, 0.0f,
                    _mat2D(1,0), _mat2D(1,1), 0.0f, 0.0f,
                    0.0f,        0.0f,        1.0f, 0.0f,
                    _mat2D(2,0), _mat2D(2,1), 0.0f, 1.0f );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void view_mat4f ( mat4f_t* _pResult, const mat4f_t& _matWorldCamera )
{
    // Get rotation & translation matrix 
    //  [ Rx  Ry  Rz  ]
    //  [ Ux  Uy  Uz  ]
    //  [ Dx  Dy  Dz  ]
    mat3f_t rot   = _matWorldCamera.rotation();
    vec3f_t trans = _matWorldCamera.translation(); 

    // get revert transport.
    rot.transpose();
    trans = -(trans*rot);

    // View matrix is:
    //
    //  [ Rx  Ux  Dx  0   ]
    //  [ Ry  Uy  Dy  0   ]
    //  [ Rz  Uz  Dz  0   ]
    //  [ TR  TU  TD  1   ]
    //
    // Where T = -(Transposed(Rot) * Pos) = -( Pos * Rot )
    // This is most efficiently done using 3x3 Matrices
    _pResult->set( rot, trans );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void view_mat4f ( mat4f_t* _pResult, const vec3f_t& _position, const quatf_t& _orientation )
{
    // get rotation matrix
    mat3f_t rot;
    _orientation.toMatrix( &rot );

    // Make the translation relative to new axes
    rot.transpose();
    vec3f_t trans = -(_position*rot);

    // Make final matrix
    _pResult->set( rot, trans );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void view_mat4f_LH ( mat4f_t* _pResult, const vec3f_t& _position, const vec3f_t& _target, const vec3f_t& _up )
{
    vec3f_t xAxis, yAxis, zAxis;
    (_target-_position).get_normalize(&zAxis);
    (_up.cross(zAxis)).get_normalize(&xAxis);
    yAxis = zAxis.cross(xAxis);

    _pResult->set(  xAxis.x(),               yAxis.x(),               zAxis.x(),              0.0f,
                    xAxis.y(),               yAxis.y(),               zAxis.y(),              0.0f,
                    xAxis.z(),               yAxis.z(),               zAxis.z(),              0.0f,
                   -(xAxis.dot(_position)), -(yAxis.dot(_position)), -(zAxis.dot(_position)), 1.0f );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void view_mat4f_RH ( mat4f_t* _pResult, const vec3f_t& _position, const vec3f_t& _target, const vec3f_t& _up )
{
    vec3f_t xAxis, yAxis, zAxis;
    (_position-_target).get_normalize(&zAxis);
    (_up.cross(zAxis)).get_normalize(&xAxis);
    yAxis = zAxis.cross(xAxis);

    _pResult->set(  xAxis.x(),               yAxis.x(),               zAxis.x(),              0.0f,
                    xAxis.y(),               yAxis.y(),               zAxis.y(),              0.0f,
                    xAxis.z(),               yAxis.z(),               zAxis.z(),              0.0f,
                   -(xAxis.dot(_position)), -(yAxis.dot(_position)), -(zAxis.dot(_position)), 1.0f );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void view_mat4f ( mat4f_t* _pResult, const vec3f_t& _position, const vec3f_t& _target, const vec3f_t& _up )
{
#if ( EX_COORDINATE_SYSTEM == EX_COORDINATE_LEFT_HANDED )
    view_mat4f_LH( _pResult, _position, _target, _up );
#elif ( EX_COORDINATE_SYSTEM == EX_COORDINATE_RIGHT_HANDED )
    view_mat4f_RH( _pResult, _position, _target, _up );
#endif 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void perspective_fov_mat4f_LH ( mat4f_t* _pResult, float _fov_x, float _fov_y, float _nearDistance, float _farDistance )
{
    const float scale_x = 1.0f / mathop::tan( _fov_x * 0.5f );
    const float scale_y = 1.0f / mathop::tan( _fov_y * 0.5f );

    _pResult->set( scale_x,  0.0f,       0.0f,                                                    0.0f,
                   0.0f,     scale_y,    0.0f,                                                    0.0f,
                   0.0f,     0.0f,       _farDistance/(_farDistance-_nearDistance),               1.0f, 
                   0.0f,     0.0f,      -_nearDistance*_farDistance/(_farDistance-_nearDistance), 0.0f );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void perspective_fov_mat4f_RH ( mat4f_t* _pResult, float _fov_x, float _fov_y, float _nearDistance, float _farDistance )
{
    const float scale_x = 1.0f / mathop::tan( _fov_x * 0.5f );
    const float scale_y = 1.0f / mathop::tan( _fov_y * 0.5f );

    _pResult->set( scale_x,  0.0f,       0.0f,                                                    0.0f,
                   0.0f,     scale_y,    0.0f,                                                    0.0f,
                   0.0f,     0.0f,       _farDistance/(_nearDistance-_farDistance),              -1.0f,
                   0.0f,     0.0f,       _nearDistance*_farDistance/(_nearDistance-_farDistance), 0.0f );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void perspective_fov_mat4f ( mat4f_t* _pResult, float _fov_x, float _fov_y, float _nearDistance, float _farDistance )
{
#if ( EX_COORDINATE_SYSTEM == EX_COORDINATE_LEFT_HANDED )
    perspective_fov_mat4f_LH( _pResult, _fov_x, _fov_y, _nearDistance, _farDistance );
#elif ( EX_COORDINATE_SYSTEM == EX_COORDINATE_RIGHT_HANDED )
    perspective_fov_mat4f_RH( _pResult, _fov_x, _fov_y, _nearDistance, _farDistance );
#endif 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void perspective_fov_aspect_mat4f_LH ( mat4f_t* _pResult, float _camera_fov_x, float _aspectRatio, float _nearDistance, float _farDistance )
{
    const float scale_x = mathop::tan( _camera_fov_x * 0.5f );
    const float scale_y = scale_x / _aspectRatio;

    _pResult->set( scale_x,  0.0f,       0.0f,                                                    0.0f,
                   0.0f,     scale_y,    0.0f,                                                    0.0f,
                   0.0f,     0.0f,       _farDistance/(_farDistance-_nearDistance),               1.0f, 
                   0.0f,     0.0f,      -_nearDistance*_farDistance/(_farDistance-_nearDistance), 0.0f );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void perspective_fov_aspect_mat4f_RH ( mat4f_t* _pResult, float _camera_fov_x, float _aspectRatio, float _nearDistance, float _farDistance )
{
    const float scale_x = mathop::tan( _camera_fov_x * 0.5f );
    const float scale_y = scale_x / _aspectRatio;

    _pResult->set( scale_x,  0.0f,       0.0f,                                                    0.0f,
                   0.0f,     scale_y,    0.0f,                                                    0.0f,
                   0.0f,     0.0f,       _farDistance/(_nearDistance-_farDistance),              -1.0f,
                   0.0f,     0.0f,       _nearDistance*_farDistance/(_nearDistance-_farDistance), 0.0f );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void perspective_fov_aspect_mat4f ( mat4f_t* _pResult, float _camera_fov_x, float _aspectRatio, float _nearDistance, float _farDistance )
{
#if ( EX_COORDINATE_SYSTEM == EX_COORDINATE_LEFT_HANDED )
    perspective_fov_aspect_mat4f_LH( _pResult, _camera_fov_x, _aspectRatio, _nearDistance, _farDistance );
#elif ( EX_COORDINATE_SYSTEM == EX_COORDINATE_RIGHT_HANDED )
    perspective_fov_aspect_mat4f_RH( _pResult, _camera_fov_x, _aspectRatio, _nearDistance, _farDistance );
#endif 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void ortho_mat4f_LH ( mat4f_t* _pResult, float _viewWidth, float _viewHeight, float _nearDistance, float _farDistance )
{
    _pResult->set( 2.0f/_viewWidth, 0.0f,              0.0f,                                       0.0f,
                   0.0f,            2.0f/_viewHeight,  0.0f,                                       0.0f,
                   0.0f,            0.0f,              1.0f/(_farDistance-_nearDistance),          0.0f,
                   0.0f,            0.0f,             -_nearDistance/(_farDistance-_nearDistance), 1.0f );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void ortho_mat4f_RH ( mat4f_t* _pResult, float _viewWidth, float _viewHeight, float _nearDistance, float _farDistance )
{
    _pResult->set( 2.0f/_viewWidth, 0.0f,              0.0f,                                       0.0f,
                   0.0f,            2.0f/_viewHeight,  0.0f,                                       0.0f,
                   0.0f,            0.0f,              1.0f/(_nearDistance-_farDistance),          0.0f,
                   0.0f,            0.0f,              _nearDistance/(_nearDistance-_farDistance), 1.0f );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

INLINE void ortho_mat4f ( mat4f_t* _pResult, float _viewWidth, float _viewHeight, float _nearDistance, float _farDistance )
{
#if ( EX_COORDINATE_SYSTEM == EX_COORDINATE_LEFT_HANDED )
    ortho_mat4f_LH( _pResult, _viewWidth, _viewHeight, _nearDistance, _farDistance );
#elif ( EX_COORDINATE_SYSTEM == EX_COORDINATE_RIGHT_HANDED )
    ortho_mat4f_RH( _pResult, _viewWidth, _viewHeight, _nearDistance, _farDistance );
#endif 
}

// ------------------------------------------------------------------
// Desc: 
// CW rotate
// ------------------------------------------------------------------

INLINE void rot_x_axis_mat4f ( mat3f_t* _pResult, float _radians )
{
    _pResult->set( 1.0f,  0.0f,              0.0f, 
                   0.0f,  mathop::cos(_radians), mathop::sin(_radians),
                   0.0f, -mathop::sin(_radians), mathop::cos(_radians) );
}

// ------------------------------------------------------------------
// Desc: 
// CW rotate
// ------------------------------------------------------------------

INLINE void rot_y_axis_mat4f ( mat3f_t* _pResult, float _radians )
{
    _pResult->set( mathop::cos(_radians), 0.0f, -mathop::sin(_radians),
                   0.0f,                  1.0f,  0.0f,
                   mathop::sin(_radians), 0.0f,  mathop::cos(_radians) );
}

// ------------------------------------------------------------------
// Desc: 
// CW rotate
// ------------------------------------------------------------------

INLINE void rot_z_axis_mat4f ( mat3f_t* _pResult, float _radians )
{
    _pResult->set(  mathop::cos(_radians), mathop::sin(_radians), 0.0f, 
                   -mathop::sin(_radians), mathop::cos(_radians), 0.0f,
                    0.0f,              0.0f,              1.0f );
}

// ------------------------------------------------------------------
// Desc: 
// CW rotate
// ------------------------------------------------------------------

INLINE void rot_axis_mat4f ( mat3f_t* _pResult, const vec3f_t& _axis, float _radians )
{
    // Computers Graphics, 2nd Edition, 5.15, p 227
    float halfRadians = _radians * 0.5f;
    float sn = mathop::sin(halfRadians);
    float cs = mathop::cos(halfRadians);
    float x = _axis.x() * sn;
    float y = _axis.y() * sn;
    float z = _axis.z() * sn;

    float xs = 2.0f * x,
          ys = 2.0f * y,
          zs = 2.0f * z;

    float wx = cs * xs,
          wy = cs * ys,
          wz = cs * zs,

          xx = x * xs,
          xy = x * ys,
          xz = x * zs,

          yy = y * ys,
          yz = y * zs,

          zz = z * zs;

    // Fill destination matrix.
    _pResult->set( 1.0f - (yy + zz), xy + wz,          xz - wy, 
                   xy - wz,          1.0f - (zz + xx), yz + wx, 
                   xz + wy,          yz - wx,          1.0f - (xx + yy) );
}

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END MATRIX_OP_H_1281863689
// #################################################################################
