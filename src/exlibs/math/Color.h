// ======================================================================================
// File         : Color.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:16:25 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef COLOR_H_1250525788
#define COLOR_H_1250525788
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

class Color3u;
class Color4u;
class Color3f;
class Color4f;

///////////////////////////////////////////////////////////////////////////////
// class Color3u 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Color3u
{

    ///////////////////////////////////////////////////////////////////////////////
    // static const
    ///////////////////////////////////////////////////////////////////////////////

public:

    static const Color3u black;
    static const Color3u white;

    ///////////////////////////////////////////////////////////////////////////////
    // public member data 
    ///////////////////////////////////////////////////////////////////////////////

public:
    union
    {
        struct { uint8 r, g, b; }; // end struct
        uint8 c[3];
    }; // end union


    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    Color3u()
        : r(0), g(0), b(0)
    {
    }

    Color3u ( const Color3u& _color )
        : r(_color.r), g(_color.g), b(_color.b)
    {
    }

    Color3u( uint8 _r, uint8 _g, uint8 _b )
        : r(_r), g(_g), b(_b)
    {
    }

    explicit Color3u( uint8 _value )
        : r(_value), g(_value), b(_value)
    {
    }

    explicit Color3u( const uint8* _pArray )
        : r(_pArray[0]), g(_pArray[1]), b(_pArray[2])
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ========================================================
    // set
    // ========================================================

    INLINE void set ( uint8 _r, uint8 _g, uint8 _b ) { r = _r; g = _g; b = _b; }
    INLINE void set ( uint8 _value ) { r = _value; g = _value; b = _value; }
    INLINE void set ( const uint8* _pArray ) { r = _pArray[0]; g = _pArray[1]; b = _pArray[2]; }
    INLINE void set ( const Color3u& _col ) { r = _col.r; g = _col.g; b = _col.b; }

    // ========================================================
    // cast
    // ========================================================

    INLINE operator uint8* () { return (uint8*)this; }
    Color4u toColor4u () const;
    Color3f toColor3f () const;
    Color4f toColor4f () const;
    INLINE uint32 toARGB () const { return ((uint32)( ((0xff)<<24) | ((r&0xff)<<16) | ((g&0xff)<<8) | (b&0xff)) ); }
    INLINE uint32 toRGBA () const { return ((uint32)( ((r&0xff)<<24) | ((g&0xff)<<16) | ((b&0xff)<<8) | (0xff)) ); }

    // ========================================================
    // operator
    // ========================================================

    //
    INLINE Color3u& operator = ( const Color3u& _color )
    {
        r = _color.r; g = _color.g; b = _color.b;
        return *this;
    }

    //
    INLINE Color3u& operator += ( const Color3u& _color )
    {
        r += _color.r; g += _color.g; b += _color.b;
        return *this;
    }

    //
    INLINE Color3u& operator -= ( const Color3u& _color )
    {
        r -= _color.r; g -= _color.g; b -= _color.b;
        return *this;
    }

    //
    INLINE Color3u& operator *= ( const Color3u& _color )
    {
        r *= _color.r; g *= _color.g; b *= _color.b;
        return *this;
    }

    //
    INLINE Color3u& operator *= ( uint8 _scalar )
    {
        r *= _scalar; g *= _scalar; b *= _scalar;
        return *this;
    }

    //
    INLINE Color3u& operator /= ( const Color3u& _color ) 
    {
        r /= _color.r; g /= _color.g; b /= _color.b;
        return *this;
    }

    //
    INLINE Color3u& operator /= ( uint8 _scalar )
    {
        float inv_scalar = 1.0f / _scalar;
        r = uint8(r*inv_scalar); g = uint8(g*inv_scalar); b = uint8(b*inv_scalar);
        return *this;
    }

    // ========================================================
	// logic operator 
    // ========================================================

    INLINE bool operator <  ( const Color3u& _color )  const    { return ( r < _color.r && g < _color.g && b < _color.b ); }
    INLINE bool operator <= ( const Color3u& _color )  const    { return ( r <= _color.r && g <= _color.g && b <= _color.b ); }
    INLINE bool operator >  ( const Color3u& _color )  const    { return ( r > _color.r && g > _color.g && b > _color.b ); }
    INLINE bool operator >= ( const Color3u& _color )  const    { return ( r >= _color.r && g >= _color.g && b >= _color.b ); }
    INLINE bool operator == ( const Color3u& _color )  const    { return ( r == _color.r && g == _color.g && b == _color.b ); }
    INLINE bool operator != ( const Color3u& _color )  const    { return ( r != _color.r || g != _color.g || b != _color.b ); }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string = to_str<FLAGS>(this->r) + "," + 
                          to_str<FLAGS>(this->g) + "," +
                          to_str<FLAGS>(this->b)
                          ;
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("Color3u");
        return strID;
    }
    void serialize ( ISerializeNode* _pNode );

}; // end class Color3u

