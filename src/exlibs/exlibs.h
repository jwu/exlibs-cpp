// ======================================================================================
// File         : exlibs.h
// Author       : Wu Jie 
// Last Change  : 08/13/2010 | 23:39:39 PM | Friday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef EXLIBS_H_1281713981
#define EXLIBS_H_1281713981
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////


// ======================================================== 
// global includes (order important)
// ======================================================== 

#include "global/global_inc.h"
#include "misc/ASCII.h"

#include "core/debug.h"
#include "meta/typeop.h"
#include "memory/memory_inc.h"

#include "core/Core.h"
#include "string/typedefs.h"
#include "string/String.h"
    #include "string/Path.h"
        #include "string/ResPath.h"

#include "pattern/SmartPtr.h"
#include "pattern/WeakPtr.h"
#include "meta/meta_inc.h"
#include "gf/gf_inc.h"
#include "container/container_inc.h"
#include "string/StringID.h" // depends on HashSet
#include "log/Log.h"
#include "generic/registry.h"

// patterns
#include "pattern/singleton.h"
#include "pattern/RuntimeClass.h"
#include "pattern/Factory.h"
#include "pattern/Functor.h"
#include "pattern/AbstractFactory.h"
#include "pattern/MemberPtr.h"
#include "pattern/Tuple.h"

// ======================================================== 
// general includes (orderless, because these header will have self includes)
// ======================================================== 

#include "thread/thread_inc.h"
#include "file/file_inc.h"
#include "time/time_inc.h"
#include "xml/xml_inc.h"
#include "serialization/serialization_inc.h"
#include "property/property_inc.h"
#include "math/math_inc.h"

// classes
#include "core/ConfigParser.h"
#include "core/uid.h"
#include "core/Version.h"
#include "memory/DataHolder.h"
#include "resource/ResourceMng.h"

// ======================================================== 
// generic includes 
// ======================================================== 

#include "generic/enum_props.h"
#include "generic/serialize_defs.hpp"
#include "generic/prop_instance_defs.hpp"

// ======================================================== 
// late-inline function defines  
// ======================================================== 

#include "meta/TypeTraits.hpp"
#include "string/StringID.hpp"
#include "string/ResPath.hpp"
#include "math/meta/Mathop.hpp"

// #################################################################################
#endif // END EXLIBS_H_1281713981
// #################################################################################
