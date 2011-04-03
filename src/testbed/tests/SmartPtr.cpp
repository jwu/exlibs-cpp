// ======================================================================================
// File         : SmartPtr.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:21:01 AM | Saturday,September
// Description  : 
// ======================================================================================

// TODO: make it better

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

class CTestCallback
{
public:
    static void OnRelease ( void* _pTest )
    {
        printf ("OnRelease\n");
        ex_delete ((CTestCallback*)_pTest);
    }
}; // end

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( WeakPtr, normal, off )
{
    printf ( " WeakPtr Normal Test\n" );

    ex::SmartPtr<ClassProbe> sp;
    {
        //
        ex::SmartPtr<ClassProbe> sp1( ex_new ClassProbe("SP_01") );
        ex::WeakPtr<ClassProbe> wp1(sp1);
        sp = wp1;
        // ClassProbe* pClassProbe = sp1.ptr();

        // test if (sp)
        CHECK( sp1 );
        CHECK( wp1 );
        CHECK( wp1 == sp1 );
        CHECK( sp1 == wp1 );

        // copy
        ex::SmartPtr<ClassProbe> sp2 = sp1;
        ex::SmartPtr<ClassProbe> sp3( ex_new ClassProbe("SP_02") );

        //
        CHECK( sp1 == sp2 );
        CHECK( sp1 != sp3 );

        ex::WeakPtr<ClassProbe> wp2(sp2);
        ex::WeakPtr<ClassProbe> wp3(sp3);

        CHECK( wp1 == wp2 );
        CHECK( wp1 != wp3 );

        CHECK( wp1 == sp2 );
        CHECK( wp2 == sp1 );
        CHECK( wp1 != sp3 );
        CHECK( sp3 != wp1 );

        // test if remove sp3 manually
        // sp3.~SmartPtr(); // <== this will lead to crash after "Finish\n"
        // sp3 = ex::SmartPtr<ClassProbe>();
        ex::SmartPtr<ClassProbe> sp4 = sp3;
        sp3.m_release();
        sp4.m_release();

        printf ("scope in end\n");
    }
    printf ("scope out end\n");
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( SmartPtr, Callback, off )
{
	typedef ex::SmartPtr< CTestCallback, ex::RefCounted, &CTestCallback::OnRelease > callback_smart_ptr_t;
    {
        callback_smart_ptr_t spCallback ( ex_new CTestCallback );
        callback_smart_ptr_t spCallback2 = spCallback;
        spCallback = spCallback2; 
        callback_smart_ptr_t spCallback3( ex_new CTestCallback );
    }

    typedef ex::SmartPtr< CTestCallback > smart_ptr_t;
    {
        smart_ptr_t sp ( ex_new CTestCallback );
        smart_ptr_t sp2 = sp;
        // smart_ptr_t sp3();
        sp = sp2;
    }

}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( SmartPtr, Normal, off )
{
    // test_fun<int>(20);

    printf ( " SmartPtr Normal Test\n" );

    {
        //
        ex::SmartPtr<ClassProbe> sp1( ex_new ClassProbe("SP_01") );
        // ClassProbe* pClassProbe = sp1.ptr();

        // test if (sp)
        CHECK( sp1 );

        // copy
        ex::SmartPtr<ClassProbe> sp2 = sp1;
        ex::SmartPtr<ClassProbe> sp3( ex_new ClassProbe("SP_02") );

        //
        CHECK( sp1 == sp2 );
        CHECK( sp1 != sp3 );

        // test if remove sp3 manually
        // sp3.~SmartPtr(); // <== this will lead to crash after "Finish\n"
        // sp3 = ex::SmartPtr<ClassProbe>();
        ex::SmartPtr<ClassProbe> sp4 = sp3;
        sp3.m_release();
        sp4.m_release();

        printf ("Finish\n");
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( SmartPtr, DynamicCast, off )
{
    ex::IFile::smart_ptr_t spFile ( ex_new ex::TextFile() );
    spFile.cast<ex::TextFile>()->close();
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( DataHolder, Normal, off )
{
    {
        ex::DataHolder dataHolder1;
        ex::DataHolder dataHolder2;

        dataHolder1.alloc( sizeof(char)*10 );
        dataHolder2.alloc( sizeof(char)*20 );

        {
            ex::DataHolder dataHolder1_copy(dataHolder1);
            ex::DataHolder dataHolder2_copy(dataHolder2);
        }
    }

}
