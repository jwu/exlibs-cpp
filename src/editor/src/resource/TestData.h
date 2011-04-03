// ======================================================================================
// File         : TestData.h
// Author       : Wu Jie 
// Last Change  : 08/29/2010 | 09:54:55 AM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef TESTDATA_H_1283046897
#define TESTDATA_H_1283046897
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// class TestData 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class TestData : public ex::PropertyObject
{
    EX_DECL_PROPERTY_OBJECT ( TestData, ex::PropertyObject )

public:

    TestData ();        
    virtual ~TestData ();        

    void setID ( int _id ) { m_ID = _id; }
    int ID () const { return m_ID; }

    void setTag ( const ex::string_t& _tag ) { m_tag = _tag; }
    const ex::string_t& tag () const { return m_tag; }

protected:

    int             m_ID;
    ex::string_t    m_tag;

    int     m_action;
    int     m_magic;
    float   m_hp;
    float   m_mp;

}; // end class TestData

// #################################################################################
#endif // END TESTDATA_H_1283046897
// #################################################################################


