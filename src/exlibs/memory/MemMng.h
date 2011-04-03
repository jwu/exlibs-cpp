// ======================================================================================
// File         : MemMng.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:20:14 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MEMMNG_H_1250526017
#define MEMMNG_H_1250526017
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "container/HashMap.h"
#include "pattern/singleton_macro.h"

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// class MemMng
// 
// Purpose: memory manager help debug
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL MemMng
{
    ///////////////////////////////////////////////////////////////////////////////
    // singleton decl
    ///////////////////////////////////////////////////////////////////////////////

    EX_DECL_SINGLETON ( MemMng );

    ///////////////////////////////////////////////////////////////////////////////
    // internal structures 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    ///////////////////////////////////////////////////////////////////////////////
    // class AllocInfo 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    struct AllocInfo 
    {
        size_t          originalSize;
        size_t          debugSize;
        void*           originalAddr;
        void*           debugAddr;
        const char*     tagName;
        const char*     fileName;
        const char*     functionName;
        size_t          lineNr;
        EMemop::Enum    memopType;
        bool            breakonFree;
        bool            breakonRealloc;
        size_t          allocNr;
        uint32          threadID;
        Allocator*      allocator;
        AllocInfo*      next;
        AllocInfo*      prev;
    }; // end struct AllocInfo 

    ///////////////////////////////////////////////////////////////////////////////
    // struct ViolationInfo 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    struct ViolationInfo
    {
        ViolationInfo()
            : violationFlags(0),
              allocInfo(NULL)
        {
        }

        uint32      violationFlags;
        AllocInfo*  allocInfo;  
    }; // end struct ViolationInfo


    // ------------------------------------------------------------------
    // Desc: const values 
    // ------------------------------------------------------------------

#if ( EX_COMPILER == EX_MSVC )
    static const uint MAX_HASH          = 4096;
    static const uint MAX_NEW_ALLOCINFO = 256;
    static const uint32 PREFIX_PATTERN  = 0xABBCCDDA;
    static const uint32 SUFFIX_PATTERN  = 0xFEEDDCCF;
    static const uint32 MAX_PATTERN  = 2;
#elif ( EX_COMPILER == EX_GCC )
    enum { MAX_NEW_ALLOCINFO = 256 };
    enum { MAX_HASH = 4096 };
    enum { PREFIX_PATTERN = 0xABBCCDDA };
    enum { SUFFIX_PATTERN = 0xFEEDDCCF };
    enum { MAX_PATTERN = 2 };
#endif 

    ///////////////////////////////////////////////////////////////////////////////
    // public member 
    ///////////////////////////////////////////////////////////////////////////////

public:

    MemMng();
    ~MemMng();

    // ========================================================
    // type defines
    // ========================================================

    typedef MemMng self_t;
    typedef Pair<const void*,AllocInfo*> AllocInfoPair_t;
    typedef HashMap< void*,
                     AllocInfo*,
                     Hash<void*>, 
                     EqualTo<void*>, 
                     NoManaged<NullType>::TAllocator >              AllocInfoHashMap_t;
    typedef List< AllocInfo*, NoManaged<NullType>::TAllocator >     AllocInfoList_t;
    typedef List< ViolationInfo, NoManaged<NullType>::TAllocator >  ViolationInfoList_t;

public:

    //
    void init ();

    // 
    void* alloc ( size_t _size, 
                  Allocator* _pAllocator,
                  const char* _tagName,
                  const char* _fileName,
                  const char* _functionName,
                  size_t _line,
                  EMemop::Enum _memopType );
    //
    void* allocAligned ( size_t _size, 
                         uint _alignment,
                         Allocator* _pAllocator,
                         const char* _tagName,
                         const char* _fileName,
                         const char* _functionName,
                         size_t _line,
                         EMemop::Enum _memopType );

    //
    void* realloc ( void* _ptr,
                    size_t _newSize,
                    Allocator* _pAllocator,
                    const char* _tagName,
                    const char* _fileName,
                    const char* _functionName,
                    size_t _line,
                    EMemop::Enum _memopType );
    //
    void* reallocAligned ( void* _ptr,
                           size_t _newSize,
                           uint _alignment,
                           Allocator* _pAllocator,
                           const char* _tagName,
                           const char* _fileName,
                           const char* _functionName,
                           size_t _line,
                           EMemop::Enum _memopType );
    //
    void free ( void* _ptr,
                Allocator* _pAllocator,
                const char* _fileName,
                const char* _functionName,
                size_t _line,
                EMemop::Enum _memopType );

    //
    void dump() const;
    void checkMemoryLeak() const;
    void checkMemoryViolation() const;

    ///////////////////////////////////////////////////////////////////////////////
    // private:
    ///////////////////////////////////////////////////////////////////////////////

private:
    // 
    AllocInfo* requestAllocInfo();
    result_t pushAllocInfo( AllocInfo* _pAllocInfo );
    result_t rearrangeAllocInfo( AllocInfo* _pAllocInfo, AllocInfoHashMap_t::iterator _iter );
    result_t reclaimAllocInfo( AllocInfo* _pAllocInfo, AllocInfoHashMap_t::iterator _iter );
    AllocInfoHashMap_t::iterator findAllocInfo( void* _ptr );

    //
    result_t verifyPattern( AllocInfo* _pAllocInfo, const char* _fileName, const char* _functionName, size_t _line );
    result_t verifyMemop( AllocInfo* _pAllocInfo, EMemop::Enum _freeType, const char* _fileName, const char* _functionName, size_t _line );

    //
    size_t  calculateDebugSize( size_t _size );

    ///////////////////////////////////////////////////////////////////////////////
    // private member
    ///////////////////////////////////////////////////////////////////////////////

private:

    //
    AllocInfo*          m_pReserveAllocInfo;
    AllocInfoHashMap_t  m_allocInfoHashMap;    
    AllocInfoList_t     m_allocInfoList;

    // memory record information 
    size_t          m_allocUnitCount;
    size_t          m_totalOriginalMemory;      
    size_t          m_totalDebugMemory;
    size_t          m_accumulateOriginalMemory;
    size_t          m_accumulateDebugMemory;

    // memory debug protector 
    size_t          m_patternSize[MAX_PATTERN];
    size_t          m_patternCount[MAX_PATTERN];
    uint32          m_verifyFlags;

    // memory debug check members
    ViolationInfoList_t     m_violationInfoList;

    //
    char*           m_memleakLogFile;
    Mutex*          m_accessMutex;

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        string_t string;
        return string;
    }

}; // end class MemMng

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END MEMMNG_H_1250526017
// #################################################################################
