// ======================================================================================
// File         : registry.hpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 15:04:25 PM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// register tests 
///////////////////////////////////////////////////////////////////////////////

{
    // ======================================================== 
    // testing 
    // ======================================================== 

    TestResult tr;
    // TestRegistry::runAllTests(tr);

    // ======================================================== 
    // Test Math 
    // ======================================================== 

    // TODO: TestRegistry::runTest( "Vector", tr);

    // ======================================================== 
    // Test scripts 
    // ======================================================== 

    TestRegistry::runTest( "lua", tr);

    // ======================================================== 
    // Test System 
    // ======================================================== 

    // TODO: TestRegistry::runTest( "MemMng", tr);
    // TODO: TestRegistry::runTest( "File", tr);
    TestRegistry::runTest( "mathop", tr);
    TestRegistry::runTest( "futil", tr);
    TestRegistry::runTest( "fsys", tr);
    TestRegistry::runTest( "fsys_watcher", tr);

    // ======================================================== 
    // Test Time
    // ======================================================== 

    TestRegistry::runTest( "Date", tr);
    TestRegistry::runTest( "TimeSpan", tr);
    TestRegistry::runTest( "DayTime", tr);
    TestRegistry::runTest( "DateTime", tr);
    TestRegistry::runTest( "CpuClock", tr);
    TestRegistry::runTest( "Timer", tr);

    // ======================================================== 
    // Test Design Pattern 
    // ======================================================== 

    // TODO: TestRegistry::runTest( "TDelegate", tr);
    // TODO: TestRegistry::runTest( "Functor", tr);
    TestRegistry::runTest( "SmartPtr", tr);
    TestRegistry::runTest( "WeakPtr", tr);
    // TODO: TestRegistry::runTest( "DataHolder", tr);
    // TODO: TestRegistry::runTest( "RuntimeClass", tr);
    // TODO: TestRegistry::runTest( "TProperty", tr);
    TestRegistry::runTest( "TypeTraits", tr);
    // TODO: TestRegistry::runTest( "TMemberPtr", tr);

    // ======================================================== 
    // Test XML 
    // ======================================================== 

    // TODO: TestRegistry::runTest( "XmlNode", tr);
    // TODO: TestRegistry::runTest( "XmlParser", tr);
    // TODO: TestRegistry::runTest( "ConfigParser", tr);

    // ======================================================== 
    // Test Yaml 
    // ======================================================== 

    TestRegistry::runTest( "CYamlParser", tr);

    // ======================================================== 
    // Test String 
    // ======================================================== 

    TestRegistry::runTest( "c_str", tr);
    TestRegistry::runTest( "String", tr);
    TestRegistry::runTest( "Path", tr);
    TestRegistry::runTest( "StringID", tr);

    // ======================================================== 
    // Test Container 
    // ======================================================== 

    TestRegistry::runTest( "Array", tr);
    TestRegistry::runTest( "Pool", tr);
    // TODO: TestRegistry::runTest( "TRecyclePool", tr);
    // TODO: TestRegistry::runTest( "List", tr);
    // TODO: TestRegistry::runTest( "HashMap", tr);
    // TODO: TestRegistry::runTest( "HashMultiMap", tr);
    // TODO: TestRegistry::runTest( "iterator", tr);

    // ======================================================== 
    // Test serialize 
    // ======================================================== 

    TestRegistry::runTest( "XmlSerializeNode", tr);
    TestRegistry::runTest( "BinarySerializeNode", tr);
}

