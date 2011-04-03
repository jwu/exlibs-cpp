// ======================================================================================
// File         : Pair.h
// Author       : Wu Jie 
// Last Change  : 08/17/2009 | 23:33:28 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PAIR_H_1250523212
#define PAIR_H_1250523212
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class Pair
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////
 
template < typename T1, typename T2 >
struct Pair
{
    // typedef
    typedef Pair<T1,T2> self_t;
    typedef T1 first_t;
    typedef T2 second_t;
    typedef std::pair<T1,T2> std_pair_t;

    // member
    T1 first;
    T2 second;

    // constructor
    Pair() : first(T1()), second(T2()) {}
    Pair( const T1& _t1, const T2& _t2 ) : first(_t1), second(_t2) {}
    Pair( const Pair& _pair ) : first(_pair.first), second(_pair.second) {}
    Pair( const std_pair_t& _pair ) : first(_pair.first), second(_pair.second) {}

    // std::pair cast
    INLINE operator std_pair_t () { return std_pair_t(first,second); }

    //
    INLINE self_t& operator = ( const self_t& _copy ) 
    {
        first = _copy.first;
        second = _copy.second;
        return *this;
    }

    //
    INLINE self_t& operator = ( const std_pair_t& _stdPair ) 
    {
        first = _stdPair.first;
        second = _stdPair.second;
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string = ex::to_str<FLAGS>(first) + " -- " + 
                          ex::to_str<FLAGS>(second)
                          ;
        return string;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("Pair");
        return strID;
    }
    void serialize ( ISerializeNode* _pNode );

}; // end struct Pair

// ------------------------------------------------------------------
// Desc: ==
// ------------------------------------------------------------------
template < typename T1, typename T2 >
INLINE bool operator == ( const Pair<T1,T2>& _pair1, const Pair<T1,T2>& _pair2 )
{
    return _pair1.first == _pair2.first && _pair1.second == _pair2.second; 
}

// ------------------------------------------------------------------
// Desc: <
// ------------------------------------------------------------------
template < typename T1, typename T2 >
INLINE bool operator < ( const Pair<T1,T2>& _pair1, const Pair<T1,T2>& _pair2 )
{ 
    return _pair1.first < _pair2.first || (!(_pair2.first < _pair1.first) && _pair1.second < _pair2.second); 
}

// ------------------------------------------------------------------
// Desc: !=
// ------------------------------------------------------------------
template < typename T1, typename T2 >
INLINE bool operator != ( const Pair<T1,T2>& _pair1, const Pair<T1,T2>& _pair2 )
{ 
    return !( _pair1 == _pair2 );
}

// ------------------------------------------------------------------
// Desc: >
// ------------------------------------------------------------------
template < typename T1, typename T2 >
INLINE bool operator > ( const Pair<T1,T2>& _pair1, const Pair<T1,T2>& _pair2 )
{ 
    return _pair2 < _pair1;
}

// ------------------------------------------------------------------
// Desc: <=
// ------------------------------------------------------------------
template < typename T1, typename T2 >
INLINE bool operator <= ( const Pair<T1,T2>& _pair1, const Pair<T1,T2>& _pair2 )
{ 
    return !( _pair2 < _pair1 );
}

// ------------------------------------------------------------------
// Desc: >=
// ------------------------------------------------------------------
template < typename T1, typename T2 >
INLINE bool operator >= ( const Pair<T1,T2>& _pair1, const Pair<T1,T2>& _pair2 )
{ 
    return !( _pair1 < _pair2 );
}

// ------------------------------------------------------------------
// Desc: make_pair
// ------------------------------------------------------------------
template < typename T1, typename T2 >
INLINE Pair<T1,T2> make_pair( const T1& _t1, const T2& _t2 )
{
    return Pair<T1,T2>(_t1,_t2);
}

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END PAIR_H_1250523212
// #################################################################################
