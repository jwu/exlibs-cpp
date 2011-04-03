// ======================================================================================
// File         : uid.h
// Author       : Wu Jie 
// Last Change  : 03/21/2010 | 17:54:32 PM | Sunday,March
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef UID_H_1269165274
#define UID_H_1269165274
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class UID 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL UID
{
    typedef UID self_t;

    template < typename U > friend struct Hash;

    ///////////////////////////////////////////////////////////////////////////////
    // static member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    static UID null;
    static UID gen_uid ();

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // use uid_t::gen_uid() to get a uid. 
    UID ();
    UID ( const UID& _uid );
    UID ( uint64 _id );

    uint64 id() const { return m_ID; }
    void set_id ( uint64 _id ) { m_ID = _id; }

    //
    INLINE self_t& operator = ( const self_t& _other ) { m_ID = _other.m_ID; return *this; }

    INLINE bool operator == ( const self_t& _other ) const { return m_ID == _other.m_ID; }
    INLINE bool operator != ( const self_t& _other ) const { return m_ID != _other.m_ID; }
    INLINE bool operator <  ( const self_t& _other ) const { return m_ID <  _other.m_ID; }
    INLINE bool operator <= ( const self_t& _other ) const { return m_ID <= _other.m_ID; }
    INLINE bool operator >  ( const self_t& _other ) const { return m_ID >  _other.m_ID; }
    INLINE bool operator >= ( const self_t& _other ) const { return m_ID >= _other.m_ID; }

    ///////////////////////////////////////////////////////////////////////////////
    // protected
    ///////////////////////////////////////////////////////////////////////////////

protected:

    void GenerateID();

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string = ex::to_str<FLAGS>(m_ID);
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("uid_t");
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    uint64  m_ID;

}; // end class UID

///////////////////////////////////////////////////////////////////////////////
// typedefs
///////////////////////////////////////////////////////////////////////////////

typedef UID uid_t;

///////////////////////////////////////////////////////////////////////////////
// Hash instance
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: typedef hash function 
// ------------------------------------------------------------------

template <>
struct Hash<uid_t> 
{
    INLINE uint operator () ( const uid_t & _value ) const { return (uint32)_value.m_ID; }
}; // end struct Hash<uid_t>

// ######################### 
} // end namespace ex 
// ######################### 


// #################################################################################
#endif // END UID_H_1269165274
// #################################################################################


