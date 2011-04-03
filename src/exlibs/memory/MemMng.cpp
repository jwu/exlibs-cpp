// ======================================================================================
// File         : MemMng.cpp
// Author       : Wu Jie 
// Last Change  : 03/26/2010 | 19:23:15 PM | Friday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//  includes 
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"
#include "MemMng.h"

// #########################
namespace ex { 
// #########################

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define PRE_PATTERN_IDX   0
#define POST_PATTERN_IDX  1

// ------------------------------------------------------------------
// Desc: verify method 
// ------------------------------------------------------------------

#define VERIFY_PRE_PATTERN      0x00000001
#define VERIFY_POST_PATTERN     0x00000010
#define VERIFY_FREE             0x00000100
#define VERIFY_REALLOC          0x00001000
#define VERIFY_MEMOP            0x00010000

// ------------------------------------------------------------------
// Desc: violation type
// ------------------------------------------------------------------

#define VIOLATION_OVERFLOW          0x00000001
#define VIOLATION_WRONG_DEALLOC     0x00000010
#define VIOLATION_ILLEGAL_WRITTEN   0x00000100

///////////////////////////////////////////////////////////////////////////////
// member function defines 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

MemMng::MemMng()
    : m_pReserveAllocInfo(NULL)
    , m_allocUnitCount(0)
    , m_totalOriginalMemory(0)      
    , m_totalDebugMemory(0)
    , m_accumulateOriginalMemory(0)
    , m_accumulateDebugMemory(0)
    , m_verifyFlags(0)
    , m_memleakLogFile (NULL)
    , m_accessMutex (NULL)
{
    m_allocInfoHashMap.resize(MAX_HASH);    

    //
    // |________________| |________________________| |_________________|
    //  PRE_PATTERN_SIZE        _size_to_alloc        POST_PATTERN_SIZE
    //

    // pre-pattern
    m_patternCount[PRE_PATTERN_IDX] = 4; // 4 * sizeof(uint32) == 16Byte
    m_patternSize[PRE_PATTERN_IDX] = sizeof(uint32) * m_patternCount[PRE_PATTERN_IDX];

    // post-pattern
    m_patternCount[POST_PATTERN_IDX] = 4; // 4 * sizeof(uint32) == 16Byte
    m_patternSize[POST_PATTERN_IDX] = sizeof(uint32) * m_patternCount[POST_PATTERN_IDX];

    //
    flags_add( m_verifyFlags, VERIFY_PRE_PATTERN );
    flags_add( m_verifyFlags, VERIFY_POST_PATTERN );
    flags_add( m_verifyFlags, VERIFY_FREE );
    flags_add( m_verifyFlags, VERIFY_REALLOC );
    flags_add( m_verifyFlags, VERIFY_MEMOP );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

MemMng::~MemMng()
{
    // TODO: dump here?
    dump();
    ex_free_nomng(m_memleakLogFile, EX_GP(EX_ALLOCATOR));

    // clear
    m_allocInfoHashMap.clear();

    // free the reserve alloc info buffer
    AllocInfoList_t::iterator iter = m_allocInfoList.begin(); 
    AllocInfoList_t::iterator iterEnd = m_allocInfoList.end(); 
    for ( ; iter != iterEnd; ++iter )
        ex_free_nomng ( *iter, EX_GP(EX_ALLOCATOR) );
    m_allocInfoList.clear();
    m_violationInfoList.clear();

    // destroy mutex
    ex_delete_nomng ( m_accessMutex, EX_GP(EX_ALLOCATOR) );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void MemMng::init()
{
    // create local mutex
    if ( m_accessMutex == NULL )
        m_accessMutex = ex_new_nomng(EX_GP(EX_ALLOCATOR)) Mutex (); 

    // 
    const char* logFileName = NULL;
    if ( ex::core_t::config() )
    {
        logFileName = ex::core_t::config()->get<const char*>("memleak_log"); 
    }

    // if we don't get MemleakLog path, use this as default.
    if ( (logFileName == NULL) || ex::str::cmp (logFileName, "") == 0 ) 
    {
        logFileName = "./memleak.err";
    }

    // NOTE: the m_memleakLogFile used in dump would be destroy at first if direct come from config parser
    uint len = str::len (logFileName);
    m_memleakLogFile = (char*)ex_malloc_nomng(sizeof(char) * (len+1), EX_GP(EX_ALLOCATOR));
    ex::mem::zero ( m_memleakLogFile, len+1 );
    str::ncpy ( m_memleakLogFile, len, logFileName, len );
    unlink( m_memleakLogFile );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void* MemMng::alloc ( size_t _size, Allocator* _pAllocator, const char* _tagName, const char* _fileName, const char* _functionName, size_t _line, EMemop::Enum _memopType )
{
    return allocAligned( _size, EX_DEFAULT_ALIGNMENT, _pAllocator, _tagName, _fileName, _functionName, _line, _memopType );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void* MemMng::allocAligned ( size_t _size, uint _alignment, Allocator* _pAllocator, const char* _tagName, const char* _fileName, const char* _functionName, size_t _line, EMemop::Enum _memopType )
{
#ifdef EX_USE_MULTI_THREAD
    // auto-lock local mutex
    TAutoLock<Mutex> lock(m_accessMutex);
#endif

    //
    ex_assert( _pAllocator, "Allocator can't be NULL" );

    // ANSI says: allocation requests of 0 bytes will still return a valid value
    if ( _size == 0) _size = 1;

    // use allocator to allocate memory
    size_t dbgSize = calculateDebugSize(_size);
    void* dbgPtr = _pAllocator->allocAligned( dbgSize, _alignment );
    void* orgPtr = (void*)( (int8*)dbgPtr + m_patternSize[PRE_PATTERN_IDX] );

    // get AllocInfo, if not, create one
    AllocInfo* pAllocInfo = requestAllocInfo();
    ex_assert( pAllocInfo, "AllocInfo not found, check if the _ptr have been free or invalid" );
    // write information
    pAllocInfo->originalSize     = _size;
    pAllocInfo->debugSize        = dbgSize;
    pAllocInfo->debugAddr     = dbgPtr;
    pAllocInfo->originalAddr  = orgPtr;
    pAllocInfo->tagName          = _tagName;
    pAllocInfo->fileName         = _fileName;
    pAllocInfo->functionName     = _functionName;
    pAllocInfo->lineNr             = _line;
    pAllocInfo->memopType        = _memopType;
    pAllocInfo->breakonFree      = false;
    pAllocInfo->breakonRealloc   = false;
    pAllocInfo->allocator        = _pAllocator;
    pAllocInfo->allocNr = m_allocUnitCount;
    pAllocInfo->threadID         = cur_threadID() ;

    //
    // |________________| |________________________| |_________________|
    //  PRE_PATTERN_SIZE        _size_to_alloc        POST_PATTERN_SIZE
    //

    // add protector
    uint32* pre  = (uint32*)dbgPtr;
    uint32* post = (uint32*)( (int8*)orgPtr + _size );

    // add pre&post pattern
    for( uint iPre = 0; iPre < m_patternCount[PRE_PATTERN_IDX]; ++iPre, ++pre )
        *pre = PREFIX_PATTERN;
    for( uint iPost = 0; iPost < m_patternCount[POST_PATTERN_IDX]; ++iPost, ++post )
        *post = SUFFIX_PATTERN;

    // Record memory information
    m_allocUnitCount            += 1;
    m_totalOriginalMemory       += pAllocInfo->originalSize;      
    m_totalDebugMemory          += pAllocInfo->debugSize;
    m_accumulateOriginalMemory  += pAllocInfo->originalSize;
    m_accumulateDebugMemory     += pAllocInfo->debugSize;

    // finally push the alloc info into hash_list 
    ex_check( pushAllocInfo(pAllocInfo) == EResult::ok, "" );

    return orgPtr;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void* MemMng::realloc ( void* _ptr, size_t _newSize, Allocator* _pAllocator, const char* _tagName, const char* _fileName, const char* _functionName, size_t _line, EMemop::Enum _memopType )
{
    return reallocAligned( _ptr, _newSize, EX_DEFAULT_ALIGNMENT, _pAllocator, _tagName, _fileName, _functionName, _line, _memopType );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void* MemMng::reallocAligned ( void* _ptr, size_t _newSize, uint _alignment, Allocator* _pAllocator, const char* _tagName, const char* _fileName, const char* _functionName, size_t _line, EMemop::Enum _memopType )
{
#ifdef EX_USE_MULTI_THREAD
    // auto-lock local mutex
    TAutoLock<Mutex> lock(m_accessMutex);
#endif

    // alloc NULL memory address
    if ( _ptr == NULL )
    {
        return allocAligned( _newSize, _alignment, _pAllocator, _tagName, _fileName, _functionName, _line, _memopType );
    }

    // realloc zero bytes free 
    if ( _newSize == 0 ) 
    {
        free( _ptr, _pAllocator, _fileName, _functionName, _line, _memopType );
        return NULL;
    }

    // find AllocInfo* by address
    AllocInfoHashMap_t::iterator iter = findAllocInfo(_ptr); 
    AllocInfo* pAllocInfo = (*iter);
    ex_assert( pAllocInfo, "AllocInfo not found, check if the _ptr have been free or invalid" );

    // verify memory conflic first if needed
    if ( flags_has( m_verifyFlags, VERIFY_REALLOC) )
        verifyPattern( pAllocInfo, _fileName, _functionName, _line );

    // verify memory operation
    if ( flags_has( m_verifyFlags, VERIFY_MEMOP) )
        verifyMemop( pAllocInfo, _memopType, _fileName, _functionName, _line );

    // check allocator
    if ( _pAllocator == NULL )
        _pAllocator = pAllocInfo->allocator;
    ex_assert( _pAllocator==pAllocInfo->allocator, "Allocator not the same" );

    // remove original memory information
    m_totalOriginalMemory -= pAllocInfo->originalSize;      
    m_totalDebugMemory    -= pAllocInfo->debugSize;

    // use allocator to allocate memory
    size_t dbgSize = calculateDebugSize(_newSize);
    void* dbgPtr = _pAllocator->reallocAligned( pAllocInfo->debugAddr, dbgSize, _alignment );
    void* orgPtr = (void*)( (int8*)dbgPtr + m_patternSize[PRE_PATTERN_IDX] );

    // write information
    pAllocInfo->originalSize     = _newSize;
    pAllocInfo->debugSize        = dbgSize;
    pAllocInfo->debugAddr     = dbgPtr;
    pAllocInfo->originalAddr  = orgPtr;
    pAllocInfo->tagName          = _tagName;
    pAllocInfo->fileName         = _fileName;
    pAllocInfo->functionName     = _functionName;
    pAllocInfo->lineNr             = _line;
    pAllocInfo->memopType        = _memopType;
    pAllocInfo->breakonFree      = false;
    pAllocInfo->breakonRealloc   = false;
    pAllocInfo->allocator        = _pAllocator;
    pAllocInfo->allocNr = m_allocUnitCount;
    pAllocInfo->threadID         = cur_threadID() ;

    //
    // |________________| |________________________| |_________________|
    //  PRE_PATTERN_SIZE        _size_to_alloc        POST_PATTERN_SIZE
    //

    // add protector
    uint32* pre  = (uint32*)dbgPtr;
    uint32* post = (uint32*)( (int8*)orgPtr + _newSize );

    // add pre&post pattern
    for( uint iPre = 0; iPre < m_patternCount[PRE_PATTERN_IDX]; ++iPre, ++pre )
        *pre = PREFIX_PATTERN;
    for( uint iPost = 0; iPost < m_patternCount[POST_PATTERN_IDX]; ++iPost, ++post )
        *post = SUFFIX_PATTERN;

    // Record memory information
    m_totalOriginalMemory       += pAllocInfo->originalSize;      
    m_totalDebugMemory          += pAllocInfo->debugSize;
    m_accumulateOriginalMemory  += pAllocInfo->originalSize;
    m_accumulateDebugMemory     += pAllocInfo->debugSize;

    // finally push the alloc info into hash_list 
    ex_check( rearrangeAllocInfo(pAllocInfo,iter) == EResult::ok, "" );

    return orgPtr;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void MemMng::free ( void* _ptr, Allocator* _pAllocator, const char* _fileName, const char* _functionName, size_t _line, EMemop::Enum _memopType )
{
#ifdef EX_USE_MULTI_THREAD
    // auto-lock local mutex
    TAutoLock<Mutex> lock(m_accessMutex);
#endif

    // nothing to do with NULL ptr
    if ( _ptr == NULL )
        return;

    // find AllocInfo* by address
    AllocInfoHashMap_t::iterator iter = findAllocInfo(_ptr); 
    AllocInfo* pAllocInfo = (*iter);
    ex_assert( pAllocInfo, "AllocInfo not found, check if the _ptr have been free or invalid" );

    // verify memory conflic first if needed
    if ( flags_has( m_verifyFlags, VERIFY_FREE) )
        verifyPattern( pAllocInfo, _fileName, _functionName, _line );

    // verify memory operation
    if ( flags_has( m_verifyFlags, VERIFY_MEMOP) )
        verifyMemop( pAllocInfo, _memopType, _fileName, _functionName, _line );

    // check allocator
    if ( _pAllocator == NULL )
        _pAllocator = pAllocInfo->allocator;
    ex_assert( _pAllocator==pAllocInfo->allocator, "Allocator not the same" );

    _pAllocator->free( pAllocInfo->debugAddr );

    // remove original memory information
    m_allocUnitCount            -= 1;
    m_totalOriginalMemory       -= pAllocInfo->originalSize;      
    m_totalDebugMemory          -= pAllocInfo->debugSize;
    m_accumulateOriginalMemory  -= pAllocInfo->originalSize;
    m_accumulateDebugMemory     -= pAllocInfo->debugSize;

    // reclaim the alloc info for next alloc
    reclaimAllocInfo(pAllocInfo,iter);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

MemMng::AllocInfo* MemMng::requestAllocInfo()
{
    if ( !m_pReserveAllocInfo )
    {
        // Allocate MAX_NEW_ALLOCINFO reserve alloc-info
        m_pReserveAllocInfo = (AllocInfo*)ex_malloc_nomng( MAX_NEW_ALLOCINFO*sizeof(AllocInfo), EX_GP(EX_ALLOCATOR) );

        // Assert exAllocInfo != NULL
        ex_assert( m_pReserveAllocInfo != NULL, "Out of memory" );

        // Build a linked-list of the elements in our reserve-allocinfo-list
        // memzero setting
        ex::mem::zero( m_pReserveAllocInfo, MAX_NEW_ALLOCINFO*sizeof(AllocInfo) );
        for( uint i = 0; i < MAX_NEW_ALLOCINFO-1; ++i )
        {
            m_pReserveAllocInfo[i].next = m_pReserveAllocInfo + (i+1);
            m_pReserveAllocInfo[i+1].prev = m_pReserveAllocInfo + i; 
        }

        // Add this address to our m_pReserveAllocInfo so we can free it later
        m_allocInfoList.push_back(m_pReserveAllocInfo);
    }

    // this is the standard use of go next and unlink
    AllocInfo* tmpAllocInfo = m_pReserveAllocInfo;
    m_pReserveAllocInfo = m_pReserveAllocInfo->next;

    // unlink the getted alloc info
    tmpAllocInfo->next = NULL;
    tmpAllocInfo->prev = NULL;

    //
    return tmpAllocInfo;
}

// ------------------------------------------------------------------
// Desc:  
// ------------------------------------------------------------------

MemMng::AllocInfoHashMap_t::iterator MemMng::findAllocInfo( void* _ptr )
{
    //
    AllocInfoHashMap_t::iterator iter = m_allocInfoHashMap.find(_ptr);
    ex_assert( iter != m_allocInfoHashMap.end(), "Can't found the AllocInfo by Key: %i", size_t(_ptr) );
    return iter;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t MemMng::pushAllocInfo( AllocInfo* _pAllocInfo )
{
    Pair<AllocInfoHashMap_t::sz_t,result_t> pair = m_allocInfoHashMap.insert(_pAllocInfo->originalAddr, _pAllocInfo);
    return pair.second;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t MemMng::rearrangeAllocInfo( AllocInfo* _pAllocInfo, AllocInfoHashMap_t::iterator _iter )
{
    // TODO: I think check return is good
    // result_t eResult; 
    // ex_check_return( m_allocInfoHashMap.erase(_iter) );
    m_allocInfoHashMap.erase(_iter); 
    return pushAllocInfo(_pAllocInfo);
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t MemMng::reclaimAllocInfo( AllocInfo* _pAllocInfo, AllocInfoHashMap_t::iterator _iter )
{
    m_allocInfoHashMap.erase(_iter); 

    // append to reserve alloc info
    _pAllocInfo->next = m_pReserveAllocInfo;
    _pAllocInfo->prev = NULL;

    // reserve alloc info could be use out
    if ( m_pReserveAllocInfo ) 
        m_pReserveAllocInfo->prev = _pAllocInfo;

    m_pReserveAllocInfo = _pAllocInfo;

    //
    return EResult::ok;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

result_t MemMng::verifyMemop( AllocInfo* _pAllocInfo, EMemop::Enum _freeType, const char* _fileName, const char* _functionName, size_t _line )
{
    uint32 flagsToCheck = uint32(_pAllocInfo->memopType) | (uint32)_freeType;
    if (
        flags_is( EMemop::check_new, flagsToCheck )        ||
        flags_is( EMemop::check_new_array, flagsToCheck )  ||
        flags_is( EMemop::check_malloc, flagsToCheck )     ||
        flags_is( EMemop::check_calloc, flagsToCheck )     ||
        flags_is( EMemop::check_realloc, flagsToCheck )    ||
        flags_hasAll ( EMemop::check_realloc_ptr, flagsToCheck )  
       )
    {
        return EResult::ok;
    }

    // add to violation list
    ViolationInfo vi;
    flags_add( vi.violationFlags, VIOLATION_WRONG_DEALLOC );
    vi.allocInfo = _pAllocInfo;
    m_violationInfoList.push_back(vi);

    //
    ex_warning( "[%s](%d)<%s>::Memory operation not matched", _fileName, _line, _functionName );
    return EResult::verify_failed;
}

// ------------------------------------------------------------------
// Desc:  
// ------------------------------------------------------------------

result_t MemMng::verifyPattern( AllocInfo* _pAllocInfo, const char* _fileName, const char* _functionName, size_t _line )
{
    // verify pre-pattern
    if ( flags_has( m_verifyFlags, VERIFY_PRE_PATTERN ) )
    {
        uint32* pre  = (uint32*)_pAllocInfo->debugAddr;

        //
        for( uint iPre = 0; iPre < m_patternCount[PRE_PATTERN_IDX]; ++iPre, ++pre )
        {
            if( *pre != PREFIX_PATTERN )
            {
                // add to violation list
                ViolationInfo vi;
                flags_add( vi.violationFlags, VIOLATION_ILLEGAL_WRITTEN );
                vi.allocInfo = _pAllocInfo;
                m_violationInfoList.push_back(vi);

                //
                ex_warning( "Memory Prefix Conflict\n"
                            "FielName: %s\n"
                            "lineNr: %d\n"
                            "functionName: %s\n"
                            "alloc threadID: %d\n"
                            "Current threadID: %d\n", 
                            _fileName, _line, _functionName, _pAllocInfo->threadID, cur_threadID() );

                return EResult::verify_failed;
            }
        }
    }

    // verify post-pattern
    if ( flags_has( m_verifyFlags, VERIFY_POST_PATTERN ) )
    {
        uint32* post = (uint32*)( (int8*)_pAllocInfo->debugAddr + m_patternSize[PRE_PATTERN_IDX] + _pAllocInfo->originalSize );

        //
        for( uint iPost = 0; iPost < m_patternCount[POST_PATTERN_IDX]; ++iPost, ++post )
        {
            if( *post != SUFFIX_PATTERN )
            {
                // add to violation list
                ViolationInfo vi;
                flags_add( vi.violationFlags, VIOLATION_OVERFLOW );
                vi.allocInfo = _pAllocInfo;
                m_violationInfoList.push_back(vi);

                //
                ex_warning( "Memory Postfix Conflict\n"
                            "FielName: %s\n"
                            "lineNr: %d\n"
                            "functionName: %s\n"
                            "alloc threadID: %d\n"
                            "Current threadID: %d\n", 
                            _fileName, _line, _functionName, _pAllocInfo->threadID, cur_threadID() );

                return EResult::verify_failed;
            }
        }
    }

    return EResult::ok;
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

size_t MemMng::calculateDebugSize( size_t _size )
{
    return _size + m_patternSize[PRE_PATTERN_IDX] + m_patternSize[POST_PATTERN_IDX];
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void MemMng::dump() const
{
    checkMemoryLeak();
    checkMemoryViolation();
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void MemMng::checkMemoryLeak() const
{
    //
    ex_assert( m_allocInfoHashMap.size() == 0, "There are %d place(s) exsits memory leak.",  m_allocInfoHashMap.size() );

    //
    if ( m_allocInfoHashMap.size() )
    {
        AllocInfoHashMap_t::c_iterator iter = m_allocInfoHashMap.begin();
        AllocInfoHashMap_t::c_iterator iterEnd = m_allocInfoHashMap.end();
        for ( ; iter != iterEnd; ++iter )
        {
            AllocInfo* pAllocInfo = (*iter); 
            String<char,NoManaged<NullType>::TAllocator> strAddr, strSize, strAllocNum, strTemp;

            // make expr string
            String<char,NoManaged<NullType>::TAllocator> strExpr; 

            // fileName:lineNr: error memory leak
            get_str<dec> ( pAllocInfo->fileName, &strTemp );
            strExpr += strTemp + ":";
            get_str<dec> ( uint32(pAllocInfo->lineNr), &strTemp );
            strExpr += strTemp + ":";
            strExpr += " error memory leak \r\n";

            // function name
            get_str<dec> ( pAllocInfo->functionName, &strTemp );
            strExpr += "    functionName:     " + strTemp + "\r\n";

            // tag name
            get_str<dec> ( pAllocInfo->tagName, &strTemp );
            strExpr += "    Tag Name:         " + strTemp + "\r\n"; 

            // address
            get_str<hex> ( pAllocInfo->originalAddr, &strTemp );
            strExpr += "    Original Addr:    " + strTemp + "\r\n"; 
            get_str<hex> ( pAllocInfo->debugAddr, &strTemp );
            strExpr += "    Debug Addr:       " + strTemp + "\r\n"; 

            // size
            get_str<dec|hex> ( uint32(pAllocInfo->originalSize), &strTemp );
            strExpr += "    Original size:    " + strTemp + " bytes\r\n";
            get_str<dec|hex> ( uint32(pAllocInfo->debugSize), &strTemp );
            strExpr += "    Debug size:       " + strTemp + " bytes\r\n";

            // alloc nr.
            get_str<dec|hex> ( uint32(pAllocInfo->allocNr), &strTemp );
            strExpr += "    alloc Nr.:        " + strTemp + "\r\n"; 

            // thread ID
            get_str<dec|hex> ( uint32(pAllocInfo->threadID), &strTemp );
            strExpr += "    Thread ID:        " + strTemp + "\r\n"; 

            // format log info
            logf( m_memleakLogFile, "%s", strExpr.c_str() );
        }
    }
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void MemMng::checkMemoryViolation() const
{
}

// #########################
} // end namespace ex 
// #########################

