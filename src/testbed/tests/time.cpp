// ======================================================================================
// File         : Time.cpp
// Author       : Wu Jie 
// Last Change  : 03/02/2010 | 14:25:49 PM | Tuesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "testbed.h"

///////////////////////////////////////////////////////////////////////////////
// Test cases
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

TEST( Date, normal, off )
{
    ex::date_t date( 2008, 5, 22 );
    ex_log ( date.to_str<ex::dec>().c_str() );
    CHECK ( date.Year() == 2008 );
    CHECK ( date.Month() == 5 );
    CHECK ( date.Day() == 22 );

    date += 15;
    ex_log ( date.to_str<ex::dec>().c_str() );
    CHECK ( date.Year() == 2008 );
    CHECK ( date.Month() == 6 );
    CHECK ( date.Day() == 6 );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( TimeSpan, normal, off )
{
    ex::timespan_t span;
    span.set ( 7, 234 );
    ex_log ( span.to_str<ex::dec>().c_str() );
    CHECK ( span.TotalSeconds() == 7.234 );
    CHECK ( span.TotalMilliseconds() == 7.234 * 1000 );

    span.SetSeconds_f32 ( 1.26f );
    ex_log ( span.to_str<ex::dec>().c_str() );
    ex_log ( (ex::to_str<ex::dec>(span.TotalSeconds()) + "s").c_str() );
    CHECK ( span.TotalSeconds() - 1.26 < 0.0001 );

    span.SetSeconds_f64 ( 432.1234 );
    ex_log ( span.to_str<ex::dec>().c_str() );
    ex_log ( (ex::to_str<ex::dec>(span.TotalSeconds()) + "s").c_str() );
    CHECK ( span.TotalSeconds() - 432.1234 < 0.0001 );

    span.SetMilliseconds_f32 ( 123.21246f );
    ex_log ( span.to_str<ex::dec>().c_str() );
    ex_log ( (ex::to_str<ex::dec>(span.TotalMilliseconds()) + "ms").c_str() );
    CHECK ( span.TotalMilliseconds() - 123.21246 < 0.0001 );

    span.SetMilliseconds_f64 ( 4124332.134234 );
    ex_log ( span.to_str<ex::dec>().c_str() );
    ex_log ( (ex::to_str<ex::dec>(span.TotalMilliseconds()) + "ms").c_str() );
    CHECK ( span.TotalMilliseconds() - 4124332.134234 < 0.0001 );

    span.set ( 7200 );
    ex_log ( span.to_str<ex::dec>().c_str() );
    CHECK ( span.TotalHours() == 2 );

    span.set ( 0, 10000 );
    ex_log ( span.to_str<ex::dec>().c_str() );
    double d = span.TotalSeconds();
    CHECK ( span.TotalSeconds() == 10.0 );
    CHECK ( span.TotalMilliseconds() == 10000.0 );

    span.set ( 20000, 0 );
    ex_log ( span.to_str<ex::dec>().c_str() );
    CHECK ( span.TotalSeconds() == 20000 );
    CHECK ( span.TotalMilliseconds() == 20000 * 1000.0 );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( DayTime, normal, off )
{
    ex::timespan_t span;
    ex::day_time_t day_time;

    day_time.set( 23, 22, 44 ); 
    ex_log ( day_time.to_str<ex::dec>().c_str() );
    // day_time = 23h 22m 44s
    CHECK ( day_time.Hours() == 23 );
    CHECK ( day_time.Minutes() == 22 );
    CHECK ( day_time.Seconds() == 44 );
    CHECK ( day_time.Milliseconds() == 0 );

    span.set (0,0,0,22);
    day_time += span;
    ex_log ( day_time.to_str<ex::dec>().c_str() );
    // day_time = 23h 23m 6s
    CHECK ( day_time.Hours() == 23 );
    CHECK ( day_time.Minutes() == 23 );
    CHECK ( day_time.Seconds() == 6 );
    CHECK ( day_time.Milliseconds() == 0 );

    span.set (0,0,44,11);
    ex_log ( span.to_str<ex::dec>().c_str() );
    ex::day_time_t day_time2;
    day_time2 = day_time + span;
    ex_log ( day_time.to_str<ex::dec>().c_str() );
    ex_log ( day_time2.to_str<ex::dec>().c_str() );
    // day_time = 23h 23m 6s
    // day_time2 = 00h 7m 17s
    CHECK ( day_time2.Hours() == 0 );
    CHECK ( day_time2.Minutes() == 7 );
    CHECK ( day_time2.Seconds() == 17 );
    CHECK ( day_time2.Milliseconds() == 0 );

    ex::timespan_t span2to1 = day_time - day_time2;
    ex_log ( span2to1.to_str<ex::dec>().c_str() );

    ex::timespan_t span1to2 = day_time2 - day_time;
    ex_log ( span1to2.to_str<ex::dec>().c_str() );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( DateTime, normal, off )
{
    ex::timespan_t span;
    ex::date_time_t date_time;

    // current date time
    ex_log ( date_time.to_str<ex::dec>().c_str() );

    //
    ex::date_time_t date_time1;
    date_time1.set ( 2008, 4, 12, 13, 22, 45, 12 );
    ex_log ( date_time1.to_str<ex::dec>().c_str() );
    CHECK ( date_time1.Year() == 2008 );
    CHECK ( date_time1.Month() == 4 );
    CHECK ( date_time1.Day() == 12 );
    CHECK ( date_time1.Hours() == 13 );
    CHECK ( date_time1.Minutes() == 22 );
    CHECK ( date_time1.Seconds() == 45 );
    CHECK ( date_time1.Milliseconds() == 12 );

    ex::date_time_t date_time2;
    date_time2.set ( 2008, 5, 24, 21, 59, 32, 345 );
    ex_log ( date_time2.to_str<ex::dec>().c_str() );

    span = date_time2 - date_time1;
    ex_log ( span.to_str<ex::dec>().c_str() );

    //
    CHECK ( date_time1 != date_time2 );
    CHECK ( date_time1 + span == date_time2 );
    CHECK ( date_time2 - span == date_time1 );

    ex::date_time_t date_time3 = date_time1;
    date_time3 += span;
    CHECK ( date_time3 == date_time2 );
    date_time3 -= span;
    CHECK ( date_time3 == date_time1 );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( CpuClock, normal, off )
{
    ex::cpu_clock_t cpuClock;
    ex::timespan_t timeSpan;

    cpuClock.start ();
    // test string_id_t
    {
        cpuClock.count ();
        ex::string_id_t string ("this");
        timeSpan = cpuClock.count ();
        ex_log("string_id_t construct time: \n" + timeSpan.to_str<ex::dec>() );
    }

    // test string_t
    {
        cpuClock.count ();
        ex::string_t string ("this");
        timeSpan = cpuClock.count ();
        ex_log("string_t construct time: \n" + timeSpan.to_str<ex::dec>() );
    }

    // test string_id_t 1000 times
    {
        cpuClock.count ();
        int count = 0;
        while ( count < 1000 )
        {
            ex::string_id_t string ("this");
            ++count;
        }
        timeSpan = cpuClock.count ();
        ex_log("string_id_t construct 1000 times: \n" + timeSpan.to_str<ex::dec>() );
    }

    // test string_t 1000 times
    {
        cpuClock.count ();
        int count = 0;
        while ( count < 1000 )
        {
            ex::string_t string ("this");
            ++count;
        }
        timeSpan = cpuClock.count ();
        ex_log("string_t construct 1000 times: \n" + timeSpan.to_str<ex::dec>() );
    }

    // tarray push
    {
        cpuClock.count ();
        int count = 0;
        ex::Array<int> arr; 
        while ( count < 1000 )
        {
            arr.push_back (1);
            ++count;
        }
        timeSpan = cpuClock.count ();
        ex_log("tarray push: \n" + timeSpan.to_str<ex::dec>() );
    }

    // string_t search
    {
        cpuClock.count ();
        int count = 0;
        ex::HashMap<ex::string_t,float> hash_map; 
        typedef ex::List<ex::string_t> keys_t; 
        keys_t keys; 
        while ( count < 10000 )
        {
            float value = ex::mathop::range_rand(0.0, 10.0);
            ex::string_t key = ex::string_t( ex::to_str<ex::dec>(value) );
            hash_map.insert ( key, value );
            keys.push_back (key);
            ++count;
        }
        timeSpan = cpuClock.count ();
        ex_log("string_t search table insert: \n" + timeSpan.to_str<ex::dec>() );

        cpuClock.count ();
        for ( keys_t::iterator iter = keys.begin(); iter != keys.end(); ++iter )
        {
            hash_map.find ( *iter );
        }
        timeSpan = cpuClock.count ();
        ex_log("string_t search: \n" + timeSpan.to_str<ex::dec>() );
    }

    // string_id_t search
    {
        cpuClock.count ();
        int count = 0;
        ex::HashMap<ex::string_id_t,float> hash_map; 
        typedef ex::List<ex::string_id_t> keys_t; 
        keys_t keys; 
        while ( count < 10000 )
        {
            float value = ex::mathop::range_rand(0.0, 10.0);
            ex::string_id_t key = ex::string_id_t( ex::to_str<ex::dec>(value) );
            hash_map.insert ( key, value );
            keys.push_back (key);
            ++count;
        }
        timeSpan = cpuClock.count ();
        ex_log("string_id_t search table insert: \n" + timeSpan.to_str<ex::dec>() );

        cpuClock.count ();
        for ( keys_t::iterator iter = keys.begin(); iter != keys.end(); ++iter )
        {
            hash_map.find ( *iter );
        }
        timeSpan = cpuClock.count ();
        ex_log("string_id_t search: \n" + timeSpan.to_str<ex::dec>() );
    }

    timeSpan = cpuClock.Stop ();
    ex_log("total-time: \n" + timeSpan.to_str<ex::dec>() );

    EX_HW_BREAK ();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool timer_callback ( const ex::timer_t& _timer, const ex::timespan_t& _elapsed ) 
{
    ex_log("timer_callback invoked! time elapsed %f\n", _elapsed.TotalSeconds() );
    return true;
}
bool timer_callback_inject ( const ex::timer_t& _timer, const ex::timespan_t& _elapsed ) 
{
    ex_log("timer_callback_inject invoked! time elapsed %f\n", _elapsed.TotalSeconds() );
    ex_log("inject the callback\n", _elapsed.TotalSeconds() );
    return false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

TEST( Timer, normal, off )
{
    ex::cpu_clock_t cpuClock;
    ex::timespan_t timeSpan;

    // test timer-wait
    cpuClock.start ();
    ex_log("test timer wait\n" );

    cpuClock.count ();
    ex_log("timer wait for 2 secs...\n" );
    ex::timer_t::wait ( ex::timespan_t(2) );
    timeSpan = cpuClock.count ();
    CHECK ( timeSpan.ToSecs() == 2 );
    ex_log("finish test timer wait\n" );

    cpuClock.Stop ();

    // test enable/disable
    if (1)
    {
        // test timer invalid input
        ex::timer_t* pTimer1 = EX_GP(ex::TimerMng)->createTimer();
        pTimer1->setInterval ( ex::timespan_t(1) );
        pTimer1->addCallback (timer_callback);

        ex_log("start test timer invoke...\n");
        cpuClock.start ();
        timeSpan = 0;

        pTimer1->start ();
        while ( timeSpan < ex::timespan_t(5) )
        {
            pTimer1->tick ();
            timeSpan = cpuClock.Elapsed ();
        }
        pTimer1->stop (); // this trigger auto-delete.
    }

    // test enable/disable
    if (1)
    {
        // test timer invalid input
        ex::timer_t& timer1 = *EX_GP(ex::TimerMng)->createTimer();
        timer1.autoDelete (false);
        // DISABLE: timer1.start (); // failed because we don't set interval.
        timer1.setInterval ( ex::timespan_t(1) );
        // DISABLE: timer1.start (); // failed because we don't set callbacks.
        timer1.addCallback (timer_callback);

        // failed because we already add one
        CHECK( timer1.addCallback (timer_callback) != ex::EResult::ok ) 
        CHECK( timer1.addCallback (timer_callback_inject) == ex::EResult::ok ) 
        CHECK( timer1.removeCallback (timer_callback_inject) == ex::EResult::ok ) 
        CHECK( timer1.removeCallback (timer_callback_inject) != ex::EResult::ok ) 

        // ======================================================== 
        // test timer invoke
        // ======================================================== 

        ex_log("start test timer invoke...\n");
        cpuClock.start ();
        timeSpan = 0;

        timer1.start ();
        while ( timeSpan < ex::timespan_t(5) )
        {
            timer1.tick ();
            timeSpan = cpuClock.Elapsed ();
        }
        timer1.stop ();
        ex_log("finish timer invoke test\n");

        // ======================================================== 
        // test timer lifetime
        // ======================================================== 

        timer1.setLifetime ( ex::timespan_t(5) );

        ex_log("start test timer lifetime...\n");
        cpuClock.start ();
        timeSpan = 0;

        timer1.start ();
        while ( timeSpan < ex::timespan_t::INF && !timer1.isStopped() )
        {
            timer1.tick ();
            timeSpan = cpuClock.Elapsed ();
        }
        timer1.stop ();
        ex_log("finish timer lifetime test\n");

        // ======================================================== 
        // test timer lifetime with pasued
        // ======================================================== 

        timer1.setLifetime ( ex::timespan_t(5) );

        ex_log("start test timer lifetime...\n");
        cpuClock.start ();
        timeSpan = 0;

        timer1.start ();
        bool pause = true;
        while ( timeSpan < ex::timespan_t::INF && !timer1.isStopped() )
        {
            timer1.tick ();

            if ( timeSpan > ex::timespan_t(2) && pause )
            {
                timer1.pause ();
                ex_log("pause timer for 5 secs...\n");
                ex::timer_t::wait ( ex::timespan_t(5) );
                timer1.resume ();
                ex_log("resume\n");
                pause = false;
            }

            timeSpan = cpuClock.Elapsed ();
        }
        timer1.stop ();
        EX_GP(ex::TimerMng)->deleteTimer(&timer1);
        ex_log("finish timer lifetime test\n");
    }

    // test enable/disable
    if (1)
    {
        //
        ex::timer_t& timer2 = *EX_GP(ex::TimerMng)->createTimer();
        timer2.autoDelete (false);
        timer2.setInterval ( ex::timespan_t(1,500) );
        timer2.addCallback (timer_callback_inject);

        // ======================================================== 
        // test timer callback inject
        // ======================================================== 

        ex_log("start test timer inject...\n");
        cpuClock.Stop ();
        cpuClock.start ();
        timeSpan = 0;

        timer2.start ();
        while ( timeSpan < ex::timespan_t::INF && !timer2.isStopped() )
        {
            timer2.tick ();
            timeSpan = cpuClock.Elapsed ();
        }
        ex_log("finish timer inject test\n");

        // ======================================================== 
        // test multi-callback 
        // ======================================================== 

        ex_log("start test timer multi-callback...\n");
        cpuClock.Stop ();
        cpuClock.start ();
        timeSpan = 0;

        timer2.addCallback (timer_callback);
        timer2.start ();
        while ( timeSpan < ex::timespan_t(5) )
        {
            timer2.tick ();
            timeSpan = cpuClock.Elapsed ();
        }
        timer2.stop ();
        EX_GP(ex::TimerMng)->deleteTimer(&timer2);
        ex_log("finish timer multi-callback test\n");
    }

    EX_HW_BREAK ();
}
