// ======================================================================================
// File         : XmlNode.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:27:44 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef XMLNODE_H_1250526466
#define XMLNODE_H_1250526466
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "XmlAttribute.h"

// #########################
namespace ex { 
// #########################


///////////////////////////////////////////////////////////////////////////////
// class XmlNode 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class EX_LIBS_DLL XmlNode
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs 
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    typedef SmartPtr<XmlNode> smart_ptr_t;

    //
    typedef Array<XmlNode::smart_ptr_t> xml_nodes_t; 
    typedef Array<XmlAttribute> xml_attributes_t;

    ///////////////////////////////////////////////////////////////////////////////
    // iterator 
    ///////////////////////////////////////////////////////////////////////////////

public:

    ///////////////////////////////////////////////////////////////////////////////
    // class TXmlNodeIterator 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template< typename Val_T, typename Ref_T, typename Ptr_T >
    class TXmlNodeIterator : public std::iterator< std::forward_iterator_tag, Val_T, ptrdiff_t, Ptr_T, Ref_T >
    {
        ///////////////////////////////////////////////////////////////////////////////
        // typedefs
        ///////////////////////////////////////////////////////////////////////////////

    public:
        typedef TXmlNodeIterator<Val_T,Ref_T,Ptr_T>                          iter_self_t; 
        typedef std::iterator< std::forward_iterator_tag, 
                               Val_T, 
                               ptrdiff_t, 
                               Ptr_T, 
                               Ref_T >                                       iter_base_t;
        typedef TXmlNodeIterator< Val_T, Val_T&, Val_T* >                    iterator_t;
        typedef TXmlNodeIterator< Val_T, const Val_T&, const Val_T* >        const_iterator_t;

        typedef Val_T       iter_value_t;
        typedef Ptr_T       iter_pointer_t;
        typedef Ref_T       iter_reference_t;

        ///////////////////////////////////////////////////////////////////////////////
        // constructor & destructor
        ///////////////////////////////////////////////////////////////////////////////

    public:

        //
        TXmlNodeIterator()
            : m_spNode(XmlNode::smart_ptr_t(NULL)),
              m_idx(0)
        {
        }

        //
        TXmlNodeIterator( const XmlNode::smart_ptr_t& _spNode, uint _idx = 0 )
            : m_spNode(_spNode),
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
            iter_value_t spNode;
            do
            {
                this->_incr();
                spNode = *(*this);
                if ( spNode && spNode->isTag (_tag) )
                {
                    break;
                }
            } while ( spNode );

            return *this;
        }

        //
        INLINE bool operator == ( const iter_self_t& _cmp_iter ) const { return (m_spNode == _cmp_iter.m_spNode) && (m_idx == _cmp_iter.m_idx); } 
        INLINE bool operator != ( const iter_self_t& _cmp_iter ) const { return !( (*this) == _cmp_iter ); } 

        //
        iter_value_t operator * () const 
        {
            //
            if( !m_spNode )
                return XmlNode::smart_ptr_t(NULL);
            //
            if( m_idx < m_spNode->childCount() )
            {
                return m_spNode->child(m_idx);
            }
            //
            return XmlNode::smart_ptr_t(NULL);
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

        XmlNode::smart_ptr_t   m_spNode;
        uint                   m_idx;

    }; // end class TXmlNodeIterator

    typedef TXmlNodeIterator<smart_ptr_t,smart_ptr_t&,smart_ptr_t*>                 iterator;
    typedef TXmlNodeIterator<smart_ptr_t,const smart_ptr_t&,const smart_ptr_t*>     c_iterator;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    XmlNode( const char* _pTagName );
    ~XmlNode();

    ///////////////////////////////////////////////////////////////////////////////
    // iterator operations
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    INLINE iterator begin( const XmlNode::smart_ptr_t& _spNode ) { ex_assert( _spNode.ptr() == this, "you must use smart pointer this as your parameter" ); return iterator ( _spNode, 0 ); }
    INLINE c_iterator begin( const XmlNode::smart_ptr_t& _spNode ) const { ex_assert( _spNode.ptr() == this, "you must use smart pointer this as your parameter" ); return c_iterator ( _spNode, 0 ); }

    // 
    INLINE iterator begin ( const XmlNode::smart_ptr_t& _spNode, const char* _tagName ) { ex_assert( _spNode.ptr() == this, "you must use smart pointer this as your parameter" ); return iterator( _spNode, this->firstChild(_tagName) ); }
    INLINE c_iterator begin ( const XmlNode::smart_ptr_t& _spNode, const char* _tagName ) const { ex_assert( _spNode.ptr() == this, "you must use smart pointer this as your parameter" ); return c_iterator( _spNode, this->firstChild(_tagName) ); }