///////////////////////////////////////////////////////////////////////////////
// class Color4u 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Color4u
{

    ///////////////////////////////////////////////////////////////////////////////
    // static const
    ///////////////////////////////////////////////////////////////////////////////

public:

    ///////////////////////////////////////////////////////////////////////////////
    // public member data 
    ///////////////////////////////////////////////////////////////////////////////

public:
    union
    {
        struct { uint8 r, g, b, a; }; // end struct
        uint8 c[4];
    }; // end union


    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    Color4u()
        : r(0), g(0), b(0), a(255)
    {
    }

    Color4u ( const Color4u& _color )
        : r(_color.r), g(_color.g), b(_color.b), a(_color.a)
    {
    }

    Color4u( uint8 _r, uint8 _g, uint8 _b, uint8 _a = 255 )
        : r(_r), g(_g), b(_b), a(_a)
    {
    }

    Color4u( const Color3u& _clr )
        : r(_clr.r), g(_clr.g), b(_clr.b), a(255)
    {
    }

    explicit Color4u( uint8 _value )
        : r(_value), g(_value), b(_value), a(_value)
    {
    }

    explicit Color4u( const uint8* _pArray )
        : r(_pArray[0]), g(_pArray[1]), b(_pArray[2]), a(_pArray[3])
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ========================================================
    // set
    // ========================================================

    INLINE void set ( uint8 _r, uint8 _g, uint8 _b, uint8 _a ) { r = _r; g = _g; b = _b; a = _a; }
    INLINE void set ( uint8 _value ) { r = _value; g = _value; b = _value; }
    INLINE void set ( const uint8* _pArray ) { r = _pArray[0]; g = _pArray[1]; b = _pArray[2]; a = _pArray[3]; }
    INLINE void set ( const Color3u& _clr ) { r = _clr.r; g = _clr.g; b = _clr.b; a = 255; }
    INLINE void set ( const Color4u& _clr ) { r = _clr.r; g = _clr.g; b = _clr.b; a = _clr.a; }

    // ========================================================
    // cast
    // ========================================================

    INLINE operator uint8* () { return (uint8*)this; }
    INLINE operator Color3u () { return Color3u(r,g,b);}

    Color3u toColor3u () const;
    Color3f toColor3f () const;
    Color4f toColor4f () const;
    INLINE uint32 toARGB () const { return ((uint32)( ((a&0xff)<<24) | ((r&0xff)<<16) | ((g&0xff)<<8) | (b&0xff)) ); }
    INLINE uint32 toRGBA () const { return ((uint32)( ((r&0xff)<<24) | ((g&0xff)<<16) | ((b&0xff)<<8) | (a&0xff)) ); }

    // ========================================================
    // operator
    // ========================================================

    //
    INLINE Color4u& operator = ( const Color4u& _color )
    {
        r = _color.r; g = _color.g; b = _color.b; a = _color.a;
        return *this;
    }

    //
    INLINE Color4u& operator += ( const Color4u& _color )
    {
        r += _color.r; g += _color.g; b += _color.b; a += _color.a;
        return *this;
    }

    //
    INLINE Color4u& operator -= ( const Color4u& _color )
    {
        r -= _color.r; g -= _color.g; b -= _color.b; a -= _color.a;
        return *this;
    }

    //
    INLINE Color4u& operator *= ( const Color4u& _color )
    {
        r *= _color.r; g *= _color.g; b *= _color.b; a *= _color.a;
        return *this;
    }

    //
    INLINE Color4u& operator *= ( uint8 _scalar )
    {
        r *= _scalar; g *= _scalar; b *= _scalar; a *= _scalar;
        return *this;
    }

    //
    INLINE Color4u& operator /= ( const Color4u& _color ) 
    {
        r /= _color.r; g /= _color.g; b /= _color.b; a /= _color.a;
        return *this;
    }

    //
    INLINE Color4u& operator /= ( uint8 _scalar )
    {
        float inv_scalar = 1.0f / _scalar;
        r = uint8(r*inv_scalar); g = uint8(g*inv_scalar); b = uint8(b*inv_scalar); a = uint8(a*inv_scalar); 
        return *this;
    }

    // ========================================================
	// logic operator 
    // ========================================================

    INLINE bool operator <  ( const Color4u& _color )  const    { return ( r < _color.r && g < _color.g && b < _color.b && a < _color.a ); }
    INLINE bool operator <= ( const Color4u& _color )  const    { return ( r <= _color.r && g <= _color.g && b <= _color.b && a <= _color.a ); }
    INLINE bool operator >  ( const Color4u& _color )  const    { return ( r > _color.r && g > _color.g && b > _color.b && a > _color.a ); }
    INLINE bool operator >= ( const Color4u& _color )  const    { return ( r >= _color.r && g >= _color.g && b >= _color.b && a >= _color.a ); }
    INLINE bool operator == ( const Color4u& _color )  const    { return ( r == _color.r && g == _color.g && b == _color.b && a == _color.a ); }
    INLINE bool operator != ( const Color4u& _color )  const    { return ( r != _color.r || g != _color.g || b != _color.b || a != _color.a ); }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string = to_str<FLAGS>(this->r) + "," + 
                          to_str<FLAGS>(this->g) + "," +
                          to_str<FLAGS>(this->b) + "," +
                          to_str<FLAGS>(this->a)
                          ;
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("Color4u");
        return strID;
    }
    void serialize ( ISerializeNode* _pNode );

}; // end class Color4u

