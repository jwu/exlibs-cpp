// ======================================================================================
// File         : Delegate.hpp
// Author       : Wu Jie 
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// class TDelegate
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template< typename RET_T _COMMA_TEMPLATE_TYPES >
class _CLASS_NAME : public CDelegateBase
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    // types 
    ///////////////////////////////////////////////////////////////////////////////
    typedef RET_T (*pfn_t) (_DECLARE_PARAMS);

    ///////////////////////////////////////////////////////////////////////////////
    // construction
    ///////////////////////////////////////////////////////////////////////////////
public:
    //
	INLINE _CLASS_NAME()
	{
	}

    //
    template< typename OBJ_T, typename FCT_T >
    INLINE _CLASS_NAME( OBJ_T* _obj, FCT_T _func_ptr )
    {
        ex_assert( _obj && _func_ptr, "the _obj/_func_ptr can't be NULL" );
        ex_static_assert( sizeof( TDelegateMember< OBJ_T, FCT_T, RET_T > ) <= sizeof( UDelegateInfo ), "The function don't support delegate" );
        ex_new_in ( &m_DelegateInfo ) TDelegateMember< OBJ_T, FCT_T, RET_T >( _obj, _func_ptr );
    }

    //
	template< typename FCT_T >
	INLINE _CLASS_NAME( FCT_T _func_ptr )
	{
        ex_assert( _func_ptr, "the _func_ptr can't be NULL" );
        ex_static_assert( sizeof( TDelegateNormal< FCT_T, RET_T > ) <= sizeof( UDelegateInfo ), "The function don't support delegate" );
        ex_new_in ( &m_DelegateInfo ) TDelegateNormal< FCT_T, RET_T >( _func_ptr );
	}

    ///////////////////////////////////////////////////////////////////////////////
    // member functions
    ///////////////////////////////////////////////////////////////////////////////
