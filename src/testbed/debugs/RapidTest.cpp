// ======================================================================================
// File         : RapidTest.cpp
// Author       : Wu Jie 
// Last Change  : 09/26/2009 | 11:20:29 AM | Saturday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

typedef ex::Seq<ex::uint,float,double>::typelist_t   priority_t;

template < typename T1, typename T2 >
class TTypeSelector
{
public:
    typedef typename ex::typeop::Select< (ex::typelist::IndexOf<priority_t,T1>::value > ex::typelist::IndexOf<priority_t,T2>::value), T1, T2 >::result_t result_t;
};

///////////////////////////////////////////////////////////////////////////////
// class TTestClass 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class TTestClass 
{
public:

    TTestClass () {}
    ~TTestClass () {}

    template < typename U >
    U Test (); 
    // { return U(m_Value); }

    T m_Value;

    //
	void test_string( const ex::string_id_t& _test )
    {
        printf ( _test.c_str() );
    }

}; // end class TTestClass

template < typename T >
template < typename U >
U TTestClass<T>::Test () { return U(m_Value); }

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////


class Soldier { public: virtual ~Soldier() {} };
class Monster { public: virtual ~Monster() {} };
class SuperMonster { public: virtual ~SuperMonster() {} };

class SillySoldier : public Soldier {};
class SillyMonster : public Monster {};
class SillySuperMonster : public SuperMonster {};

class BadSoldier : public Soldier {};
class BadMonster : public Monster {};
class BadSuperMonster : public SuperMonster {};

typedef ex::AbstractFactory<ex::Seq<Soldier, Monster, SuperMonster>::typelist_t > AbstractEnemyFactory_t; 
typedef ex::ConcreteFactory<AbstractEnemyFactory_t, ex::UnitCreator_ex_new, ex::Seq<SillySoldier, SillyMonster, SillySuperMonster>::typelist_t > EasyLevelEnemyFactory_t;
typedef ex::ConcreteFactory<AbstractEnemyFactory_t, ex::UnitCreator_ex_new, ex::Seq<BadSoldier, BadMonster, BadSuperMonster>::typelist_t > HardLevelEnemyFactory_t;

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( Rapid, Rapid, off )
{
    EX_HW_BREAK();

    // TTypeSelector<ex::uint,float>::result_t test;
    TTypeSelector<ex::uint,float >::result_t test;
	printf ( "My Type Is: %s\n", ex::typeop::type_name( test ).c_str() );

    //
    ex::uint32 hash_value = ex::hash_use (EX_HASH_CRC, "hello" );

    TTestClass<int> testClass;
    testClass.test_string( ex::string_id_t("hello") );

    AbstractEnemyFactory_t* pEasyFactory = ex_new EasyLevelEnemyFactory_t;
    AbstractEnemyFactory_t* pHardFactory = ex_new HardLevelEnemyFactory_t;
    Soldier* pSoldier;

    pSoldier = pEasyFactory->create<Soldier>();
    ex_delete (pSoldier);
    pSoldier = pHardFactory->create<Soldier>();
    ex_delete (pSoldier);

    ex_delete (pEasyFactory);
    ex_delete (pHardFactory);

    ex::GenScatterHierarchy< ex::Seq<int,ex::uint32,ex::uint64>::typelist_t, TTestClass > hchy;
    TTestClass<int>& test_int = hchy;
    test_int.m_Value = 1;
    TTestClass<ex::uint32>& test_uint32 = hchy;
    test_uint32.m_Value = 2;
    TTestClass<ex::uint64>& test_uint64 = hchy;
    test_uint64.m_Value = 3;

    TTestClass<float> test1;
    test1.m_Value = 20.0f;
    int test_var = test1.Test<int>();

    int a = 20;
    int b = 30;
	const int c = 0;
    ex::_private::AccessTraits<const int&>::parameter_t d = b;
    typedef ex::Tuple<const int&, int> tuple_t; 

    tuple_t tuple1 ( a, b ); 
    tuple_t tuple2 = ex::tuple::MakeTuple( ex::CRef(a), b );      // creates tuple<const A&, B>

    printf ( "a = %d, b = %d \n", ex::tuple::get<0>(tuple2), ex::tuple::get<1>(tuple2) );
    printf ( "a = %d, b = %d \n", tuple2.get<0>(), tuple2.get<1>() );

#if 0
    typedef ex::List<int> test_t; 
    test_t array;
    array.push_back (0 );
    array.push_back (1 );
    array.push_back (2 );
    array.push_back (3 );
    array.push_back (4 );
    array.push_back (5 );
    array.push_back (6 );
    array.push_back (7 );
    array.push_back (8 );
    array.push_back (9 );
    array.push_back (10);
    array.push_back (11);
    array.push_back (12);
    array.push_back (13);
    array.push_back (14);
    array.push_back (15);
    array.push_back (16);

    test_t::iterator iter = array.begin(); 
    while ( iter != array.end() )
    {
        iter = array.erase (iter);
    }
#endif

    typedef ex::HashMap<int,float> test_t; 
    test_t testCont;
    testCont.insert (0 , 1.0f );
    testCont.insert (1 , 1.1f );
    testCont.insert (2 , 1.2f );
    testCont.insert (3 , 1.3f );
    testCont.insert (4 , 1.4f );
    testCont.insert (5 , 1.5f );
    testCont.insert (6 , 1.6f );
    testCont.insert (7 , 1.7f );
    testCont.insert (8 , 1.8f );
    testCont.insert (9 , 1.9f );
    testCont.insert (10, 1.10f );
    testCont.insert (11, 1.11f );
    testCont.insert (12, 1.12f );
    testCont.insert (13, 1.13f );
    testCont.insert (14, 1.14f );
    testCont.insert (15, 1.15f );
    testCont.insert (16, 1.16f );

#if 1
    test_t::iterator iter = testCont.find(8); 
    test_t::iterator iterLast = testCont.find(10); 
#else
    test_t::iterator iter = testCont.begin();
    test_t::iterator iterLast = testCont.end();
#endif

    testCont.erase (iter,iterLast);
#if 0
    while ( iter != testCont.end() )
    {
        iter = testCont.erase (iter);
    }
#endif
}
