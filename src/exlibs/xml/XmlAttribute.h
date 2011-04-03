// ======================================================================================
// File         : XmlAttribute.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:27:33 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef XMLATTRIBUTE_H_1250526456
#define XMLATTRIBUTE_H_1250526456
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class XmlAttribute 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class XmlAttribute
{

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    XmlAttribute()
    {
    }

    //
    XmlAttribute( const char* _key, const char* _value )
        : m_Key (_key),
          m_Value (_value)
    {
    }

    //
    ~XmlAttribute() {}

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    INLINE bool operator < ( const XmlAttribute& _attr ) const { return m_Key < _attr.m_Key; }
    INLINE bool operator > ( const XmlAttribute& _attr ) const { return m_Key > _attr.m_Key; }
    INLINE bool operator <= ( const XmlAttribute& _attr ) const { return m_Key <= _attr.m_Key; }
    INLINE bool operator >= ( const XmlAttribute& _attr ) const { return m_Key >= _attr.m_Key; }
    INLINE bool operator == ( const XmlAttribute& _attr ) const { return m_Key == _attr.m_Key; }
    INLINE bool operator != ( const XmlAttribute& _attr ) const { return m_Key != _attr.m_Key; }
    INLINE bool operator == ( const char* _key ) const { return m_Key == _key; }
    INLINE bool operator != ( const char* _key ) const { return m_Key != _key; }

    //
    INLINE void SetKey( const char* _key ) { m_Key = _key; }
    INLINE const char* key() const { return m_Key.c_str(); }

    //
    INLINE void SetValue( const char* _value ) { m_Value = _value; }
    INLINE const char* GetValue() const { return m_Value.c_str(); }


    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    string_t    m_Key;
    string_t    m_Value;

}; // end class XmlAttribute 


// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END XMLATTRIBUTE_H_1250526456
// #################################################################################
