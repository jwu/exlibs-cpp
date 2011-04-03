// ======================================================================================
// File         : TestRegistry.cpp
// Author       : Wu Jie 
// Last Change  : 01/08/2010 | 23:42:29 PM | Friday,January
// Description  : This is a modified version of CppUnitLite
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"

#include "Test.h"
#include "TestResult.h"
#include "TestRegistry.h"

///////////////////////////////////////////////////////////////////////////////
// static function defines 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TestRegistry::addTest (Test *test) 
{
	instance().add(test);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TestRegistry::runAllTests (TestResult& result) 
{
	instance().run(result);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TestRegistry::runTest ( const std::string& _testName, TestResult& result )
{
	instance().run( _testName, result );
}

///////////////////////////////////////////////////////////////////////////////
// member function defines 
///////////////////////////////////////////////////////////////////////////////


// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TestRegistry& TestRegistry::instance () 
{
	static TestRegistry registry;
	return registry;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TestRegistry::add (Test *test) 
{
	tests.push_back(test);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TestRegistry::run (TestResult& result) 
{
	result.startTests();
	for ( std::vector<Test *>::iterator it = tests.begin (); it != tests.end (); ++it )
		(*it)->run(result);
	result.endTests();
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TestRegistry::run ( const std::string& _testName, TestResult& result ) 
{
	result.startTests();
    std::string test_name_on = _testName + "_on";
	for ( std::vector<Test *>::iterator it = tests.begin (); it != tests.end (); ++it )
    {
        if ( (*it)->name == test_name_on )
            (*it)->run(result);
    }
	result.endTests();
}
