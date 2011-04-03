// ======================================================================================
// File         : enum_props.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 17:33:53 PM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ENUM_PROPS_H_1281864834
#define ENUM_PROPS_H_1281864834
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// register enums 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

EX_DECL_ENUM_PROPERTY_BEGIN ( EX_LIBS_DLL, result_t )
    EX_ADD_ENUM (EResult::already_existed)
    EX_ADD_ENUM (EResult::already_freed)
    EX_ADD_ENUM (EResult::compile_failed)
    EX_ADD_ENUM (EResult::create_failed)
    EX_ADD_ENUM (EResult::destroy_failed)
    EX_ADD_ENUM (EResult::device_lost)
    EX_ADD_ENUM (EResult::device_resetfailed)
    EX_ADD_ENUM (EResult::end_of_file)
    EX_ADD_ENUM (EResult::failed)
    EX_ADD_ENUM (EResult::infinity)
    EX_ADD_ENUM (EResult::init_failed)
    EX_ADD_ENUM (EResult::invalid_input)
    EX_ADD_ENUM (EResult::invalid_output)
    EX_ADD_ENUM (EResult::lock_failed)
    EX_ADD_ENUM (EResult::nan)
    EX_ADD_ENUM (EResult::no_change)
    EX_ADD_ENUM (EResult::not_exists)
    EX_ADD_ENUM (EResult::not_found)
    EX_ADD_ENUM (EResult::ok)
    EX_ADD_ENUM (EResult::out_of_range)
    EX_ADD_ENUM (EResult::parse_failed)
    EX_ADD_ENUM (EResult::read_failed)
    EX_ADD_ENUM (EResult::render_paused)
    EX_ADD_ENUM (EResult::serialize_failed)
    EX_ADD_ENUM (EResult::unknown)
    EX_ADD_ENUM (EResult::verify_failed)
    EX_ADD_ENUM (EResult::write_failed)
EX_DECL_ENUM_PROPERTY_END ()

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END ENUM_PROPS_H_1281864834
// #################################################################################
