// ======================================================================================
// File         : TProperty.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:58 AM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

template < typename T, typename T2 >
class T_TypeParser
{
public:
    T_TypeParser ( T _param, T2 _param2 ) {}

    typedef T type_t;
}; // end class T_TypeParser

template < typename T, typename T2 >
void T_Func (  T _param, T2 _param2  )
{
    T_TypeParser <T,T2> (_param, _param2 );
}

class CTestProperty
{
public:
    ex::Array<int> m_Array;
};

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( TProperty, create, off )
{
    // T_TypeParser<int>( i, j ) typeParser;
    T_Func ( 1, 2 );

#if 0
    ex::PropertyBase* pProperty = ex_new ex::MemberProperty< ClassProbe, const char*>( "Test", &ClassProbe::Name );
    ex_delete (pProperty);
#endif

    // ======================================================== 
    // 
    // ======================================================== 

    ex::PropertyBase* pProperty = ex::CreateMemberProperty< ex::Managed<EX_ALLOCATOR>::TAllocator > ( "Test", "Test", &ClassProbe::Name ); // ex_new ex::MemberProperty< ClassProbe, const char*>( "Test", &ClassProbe::Name );
    ex::DestroyProperty< ex::Managed<EX_ALLOCATOR>::TAllocator > (pProperty);

    // ======================================================== 
    // 
    // ======================================================== 

    CTestProperty obj;
    obj.m_Array.push_back (1);
    obj.m_Array.push_back (2);
    obj.m_Array.push_back (3);
    obj.m_Array.push_back (4);
    obj.m_Array.push_back (5);
    obj.m_Array.push_back (6);

    ex::PropertyBase* pProperty2 = ex::CreateMemberProperty< ex::Managed<EX_ALLOCATOR>::TAllocator > ( "Array", "Array", &CTestProperty::m_Array ); // ex_new ex::MemberProperty< ClassProbe, const char*>( "Test", &ClassProbe::Name );

    ex::PropertyInstanceBase::smart_ptr_t pPropInstance = pProperty2->createPropertyInstance_sp(&obj); 

    ex::DestroyProperty< ex::Managed<EX_ALLOCATOR>::TAllocator > (pProperty2);
}