public:
    //
    template< typename OBJ_T, typename FCT_T >
    void Set( OBJ_T* _obj, FCT_T _func_ptr )
    {
        ex_assert( _obj && _func_ptr, "the _obj/_func_ptr can't be NULL" );
        ex_static_assert( sizeof( TDelegateMember< OBJ_T, FCT_T, RET_T > ) <= sizeof( UDelegateInfo ), "The function don't support delegate" );
        Reset();
        ex_new_in ( &m_DelegateInfo ) TDelegateMember< OBJ_T, FCT_T, RET_T >( _obj, _func_ptr );
    }

    //
	template< typename FCT_T >
	void Set( FCT_T _func_ptr )
	{
        ex_assert( _func_ptr, "the _func_ptr can't be NULL" );
        ex_static_assert( sizeof( TDelegateNormal< FCT_T, RET_T > ) <= sizeof( UDelegateInfo ), "The function don't support delegate" );
        Reset();
        ex_new_in ( &m_DelegateInfo ) TDelegateNormal< FCT_T, RET_T >( _func_ptr );
	}

    //
	template< typename OBJ_T, typename FCT_T, typename BIND_PARAM0_T >
	void BindParam( OBJ_T* _obj, FCT_T _func_ptr, BIND_PARAM0_T _bind_param0 )
	{
        ex_assert( _obj && _func_ptr, "the _obj/_func_ptr can't be NULL" );
        ex_static_assert( sizeof( TDelegateMemberWithParamBind< OBJ_T, FCT_T, BIND_PARAM0_T, RET_T > ) <= sizeof( UDelegateInfo ), "The function don't support delegate" );
        Reset();
        ex_new_in ( &m_DelegateInfo ) TDelegateMemberWithParamBind< OBJ_T, FCT_T, BIND_PARAM0_T, RET_T >( _obj, _func_ptr, _bind_param0 );
	}

    //
	template< typename FCT_T, typename BIND_PARAM0_T >
	void BindParam( FCT_T _func_ptr, BIND_PARAM0_T _bind_param0 )
	{
        ex_assert( _func_ptr, "the _func_ptr can't be NULL" );
        ex_static_assert( sizeof( TDelegateNormalWithParamBind< FCT_T, BIND_PARAM0_T, RET_T > ) <= sizeof( UDelegateInfo ), "The function don't support delegate" );
        Reset();
        ex_new_in ( &m_DelegateInfo ) TDelegateNormalWithParamBind< FCT_T, BIND_PARAM0_T, RET_T >( _func_ptr, _bind_param0 );
	}

    //
	INLINE RET_T Call( _DECLARE_PARAMS ) const
	{
        ex_assert( m_DelegateInfo.FunctionInfo.pVtable, "delegate function can't be NULL" );
        const IDelegateBase* delegateBase = reinterpret_cast< const IDelegateBase* >( &m_DelegateInfo );
		return delegateBase->Call( _USE_PARAMS );
	}

    //
	INLINE _CLASS_NAME_STATIC<RET_T _COMMA_USE_TYPES> ToStaticDelegate() const
	{
        ex_assert( m_DelegateInfo.FunctionInfo.pVtable, "delegate function can't be NULL" );
        const IDelegateBase* delegateBase = reinterpret_cast< const IDelegateBase* >( &m_DelegateInfo );
		return delegateBase->ToStaticDelegate();
	}

    ///////////////////////////////////////////////////////////////////////////////
    // operators
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    INLINE RET_T operator()( _DECLARE_PARAMS ) const
    {
        return Call( _USE_PARAMS );
    }

    //
    bool operator == ( const _CLASS_NAME& _rhs ) const
    {
        return m_DelegateInfo.FunctionInfo.pVtable   == _rhs.m_DelegateInfo.FunctionInfo.pVtable   &&
               m_DelegateInfo.FunctionInfo.pObject   == _rhs.m_DelegateInfo.FunctionInfo.pObject   &&
               m_DelegateInfo.FunctionInfo.pFunction == _rhs.m_DelegateInfo.FunctionInfo.pFunction &&
               m_DelegateInfo.FunctionInfo.pData     == _rhs.m_DelegateInfo.FunctionInfo.pData;
    }

    //
    bool operator != ( const _CLASS_NAME& _rhs ) const
    {
        return m_DelegateInfo.FunctionInfo.pVtable   != _rhs.FunctionInfo.m_DelegateInfo.pVtable   ||
               m_DelegateInfo.FunctionInfo.pObject   != _rhs.FunctionInfo.m_DelegateInfo.pObject   ||
               m_DelegateInfo.FunctionInfo.pFunction != _rhs.FunctionInfo.m_DelegateInfo.pFunction ||
               m_DelegateInfo.FunctionInfo.pData     != _rhs.FunctionInfo.m_DelegateInfo.pData;
    }

    //
    INLINE _CLASS_NAME& operator = ( int _zero )
    {
        ex_assert( _zero == 0, "" );
        Reset();
        return *this;
    }

    //
	template< typename FCT_T >
    INLINE _CLASS_NAME& operator = ( FCT_T _func_ptr )
    {
        Set(_func_ptr);
        return *this;
    }

    //
    INLINE _CLASS_NAME& operator = ( const _CLASS_NAME& _copy )
    {
        m_DelegateInfo = _copy.m_DelegateInfo;
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // internal classes 
    ///////////////////////////////////////////////////////////////////////////////

protected:

    ///////////////////////////////////////////////////////////////////////////////
    // class IDelegateBase 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    class IDelegateBase
    {
    protected:
        IDelegateBase() {}
        virtual ~IDelegateBase() {};

    public:
        virtual RET_T Call( _DECLARE_PARAMS ) const = 0;
		virtual _CLASS_NAME_STATIC<RET_T _COMMA_USE_TYPES> ToStaticDelegate() const = 0;
    }; // end class IDelegateBase

    ///////////////////////////////////////////////////////////////////////////////
    // class TDelegateNormal 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template< typename FCT_T, typename LOCAL_RET_T >
    class TDelegateNormal : public IDelegateBase
    {
    public:
        TDelegateNormal( FCT_T _func_ptr )
            :   m_FuncPtr( _func_ptr )
        {
        }

        virtual LOCAL_RET_T Call( _DECLARE_PARAMS ) const
        {
            return m_FuncPtr( _USE_PARAMS );
        }

        virtual _CLASS_NAME_STATIC<LOCAL_RET_T _COMMA_USE_TYPES> ToStaticDelegate() const 
        {
            return T_MakeDelegate( &_CLASS_NAME_STATIC<LOCAL_RET_T _COMMA_USE_TYPES>(), m_FuncPtr );
        }

    private:
        FCT_T m_FuncPtr;
    }; // end class TDelegateNormal

    ///////////////////////////////////////////////////////////////////////////////
    // class 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template< typename FCT_T, typename BIND_PARAM0_T, typename LOCAL_RET_T >
    class TDelegateNormalWithParamBind : public IDelegateBase
    {
    public:
        TDelegateNormalWithParamBind( FCT_T _func_ptr, BIND_PARAM0_T _bind_param0 )
            :   m_FuncPtr( _func_ptr ),
                m_Param0( _bind_param0 )
        {
        }

        virtual LOCAL_RET_T Call( _DECLARE_PARAMS ) const
        {
            return m_FuncPtr( m_Param0 _COMMA_USE_PARAMS );
        }

        virtual _CLASS_NAME_STATIC<LOCAL_RET_T _COMMA_USE_TYPES> ToStaticDelegate() const 
        {
            return T_MakeDelegate( &_CLASS_NAME_STATIC<LOCAL_RET_T _COMMA_USE_TYPES>(), m_FuncPtr );
        }

    private:
        FCT_T           m_FuncPtr;
        BIND_PARAM0_T   m_Param0;
    }; // end class TDelegateNormalWithParamBind

    ///////////////////////////////////////////////////////////////////////////////
    // class TDelegateMember 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template< typename OBJ_T, typename FCT_T, typename LOCAL_RET_T >
    class TDelegateMember : public IDelegateBase
    {
    public:
        TDelegateMember( OBJ_T* _obj, FCT_T _func_ptr )
            :   m_Obj( _obj ),
                m_FuncPtr( _func_ptr )
        {
        }

        virtual LOCAL_RET_T Call( _DECLARE_PARAMS ) const
        {
            return (m_Obj->*m_FuncPtr)( _USE_PARAMS );
        }

        virtual _CLASS_NAME_STATIC<LOCAL_RET_T _COMMA_USE_TYPES> ToStaticDelegate() const 
        {
            return T_MakeDelegate( &_CLASS_NAME_STATIC<LOCAL_RET_T _COMMA_USE_TYPES>(), m_Obj, m_FuncPtr );
        }

    private:
        OBJ_T*  m_Obj;
        FCT_T   m_FuncPtr;
    }; // end class TDelegateMember

    ///////////////////////////////////////////////////////////////////////////////
    // class TDelegateMemberWithParamBind 
    // 
    // Purpose: 
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template< typename OBJ_T, typename FCT_T, typename BIND_PARAM0_T, typename LOCAL_RET_T >
    class TDelegateMemberWithParamBind : public IDelegateBase
    {
    public:
        TDelegateMemberWithParamBind( OBJ_T* _obj, FCT_T _func_ptr, BIND_PARAM0_T _bind_param0 )
            :   m_Obj( _obj ),
                m_FuncPtr( _func_ptr ),
                m_Param0( _bind_param0 )
        {
        }

        virtual LOCAL_RET_T Call( _DECLARE_PARAMS ) const
        {
            return (m_Obj->*m_FuncPtr)( m_Param0 _COMMA_USE_PARAMS );
        }

        virtual _CLASS_NAME_STATIC<LOCAL_RET_T _COMMA_USE_TYPES> ToStaticDelegate() const 
        {
            return T_MakeDelegate( &_CLASS_NAME_STATIC<LOCAL_RET_T _COMMA_USE_TYPES>(), m_Obj, m_FuncPtr );
        }

    private:
        OBJ_T*          m_Obj;
        FCT_T           m_FuncPtr;
        BIND_PARAM0_T   m_Param0;
    }; // end class TDelegateMemberWithParamBind

    ///////////////////////////////////////////////////////////////////////////////
    // class TDelegateNormal
    // 
    // Purpose: void ver.
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template< typename FCT_T >
    class TDelegateNormal< FCT_T, void > : public IDelegateBase
    {
    public:
        TDelegateNormal( FCT_T _func_ptr )
            :   m_FuncPtr( _func_ptr )
        {
        }

        virtual void Call( _DECLARE_PARAMS ) const
        {
            m_FuncPtr( _USE_PARAMS );
        }

        virtual _CLASS_NAME_STATIC<void _COMMA_USE_TYPES> ToStaticDelegate() const 
        {
            return T_MakeDelegate( &_CLASS_NAME_STATIC<void _COMMA_USE_TYPES>(), m_FuncPtr );
        }

    private:
        FCT_T m_FuncPtr;
    }; // end class TDelegateNormal

    ///////////////////////////////////////////////////////////////////////////////
    // class TDelegateNormalWithParamBind 
    // 
    // Purpose: void ver.
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template< typename FCT_T, typename BIND_PARAM0_T >
    class TDelegateNormalWithParamBind< FCT_T, BIND_PARAM0_T, void > : public IDelegateBase
    {
    public:
        TDelegateNormalWithParamBind( FCT_T _func_ptr, BIND_PARAM0_T _bind_param0 )
            :   m_FuncPtr( _func_ptr ),
                m_Param0( _bind_param0 )
        {
        }

        virtual void Call( _DECLARE_PARAMS ) const
        {
            m_FuncPtr( m_Param0 _COMMA_USE_PARAMS );
        }

        virtual _CLASS_NAME_STATIC<void _COMMA_USE_TYPES> ToStaticDelegate() const 
        {
            return T_MakeDelegate( &_CLASS_NAME_STATIC<void _COMMA_USE_TYPES>(), m_FuncPtr );
        }

    private:
        FCT_T           m_FuncPtr;
        BIND_PARAM0_T   m_Param0;
    }; // end class TDelegateNormalWithParamBind

    ///////////////////////////////////////////////////////////////////////////////
    // class TDelegateMember 
    // 
    // Purpose: void ver.
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template< typename OBJ_T, typename FCT_T >
    class TDelegateMember< OBJ_T, FCT_T, void > : public IDelegateBase
    {
    public:
        TDelegateMember( OBJ_T* _obj, FCT_T _func_ptr )
            :   m_Obj( _obj ),
                m_FuncPtr( _func_ptr )
        {
        }

        virtual void Call( _DECLARE_PARAMS ) const
        {
            (m_Obj->*m_FuncPtr)( _USE_PARAMS );
        }

        virtual _CLASS_NAME_STATIC<void _COMMA_USE_TYPES> ToStaticDelegate() const 
        {
            return T_MakeDelegate( &_CLASS_NAME_STATIC<void _COMMA_USE_TYPES>(), m_Obj, m_FuncPtr );
        }

    private:
        OBJ_T*  m_Obj;
        FCT_T   m_FuncPtr;
    }; // end class TDelegateMember

    ///////////////////////////////////////////////////////////////////////////////
    // class TDelegateMemberWithParamBind 
    // 
    // Purpose: void ver.
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template< typename OBJ_T, typename FCT_T, typename BIND_PARAM0_T >
    class TDelegateMemberWithParamBind< OBJ_T, FCT_T, BIND_PARAM0_T, void > : public IDelegateBase
    {
    public:
        TDelegateMemberWithParamBind( OBJ_T* _obj, FCT_T _func_ptr, BIND_PARAM0_T _bind_param0 )
            :   m_Obj( _obj ),
                m_FuncPtr( _func_ptr ),
                m_Param0( _bind_param0 )
        {
        }

        virtual void Call( _DECLARE_PARAMS ) const
        {
            (m_Obj->*m_FuncPtr)( m_Param0 _COMMA_USE_PARAMS );
        }

        virtual _CLASS_NAME_STATIC<void _COMMA_USE_TYPES> ToStaticDelegate() const 
        {
            return T_MakeDelegate( &_CLASS_NAME_STATIC<void _COMMA_USE_TYPES>(), m_Obj, m_FuncPtr );
        }

    private:
        OBJ_T*          m_Obj;
        FCT_T           m_FuncPtr;
        BIND_PARAM0_T   m_Param0;
    }; // end class TDelegateMemberWithParamBind


    ///////////////////////////////////////////////////////////////////////////////
    // generics function 
    ///////////////////////////////////////////////////////////////////////////////
public:

    //
    template < uint FLAGS >
    INLINE string_t to_str() const
    {
        return CDelegateBase::to_str<FLAGS>();
    }
}; // end class TDelegate

