// ======================================================================================
// File         : registry.hpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 15:04:19 PM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// register debugs 
///////////////////////////////////////////////////////////////////////////////

{
    // ======================================================== 
    // debuging 
    // ======================================================== 

    TestResult tr;
    TestRegistry::runTest( "Rapid", tr);

    TestRegistry::runTest( "uid_t", tr);
    TestRegistry::runTest( "easingCurve", tr);

    TestRegistry::runTest( "Thread", tr);
    TestRegistry::runTest( "MemMng", tr);
    TestRegistry::runTest( "IFile", tr);
    TestRegistry::runTest( "Resource", tr);

    TestRegistry::runTest( "RuntimeClass", tr);
    TestRegistry::runTest( "TDelegate", tr);
    TestRegistry::runTest( "Functor", tr);
    TestRegistry::runTest( "TMemberPtr", tr);

    TestRegistry::runTest( "iterator", tr);
    TestRegistry::runTest( "Array", tr);
    TestRegistry::runTest( "HashMap", tr);
    TestRegistry::runTest( "HashMultiMap", tr);
    TestRegistry::runTest( "List", tr);
    TestRegistry::runTest( "TProperty", tr);
    TestRegistry::runTest( "TRecyclePool", tr);
    TestRegistry::runTest( "TQuadTree", tr);
    TestRegistry::runTest( "T_Intersection", tr);

    TestRegistry::runTest( "expat", tr);
    TestRegistry::runTest( "ConfigParser", tr);
    TestRegistry::runTest( "xml", tr);
    TestRegistry::runTest( "libyaml", tr);

    TestRegistry::runTest( "sdl_input", tr);
}