///////////////////////////////////////////////////////////////////////////////
// class Color3f 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Color3f
{

    ///////////////////////////////////////////////////////////////////////////////
    // static const
    ///////////////////////////////////////////////////////////////////////////////

public:

    static const Color3f black;
    static const Color3f white;

    ///////////////////////////////////////////////////////////////////////////////
    // public member data 
    ///////////////////////////////////////////////////////////////////////////////

public:
    union
    {
        struct { float r, g, b; }; // end struct
        float c[3];
    }; // end union


    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ========================================================
    // float init
    // ========================================================

    INLINE Color3f()
        : r(0.0f), g(0.0f), b(0.0f)
    {
    }

    INLINE Color3f( const Color3f& _color )
        : r(_color.r), g(_color.g), b(_color.b)
    {
    }

    INLINE Color3f( float _r, float _g, float _b )
    {
        this->set (_r,_g,_b);
    }

    INLINE explicit Color3f( float _value )
    {
        this->set (_value);
    }

    INLINE explicit Color3f( const float* _pArray )
    {
        this->set (_pArray);
    }

    // ========================================================
    // uint8 init 
    // ========================================================

    INLINE Color3f( uint8 _r, uint8 _g, uint8 _b )
    {
        this->set ( _r, _g, _b );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public memeber functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ========================================================
    // set 
    // ========================================================

    INLINE void set ( float _r, float _g, float _b ) 
    { 
        r = _r; g = _g; b = _b;
    } 
    INLINE void set ( float _value ) { this->set(_value,_value,_value); }
    INLINE void set ( const float* _pArray ) { this->set(_pArray[0],_pArray[1],_pArray[2]); }
    INLINE void set ( const Color3f& _clr ) { r = _clr.r; g = _clr.g; b = _clr.b; }

    INLINE void set ( uint8 _r, uint8 _g, uint8 _b ) 
    { 
        this->set( _r / 255.0f, _g / 255.0f, _b / 255.0f );
    }
    void clamp() {
        r = mathop::clamp(r,0.0f,1.0f); 
        g = mathop::clamp(g,0.0f,1.0f); 
        b = mathop::clamp(b,0.0f,1.0f); 
    }

    // ========================================================
    // cast 
    // ========================================================

    INLINE operator float* () { return (float*)this;}
    Color3u toColor3u () const;
    Color4u toColor4u () const;
    Color4f toColor4f () const;

    INLINE uint32 toARGB () const 
    {
        Color4u color4u = toColor4u();
        return color4u.toARGB();
    }

    INLINE uint32 toRGBA () const 
    {
        Color4u color4u = toColor4u();
        return color4u.toRGBA();
    }

    // ========================================================
    // operator 
    // ========================================================

    //
    INLINE Color3f& operator = ( const Color3f& _color )
    {
        r = _color.r; g = _color.g; b = _color.b;
        return *this;
    }

    //
    INLINE Color3f& operator += ( const Color3f& _color )
    {
        r += _color.r; g += _color.g; b += _color.b;
        return *this;
    }

    //
    INLINE Color3f& operator -= ( const Color3f& _color )
    {
        r -= _color.r; g -= _color.g; b -= _color.b;
        return *this;
    }

    //
    INLINE Color3f& operator *= ( const Color3f& _color )
    {
        r *= _color.r; g *= _color.g; b *= _color.b;
        return *this;
    }

    //
    INLINE Color3f& operator *= ( float _scalar )
    {
        r *= _scalar; g *= _scalar; b *= _scalar;
        return *this;
    }

    //
    INLINE Color3f& operator /= ( const Color3f& _color ) 
    {
        r /= _color.r; g /= _color.g; b /= _color.b;
        return *this;
    }


    //
    INLINE Color3f& operator /= ( float _scalar )
    {
        float inv_scalar = 1.0f / _scalar;
        r *= inv_scalar; g *= inv_scalar; b *= inv_scalar;
        return *this;
    }

    // ========================================================
	// logic operator 
    // ========================================================

    //
    INLINE bool operator < ( const Color3f& _color ) const { return ( r < _color.r && g < _color.g && b < _color.b ); }
    INLINE bool operator <= ( const Color3f& _color ) const { return ( r <= _color.r && g <= _color.g && b <= _color.b ); }
    INLINE bool operator > ( const Color3f& _color ) const { return ( r > _color.r && g > _color.g && b > _color.b ); }
    INLINE bool operator >= ( const Color3f& _color ) const { return ( r >= _color.r && g >= _color.g && b >= _color.b ); }
    INLINE bool operator == ( const Color3f& _color ) const { return ( r == _color.r && g == _color.g && b == _color.b ); }
    INLINE bool operator != ( const Color3f& _color ) const { return ( r != _color.r || g != _color.g || b != _color.b ); }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string = to_str<FLAGS>(this->r) + "," + 
                          to_str<FLAGS>(this->g) + "," +
                          to_str<FLAGS>(this->b)
                          ;
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("Color3f");
        return strID;
    }
    void serialize ( ISerializeNode* _pNode );

}; // end class Color3f


