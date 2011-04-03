// ======================================================================================
// File         : singleton_defs.cpp
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 09:21:32 AM | Saturday,August
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "memory/Allocator_sys.h"
#include "memory/Allocator_dl283.h"
#include "memory/StackAllocator.h"
#include "memory/MemMng.h"
#include "log/Log.h"
#include "resource/ResourceMng.h"
#include "time/TimerMng.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

EX_DEF_SINGLETON_3 ( Allocator_sys,    ESingletonLevel::exlibs_lv_0, NoManaged<NullType>::TAllocator )
EX_DEF_SINGLETON_3 ( Allocator_dl283,  ESingletonLevel::exlibs_lv_0, NoManaged<NullType>::TAllocator ) 
EX_DEF_SINGLETON_3 ( StackAllocator,   ESingletonLevel::exlibs_lv_0, NoManaged<NullType>::TAllocator ) 
EX_DEF_SINGLETON_3 ( Log,              ESingletonLevel::exlibs_lv_0, NoManaged<NullType>::TAllocator )
EX_DEF_SINGLETON_3 ( MemMng,           ESingletonLevel::exlibs_lv_1, NoManaged<NullType>::TAllocator )
EX_DEF_SINGLETON_2 ( TimerMng,         ESingletonLevel::exlibs_lv_2 )
EX_DEF_SINGLETON_3 ( ResourceMng,      ESingletonLevel::exlibs_lv_3, Managed<EX_ALLOCATOR>::TAllocator )

// ######################### 
} // end namespace ex 
// ######################### 


