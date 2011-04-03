// ======================================================================================
// File         : wrap_CActionData.cpp
// Author       : Wu Jie 
// Last Change  : 09/01/2010 | 16:19:03 PM | Wednesday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "dho_editor.h"
#include "wrap_lua.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

#define check_CActionData(_L) (CActionData*)(((::ex::lua::Proxy*)luaL_checkudata( _L, 1, "CActionData.meta" ))->user_data)

typedef void (*CActionData_pfn) ( lua_State*, CActionData* );

static ex::HashMap< ex::string_id_t, 
                    CActionData_pfn, 
                    ex::Hash<ex::string_id_t>,
                    ex::EqualTo<ex::string_id_t>,
                    ex::NoManaged<ex::NullType>::TAllocator > s_keyToSet;

static ex::HashMap< ex::string_id_t, 
                    CActionData_pfn, 
                    ex::Hash<ex::string_id_t>,
                    ex::EqualTo<ex::string_id_t>,
                    ex::NoManaged<ex::NullType>::TAllocator > s_keyToGet;

#define EX_REGKEY_GET_SET( _key, _get_func, _set_func ) s_keyToGet[_key] = _get_func; s_keyToSet[_key] = _set_func;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int CActionData_set (lua_State * _l) {
    CActionData* obj = check_CActionData(_l);
    const char* str_key = luaL_checkstring(_l, 2);
    ex::string_id_t key(str_key);

    if ( s_keyToSet.find(key) != s_keyToSet.end() ) {
        CActionData_pfn pfn = s_keyToSet[key];
        if ( pfn )
            pfn(_l,obj);
        else {
            ex_warning("%s is readonly", str_key );
            return 0;
        }
    }
    else {
        ex_warning( "can't find the key %s", str_key );
        return 0;
    }

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int CActionData_get (lua_State * _l) {
    CActionData* obj = check_CActionData(_l);
    const char* str_key = luaL_checkstring(_l, 2);
    ex::string_id_t key(str_key);

    if ( s_keyToGet.find(key) != s_keyToGet.end() ) {
        CActionData_pfn pfn = s_keyToGet[key];
        if ( pfn )
            pfn(_l,obj);
        else {
            ex_warning("%s is writeonly", str_key );
            lua_pushnil(_l);
            return 0;
        }
    }
    else {
        ex_warning( "can't find the key %s", str_key );
    }

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int CActionData_size (lua_State * _l) {
    lua_pushinteger(_l, sizeof(CActionData) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int CActionData_toString (lua_State * _l) {
    CActionData* obj = check_CActionData(_l);
    ex::string_t str = ex::to_str<ex::dec> (obj->ID());           
    lua_pushfstring(_l, str.c_str(), str.size() );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg method_m [] = {
    { "__newindex", CActionData_set },
    { "__index", CActionData_get },
    { "__len", CActionData_size },
    { "__tostring", CActionData_toString },
    { "__gc", lua__GB__gc },
    { NULL, NULL }
};

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int CActionData_new (lua_State * _l) {

    ex::lua::Proxy* proxy = (ex::lua::Proxy*)lua_newuserdata( _l, sizeof(ex::lua::Proxy) );
    proxy->user_data = NiNew CActionData();
    proxy->own_by_gc = true;

    luaL_getmetatable(_l, "CActionData.meta");
    lua_setmetatable(_l, -2);

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg method_f [] = {
    { "new", CActionData_new },
    { NULL, NULL }
};

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void CActionData_ID_get ( lua_State* _l, CActionData* _obj ) {
    lua_pushinteger ( _l, _obj->ID() );
}
static void CActionData_ID_set ( lua_State* _l, CActionData* _obj ) {
    int value = luaL_checkinteger(_l, 3);
    _obj->setID(value);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void CActionData_tag_get ( lua_State* _l, CActionData* _obj ) {
    lua_pushstring ( _l, _obj->tag() );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void CActionData_actionLeft_get ( lua_State* _l, CActionData* _obj ) {
    lua_pushinteger ( _l, _obj->m_nActionLeft );
}
static void CActionData_actionLeft_set ( lua_State* _l, CActionData* _obj ) {
    int value = luaL_checkinteger(_l, 3);
    _obj->m_nActionLeft = value;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void CActionData_actionRight_get ( lua_State* _l, CActionData* _obj ) {
    lua_pushinteger ( _l, _obj->m_nActionRight );
}
static void CActionData_actionRight_set ( lua_State* _l, CActionData* _obj ) {
    int value = luaL_checkinteger(_l, 3);
    _obj->m_nActionRight = value;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void CActionData_playSpeed_get ( lua_State* _l, CActionData* _obj ) {
    lua_pushinteger ( _l, _obj->m_nPlaySpeed );
}
static void CActionData_playSpeed_set ( lua_State* _l, CActionData* _obj ) {
    int value = luaL_checkinteger(_l, 3);
    _obj->m_nPlaySpeed = value;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void CActionData_actionLoop_get ( lua_State* _l, CActionData* _obj ) {
    lua_pushinteger ( _l, _obj->m_bActionLoop );
}
static void CActionData_actionLoop_set ( lua_State* _l, CActionData* _obj ) {
    int value = luaL_checkinteger(_l, 3);
    _obj->m_bActionLoop = value;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void CActionData_keyOpen_get ( lua_State* _l, CActionData* _obj ) {
    lua_pushinteger ( _l, _obj->m_bKeyOpen );
}
static void CActionData_keyOpen_set ( lua_State* _l, CActionData* _obj ) {
    int value = luaL_checkinteger(_l, 3);
    _obj->m_bKeyOpen = value;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void CActionData_continueTimer_get ( lua_State* _l, CActionData* _obj ) {
    lua_pushinteger ( _l, _obj->m_nMContinueTimer );
}
static void CActionData_continueTimer_set ( lua_State* _l, CActionData* _obj ) {
    int value = luaL_checkinteger(_l, 3);
    _obj->m_nMContinueTimer = value;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void CActionData_endType_get ( lua_State* _l, CActionData* _obj ) {
    lua_pushinteger ( _l, _obj->m_eMEndType );
}
static void CActionData_endType_set ( lua_State* _l, CActionData* _obj ) {
    int value = luaL_checkinteger(_l, 3);
    _obj->m_eMEndType = (EMEND)value;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

    // MKEY	m_szMKey[MAX_MOVEKEY];

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void CActionData_n_effect_list_get ( lua_State* _l, CActionData* _obj ) {
    // lua_getfield( _l, 1, "n_effect_list" );
}
// static void CActionData_n_effect_list_set ( lua_State* _l, CActionData* _obj ) {
//     int value = luaL_checkinteger(_l, 3);
// }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#if 1
int luaopen_CActionData ( lua_State* _l ) {

    luaL_newmetatable( _l, "CActionData.meta" );
    luaL_register( _l, NULL, method_m ); {
        EX_REGKEY_GET_SET ( ex::string_id_t("ID"), CActionData_ID_get, CActionData_ID_set );
        EX_REGKEY_GET_SET ( ex::string_id_t("tag"), CActionData_tag_get, NULL );
        EX_REGKEY_GET_SET ( ex::string_id_t("actionLeft"), CActionData_actionLeft_get, CActionData_actionLeft_set );
        EX_REGKEY_GET_SET ( ex::string_id_t("actionRight"), CActionData_actionRight_get, CActionData_actionRight_set );
        EX_REGKEY_GET_SET ( ex::string_id_t("playSpeed"), CActionData_playSpeed_get, CActionData_playSpeed_set );
        EX_REGKEY_GET_SET ( ex::string_id_t("actionLoop"), CActionData_actionLoop_get, CActionData_actionLoop_set );
        EX_REGKEY_GET_SET ( ex::string_id_t("keyOpen"), CActionData_keyOpen_get, CActionData_keyOpen_set );
        EX_REGKEY_GET_SET ( ex::string_id_t("continueTimer"), CActionData_continueTimer_get, CActionData_continueTimer_set );
        EX_REGKEY_GET_SET ( ex::string_id_t("endType"), CActionData_endType_get, CActionData_endType_set );
        // EX_REGKEY_GET_SET ( ex::string_id_t("moveKeyList"), CActionData_endType_get, CActionData_endType_set );
        EX_REGKEY_GET_SET ( ex::string_id_t("n_effect_list"), CActionData_n_effect_list_get, NULL );
        lua_newtable(_l); lua_setfield( _l, -2, "n_effect_list" );
    }

    luaL_register( _l, "CActionData", method_f ); {
        // lua_newtable(_l); lua_setfield( _l, -2, "n_effect_list" );
    }

    return 1;
}
#else
int luaopen_CActionData ( lua_State* _l ) {

    using namespace luabind;
    module(_l) [
        class_<CActionData>("CActionData")
            .def(constructor<>())
            .def_readwrite("actionLeft", &CActionData::m_nActionLeft )
    ];
    return 1;
}
#endif
