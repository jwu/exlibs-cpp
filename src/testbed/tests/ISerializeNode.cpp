// ======================================================================================
// File         : ISerializeNode.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:24 AM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"
#include "exlibs/Serialization/SerializeNode.h"
#include "exlibs/Serialization/XmlSerializeNode.h"
#include "exlibs/Serialization/BinarySerializeNode.h"

///////////////////////////////////////////////////////////////////////////////
// test functions
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace _private { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

template <typename T>
void test_serialize ( const ex::path_t& _path, ex::ISerializeNode* _pSaveNode, T* _pSaves, ex::ISerializeNode* _pLoadNode, T* _pLoads ) 
{
    // ======================================================== 
    // Save 
    // ======================================================== 

    //
    ex::Serialize ( _pSaveNode, "class_node", _pSaves );

    _pSaveNode->saveToFile (_path.c_str());

    // ======================================================== 
    // Load 
    // ======================================================== 

    //
    _pLoadNode->loadFromFile (_path.c_str());

    //
    ex::Serialize ( _pLoadNode, "class_node", _pLoads );
}

// ######################### 
} // end namespace _private 
// ######################### 


///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( XmlSerializeNode, SaveLoad, off )
{
    // ======================================================== 
    // Array 
    // ======================================================== 

    if (0) // SWITCH
    {
        typedef ex::Array<ex::string_t> array_t;

        array_t saves;
        array_t loads;

        saves.push_back ("Hello");
        saves.push_back ("This");
        saves.push_back ("is");
        saves.push_back ("Wu");
        saves.push_back ("Jie");
        saves.push_back ("His");
        saves.push_back ("is");
        saves.push_back ("a");
        saves.push_back ("great");
        saves.push_back ("man");
        saves.push_back ("you");
        saves.push_back ("know");
        saves.push_back ("?");

        //
        ex::XmlSerializeNode saveNode ( ex::XmlNode::smart_ptr_t(ex_new ex::XmlNode("Root") ) );
        ex::XmlSerializeNode loadNode;
        _private::test_serialize ( ex::r_path_t("res://xml/Array.xml").rawfile(), &saveNode, &saves, &loadNode, &loads );

        // check
        CHECK ( saves == loads );

        // result
        printf ( "save value: %s \n", saves.to_str<ex::dec>().c_str() );
        printf ( "load value: %s \n", loads.to_str<ex::dec>().c_str() );
    }

    // ======================================================== 
    // Pool 
    // ======================================================== 

    if (0) // SWITCH
    {
        typedef ex::Pool<ex::string_t> pool_t;

        pool_t saves;
        pool_t loads;

        saves.insert ("Hello");
        saves.insert ("This");
        saves.insert ("is");
        saves.insert ("Wu");
        saves.insert ("Jie");
        saves.insert ("His");
        saves.insert ("is");
        saves.insert ("a");
        saves.insert ("great");
        saves.insert ("man");
        saves.insert ("you");
        saves.insert ("know");
        saves.insert ("?");
        saves.push_at ( 24, "foo");
        saves.push_at ( 28, "bar");

        //
        ex::XmlSerializeNode saveNode ( ex::XmlNode::smart_ptr_t(ex_new ex::XmlNode("Root") ) );
        ex::XmlSerializeNode loadNode;
        _private::test_serialize ( ex::r_path_t("res://xml/Pool.xml").rawfile(), &saveNode, &saves, &loadNode, &loads );

        // check
        CHECK ( saves == loads );

        // result
        printf ( "save value: %s \n", saves.to_str<ex::dec>().c_str() );
        printf ( "load value: %s \n", loads.to_str<ex::dec>().c_str() );
    }

    // ======================================================== 
    // HashMap 
    // ======================================================== 

    if (1) // SWITCH
    {
        typedef ex::HashMap<int, ex::string_t> map_t;

        map_t saves;
        map_t loads;

        saves.insert ( (int)ex::mathop::range_rand(10,1000), "Hello");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "This");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "is");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "Wu");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "Jie");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "His");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "is");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "a");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "great");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "man");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "you");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "know");
        saves.insert ( (int)ex::mathop::range_rand(10,1000), "?");

        //
        ex::XmlSerializeNode saveNode ( ex::XmlNode::smart_ptr_t(ex_new ex::XmlNode("Root") ) );
        ex::XmlSerializeNode loadNode;
        _private::test_serialize ( ex::r_path_t("res://xml/HashMap.xml").rawfile(), &saveNode, &saves, &loadNode, &loads );

        // check
        CHECK ( saves == loads );

        // result
        printf ( "save value: %s \n", saves.to_str<ex::dec>().c_str() );
        printf ( "load value: %s \n", loads.to_str<ex::dec>().c_str() );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( BinarySerializeNode, SaveLoad, off )
{
    typedef ex::Array<ex::string_t> array_t;

    array_t saves;
    array_t loads;

    saves.push_back ("Hello");
    saves.push_back ("This");
    saves.push_back ("is");
    saves.push_back ("Wu");
    saves.push_back ("Jie");
    saves.push_back ("His");
    saves.push_back ("is");
    saves.push_back ("a");
    saves.push_back ("great");
    saves.push_back ("man");
    saves.push_back ("you");
    saves.push_back ("know");
    saves.push_back ("?");

    //
    ex::BinarySerializeNode saveNode (512);
    ex::BinarySerializeNode loadNode;
    _private::test_serialize ( ex::r_path_t("res://xml/Array.bin").rawfile(), &saveNode, &saves, &loadNode, &loads );

    // ======================================================== 
    // checks 
    // ======================================================== 

    CHECK ( saves == loads );

    printf ( "loaded value: %s \n", loads.to_str<ex::dec>().c_str() );
}
