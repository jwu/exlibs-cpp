// ======================================================================================
// File         : TestResult.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:29:39 AM | Tuesday,August
// Description  : This is a modified version of CppUnitLite
// ======================================================================================

// #################################################################################
#ifndef TESTRESULT_H_1250526585
#define TESTRESULT_H_1250526585
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// forward decls 
///////////////////////////////////////////////////////////////////////////////

class Failure;

///////////////////////////////////////////////////////////////////////////////
// class 
// 
// Purpose: 
//  TestResult is a simple little class which accepts notifications from
//  tests.  In its current form, it takes these notifications and prints
//  them on the standard output.
//
//  If you need different behavior, you can alter it in place or subclass 
//  TestResult to provide it.  The TestResult hierarchy can be as simple
//  or complex as you require to support your application.
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL TestResult
{
public:
    TestResult () 
        : failureCount (0), 
          testCount(0) 
    {
    }

    //
	void testWasRun ();
	void startTests ();
	void addFailure (Failure failure);
	void endTests ();

private:
	int failureCount;
	int testCount;

}; // end class TestResult

// #################################################################################
#endif // END TESTRESULT_H_1250526585
// #################################################################################

