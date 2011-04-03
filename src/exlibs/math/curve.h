// ======================================================================================
// File         : curve.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 17:20:24 PM | Sunday,August
// Description  : 
// ======================================================================================

/*
Disclaimer for Robert Penner's Easing Equations license:

TERMS OF USE - EASING EQUATIONS

Open source under the BSD License.

Copyright 2001 Robert Penner
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor the names of contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
namespace curve { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// easing curves
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template < typename T >
T linear ( T _t ) {
    return _t;
}

///////////////////////////////////////////////////////////////////////////////
// class quad 
// 
// Purpose: 
// Easing equation function for a quadratic (_t^2)
// param _t		Current time (in frames or seconds).
// return		The correct value.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
struct quad {

    // ------------------------------------------------------------------ 
    // Desc: easing in: accelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T in ( T _t ) { return _t*_t; }

    // ------------------------------------------------------------------ 
    // Desc: easing out: decelerating to zero velocity.
    // ------------------------------------------------------------------ 

    static T out ( T _t ) { return -_t*(_t-T(2)); }

    // ------------------------------------------------------------------ 
    // Desc: easing in/out: acceleration until halfway, then deceleration.
    // ------------------------------------------------------------------ 

    static T in_out ( T _t ) {
        _t *= T(2.0);
        if ( _t < T(1) ) {
            return _t*_t/T(2);
        } else {
            --_t;
            return - T(0.5) * (_t*(_t-T(2)) - T(1));
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out/in: deceleration until halfway, then acceleration.
    // ------------------------------------------------------------------ 

    static T out_in ( T _t ) {
        if (_t < T(0.5)) return quad::out (_t*T(2))/T(2);
        return quad::in((T(2)*_t)-T(1))/T(2) + T(0.5);
    }

}; // end struct quad

///////////////////////////////////////////////////////////////////////////////
// class cubic 
// 
// Purpose: 
// Easing equation function for a cubic (_t^3)
// param _t		Current time (in frames or seconds).
// return		The correct value.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
struct cubic {

    // ------------------------------------------------------------------ 
    // Desc: easing in: accelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T in ( T _t ) { return _t*_t*_t; }

    // ------------------------------------------------------------------ 
    // Desc: easing out: decelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T out ( T _t ) {
        _t -= T(1.0);
        return _t*_t*_t + T(1);
    }

    // ------------------------------------------------------------------ 
    // Desc: easing in/out: acceleration until halfway, then deceleration.
    // ------------------------------------------------------------------ 

    static T in_out ( T _t ) {
        _t *= T(2.0);
        if(_t < T(1)) {
            return T(0.5)*_t*_t*_t;
        } else {
            _t -= T(2.0);
            return T(0.5)*(_t*_t*_t + T(2));
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    static T out_in ( T _t ) {
        if ( _t < T(0.5) ) return cubic::out(T(2)*_t)/T(2);
        return cubic::in(T(2)*_t-T(1))/T(2) + T(0.5);
    }
}; // end struct cubic

///////////////////////////////////////////////////////////////////////////////
// class quart 
// 
// Purpose: 
// Easing equation function for a quartic (_t^4)
// param _t		Current time (in frames or seconds).
// return		The correct value.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
struct quart {

    // ------------------------------------------------------------------ 
    // Desc: easing in: accelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T in ( T _t ) {
        return _t*_t*_t*_t;
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out: decelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T out ( T _t ) {
        _t-= T(1.0);
        return - (_t*_t*_t*_t - T(1));
    }

    // ------------------------------------------------------------------ 
    // Desc:  easing in/out: acceleration until halfway, then deceleration.
    // ------------------------------------------------------------------ 

    static T in_out ( T _t ) {
        _t*=T(2);
        if (_t < T(1)) return T(0.5)*_t*_t*_t*_t;
        else {
            _t -= T(2.0);
            return -T(0.5) * (_t*_t*_t*_t- T(2));
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out/in: deceleration until halfway, then acceleration.
    // ------------------------------------------------------------------ 

    static T out_in ( T _t ) {
        if (_t < T(0.5)) return quart::out (T(2)*_t)/T(2);
        return quart::in(T(2)*_t-T(1))/T(2) + T(0.5);
    }

}; // end struct quart

///////////////////////////////////////////////////////////////////////////////
// class quint
// 
// Purpose: 
// Easing equation function for a quintic (_t^5)
// param _t		Current time (in frames or seconds).
// return		The correct value.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
struct quint {

    // ------------------------------------------------------------------ 
    // Desc: easing in: accelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T in ( T _t ) {
        return _t*_t*_t*_t*_t;
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out: decelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T out ( T _t ) {
        _t -= T(1.0);
        return _t*_t*_t*_t*_t + T(1);
    }

    // ------------------------------------------------------------------ 
    // Desc: easing in/out: acceleration until halfway, then deceleration.
    // ------------------------------------------------------------------ 

    static T in_out(T _t) {
        _t*=T(2.0);
        if (_t < T(1)) return T(0.5)*_t*_t*_t*_t*_t;
        else {
            _t -= T(2.0);
            return T(0.5)*(_t*_t*_t*_t*_t + T(2));
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out/in: deceleration until halfway, then acceleration.
    // ------------------------------------------------------------------ 

    static T out_in(T _t) {
        if (_t < T(0.5)) return quint::out (T(2)*_t)/T(2);
        return quint::in(T(2)*_t - T(1))/T(2) + T(0.5);
    }

}; // end struct quint

///////////////////////////////////////////////////////////////////////////////
// class sine 
// 
// Purpose: 
// Easing equation function for a sinusoidal (sin(_t))
// param _t		Current time (in frames or seconds).
// return		The correct value.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
struct sine {

    // ------------------------------------------------------------------ 
    // Desc: easing in: accelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T in ( T _t ) {
        return (_t == T(1.0)) ? T(1.0) : -mathop::cos(_t * T(EX_HALF_PI)) + T(1.0);
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out: decelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T out ( T _t ) {
        return mathop::sin(_t* T(EX_HALF_PI));
    }

    // ------------------------------------------------------------------ 
    // Desc: easing in/out: acceleration until halfway, then deceleration.
    // ------------------------------------------------------------------ 

    static T in_out(T _t) {
        return -T(0.5) * (mathop::cos(T(EX_HALF_PI)*_t) - T(1));
    }

    // ------------------------------------------------------------------ 
    // Desc: deceleration until halfway, then acceleration.
    // ------------------------------------------------------------------ 

    static T out_in ( T _t ) {
        if (_t < T(0.5)) return sine::out (T(2)*_t)/T(2);
        return sine::in(T(2)*_t - T(1))/T(2) + T(0.5);
    }

}; // end struct sine

///////////////////////////////////////////////////////////////////////////////
// class expo 
// 
// Purpose: 
// Easing equation function for an exponential (2^_t)
// param _t		Current time (in frames or seconds).
// return		The correct value.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
struct expo
{
    // ------------------------------------------------------------------ 
    // Desc: easing in: accelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T in ( T _t ) {
        return (_t == T(0) || _t == T(1.0)) ? _t : mathop::pow(T(2.0), T(10) * (_t - T(1))) - T(0.001);
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out: decelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T out ( T _t ) {
        return (_t==T(1.0)) ? T(1.0) : T(1.001) * (-mathop::pow(T(2.0), -T(10) * _t) + T(1));
    }

    // ------------------------------------------------------------------ 
    // Desc: easing in/out: acceleration until halfway, then deceleration.
    // ------------------------------------------------------------------ 

    static T in_out ( T _t ) {
        if (_t==T(0.0)) return T(0.0);
        if (_t==T(1.0)) return T(1.0);
        _t *= T(2.0);
        if (_t < T(1)) return T(0.5) * mathop::pow(T(2.0), T(10) * (_t - T(1))) - T(0.0005);
        return T(0.5) * T(1.0005) * (-mathop::pow(T(2.0), -T(10) * (_t - T(1))) + T(2));
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out/in: deceleration until halfway, then acceleration.
    // ------------------------------------------------------------------ 

    static T out_in ( T _t ) {
        if (_t < T(0.5)) return expo::out (T(2)*_t)/T(2);
        return expo::in(T(2)*_t - T(1))/T(2) + T(0.5);
    }
}; // end struct expo

///////////////////////////////////////////////////////////////////////////////
// class circ 
// 
// Purpose: 
// Easing equation function for a circular (sqrt(1-_t^2))
// @param _t		Current time (in frames or seconds).
// @return		The correct value.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
struct circ {

    // ------------------------------------------------------------------ 
    // Desc: easing in: accelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T in ( T _t ) {
        return -(mathop::sqrt(T(1) - _t*_t) - T(1));
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out: decelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T out ( T _t ) {
        _t-= T(1.0);
        return mathop::sqrt(T(1) - _t*_t);
    }

    // ------------------------------------------------------------------ 
    // Desc: easing in/out: acceleration until halfway, then deceleration.
    // ------------------------------------------------------------------ 

    static T in_out ( T _t ) {
        _t*=T(2.0);
        if (_t < T(1)) {
            return -T(0.5) * (mathop::sqrt(T(1) - _t*_t) - T(1));
        } else {
            _t -= T(2.0);
            return T(0.5) * (mathop::sqrt(T(1) - _t*_t) + T(1));
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out/in: deceleration until halfway, then acceleration.
    // ------------------------------------------------------------------ 

    static T out_in ( T _t ) {
        if (_t < T(0.5)) return circ::out (T(2)*_t)/T(2);
        return circ::in(T(2)*_t - T(1))/T(2) + T(0.5);
    }

}; // end struct circ

///////////////////////////////////////////////////////////////////////////////
// class elastic 
// 
// Purpose: 
// Easing equation function for an elastic (exponentially decaying sine wave)
// param _t		Current time (in frames or seconds).
// param a		Amplitude.
// param p		Period.
// return		The correct value.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
struct elastic {

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    static T in_helper ( T _t, T _b, T _c, T _d, T _a, T _p ) {
        if (_t==T(0)) return _b;
        T t_adj = (T)_t / (T)_d;
        if (t_adj==T(1)) return _b+_c;

        T s;
        if(_a < mathop::abs(_c)) {
            _a = _c;
            s = _p / T(4.0);
        } else {
            s = _p / T(EX_TWO_PI) * mathop::asin(_c / _a);
        }

        t_adj -= T(1.0);
        return -(_a * mathop::pow(T(2.0),T(10)*t_adj) * mathop::sin( (t_adj*_d-s)*T(EX_TWO_PI)/_p )) + _b;
    }

    // ------------------------------------------------------------------ 
    // Desc: easing in: accelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T in ( T _t, T _a, T _p ) {
        return elastic::in_helper ( _t, 0, 1, 1, _a, _p );
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    static T out_helper ( T _t, T /*b*/, T _c, T /*d*/, T _a, T _p )
    {
        if (_t==0) return 0;
        if (_t==1) return _c;

        T s;
        if(_a < _c) {
            _a = _c;
            s = _p / T(4.0);
        } else {
            s = _p / T(EX_TWO_PI) * mathop::asin(_c / _a);
        }

        return (_a*mathop::pow(2.0f,-10*_t) * mathop::sin( (_t-s)*T(EX_TWO_PI)/_p ) + _c);
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out: decelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T out ( T _t, T _a, T _p )
    {
        return elastic::out_helper( _t, 0, 1, 1, _a, _p );
    }

    // ------------------------------------------------------------------ 
    // Desc: easing in/out: acceleration until halfway, then deceleration.
    // ------------------------------------------------------------------ 

    static T in_out ( T _t, T _a, T _p )
    {
        if (_t==0) return T(0.0);
        _t*=T(2.0);
        if (_t==2) return T(1.0);

        T s;
        if(_a < T(1.0)) {
            _a = T(1.0);
            s = _p / T(4.0);
        } else {
            s = _p / (T(EX_TWO_PI)) * mathop::asin(T(1.0) / _a);
        }

        if (_t < 1) return -T(0.5)*(_a*mathop::pow(T(2.0),T(10)*(_t-T(1))) * mathop::sin( (_t-T(1)-s)*T(EX_TWO_PI)/_p ));
        return _a * mathop::pow(T(2.0),-T(10)*(_t-1)) * mathop::sin( (_t-1-s)*T(EX_TWO_PI)/_p )*T(0.5) + T(1.0);
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out/in: deceleration until halfway, then acceleration.
    // ------------------------------------------------------------------ 

    static T out_in ( T _t, T _a, T _p )
    {
        if (_t < T(0.5)) return elastic::out_helper(_t*T(2), T(0), T(0.5), T(1.0), _a, _p);
        return elastic::in_helper(T(2)*_t - T(1.0), T(0.5), T(0.5), T(1.0), _a, _p);
    }
}; // end struct elastic

///////////////////////////////////////////////////////////////////////////////
// class back 
// 
// Purpose: 
// Easing equation function for a back (overshooting cubic easing: (s+1)*_t^3 - s*_t^2)
// param _t		Current time (in frames or seconds).
// param s		Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
// return		The correct value.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
struct back {

    // ------------------------------------------------------------------ 
    // Desc: easing in: accelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T in ( T _t, T _s ) {
        return _t*_t*((_s+1)*_t - _s);
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out: decelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T out ( T _t, T _s ) {
        _t-= T(1.0);
        return _t*_t*((_s+1)*_t+ _s) + 1;
    }

    // ------------------------------------------------------------------ 
    // Desc: easing in/out: acceleration until halfway, then deceleration.
    // ------------------------------------------------------------------ 

    static T in_out ( T _t, T _s ) {
        _t *= T(2.0);
        if (_t < T(1)) {
            _s *= T(1.525);
            return T(0.5)*(_t*_t*((_s+1)*_t - _s));
        } else {
            _t -= T(2);
            _s *= T(1.525);
            return T(0.5)*(_t*_t*((_s+1)*_t+ _s) + T(2));
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out/in: deceleration until halfway, then acceleration.
    // ------------------------------------------------------------------ 

    static T out_in ( T _t, T _s )
    {
        if (_t < T(0.5)) return back::out (2*_t, _s)/2;
        return back::in(2*_t - 1, _s)/2 + T(0.5);
    }
}; // end struct back

///////////////////////////////////////////////////////////////////////////////
// class bounce 
// 
// Purpose: 
// Easing equation function for a bounce (exponentially decaying parabolic bounce)
// param _t		Current time (in frames or seconds).
// param a		Amplitude.
// return		The correct value.
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
struct bounce
{
    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    static T out_helper ( T _t, T _c, T _a ) {
        if (_t == T(1.0)) return _c;
        if (_t < T(4/11.0)) {
            return _c*(T(7.5625)*_t*_t);
        } else if (_t < (T(8)/T(11.0))) {
            _t -= (T(6)/T(11.0));
            return -_a * (T(1.0) - (T(7.5625)*_t*_t + T(0.75))) + _c;
        } else if (_t < (T(10)/T(11.0))) {
            _t -= (T(9)/T(11.0));
            return -_a * (T(1.0) - (T(7.5625)*_t*_t + T(0.9375))) + _c;
        } else {
            _t -= (T(21)/T(22.0));
            return -_a * (T(1.0) - (T(7.5625)*_t*_t + T(0.984375))) + _c;
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: easing out: decelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T out (T _t, T _a) {
        return bounce::out_helper(_t, 1, _a);
    }

    // ------------------------------------------------------------------ 
    // Desc: easing in: accelerating from zero velocity.
    // ------------------------------------------------------------------ 

    static T in ( T _t, T _a ) {
        return T(1.0) - bounce::out_helper( T(1.0)-_t, T(1.0), _a );
    }

    // ------------------------------------------------------------------ 
    // Desc: easing in/out: acceleration until halfway, then deceleration.
    // ------------------------------------------------------------------ 

    static T in_out ( T _t, T _a ) {
        if (_t < T(0.5)) return bounce::in (T(2)*_t, _a)/T(2);
        else return (_t == T(1.0)) ? T(1.0) : bounce::out (T(2)*_t - T(1), _a)/T(2) + T(0.5);
    }

    // ------------------------------------------------------------------ 
    // Desc: deceleration until halfway, then acceleration.
    // ------------------------------------------------------------------ 

    static T out_in ( T _t, T _a )
    {
        if (_t < T(0.5)) return bounce::out_helper(_t*T(2), T(0.5), _a);
        return T(1.0) - bounce::out_helper (T(2.0)-T(2)*_t, T(0.5), _a);
    }
}; // end struct bounce

///////////////////////////////////////////////////////////////////////////////
// my curves
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: smooth 
// _t<=0: 0 | 0<_t<1: 3*_t^2 - 2*t^3 | _t>=1: 1
// ------------------------------------------------------------------ 

template < typename T >
T smooth ( T _t ) {
    if ( _t <= T(0) ) return T(0);
    if ( _t >= T(1) ) return T(1);
    return _t*_t*(T(3) - T(2)*_t);
}

// ------------------------------------------------------------------ 
// Desc: fade 
// _t<=0: 0 | 0<_t<1: 6*_t^5 - 15*_t^4 + 10*_t^3 | _t>=1: 1
// ------------------------------------------------------------------ 

template < typename T >
T fade ( T _t ) {
    if ( _t <= T(0) ) return T(0);
    if ( _t >= T(1) ) return T(1);
    return _t*_t*_t*(_t*(_t*6-15)+10);
}


// TODO: these part looks like qt's own function { 
// static inline T qt_sinProgress(T value)
// {
//     return qSin((value * M_PI) - M_PI_2) / 2 + T(0.5);
// }

// static inline T qt_smoothBeginEndMixFactor(T value)
// {
//     return qMin(qMax(1 - value * 2 + T(0.3), T(0.0)), T(1.0));
// }

// // SmoothBegin blends Smooth and Linear Interpolation.
// // Progress 0 - 0.3      : Smooth only
// // Progress 0.3 - ~ 0.5  : Mix of Smooth and Linear
// // Progress ~ 0.5  - 1   : Linear only

// /**
// // Easing function that starts growing slowly, then increases in speed. At the end of the curve the speed will be constant.
//  */
// static T easeInCurve(T _t)
// {
//     const T sinProgress = qt_sinProgress(_t);
//     const T mix = qt_smoothBeginEndMixFactor(_t);
//     return sinProgress * mix + _t * (1 - mix);
// }

// /**
// // Easing function that starts growing steadily, then ends slowly. The speed will be constant at the beginning of the curve.
//  */
// static T easeOutCurve(T _t)
// {
//     const T sinProgress = qt_sinProgress(_t);
//     const T mix = qt_smoothBeginEndMixFactor(1 - _t);
//     return sinProgress * mix + _t * (1 - mix);
// }

// /**
// // Easing function where the value grows sinusoidally. Note that the calculated  end value will be 0 rather than 1.
//  */
// static T easeSineCurve(T _t)
// {
//     return (qSin(((_t * M_PI * 2)) - M_PI_2) + 1) / 2;
// }

// /**
// // Easing function where the value grows cosinusoidally. Note that the calculated start value will be 0.5 and the end value will be 0.5
// // contrary to the usual 0 to 1 easing curve.
//  */
// static T easeCosineCurve(T _t)
// {
//     return (qCos(((_t * M_PI * 2)) - M_PI_2) + 1) / 2;
// }
// } TODO end 

// ######################### 
} // end namespace curve 
// ######################### 

// ######################### 
} // end namespace ex 
// ######################### 


