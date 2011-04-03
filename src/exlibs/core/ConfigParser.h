// ======================================================================================
// File         : ConfigParser.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:09:47 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef CONFIGPARSER_H_1250525390
#define CONFIGPARSER_H_1250525390
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "xml/XmlNode.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class ConfigParser 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL ConfigParser
{
    ///////////////////////////////////////////////////////////////////////////////
    // protected structure
    ///////////////////////////////////////////////////////////////////////////////

protected:

    ///////////////////////////////////////////////////////////////////////////////
    // class SubstituteInfo 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    struct SubstituteInfo
    {
        SubstituteInfo( const string_t& _value, 
                         string_t::sz_t _start,
                         string_t::sz_t _end )
            : value(_value),
              start(_start),
              end(_end)
        {
        }
        string_t        value;
        string_t::sz_t  start;
        string_t::sz_t  end;
    }; // end struct SubstituteInfo

    ///////////////////////////////////////////////////////////////////////////////
    // class ValueInfo 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    struct ValueInfo
    {
        ValueInfo()
            : id(-1)
            , autogen(false)
            , value_ptr(NULL)
            , type_name ("")
            , value_name ("")
            , raw_value("")
            , expanded_value("")
        {
        }

        void reset ()
        {
            id = -1;
            autogen = false;

            if ( value_ptr )
                ex_free (value_ptr);
            type_name = "";
            value_name = "";
            raw_value = "";
            expanded_value = "";
        }

        INLINE bool operator < ( const ValueInfo& _value ) const { return id < _value.id; }

        uint     id;
        bool     autogen;
        void*    value_ptr;
        string_t type_name;
        string_t value_name;
        string_t raw_value;
        string_t expanded_value;
    }; // end struct ValueInfo

    ///////////////////////////////////////////////////////////////////////////////
    // public typedef 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef ConfigParser self_t;
    typedef HashMap<string_id_t,ValueInfo> value_map_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    ConfigParser();
    ~ConfigParser();

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    result_t save( const char* _filename );
    result_t parse( const char* _filename );

    template < typename T > T get ( const char* _valueName ) const;
    void set ( const char* _valueName, const char* _valueType, const char* _valueText, bool _autoGen = false );
    bool has ( const char* _valueName ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // protcted member functions 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    result_t parseElement( XmlNode::smart_ptr_t _spNode );

    result_t parseValue( XmlNode::smart_ptr_t _spNode );
    string_t expandValue( const string_t& _value );

    void* allocValue( const char* _typeName, const char* _valueText );

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    uint        m_count;
    value_map_t m_values;

}; // end class ConfigParser

// #########################
namespace _private { 
// #########################

    // ------------------------------------------------------------------
    // Desc: T_VoidCast 
    // ------------------------------------------------------------------

    // true
    template <typename T>
    T VoidPtrCast( void* _ptr, intToType<true> ) { return reinterpret_cast<T>(_ptr); }

    // false
    template <typename T>
    T VoidPtrCast( void* _ptr, intToType<false> ) { return *(reinterpret_cast<T*>(_ptr)); }

// #########################
} // end namespace _private 
// #########################

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

template < typename T > 
T ConfigParser::get( const char* _valueName ) const
{
    value_map_t::c_iterator iter = m_values.find( string_id_t(_valueName) );
    if ( iter != m_values.end() )
    {
        return _private::VoidPtrCast<T>( (*iter).value_ptr, intToType< TypeTraits<T>::isPointer >() );
    }
    else
    {
        ex_warning( "%s not found", _valueName );
    }

    return T(NULL);
}

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END CONFIGPARSER_H_1250525390
// #################################################################################