    //
    INLINE iterator end( const XmlNode::smart_ptr_t& _spNode ) { ex_assert( _spNode.ptr() == this, "you must use smart pointer this as your parameter" ); return iterator( _spNode, this->childCount() ); }
    INLINE c_iterator end( const XmlNode::smart_ptr_t& _spNode ) const { ex_assert( _spNode.ptr() == this, "you must use smart pointer this as your parameter" ); return c_iterator( _spNode, this->childCount() ); }

    //
    iterator FindChildIterator( const char* _tagName );
    c_iterator FindChildIterator( const char* _tagName ) const;

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    // ======================================================== 
    // 
    // ======================================================== 

    XmlNode::smart_ptr_t clone () const; 

    // ========================================================
    // child
    // ========================================================

    void addChild( const XmlNode::smart_ptr_t& _spNode );
    void addChild( const char* _tagName, const XmlNode::smart_ptr_t& _spNode );
    XmlNode::smart_ptr_t newChild( const char* _tagName );
    bool removeChild( uint _idx );
    bool removeChild( const XmlNode::smart_ptr_t& _spNode );

    uint firstChild( const char* _tagName ) const;
    XmlNode::smart_ptr_t findChild( const char* _tagName ) const;
    XmlNode::smart_ptr_t findNode( const string_t _syntax ) const; // syntax could be "TAG1::TAG2::TAG3"
    XmlNode::smart_ptr_t child( uint _idx ) const;

    INLINE uint childCount() const { return uint(m_Children.size()); }
    uint childCount( const char* _tagName ) const;

    // ========================================================
    // tag
    // ========================================================

    INLINE void SetTag( const char* _tagName ) { m_Tag = _tagName; }
    const char* tag() const { return m_Tag.c_str(); }
    bool isTag( const char* _tagName ) const { return m_Tag ^= _tagName; }

    // ========================================================
    // constent
    // ========================================================

    INLINE void SetContent( const char* _content_text ) { m_Content = _content_text;}
    const char* GetContent() const { return m_Content.c_str(); }

    // ========================================================
    // attribute 
    // ========================================================

    void ReserveAttr ( uint _count );
    void SetAttrGeneric ( const char* _key, const char* _value );
    result_t GetAttrGeneric ( const char* _key, const char** _pValue ) const;

    XmlAttribute& GetAttrByIndex ( uint _idx ) { return m_Attributes[_idx]; }
    const XmlAttribute& GetAttrByIndex ( uint _idx ) const { return m_Attributes[_idx]; }

    const char* GetAttrValue ( const char* _key ) const;
    const char* GetAttrValue ( uint _idx ) const;

    uint attrCount () const { return uint(m_Attributes.size()); }
    uint hasAttr ( const char* _key ) const;
    bool removeAttr ( const char* _key );

	INLINE const XmlNode::xml_attributes_t& attrs () const { return m_Attributes; }
	void copyAttrsFrom ( const XmlNode::smart_ptr_t& _spNode );

    // ========================================================
    // debugs
    // ========================================================

#ifdef EX_DEBUG
    INLINE void setLine( uint _line ) { m_Line = _line; }
    INLINE uint line() const { return m_Line; }
#endif

    // ======================================================== 
    // file 
    // ======================================================== 

    result_t saveToFile ( const char* _fileName ) const;
    result_t saveToFile ( IFile::smart_ptr_t _spFile, uint _level = 0 ) const;

    // ======================================================== 
    // Get/Set Attr 
    // ======================================================== 

    template < typename T >
    void setAttr ( const char* _key, T _value )
    {
        string_t _strValue; 
        ex::get_str <dec> ( _value, &_strValue );
        this->SetAttrGeneric ( _key, _strValue.c_str() );
    }

    template < typename T >
    result_t getAttr ( const char* _key, T* _pValue ) const
    {
        const char* strAttr = NULL;
        result_t eResult = GetAttrGeneric ( _key, &strAttr );
        if ( eResult != EResult::ok )
            return eResult; 

        ex::from_str<T> ( strAttr, _pValue );
        return EResult::ok;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // static member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    static void FormatXmlString ( const char* _input, string_t* _pResult );

    ///////////////////////////////////////////////////////////////////////////////
    // member data
    ///////////////////////////////////////////////////////////////////////////////

protected:

    xml_nodes_t  m_Children;
    xml_attributes_t m_Attributes;

    string_t    m_Tag;
    string_t    m_Content;

#ifdef EX_DEBUG
    uint        m_Line;
#endif

}; // end class XmlNode

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END XMLNODE_H_1250526466
// #################################################################################

