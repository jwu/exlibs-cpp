// ======================================================================================
// File         : TestRegistry.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:29:21 AM | Tuesday,August
// Description  : This is a modified version of CppUnitLite
// ======================================================================================

// #################################################################################
#ifndef TESTREGISTRY_H_1250526570
#define TESTREGISTRY_H_1250526570
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include <vector>

///////////////////////////////////////////////////////////////////////////////
// forward decls 
///////////////////////////////////////////////////////////////////////////////

class Test;
class TestResult;

///////////////////////////////////////////////////////////////////////////////
// class TestRegistry 
// 
// Purpose: 
//  TestRegistry is a primitive singleton which collects all of the
//  tests in a system and allows them to be executed.  To see how
//  tests are added to the TestRegistry look at the Test.h file
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL TestRegistry
{
public:
	static void addTest ( Test *test );
	static void runAllTests ( TestResult& result );
	static void runTest ( const std::string& _testName, TestResult& result );

private:

	static TestRegistry&	instance ();
	void					add ( Test *test );
	void					run ( TestResult& result );
	void					run ( const std::string& _testName, TestResult& result );

	std::vector<Test *>		tests;

}; // end class TestRegistry

// #################################################################################
#endif // END TESTREGISTRY_H_1250526570
// #################################################################################
