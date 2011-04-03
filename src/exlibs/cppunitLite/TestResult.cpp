// ======================================================================================
// File         : TestResult.cpp
// Author       : Wu Jie 
// Last Change  : 01/08/2010 | 23:42:42 PM | Friday,January
// Description  : This is a modified version of CppUnitLite
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"

#include "TestResult.h"
#include "Failure.h"
#include <iostream>


// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TestResult::testWasRun()
{
	++testCount;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TestResult::startTests () 
{
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TestResult::addFailure( Failure failure ) 
{
	using namespace std;

	cout << failure << endl;
	failureCount++;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void TestResult::endTests () 
{
	using namespace std;

	cout << testCount << " tests run" << endl;
	if (failureCount > 0)
		cout << "There were " << failureCount << " failures" << endl;
	else
		cout << "There were no test failures" << endl;
}
