// ======================================================================================
// File         : XmlNode.cpp
// Author       : Wu Jie 
// Last Change  : 10/19/2008 | 22:18:01 PM | Sunday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "XmlNode.h"

// #########################
namespace ex { 
// #########################

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

XmlNode::XmlNode( const char* _pTagName )
    : m_Tag(_pTagName)
{
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

XmlNode::~XmlNode()
{
    m_Children.clear();
    m_Attributes.clear();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

XmlNode::smart_ptr_t XmlNode::clone () const
{
    XmlNode::smart_ptr_t spNewNode = XmlNode::smart_ptr_t( ex_new XmlNode( this->tag() ) );

    // copy attributes and set content from current node
    spNewNode->copyAttrsFrom( XmlNode::smart_ptr_t( const_cast<XmlNode*>(this) ) );
    spNewNode->SetContent( this->GetContent() );

    // copy children.
    for ( xml_nodes_t::c_iterator iter = m_Children.begin(); iter != m_Children.end(); ++iter )
    {
        spNewNode->addChild ( (*iter)->clone() );
    }

    return spNewNode;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlNode::addChild( const XmlNode::smart_ptr_t& _spNode )
{
    ex_assert( _spNode != NULL, "Null smart pointer" );
    m_Children.push_back(_spNode);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlNode::addChild( const char* _tagName, const XmlNode::smart_ptr_t& _spNode )
{
    XmlNode::smart_ptr_t spCloneNode = _spNode->clone();
    spCloneNode->SetTag(_tagName);

    this->addChild(spCloneNode);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

XmlNode::smart_ptr_t XmlNode::newChild( const char* _tagName )
{
    XmlNode::smart_ptr_t spNode = XmlNode::smart_ptr_t( ex_new XmlNode(_tagName) );
    addChild(spNode);
    return spNode;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

bool XmlNode::removeChild( uint _idx )
{
    if ( _idx < childCount() )
    {
        m_Children.erase_at(_idx);
        return true;
    }
    return false;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

bool XmlNode::removeChild( const XmlNode::smart_ptr_t& _spNode )
{
    xml_nodes_t::iterator iter = m_Children.find(_spNode);
    if ( iter != m_Children.end() )
    {
        m_Children.erase(iter);
        return true;
    }
    return false;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

XmlNode::smart_ptr_t XmlNode::findChild( const char* _tagName ) const
{
    for ( xml_nodes_t::c_iterator iter = m_Children.begin(); iter != m_Children.end(); ++iter )
    {
        if ( (*iter)->isTag(_tagName) )
            return *iter;
    }
    return XmlNode::smart_ptr_t(NULL); 
}


// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 


uint XmlNode::firstChild( const char* _tagName ) const
{
    xml_nodes_t::c_iterator iter = m_Children.begin();
    xml_nodes_t::c_iterator iterEnd = m_Children.end();

    uint idx = 0;
    for ( ; iter != iterEnd; ++iter, ++idx )
    {
        if ( (*iter)->isTag(_tagName) )
            return idx;
    }
    return this->childCount();
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

XmlNode::smart_ptr_t XmlNode::findNode( const string_t _syntax ) const
{
    static const char* separateFlag = "::";
    string_t tag = _syntax;
    string_t tagChain = "";

    // separateFlag
    string_t::sz_t idx = _syntax.findFirstOf(separateFlag);
    if ( idx != string_t::sz_t(IndexNone) )
    {
        tag = _syntax.left(idx);
        tagChain = _syntax.right( idx + ex::str::len(separateFlag) );
    }

    // find the tag first
    XmlNode::smart_ptr_t spNode;
    xml_nodes_t::c_iterator iter = m_Children.begin();
    xml_nodes_t::c_iterator iterEnd = m_Children.end();
    for ( ; iter != iterEnd; ++iter )
    {
        if ( (*iter)->isTag(tag.c_str()) )
        {
            if ( tagChain == "" )
                return (*iter);
            else
                spNode = (*iter)->findNode(tagChain);
        }

        // if we found, return it
        if ( spNode )
            return spNode;
    }
    return spNode;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

XmlNode::smart_ptr_t XmlNode::child( uint _idx ) const
{
    return m_Children[_idx]; 
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

uint XmlNode::childCount( const char* _tagName ) const
{
    uint count = 0;
    for ( xml_nodes_t::c_iterator iter = m_Children.begin(); iter != m_Children.end(); ++iter )
    {
        if ( (*iter)->isTag(_tagName) )
            ++count;
    }
    return count;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlNode::ReserveAttr( uint _count )
{
    m_Attributes.reserve(_count);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void XmlNode::SetAttrGeneric ( const char* _key, const char* _value )
{
    xml_attributes_t::iterator iter = ex::find( m_Attributes.begin(), m_Attributes.end(), _key );

    // new attribute
    if ( iter == m_Attributes.end() )
    {
        ex_new_in(m_Attributes) XmlAttribute(_key,_value); 
    }
    else
    {
        (*iter).SetValue(_value);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlNode::GetAttrGeneric ( const char* _key, const char** _pValue ) const
{
    //
    xml_attributes_t::c_iterator iter = ex::find( m_Attributes.begin(), m_Attributes.end(), _key );
    if ( iter == m_Attributes.end() )
    {
        return EResult::not_found;
    }

    //
    *_pValue = (*iter).GetValue();

    //
    return EResult::ok;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

const char* XmlNode::GetAttrValue( const char* _key ) const
{
	xml_attributes_t::c_iterator iter = ex::find( m_Attributes.begin(), m_Attributes.end(), _key  );

    //
    if ( iter != m_Attributes.end() ) 
        return (*iter).GetValue();

    return "";
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

const char* XmlNode::GetAttrValue( uint _idx ) const
{
    return m_Attributes[_idx].GetValue();
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

uint XmlNode::hasAttr( const char* _key ) const
{
	xml_attributes_t::c_iterator iter = ex::find( m_Attributes.begin(), m_Attributes.end(), _key  );

    //
    if ( iter != m_Attributes.end() ) 
        return uint(m_Attributes.index(iter));

    return uint(ex::IndexNone);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

bool XmlNode::removeAttr( const char* _key )
{
	xml_attributes_t::iterator iter = ex::find( m_Attributes.begin(), m_Attributes.end(), _key  );

    //
    if ( iter != m_Attributes.end() ) 
    {
        m_Attributes.erase(iter);
        return true;
    }

    return false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlNode::copyAttrsFrom ( const XmlNode::smart_ptr_t& _spNode )
{
    const xml_attributes_t& srcAttrs = _spNode->attrs();
    for ( xml_attributes_t::c_iterator iter = srcAttrs.begin(); iter != srcAttrs.end(); ++iter )
    {
        this->setAttr( (*iter).key(), (*iter).GetValue() );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlNode::saveToFile ( const char* _fileName ) const
{
    result_t eResult = EResult::ok;

    IFile::smart_ptr_t spFile = futil::file::replace<PhysicalFile>(_fileName);
    if ( spFile )
    {
        // first write xml header
        string_t line =  "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
        spFile->write ( line.c_str(), line.size() );

        // write the contents
        eResult = this->saveToFile ( spFile );
    }
    else
    {
        eResult = EResult::create_failed;
    }
    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t XmlNode::saveToFile ( IFile::smart_ptr_t _spFile, uint _level ) const
{
    result_t eResult = EResult::ok;
    futil::sz_t bytesWritten;

    // add tabs.
    string_t line;
    for ( uint i = 0; i < _level; ++i )
    {
        line += "\t";
    }

    //
    line += "<";
    line += m_Tag.c_str();

    // put attributes.
    for ( xml_attributes_t::c_iterator iter = m_Attributes.begin(); iter != m_Attributes.end(); ++iter )
    {
        line += " ";
        line += (*iter).key();
        line += "=\"";
        string_t value;
        XmlNode::FormatXmlString( (*iter).GetValue(), &value );
        line += value;
        line += "\"";
    }

    //
    if ( m_Content.empty() && m_Children.empty() )
    {
        line += " />\n";
        bytesWritten = _spFile->write ( line.c_str(), line.size() );
        if ( bytesWritten != line.size() )
            eResult = EResult::write_failed; 
        return eResult;
    }

    // put node content
    line += ">";
    line += m_Content;

    // recursively write children into file
    if ( !m_Children.empty() ) 
    {
        line += "\n"; 
        bytesWritten = _spFile->write ( line.c_str(), line.size() );
        line.clear();

        // put sub nodes.
        for ( xml_nodes_t::c_iterator iter = m_Children.begin(); iter != m_Children.end(); ++iter )
        {
            eResult = (*iter)->saveToFile( _spFile, _level + 1 );
        }

        // end tag.
        for ( uint i = 0; i < _level; ++i )
        {
            line += "\t";
        }

        //
        if ( bytesWritten != line.size() )
            eResult = EResult::write_failed; 
    }

    line += string_t("</") + m_Tag.c_str() + string_t(">\n");
    bytesWritten = _spFile->write ( line.c_str(), line.size() );

    //
    if ( bytesWritten != line.size() )
        eResult = EResult::write_failed; 
    return eResult;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void XmlNode::FormatXmlString ( const char* _input, string_t* _pResult )
{
    if ( _input )
    {
        for ( uint i = 0; _input[i] != '\0'; ++i )
        {
            switch ( _input[i] )
            {
            case '<' :
                (*_pResult) += "&lt;";
                break;

            case '>':
                (*_pResult) += "&gt;";
                break;

            case '&':
                (*_pResult) += "&amp;";
                break;

            case '\"':
                (*_pResult) += "&quot;";
                break;

            case '\'':
                (*_pResult) += "&apos;";
                break;

            default:
                (*_pResult).push_back(_input[i]);
                break;
            }
        }
    }
}

// #########################
} // end namespace ex 
// #########################

