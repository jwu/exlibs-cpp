// ======================================================================================
// File         : Version.h
// Author       : Wu Jie 
// Last Change  : 03/21/2010 | 17:54:10 PM | Sunday,March
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef VERSION_H_1269165252
#define VERSION_H_1269165252
// #################################################################################

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class Version 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL Version
{
    ///////////////////////////////////////////////////////////////////////////////
    // public
    ///////////////////////////////////////////////////////////////////////////////

public:

    Version ( uint16 _major, uint16 _minor, uint _patch )
        : m_major (_major)
        , m_minor (_minor)
        , m_patch (_patch)
    {
    }

    INLINE bool operator == ( const Version& _ver ) const
    {
        return m_major == _ver.m_major &&
               m_minor == _ver.m_minor && 
               m_patch == _ver.m_patch;
    }
    INLINE bool operator != ( const Version& _ver ) const { return !(*this == (_ver)); }  
    INLINE bool operator < ( const Version& _ver ) const 
    { 
        if ( m_major < _ver.m_major ) {
            return true;
        } else if ( m_major == _ver.m_major ) {
            if ( m_minor < _ver.m_minor ) {
                return true;
            } else if ( m_minor == _ver.m_minor ) {
                if ( m_patch < _ver.m_patch ) {
                    return true;
                }
            }
        }
        return false;
    }
    INLINE bool operator <= ( const Version& _ver ) const 
    { 
        if ( *this < _ver || *this == _ver )
            return true;
        return false;
    }
    INLINE bool operator > ( const Version& _ver ) const { return !(*this <= _ver);  }
    INLINE bool operator >= ( const Version& _ver ) const { return !(*this < _ver);  }

    INLINE uint16 major () const { return m_major; }
    INLINE uint16 minor () const { return m_minor; }
    INLINE uint16 patch () const { return m_patch; }
    
    template < uint FLAGS > INLINE string_t to_str() const
    {
        string_t string = ex::to_str<FLAGS>(m_major) + "." + 
                          ex::to_str<FLAGS>(m_minor) + "." +
                          ex::to_str<FLAGS>(m_patch) ;
        return string;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    uint16 m_major;
    uint16 m_minor;
    uint16 m_patch;

}; // end class Version

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END VERSION_H_1269165252
// #################################################################################

