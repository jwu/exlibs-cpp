// ======================================================================================
// File         : SerializeNode.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:25:36 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef SERIALIZENODE_H_1250526339
#define SERIALIZENODE_H_1250526339
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "file/File.h"

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// class ISerializeNode 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL ISerializeNode : public RuntimeClass
{
    EX_DEF_RUNTIME_CLASS ( ISerializeNode, RuntimeClass );

    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    typedef ISerializeNode* ptr_t;

    ///////////////////////////////////////////////////////////////////////////////
    // class ISerializeNodeIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template< typename Val_T, typename Ref_T, typename Ptr_T >
    class ISerializeNodeIterator : public std::iterator< std::forward_iterator_tag, Val_T, ptrdiff_t, Ptr_T, Ref_T >
    {
        ///////////////////////////////////////////////////////////////////////////////
        // typedefs
        ///////////////////////////////////////////////////////////////////////////////

    public:

        typedef ISerializeNodeIterator<Val_T,Ref_T,Ptr_T>                           iter_self_t; 
        typedef std::iterator< std::forward_iterator_tag, 
                               Val_T, 
                               ptrdiff_t, 
                               Ptr_T, 
                               Ref_T >                                              iter_base_t;
        typedef ISerializeNodeIterator< Val_T, Val_T&, Val_T* >                     iterator_t;
        typedef ISerializeNodeIterator< Val_T, const Val_T&, const Val_T* >         const_iterator_t;

        typedef Val_T       iter_value_t;
        typedef Ptr_T       iter_pointer_t;
        typedef Ref_T       iter_reference_t;

        ///////////////////////////////////////////////////////////////////////////////
        // constructor & destructor
        ///////////////////////////////////////////////////////////////////////////////

    public:

        //
        ISerializeNodeIterator()
            : m_pNode(NULL),
              m_idx(0)
        {
        }

        //
        ISerializeNodeIterator( ISerializeNode* _pNode, uint _idx = 0 )
            : m_pNode(_pNode),
              m_idx(_idx)
        {
        }

        ///////////////////////////////////////////////////////////////////////////////
        // public member functions
        ///////////////////////////////////////////////////////////////////////////////

    public:

        // 
        INLINE iter_self_t& operator ++ () 
        {
            this->_incr();
            return *this;
        }
        INLINE iter_self_t operator ++ (int) 
        {
            iter_self_t _tmp = *this;
            this->_incr();
            return _tmp; 
        }

        // iter += "tag" ==> find next "tag"
        INLINE iter_self_t operator += ( const char* _tag ) 
        {
            iter_value_t pNode;
            do
            {
                this->_incr();
                pNode = *(*this);
                // TODO: confirm this
                if ( pNode && pNode->isTag (_tag) )
                {
                    break;
                }
            } while ( pNode );

            return *this;
        }

        //
        INLINE bool operator == ( const iter_self_t& _cmp_iter ) const { return (m_pNode == _cmp_iter.m_pNode) && (m_idx == _cmp_iter.m_idx); } 
        INLINE bool operator != ( const iter_self_t& _cmp_iter ) const { return !( (*this) == _cmp_iter ); } 

        //
        iter_value_t operator * () const 
        {
            //
            if( !m_pNode )
                return NULL;
            //
            if( m_idx < m_pNode->childCount() )
            {
                return m_pNode->child(m_idx);
            }
            //
            return NULL;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // protected member functions
        ///////////////////////////////////////////////////////////////////////////////

    protected:

        void _incr() { ++m_idx; }

        ///////////////////////////////////////////////////////////////////////////////
        // protected member data
        ///////////////////////////////////////////////////////////////////////////////

    protected:

        ISerializeNode*   m_pNode;
        uint              m_idx;

    }; // end class ISerializeNodeIterator

    typedef ISerializeNodeIterator<ptr_t,ptr_t&,ptr_t*>                 iterator;
    typedef ISerializeNodeIterator<ptr_t,const ptr_t&,const ptr_t*>     c_iterator;

    ///////////////////////////////////////////////////////////////////////////////
    // iterator operations
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    INLINE iterator begin() { return iterator ( this, 0 ); }
    INLINE c_iterator begin() const { return c_iterator ( const_cast<ISerializeNode*>(this), 0 ); }

    // 
    INLINE iterator begin ( const char* _tagName ) { return iterator( this, this->firstChild(_tagName) ); }
    INLINE c_iterator begin ( const char* _tagName ) const { return c_iterator( const_cast<ISerializeNode*>(this), this->firstChild(_tagName) ); }

    //
    INLINE iterator end() { return iterator( this, this->childCount() ); }
    INLINE c_iterator end() const { return c_iterator( const_cast<ISerializeNode*>(this), this->childCount() ); }

    // TODO:
    // iterator FindChildIterator( const char* _tagName );
    // c_iterator FindChildIterator( const char* _tagName ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    ISerializeNode () 
        : m_IsLoading (false)
        , m_IsSaving (false)
    {
    }
    virtual ~ISerializeNode () {}

    //
    bool isValid () const 
    {
        bool valid = true; 
        valid = valid && (m_IsLoading || m_IsSaving); 
        return valid;
    }

    //
    void setLoading () { m_IsLoading = true; m_IsSaving = false; }
    void setSaving () { m_IsLoading = false; m_IsSaving = true; }

    //
    bool isLoading () const { return m_IsLoading; }
    bool isSaving () const { return m_IsSaving; }

    //
    void cloneState ( const ISerializeNode * _pNode )
    {
        m_IsLoading = _pNode->m_IsLoading;
        m_IsSaving = _pNode->m_IsSaving;
    }

    // ========================================================
    // child
    // ========================================================

    virtual void addChild( const char* _tagName, ISerializeNode* _pNode ) = 0;
    virtual ISerializeNode* newChild( const char* _tagName ) = 0;
    virtual bool removeChild( ISerializeNode* _pNode ) = 0;

    virtual uint firstChild( const char* _tagName ) const = 0;
    virtual ISerializeNode* nextChild( const char* _tagName ) = 0;
    virtual ISerializeNode* child( uint _idx ) const = 0;

    virtual uint childCount() const = 0;
    virtual uint childCount( const char* _tagName ) const = 0;

    // ========================================================
    // tag
    // ========================================================

    virtual const char* tag() const = 0;
    virtual bool isTag( const char* _tagName ) const = 0;

    // ========================================================
    // attribute 
    // ========================================================

    virtual uint attrCount() const = 0;
    virtual bool hasAttr( const char* _key ) const = 0;
    virtual bool removeAttr( const char* _key ) = 0;

    // ======================================================== 
    // file 
    // ======================================================== 

    virtual result_t saveToFile ( const char* fileName ) const = 0;
    virtual result_t loadFromFile ( const char* fileName ) = 0;

    virtual result_t saveToFile ( IFile::smart_ptr_t _spFile, futil::sz_t* _pBytesSaved = NULL ) const = 0;
    virtual result_t loadFromFile ( IFile::smart_ptr_t _spFile, futil::sz_t _bytesToLoad ) = 0;

    virtual result_t loadFromBuffer ( void* _pData, uint _bufferSize ) = 0;

    // ======================================================== 
    // Get/Set Attr 
    // ======================================================== 

    // bool
    virtual void setAttr ( const char* _key, bool _value ) = 0;
    virtual result_t getAttr ( const char* _key, bool* _pValue ) const = 0;

    // int8
    virtual void setAttr ( const char* _key, int8 _value ) = 0;
    virtual result_t getAttr ( const char* _key, int8* _pValue ) const = 0;

    // uint8
    virtual void setAttr ( const char* _key, uint8 _value ) = 0;
    virtual result_t getAttr ( const char* _key, uint8* _pValue ) const = 0;

    // int16
    virtual void setAttr ( const char* _key, int16 _value ) = 0;
    virtual result_t getAttr ( const char* _key, int16* _pValue ) const = 0;

    // uint16
    virtual void setAttr ( const char* _key, uint16 _value ) = 0;
    virtual result_t getAttr ( const char* _key, uint16* _pValue ) const = 0;

    // int32
    virtual void setAttr ( const char* _key, int32 _value ) = 0;
    virtual result_t getAttr ( const char* _key, int32* _pValue ) const = 0;

    // uint32
    virtual void setAttr ( const char* _key, uint32 _value ) = 0;
    virtual result_t getAttr ( const char* _key, uint32* _pValue ) const = 0;

    // int64
    virtual void setAttr ( const char* _key, int64 _value ) = 0;
    virtual result_t getAttr ( const char* _key, int64* _pValue ) const = 0;

    // uint64
    virtual void setAttr ( const char* _key, uint64 _value ) = 0;
    virtual result_t getAttr ( const char* _key, uint64* _pValue ) const = 0;

    // DISABLE { 
    // // int
    // virtual void setAttr ( const char* _key, int _value ) = 0;
    // virtual result_t getAttr ( const char* _key, int* _pValue ) const = 0;

    // // uint
    // virtual void setAttr ( const char* _key, uint _value ) = 0;
    // virtual result_t getAttr ( const char* _key, uint* _pValue ) const = 0;
    // } DISABLE end 

    // float
    virtual void setAttr ( const char* _key, float _value ) = 0;
    virtual result_t getAttr ( const char* _key, float* _pValue ) const = 0;

    // double
    virtual void setAttr ( const char* _key, double _value ) = 0;
    virtual result_t getAttr ( const char* _key, double* _pValue ) const = 0;

    // char
    virtual void setAttr ( const char* _key, char _value ) = 0;
    virtual result_t getAttr ( const char* _key, char* _pValue ) const = 0;

    // const char*
    virtual void setAttr ( const char* _key, const char* _value ) = 0;
    virtual result_t getAttr ( const char* _key, const char** _pValue ) const = 0;

    // const wchar*
    virtual void setAttr ( const char* _key, const wchar* _value ) = 0;
    virtual result_t getAttr ( const char* _key, const wchar** _pValue ) const = 0;

    // void*
    virtual void setAttr ( const char* _key, const void* _value, uint _bytes ) = 0;
    virtual result_t getAttr ( const char* _key, void** _pValue, uint _bytes ) const = 0;

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    bool m_IsLoading;
    bool m_IsSaving;

}; // end class ISerializeNode

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END SERIALIZENODE_H_1250526339
// #################################################################################

