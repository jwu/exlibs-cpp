// ======================================================================================
// File         : singleton.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 00:40:46 AM | Sunday,August
// Description  : 
// ======================================================================================

////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design 
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any 
//     purpose is hereby granted without fee, provided that the above copyright 
//     notice appear in all copies and that both that copyright notice and this 
//     permission notice appear in supporting documentation.
// The author or Addison-Welsey Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// #################################################################################
#ifndef SINGLETON_H_1250526111
#define SINGLETON_H_1250526111
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "memory/allocator_helpers.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// _private
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace _private { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class LifetimeTracker 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class LifetimeTracker
{
public:
    LifetimeTracker ( uint _level, core_t::callback_pfn_t _pfn )
        : m_level (_level),
          m_pfn ( _pfn )
    {
    }

    ~LifetimeTracker ()
    {
        m_pfn();
    }

    static bool compare ( const LifetimeTracker* _pLeft, const LifetimeTracker* _pRight ) 
    {
        return _pLeft->m_level < _pRight->m_level;
    }

protected:
    uint                    m_level;
    core_t::callback_pfn_t   m_pfn;

}; // end class LifetimeTracker 

// ------------------------------------------------------------------
// Desc: helper data 
// ------------------------------------------------------------------

// std::list because of the inserts
typedef std::list<LifetimeTracker*> lifetime_tracker_list_t;
extern EX_LIBS_DLL lifetime_tracker_list_t* g_pLifetimeTrackerList;

// ------------------------------------------------------------------
// Desc: OnSingletonDestroy
// ------------------------------------------------------------------

void EX_LIBS_DLL OnSingletonDestroy ();

// ------------------------------------------------------------------
// Desc: ScheduleDestruction
// ------------------------------------------------------------------

template < typename T >
static void ScheduleDestruction ( T* _pInstance, core_t::callback_pfn_t _pfn, uint _level ) 
{
    // manage lifetime of stack manually
    if( _private::g_pLifetimeTrackerList == NULL )
        _private::g_pLifetimeTrackerList = new _private::lifetime_tracker_list_t;

    // automatically delete the LifetimeTracker object when a exception is thrown
    LifetimeTracker* pLifetimeTracker = new LifetimeTracker(_level,_pfn);

    // find correct position
    _private::lifetime_tracker_list_t::iterator pos = std::upper_bound( _private::g_pLifetimeTrackerList->begin(), 
                                                                        _private::g_pLifetimeTrackerList->end(), 
                                                                        pLifetimeTracker,
                                                                        LifetimeTracker::compare );

    // insert the pointer to the ConcreteLifetimeTracker object into the queue
    _private::g_pLifetimeTrackerList->insert( pos, pLifetimeTracker );

    // Register a call on core exit
    core_t::registerExitCallback(_private::OnSingletonDestroy);
}

// #########################
} // end namespace _private 
// #########################

///////////////////////////////////////////////////////////////////////////////
// SingletonHolder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class SingletonHolder 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

// TODO:
#if 0
template < typename T, 
           uint LEVEL = 0xFFFFFFFF,
           template <class> class TAllocator_T = Managed::Allocator,
           template <class, class> class ThreadingModel_T = TDefaultThread,
           class MutexPolicy_T = TDefaultMutex >
#endif
template < typename T, 
           uint LEVEL = 0xFFFFFFFF,
           template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class SingletonHolder
{
public:

    // ------------------------------------------------------------------
    // Desc: types 
    // ------------------------------------------------------------------

    // Type of the singleton object
    typedef T singleton_t;

    // ------------------------------------------------------------------
    // Desc: Returns a reference to singleton object
    // ------------------------------------------------------------------

    INLINE static T& instance()
    {
        if ( !s_instance )
        {
            createInstance();
        }
        return *s_instance;
    }

    // ------------------------------------------------------------------
    // Desc: You can manually destroy instance
    // ------------------------------------------------------------------

    static void destroyInstance()
    {
        if ( !s_isDestroyed )
        {
            TAllocator_T<T>::Delete(s_instance);
            s_instance = NULL;
            s_isDestroyed = true;
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: Check if the singleton already destroyed
    // ------------------------------------------------------------------ 

    static bool is_destroyed ()
    {
        return s_isDestroyed;
    }

private:

    // ------------------------------------------------------------------
    // Desc: create Helper
    // ------------------------------------------------------------------

    static void createInstance()
    {
        // TODO:
        // typename ThreadingModel_T<SingletonHolder,MutexPolicy_T>::Lock guard;
        // (void)guard;

        if ( !s_instance )
        {
            // TODO: do this just used in PhoenixSingleton? do we need it?
            if ( s_isDestroyed )
            {
                s_isDestroyed = false;
                ex_assert ( false, "Dead Reference Detected" );
            }
            s_instance = TAllocator_T<T>::New();
            _private::ScheduleDestruction( s_instance, &destroyInstance, LEVEL );
        }
    }

    // ------------------------------------------------------------------
    // Desc: Protection
    // ------------------------------------------------------------------

    SingletonHolder();

    // ------------------------------------------------------------------
    // Desc: Data
    // ------------------------------------------------------------------

    // TODO: typedef typename ThreadingModel<T*,MutexPolicy>::VolatileType object_ptr_t;
    typedef T* object_ptr_t; 
    static object_ptr_t s_instance; 
    static bool s_isDestroyed;

}; // end class SingletonHolder 

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END SINGLETON_H_1250526111
// #################################################################################

