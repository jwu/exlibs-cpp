// ======================================================================================
// File         : fsys_watcher.cpp
// Author       : Wu Jie 
// Last Change  : 09/06/2010 | 13:52:44 PM | Monday,September
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "fsys_watcher.h"

// ######################### 
namespace ex { 
// ######################### 

// ######################### 
namespace fsys { 
// ######################### 

// ######################### 
namespace watcher { 
// ######################### 

struct FileInfo {
    uint64 id;
    wpath_t path;
}; // end struct FileInfo

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

typedef Array<wpath_t> files_t;
static files_t* files = NULL;

typedef Array<wpath_t> dirs_t;
static dirs_t* dirs = NULL;

typedef Map<wpath_t,HANDLE> dir_to_handle_t;
static dir_to_handle_t* dir_to_handle = NULL;

typedef Array<FileInfo> file_infos_t;
typedef HashMap<HANDLE,file_infos_t> handle_to_files_t;
static handle_to_files_t* handle_to_files = NULL;

file_changed_pfn_t pfn_fileChanged = NULL;
dir_changed_pfn_t pfn_dirChanged = NULL;

///////////////////////////////////////////////////////////////////////////////
// class FsysWatcher_Thread 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class FsysWatcher_Thread : public Thread 
{
    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    FsysWatcher_Thread () 
        : msg (0)
    {
        mutex = ex_new Mutex();
        if (HANDLE h = CreateEvent(0, false, false, 0)) {
            handles.reserve(MAXIMUM_WAIT_OBJECTS);
            handles.push_back(h);
        }
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    ~FsysWatcher_Thread () {
        ex_safe_delete(mutex);

        CloseHandle(handles[0]);
        handles[0] = INVALID_HANDLE_VALUE;
        for ( Array<HANDLE>::iterator iter = handles.begin(); iter != handles.end(); ++iter ) {
            if ( *iter == INVALID_HANDLE_VALUE )
                continue;
            FindCloseChangeNotification(*iter);
        }
        handles.clear();
    }

    // ------------------------------------------------------------------ 
    // Desc: 
    // ------------------------------------------------------------------ 

    result_t run () {
        TAutoLock<Mutex> lock(mutex);
        for (;;) {
            Array<HANDLE> handlesCopy = handles;
            mutex->Unlock();
            DWORD result = WaitForMultipleObjects( handlesCopy.size(), handlesCopy.ptr(0), false, INFINITE );
            mutex->Lock();

            do {
                if ( result == WAIT_OBJECT_0 ) {
                    int m = msg;
                    msg = 0;
                    if (m == 'q') {
                        return ex::EResult::ok;
                    }
                    if (m != '@') {
                        ex_error( "unknown message '%c' send to thread", char(m) );
                    }
                    break;
                } 
                else if (result > WAIT_OBJECT_0 && result < WAIT_OBJECT_0 + uint(handlesCopy.size())) {
                    uint at = result - WAIT_OBJECT_0;
                    ex_assert( at < handlesCopy.size(), "at is larger than handles" );
                    HANDLE handle = handlesCopy[at];

                    // When removing a path, FindCloseChangeNotification might actually fire a notification
                    // for some reason, so we must check if the handle exist in the handles vector
                    if ( handles.find(handle) != handles.end() ) {

                        if (!FindNextChangeNotification(handle)) {
                            ex_error( "FindNextChangeNotification failed!!" );
                        }

                        handle_to_files_t::iterator it_files = handle_to_files->find(handle);
                        if ( it_files != handle_to_files->end() ) {
                            file_infos_t& fileInfos = *it_files;
                            for ( file_infos_t::iterator it_file = fileInfos.begin(); it_file != fileInfos.end(); ++it_file ) {
                                FileInfo& fileInfo = *it_file;
                                wpath_t& absPath = fileInfo.path;

                                bool isDir = ex::futil::isdir(absPath); 
                                bool exists = ex::futil::exists(absPath); 
                                if ( !exists ) {
                                    // DISABLE { 
                                    // if ( isDir ) {
                                    //     char buf[1024];
                                    //     wchar_to_char( absPath.c_str(), buf );
                                    //     ex_log ("dir %s not exists!\n", buf );
                                    // }
                                    // else {
                                    //     char buf[1024];
                                    //     wchar_to_char( absPath.c_str(), buf );
                                    //     ex_log ("file %s not exists!\n", buf );
                                    // }
                                    // // DISABLE: it_file = fileInfos.erase(it_file);
                                    // if ( fileInfos.empty() )
                                    // {
                                    //     FindCloseChangeNotification(handle);
                                    //     dir_to_handle->erase( isDir ? absPath : absPath.dirName() );
                                    // }
                                    // } DISABLE end 
                                }
                                else if ( isDir ) {
                                    // char buf[1024];
                                    // wchar_to_char( absPath.c_str(), buf );
                                    // ex_log ("dir %s changed!\n", buf );
                                    if ( pfn_dirChanged ) {
                                        ex::Timer::wait( ex::timespan_t( 1, 0 ) );
                                        (*pfn_dirChanged)(absPath);
                                    }
                                }
                                else { 
                                    uint64 cur_id = ex::futil::file::fileID(absPath);
                                    if ( fileInfo.id != cur_id ) {
                                        // char buf[1024];
                                        // wchar_to_char( absPath.c_str(), buf );
                                        // ex_log ("file %s changed!\n", buf );
                                        if ( pfn_fileChanged ) {
                                            ex::Timer::wait( ex::timespan_t( 1, 0 ) );
                                            (*pfn_fileChanged)(absPath);
                                        }
                                        fileInfo.id = cur_id;
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    break;  // avoid endless loop
                } 
                handlesCopy = handles;
                result = WaitForMultipleObjects(handlesCopy.size(), handlesCopy.ptr(0), false, 0);
            } while ( result != WAIT_TIMEOUT );
        }
        return ex::EResult::ok;
    }

    void stop () {
        msg = 'q';
        SetEvent(handles[0]);
    }

    void wakeup () {
        msg = '@';
        SetEvent(handles[0]);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public
    ///////////////////////////////////////////////////////////////////////////////

public:

    Mutex* mutex;
    Array<HANDLE> handles;
    int msg;

}; // end class FsysWatcher_Thread

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

typedef Array<FsysWatcher_Thread*> threads_t;
static threads_t* threads = NULL;

///////////////////////////////////////////////////////////////////////////////
// fsys-watcher
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t init () 
{
    threads = ex_new threads_t();
    files = ex_new files_t();
    dirs = ex_new dirs_t();
    dir_to_handle = ex_new dir_to_handle_t();
    handle_to_files = ex_new handle_to_files_t();
    return ex::EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

result_t deinit () 
{
    for ( threads_t::iterator iter = threads->begin(); iter != threads->end(); ++iter ) {
        (*iter)->stop();
        (*iter)->kill();
        // ex_safe_delete(*iter);
    }
    ex_safe_delete(threads);
    ex_safe_delete(files);
    ex_safe_delete(dirs);
    ex_safe_delete(dir_to_handle);
    ex_safe_delete(handle_to_files);
    return ex::EResult::ok;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void add_path ( const wpath_t& _path )
{ 
    ex_assert ( ex::futil::exists(_path), "the path do not exists %s", _path.absPath().c_str() );

    bool isDir = ex::futil::isdir(_path); 

    // get absolute path & directory path.
    wpath_t absPath = _path.absPath();
    wpath_t dirPath = isDir ? absPath : absPath.dirName();

    // if we found the path, don't go any further.
    if ( isDir ) {
        Array<wpath_t>::iterator iter = dirs->find(absPath);
        if ( iter != dirs->end() ) {
            return;
        }
    }
    else {
        Array<wpath_t>::iterator iter = files->find(absPath);
        if ( iter != files->end() ) {
            return;
        }
    }

    // create the notification handle
    const uint flags = (FILE_NOTIFY_CHANGE_DIR_NAME
                        | FILE_NOTIFY_CHANGE_FILE_NAME
                        | FILE_NOTIFY_CHANGE_ATTRIBUTES
                        | FILE_NOTIFY_CHANGE_SIZE
                        | FILE_NOTIFY_CHANGE_LAST_WRITE
                        | FILE_NOTIFY_CHANGE_SECURITY);


    // check if the handle exists
    bool new_handle = false;
    HANDLE handle = INVALID_HANDLE_VALUE; {
        dir_to_handle_t::iterator iter = dir_to_handle->find(dirPath);
        if ( iter == dir_to_handle->end() ) {
            handle = ::FindFirstChangeNotificationW( (wchar_t*)(dirPath.nativePath().c_str()), false, flags );
            dir_to_handle->insert( dirPath, handle );
            new_handle = true;
        }
        else {
            handle = *iter;
        }
        ex_assert ( handle != INVALID_HANDLE_VALUE, "failed to create file notification handle." );
    }

    // push file/dir path to the handle
    handle_to_files_t::iterator it_fileInfos = handle_to_files->find(handle);
    FileInfo fileInfo;
    fileInfo.id = ex::futil::file::fileID (absPath);
    fileInfo.path = absPath;
    if ( it_fileInfos == handle_to_files->end() ) {
        file_infos_t fileInfos;
        fileInfos.push_back(fileInfo);
        handle_to_files->insert ( handle, fileInfos );
    }
    else
    {
        (*it_fileInfos).push_back(fileInfo);
    }

    // check if any thread still have slot for wait_objects.
    if ( new_handle ) {
        bool found = false;
        for ( threads_t::iterator iter = threads->begin(); iter != threads->end(); ++iter ) {
            TAutoLock<Mutex> lock( (*iter)->mutex );
            if ( (*iter)->handles.size() < MAXIMUM_WAIT_OBJECTS ) {
                (*iter)->handles.push_back ( handle );
                (*iter)->wakeup();
                found = true;
                break;
            }
        }

        // if we don't have the thread, create it.
        if ( !found ) {
            FsysWatcher_Thread* new_thread = ex_new FsysWatcher_Thread();
            new_thread->setAutoRelease(true);
            new_thread->handles.push_back ( handle );
            threads->push_back(new_thread);
            new_thread->msg = '@';
            new_thread->start();
        }
    }

    //
    if ( isDir )
        dirs->push_back(absPath);
    else
        files->push_back(absPath);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void register_fileChanged ( file_changed_pfn_t _pfn )
{
    pfn_fileChanged = _pfn;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void register_dirChanged ( dir_changed_pfn_t _pfn )
{
    pfn_dirChanged = _pfn;
}

// ######################### 
} // end namespace watcher 
// ######################### 

// ######################### 
} // end namespace fsys 
// ######################### 

// ######################### 
} // end namespace ex 
// ######################### 

