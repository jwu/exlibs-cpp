// ======================================================================================
// File         : uid.cpp
// Author       : Wu Jie 
// Last Change  : 03/21/2010 | 18:09:29 PM | Sunday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// static 
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace _private { 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const date_time_t uid_start = date_time_t( 2010, 1, 1 ); // NOTE: this is your uid time. in my design, you can use 44(14-bits) years.
static date_time_t last_time = uid_start; 
static uint offset = 0;

// ######################### 
} // end namespace _private 
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

UID UID::null = UID();

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

UID UID::gen_uid ()
{
    uid_t uid;
    uid.GenerateID ();
    return uid;
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

UID::UID ()
    : m_ID (EX_UINT64_MAX)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

UID::UID ( const UID& _uid )
    : m_ID (_uid.m_ID) 
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

UID::UID ( uint64 _id )
    : m_ID (_id)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ID: 63-56: server, 55-32: days from uid_start, 31-0: day-time by msecs
// ------------------------------------------------------------------ 

void UID::GenerateID()
{
    // get current time
    date_time_t current_time;

    // if we have time conflict, increase offset to avoid same ID.
    if ( _private::last_time == current_time ) {
        ++_private::offset;
    }
    else { // else, we need reset the offset.
        _private::offset = 0;
    }

    // if the offset over 255, we will have same uid fatal error!!
    if ( _private::offset >= 255 ) {
        ex_error ("uid generate error, generate over 255 uid in 1-ms.");
    }
    _private::last_time = current_time;

    // get time span from uid_start time to current time.
    timespan_t span = current_time - _private::uid_start;
    uint64 days = (uint64)(span.Days()); // get how many days.

    // get day time
    day_time_t& dayTime = current_time.Time();
    uint64 msecs = (uint64)(dayTime.ToMSecs());

    // TODO: 1byte for server ID. (0~255). which means we support maximum 255 nums of server.
    uint64 serverID = 0;
    uint64 offset = _private::offset;

    //
    m_ID = ( serverID & 0xff )       << 56 | 
           ( offset   & 0xff )       << 48 |
           ( days     & 0x0fffffff ) << 32 |
           ( msecs    & 0xffffffff );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void UID::serialize ( ISerializeNode* _pNode )
{
    EX_SERIALIZE ( _pNode, "uid", m_ID );
}

// ######################### 
} // end namespace ex 
// ######################### 

