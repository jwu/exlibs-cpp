// ======================================================================================
// File         : StringID.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:26:44 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef STRINGID_H_1250526407
#define STRINGID_H_1250526407
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class StringID 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// TODO: change StringID<T> to StringID but only use wchar

template < typename T >
class StringID
{
    template < typename U > friend struct Hash;

    ///////////////////////////////////////////////////////////////////////////////
    // public typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef StringID<T> self_t;
    typedef String<T,Managed<EX_ALLOCATOR>::TAllocator> str_t;
    typedef HashSet< str_t,
                     Hash<str_t>,
                     EqualTo<str_t>,
                     Managed<EX_ALLOCATOR>::TAllocator > string_set_t;

    ///////////////////////////////////////////////////////////////////////////////
    // static members
    ///////////////////////////////////////////////////////////////////////////////

    EX_LIBS_DLL static self_t null;

    // NOTE: string id registry must in init, before s_pStringSet created.
    EX_LIBS_DLL static self_t s_folder;
    EX_LIBS_DLL static self_t s_config;
    EX_LIBS_DLL static self_t s___root__;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    StringID();
    StringID( const self_t& _copy );
    explicit StringID( const char* _str );
    explicit StringID( const str_t& _string );
    ~StringID();

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    INLINE bool isValid () const;

    // ========================================================
    // Set
    // ========================================================

    //
    INLINE void set ( const char* _str );
    INLINE void set ( const str_t& _string );
    INLINE void set ( const self_t& _copy );

    // ========================================================
    // Get
    // ========================================================

    //
    INLINE const str_t& GetString() const;
    INLINE const T* c_str() const;

    // ========================================================
    // operator =
    // ========================================================

    //
    INLINE self_t& operator = ( const T* _str );
    INLINE self_t& operator = ( const str_t& _string );
    INLINE self_t& operator = ( const self_t& _copy );

    // ========================================================
    // operator ==
    // ========================================================

    //
    INLINE bool operator == ( const self_t& _string_id ) const;

    // ========================================================
    // operator != 
    // ========================================================

    //
    INLINE bool operator != ( const self_t& _string_id ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const;
    static const self_t& type_name (); 

    ///////////////////////////////////////////////////////////////////////////////
    // public static functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    static result_t resize( uint32 _newSize );
    static uint32 size();

    //
    static result_t init( uint32 _size = 65536 );
    static result_t destroy();
    static const string_set_t& GetStringTable ();

    ///////////////////////////////////////////////////////////////////////////////
    // protected static data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    EX_LIBS_DLL static string_set_t* s_pStringSet;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    uint32 m_ID;
#ifdef EX_DEBUG
    const T* m_DebugString;
#endif
    
}; // end class StringID

///////////////////////////////////////////////////////////////////////////////
// Hash instance
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: typedef hash function 
// ------------------------------------------------------------------

// ========================================================
// string_id_t 
// ========================================================


template <>
struct Hash<string_id_t> 
{
    INLINE uint operator () ( const string_id_t & _value ) const { return (uint32)_value.m_ID; }
}; // end struct Hash<string_id_t>

// ========================================================
// wstring_id_t 
// ========================================================


template <>
struct Hash<wstring_id_t> 
{
    INLINE uint operator () ( const wstring_id_t & _value ) const { return (uint32)_value.m_ID; }
}; // end struct Hash<wstring_id_t>

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END STRINGID_H_1250526407
// #################################################################################
