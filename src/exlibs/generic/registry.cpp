// ======================================================================================
// File         : registry.cpp
// Author       : Wu Jie 
// Last Change  : 08/17/2010 | 11:14:22 AM | Tuesday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"

// ######################### 
namespace ex { 
// ######################### 

typedef ::ex::Pair<int,const char*> enum_pair_t;
typedef ::ex::Pair<const enum_pair_t*,int> enum_info_t;
typedef HashMap< string_id_t,
                 enum_info_t,
                 Hash<string_id_t>, 
                 EqualTo<string_id_t>, 
                 NoManaged<NullType>::TAllocator > type_to_enumlist_t;
static type_to_enumlist_t s_typeToEnumList;

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void register_classes ()
{
    PropertyObject::staticRegisterProperties();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void register_enums ()
{
    register_enum ( TypeTraits<result_t>::type_name(), ns_result_t::list, EX_ARRAY_COUNT(ns_result_t::list) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void register_enum ( const string_id_t& _typeID, const Pair<int,const char*>* _info, int _count )
{
    s_typeToEnumList.insert( _typeID, enum_info_t(_info, _count) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void enum_info_list ( const string_id_t& _typeID, List<Pair<int,const char*> >* _result )
{
    ex_assert_return ( _result != NULL, /*void*/, "the result list you send in is NULL" );

    type_to_enumlist_t::iterator iter = s_typeToEnumList.find(_typeID);
    ex_assert_return ( iter != s_typeToEnumList.end(), /*void*/, "can't find the enum_info_list list with type %s", _typeID.c_str() );

    enum_info_t& enumInfo = *iter;
    uint infoCount = enumInfo.second;
    const enum_pair_t* infoList = enumInfo.first;
    for ( uint i = 0; i < infoCount; ++i ) {
        _result->push_back( infoList[i] );
    }
}

// ######################### 
} // end namespace ex 
// ######################### 

