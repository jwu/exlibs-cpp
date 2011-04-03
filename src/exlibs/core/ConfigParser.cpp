// ======================================================================================
// File         : ConfigParser.cpp
// Author       : Wu Jie 
// Last Change  : 11/10/2009 | 14:34:54 PM | Tuesday,November
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"

// #########################
namespace ex { 
// #########################

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

ConfigParser::ConfigParser()
    : m_count (0)
{
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

ConfigParser::~ConfigParser()
{
    for ( value_map_t::iterator iter = m_values.begin(); iter != m_values.end(); ++iter )
    {
        (*iter).reset();
    }
    m_values.clear();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t ConfigParser::save( const char* _filename )
{
    result_t eResult = EResult::ok;

    //
    IFile::smart_ptr_t spFile = futil::file::replace<TextFile>(_filename);
    if ( spFile )
    {
        typedef Array<ValueInfo> infos_t;
        infos_t customInfos;
        infos_t autogenInfos;

        // store and sort the custom infors
        for ( value_map_t::iterator iter = m_values.begin(); iter != m_values.end(); ++iter )
        {
            if ( (*iter).autogen == false )
                customInfos.push_back(*iter);
            else
                autogenInfos.push_back(*iter);
        }
        ex::sort ( autogenInfos.begin(), autogenInfos.end() );
        ex::sort ( customInfos.begin(), customInfos.end() );

        // add xml header
        spFile.cast<ex::TextFile>()->writeline ( "<?xml version=\"1.0\" encoding=\"utf-8\"?>" );

        // start settings
        spFile.cast<ex::TextFile>()->writeline ( "<settings>" );

        // autogen
        spFile.cast<ex::TextFile>()->writeline ( "" );
        spFile.cast<ex::TextFile>()->writeline ( "\t<!-- ///////////////////////////////////////////////////////////////////////////// --> " );
        spFile.cast<ex::TextFile>()->writeline ( "\t<!-- NOTE: the value in this section is automatically setup by engine. --> " );
        spFile.cast<ex::TextFile>()->writeline ( "\t<!-- ///////////////////////////////////////////////////////////////////////////// --> " );
        spFile.cast<ex::TextFile>()->writeline ( "" );
        spFile.cast<ex::TextFile>()->writeline ( "\t<autogen>" );
        for ( infos_t::iterator iter = autogenInfos.begin(); iter != autogenInfos.end(); ++iter )
        {
            spFile.cast<ex::TextFile>()->writeline ( "\t\t<" + (*iter).value_name + "/>" );
        }
        spFile.cast<ex::TextFile>()->writeline ( "\t</autogen>" );

        // custom
        spFile.cast<ex::TextFile>()->writeline ( "" );
        spFile.cast<ex::TextFile>()->writeline ( "\t<!-- ///////////////////////////////////////////////////////////////////////////// --> " );
        spFile.cast<ex::TextFile>()->writeline ( "\t<!-- NOTE: add your customize value in this section. --> " );
        spFile.cast<ex::TextFile>()->writeline ( "\t<!-- ///////////////////////////////////////////////////////////////////////////// --> " );
        spFile.cast<ex::TextFile>()->writeline ( "" );
        spFile.cast<ex::TextFile>()->writeline ( "\t<custom>" );
        for ( infos_t::iterator iter = customInfos.begin(); iter != customInfos.end(); ++iter )
        {
            spFile.cast<ex::TextFile>()->writeline ( "\t\t<" + (*iter).value_name + 
                                                      " type=\"" + (*iter).type_name + 
                                                      "\" value=\"" + (*iter).raw_value + "\"/>" );
        }
        spFile.cast<ex::TextFile>()->writeline ( "\t</custom>" );

        // finish settings
        spFile.cast<ex::TextFile>()->writeline ( "</settings>" );
    }
    else
    {
        eResult = EResult::write_failed; 
        ex_warning( "Failed to save file %s", _filename );
    }
    spFile->close();

    //
    return eResult; 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t ConfigParser::parse( const char* _filename )
{
    // check if file exist
    if ( futil::file::exists( path_t(_filename) ) )
    {
        // parse xml file
        ex::XmlParser parser;
        ex::XmlNode::smart_ptr_t spRoot = parser.ParseFile(_filename);

        // parse node
        if ( spRoot )
        {
            // custom values
            ex::XmlNode::smart_ptr_t spNode = spRoot->findChild("custom");
            if ( spNode )
            {
                for ( uint i = 0; i < spNode->childCount(); ++i )
                {
                    this->parseElement ( spNode->child(i) );
                }
            }
// KEEPME { 
//             // platform dependece values
// #if ( EX_PLATFORM == EX_WIN32 )
//             const char* syntax = "PLATFORM::Win32";
// #elif ( EX_PLATFORM == EX_XENON )
//             const char* syntax = "PLATFORM::Xenon";
// #elif ( EX_PLATFORM == EX_PS3 )
//             const char* syntax = "PLATFORM::PS3";
// #endif
//             spNode = spRoot->findNode(syntax);
//             if ( spNode )
//             {
//                 for ( uint i = 0; i < spNode->childCount(); ++i )
//                 {
//                     this->parseElement ( spNode->child(i) );
//                 }
//             }
// } KEEPME end 
        }
    }
    else
    {
        return EResult::not_found;
    }

    return EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t ConfigParser::parseElement( XmlNode::smart_ptr_t _spNode )
{
    if ( ex::str::icmp ( _spNode->tag(), "xi:include" ) == 0 )
    {
        this->parse ( _spNode->GetAttrValue("href") );
    }
    else
    {
        this->parseValue (_spNode);
    }

    return EResult::ok;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t ConfigParser::parseValue( XmlNode::smart_ptr_t _spNode )
{
    // set value
    set ( _spNode->tag(), 
          _spNode->GetAttrValue("type"), 
          _spNode->GetAttrValue("value") );

    return EResult::ok;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

string_t ConfigParser::expandValue( const string_t& _value )
{
    //
    Array<SubstituteInfo> substituteInfoList; 

    //
    string_t::sz_t start = _value.find( "$(" );
    string_t::sz_t end = _value.find( ')', start );
    while ( start != string_t::sz_t(-1) && end != string_t::sz_t(-1) )
    {
        string_t varName = _value.substr( start+2, end-start-2 );
        value_map_t::iterator iter = m_values.find( string_id_t(varName) );
        if ( iter ==  m_values.end() )
        {
            ex_warning( "can't not found variable %s", varName.c_str() );
            return _value;
        }
        ex_new_in(substituteInfoList) SubstituteInfo((*iter).expanded_value, start,end); 

        start = _value.find( "$(", end );
        end = _value.find( ')', start );
    }

    //
    if ( !substituteInfoList.empty() )
    {
        string_t result;
        for ( Array<SubstituteInfo>::iterator iter = substituteInfoList.begin(); iter != substituteInfoList.end(); ++iter )
        {
            result += (*iter).value + _value.substr( (*iter).end + 1, (iter+1) == substituteInfoList.end() ? -1 : ((*(iter+1)).start - (*iter).end - 1) );
        }
        return result;
    }

    //
    return _value;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ConfigParser::has ( const char* _valueName ) const
{
    value_map_t::c_iterator iter = m_values.find( string_id_t(_valueName) );
    if ( iter != m_values.end() )
    {
        return true;
    }
    return false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ConfigParser::set ( const char* _valueName, const char* _valueType, const char* _valueText, bool _autoGen )
{
    //
    ValueInfo valueInfo;
    valueInfo.autogen = _autoGen;
    valueInfo.type_name = _valueType;
    valueInfo.value_name = _valueName;
    valueInfo.raw_value = _valueText;
    valueInfo.expanded_value = expandValue( _valueText );
    valueInfo.value_ptr = allocValue( _valueType, valueInfo.expanded_value.c_str() );

    //
    value_map_t::iterator iter = m_values.find( string_id_t(_valueName) );
    if ( iter != m_values.end() )
    {
        // NOTE: a value once set as autogen will never go back to non-autogen. 
        valueInfo.autogen = (_autoGen == false) ? (*iter).autogen : _autoGen; 
        valueInfo.id = (*iter).id; // keep the id.
        (*iter).reset();
        (*iter) = valueInfo;
    }
    else
    {
        valueInfo.id = m_count;
        string_id_t varNameID(_valueName);
        m_values.insert( varNameID, valueInfo );

        // increase the count
        m_count = m_values.size();
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void* ConfigParser::allocValue( const char* _typeName, const char* _valueText )
{
    void* pValue = NULL;

    //
    if ( ex::str::ncmp(_typeName, "float", 5) == 0 )
    {
        pValue = ex_malloc( sizeof(float) );
        *(reinterpret_cast<float*>(pValue)) = ex::str::ato<float>(_valueText);
    }
    else if ( ex::str::ncmp(_typeName, "int", 3) == 0 )
    {
        pValue = ex_malloc( sizeof(int) );
        *(reinterpret_cast<int*>(pValue)) = ex::str::ato<int>(_valueText);
    }
    else if ( ex::str::ncmp(_typeName, "bool", 4 ) == 0 )
    {
        pValue = ex_malloc( sizeof(bool) );

        bool value = false;
        if ( ex::str::ncmp(_valueText, "true", 4 ) == 0 )
        {
            value = true;
        }
        else if ( ex::str::ncmp(_valueText, "false", 5 ) == 0 )
        {
            value = false;
        }
        else
        {
            ex_warning( "invalid bool value, set value as false" );
            value = false;
        }
        *(reinterpret_cast<bool*>(pValue)) = value;
    }
    else if ( ex::str::ncmp(_typeName, "string", 6) == 0 )
    {
        size_t size = ex::str::len( _valueText )+1;
        pValue = ex_malloc( sizeof(char) * size );
        ex::mem::set( pValue, 0, sizeof(char) * size  );
        ex::str::ncpy( reinterpret_cast<char*>(pValue), size, _valueText, size );
    }
    else
    {
        ex_warning( "unknown type %s", _typeName );
    }

    return pValue;
}

// #########################
} // end namespace ex 
// #########################

