// ======================================================================================
// File         : Xml.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:21:13 AM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( xml, test, off )
{
    ex::XmlParser parser;
    ex::XmlNode::smart_ptr_t root = parser.ParseFile("d:/Project/Dev/exUtility/src/exlibs/testbed/test.xml");

    if ( root )
    {
        ex::XmlNode::smart_ptr_t node = root->findNode("skeleton::bone"); 
        if ( node )
            printf ( "Found\n" );
    }

#if 0
    if ( root )
    {
        ex::XmlNode::iterator iter(root);
        for ( ex::XmlNode::smart_ptr_t child = iter.first(); child; child = iter.next() )
        {
            printf ( "%s\n", child->tag() );
        }

        ex::uint attr_count = root->attrCount();
        for ( ex::uint i = 0; i < attr_count; ++i )
        {
            printf ( "%s\n", root->getAttr(i) );
        }

        ex::uint child_count = root->childCount();
        for ( ex::uint i = 0; i < child_count; ++i )
        {
            printf ( "%s\n", root->child(i)->tag() );
        }
    }
#else
	
    if ( root )
    {
		// ex::XmlNode::iterator iterEnd = root->end();
        for ( ex::XmlNode::iterator iter = root->begin(root,"skeleton"); iter != root->end(root); iter += "trimesh" )
        {
            printf ( "%s\n", (*iter)->tag() );
        }

        ex::uint attr_count = root->attrCount();
        for ( ex::uint i = 0; i < attr_count; ++i )
        {
            printf ( "Key: %s, value: %s", root->GetAttrByIndex(i).key(), root->GetAttrByIndex(i).GetValue() );
        }

        ex::uint child_count = root->childCount();
        for ( ex::uint i = 0; i < child_count; ++i )
        {
            printf ( "%s\n", root->child(i)->tag() );
        }
    }
#endif
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( xml, saveTest, off )
{
    ex::XmlNode::smart_ptr_t spRoot ( ex_new ex::XmlNode("Root") );

    //
    ex::XmlNode::smart_ptr_t spChild01 = spRoot->newChild( "child_01" );
    spChild01->setAttr( "key01", "value01" );
    spChild01->setAttr( "key02", 10 );
    spChild01->setAttr( "key03", 13.232f );

    spRoot->saveToFile( "TestXmlSave.xml" );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( xml, load, off )
{
    const char* value = NULL;
    int value_int = 0;
    float value_float = 0.0f;

    {
        ex::XmlParser parser;
        ex::XmlNode::smart_ptr_t spRoot = parser.ParseFile( "TestXmlSave.xml" );

        // parse node
        if ( spRoot )
        {
            // root values
            ex::XmlNode::smart_ptr_t spNode = spRoot->findChild("child_01");
            if ( spNode )
            {
                spNode->getAttr( "key01", &value );
                spNode->getAttr( "key02", &value_int );
                spNode->getAttr( "key03", &value_float );
            }
        }

        if ( value )
        {
            CHECK( ex::str::ncmp ( value, "value01", ex::str::len("value01") ) == 0 );
        }
    }

    //
    if ( value )
    {
        CHECK( ex::str::ncmp ( value, "", ex::str::len("") ) == 0 );
    }
}