///////////////////////////////////////////////////////////////////////////////
// class Color4f 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Color4f
{

    ///////////////////////////////////////////////////////////////////////////////
    // static const
    ///////////////////////////////////////////////////////////////////////////////

public:

    ///////////////////////////////////////////////////////////////////////////////
    // public member data 
    ///////////////////////////////////////////////////////////////////////////////

public:

    union
    {
        struct { float r, g, b, a; }; // end struct
        float c[4];
    }; // end union


    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ========================================================
    // float init
    // ========================================================

    INLINE Color4f()
        : r(0.0f), g(0.0f), b(0.0f), a(1.0f)
    {
    }

    INLINE Color4f( const Color4f& _color )
        : r(_color.r), g(_color.g), b(_color.b), a(_color.a)
    {
    }

    INLINE Color4f( float _r, float _g, float _b, float _a = 1.0f )
        : r(_r), g(_g), b(_b), a(_a)
    {
    }

    INLINE Color4f( const Color3f& _col, float _a = 1.0f )
        : r(_col.r), g(_col.g), b(_col.b), a(_a)
    {
    }

    INLINE explicit Color4f( float _value )
        : r(_value), g(_value), b(_value), a(_value)
    {
    }

    INLINE explicit Color4f( const float* _pArray )
        : r(_pArray[0]), g(_pArray[1]), b(_pArray[2]), a(_pArray[3])
    {
    }

    // ========================================================
    // uint8 init 
    // ========================================================

    INLINE Color4f( uint8 _r, uint8 _g, uint8 _b, uint8 _a = 255 )
    {
        r = _r / 255.0f; 
        g = _g / 255.0f; 
        b = _b / 255.0f; 
        a = _a / 255.0f; 
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public memeber functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ========================================================
    // set 
    // ========================================================

    INLINE void set ( float _r, float _g, float _b, float _a ) { r = _r; g = _g; b = _b; a = _a; } 
    INLINE void set ( float _value ) { r = _value; g = _value; b = _value; a = _value; }
    INLINE void set ( const float* _pArray ) { r = _pArray[0]; g = _pArray[1]; b = _pArray[2]; a = _pArray[3]; }
    INLINE void set ( const Color3f& _col ) { r = _col.r; g = _col.g; b = _col.b; a = 1.0f; }
    INLINE void set ( const Color4f& _col ) { r = _col.r; g = _col.g; b = _col.b; a = _col.a; }

    INLINE void set ( uint8 _r, uint8 _g, uint8 _b, uint8 _a = 255 ) 
    { 
        r = _r / 255.0f; 
        g = _g / 255.0f; 
        b = _b / 255.0f; 
        a = _a / 255.0f; 
    } 

    // ========================================================
    // cast 
    // ========================================================

    INLINE operator float* () { return (float*)this;}
    INLINE operator Color3f () { return Color3f(r,g,b);}

    Color3u toColor3u () const;
    Color4u toColor4u () const;
    Color3f toColor3f () const;

    INLINE uint32 toARGB () const 
    {
        Color4u color4u = toColor4u();
        return color4u.toARGB();
    }

    INLINE uint32 toRGBA () const 
    {
        Color4u color4u = toColor4u();
        return color4u.toRGBA();
    }

    // ========================================================
    // operator 
    // ========================================================

    //
    INLINE Color4f& operator = ( const Color4f& _color )
    {
        r = _color.r; g = _color.g; b = _color.b; a = _color.a;
        return *this;
    }

    //
    INLINE Color4f& operator += ( const Color4f& _color )
    {
        r += _color.r; g += _color.g; b += _color.b; a += _color.a;
        return *this;
    }

    //
    INLINE Color4f& operator -= ( const Color4f& _color )
    {
        r -= _color.r; g -= _color.g; b -= _color.b; a -= _color.a;
        return *this;
    }

    //
    INLINE Color4f& operator *= ( const Color4f& _color )
    {
        r *= _color.r; g *= _color.g; b *= _color.b; a *= _color.a;
        return *this;
    }

    //
    INLINE Color4f& operator *= ( float _scalar )
    {
        r *= _scalar; g *= _scalar; b *= _scalar; a *= _scalar;
        return *this;
    }

    //
    INLINE Color4f& operator /= ( const Color4f& _color ) 
    {
        r /= _color.r; g /= _color.g; b /= _color.b; a /= _color.a;
        return *this;
    }


    //
    INLINE Color4f& operator /= ( float _scalar )
    {
        float inv_scalar = 1.0f / _scalar;
        r *= inv_scalar; g *= inv_scalar; b *= inv_scalar; a *= inv_scalar;
        return *this;
    }

    // ========================================================
	// logic operator 
    // ========================================================

    //
    INLINE bool operator < ( const Color4f& _color ) const { return ( r < _color.r && g < _color.g && b < _color.b && a < _color.a ); }
    INLINE bool operator <= ( const Color4f& _color ) const { return ( r <= _color.r && g <= _color.g && b <= _color.b && a <= _color.a ); }
    INLINE bool operator > ( const Color4f& _color ) const { return ( r > _color.r && g > _color.g && b > _color.b && a > _color.a ); }
    INLINE bool operator >= ( const Color4f& _color ) const { return ( r >= _color.r && g >= _color.g && b >= _color.b && a >= _color.a ); }
    INLINE bool operator == ( const Color4f& _color ) const { return ( r == _color.r && g == _color.g && b == _color.b && a == _color.a ); }
    INLINE bool operator != ( const Color4f& _color ) const { return ( r != _color.r || g != _color.g || b != _color.b || a != _color.a ); }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string = to_str<FLAGS>(this->r) + "," + 
                          to_str<FLAGS>(this->g) + "," +
                          to_str<FLAGS>(this->b) + "," +
                          to_str<FLAGS>(this->a)
                          ;
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("Color4f");
        return strID;
    }
    void serialize ( ISerializeNode* _pNode );

}; // end class Color4f

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END COLOR_H_1250525788
// #################################################################################
