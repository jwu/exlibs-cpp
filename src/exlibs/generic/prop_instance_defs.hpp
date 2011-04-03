// ======================================================================================
// File         : prop_instance_defs.hpp
// Author       : Wu Jie 
// Last Change  : 08/16/2010 | 17:12:24 PM | Monday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PROP_INSTANCE_DEFS_HPP_1281949945
#define PROP_INSTANCE_DEFS_HPP_1281949945
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ######################### 
namespace ex { 
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// PropertyInstance specializations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < T[SIZE] > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, uint SIZE >
class PropertyInstance < T[SIZE] > : public PropertyInstanceBase
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

    typedef T class_t[SIZE];
    typedef PropertyInstanceBase      base_t;
    typedef PropertyInstance<class_t> self_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    // 
    PropertyInstance ( PropertyBase* _pProperty, void* _pObject )
        : base_t ( _pProperty, _pObject )
    {
        //
        T* pClass = reinterpret_cast<T*>(_pProperty->getValuePtr(_pObject));

        //
        for ( uint i = 0; i < SIZE; ++i )
        {
            string_t propName( "[" + to_str<dec>(i) + "]" );
            EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( propName.c_str(), &(pClass[i]), PropAttr::none );
        }
    }

}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < uid_t > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <>
class PropertyInstance < uid_t > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( uid_t );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "uid", &(pClass->m_ID), PropAttr::readonly );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < Pair<T1,T2> > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T1, typename T2 >
class PropertyInstance < Pair<T1,T2> > : public PropertyInstanceBase
{
    // NOTE: the preprocessor failed to parase macro that recieve template class that have parameter more than two.
    typedef Pair<T1,T2> pair_t;
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( pair_t );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "first", &(pClass->first), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "second", &(pClass->second), PropAttr::none );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < List<T,TAllocator_T> > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, template <class> class TAllocator_T >
class PropertyInstance < List<T,TAllocator_T> > : public PropertyInstanceBase
{
    // NOTE: the preprocessor failed to parase macro that recieve template class that have parameter more than two.
    typedef List<T,TAllocator_T> list_t;
    EX_PROPERTY_INSTANCE_TYPEDEFS( list_t );

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    // 
    PropertyInstance ( PropertyBase* _pProperty, void* _pObject )
        : base_t ( _pProperty, _pObject )
    {
        //
        class_t* pClass = reinterpret_cast<class_t*>(_pProperty->getValuePtr(_pObject));

        //
        uint idx = 0;
        for ( typename class_t::iterator iter = pClass->begin(); iter != pClass->end(); ++iter, ++idx )
        {
            string_t propName("[" + to_str<dec>(idx) + "]");

            EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( propName.c_str(), &(*iter), PropAttr::none );
        }
    }

}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < Array<T,TAllocator_T> > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, template <class> class TAllocator_T >
class PropertyInstance < Array<T,TAllocator_T> > : public PropertyInstanceBase
{
    // NOTE: the preprocessor failed to parase macro that recieve template class that have parameter more than two.
    typedef Array<T,TAllocator_T> arr_t;
    EX_PROPERTY_INSTANCE_TYPEDEFS ( arr_t );

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    // 
    PropertyInstance ( PropertyBase* _pProperty, void* _pObject )
        : base_t ( _pProperty, _pObject )
    {
        //
        class_t* pClass = reinterpret_cast<class_t*>(_pProperty->getValuePtr(_pObject));

        //
        for ( typename class_t::iterator iter = pClass->begin(); iter != pClass->end(); ++iter )
        {
            typename class_t::sz_t idx = pClass->index(iter);
            string_t propName("[" + to_str<dec>(uint(idx)) + "]");

            EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( propName.c_str(), pClass->ptr(idx), PropAttr::none );
        }
    }

}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < HashMap > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename KEY, 
           typename VALUE, 
           typename HASH_FUNC,
           typename EQUAL_KEY,
           template <class> class TAllocator_T >
class PropertyInstance < HashMap<KEY,VALUE,HASH_FUNC,EQUAL_KEY,TAllocator_T> > : public PropertyInstanceBase
{
    // NOTE: the preprocessor failed to parase macro that recieve template class that have parameter more than two.
    typedef HashMap<KEY,VALUE,HASH_FUNC,EQUAL_KEY,TAllocator_T> map_t;
    typedef Pair<KEY,VALUE> writable_pair_t;

    EX_PROPERTY_INSTANCE_TYPEDEFS ( map_t );

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:

    // 
    PropertyInstance ( PropertyBase* _pProperty, void* _pObject )
        : base_t ( _pProperty, _pObject )
    {
        //
        class_t* pClass = reinterpret_cast<class_t*>(_pProperty->getValuePtr(_pObject));

        //
        uint idx = 0;
        for ( typename class_t::iterator iter = pClass->begin(); iter != pClass->end(); ++iter, ++idx )
        {
            string_t propName("[" + to_str<dec>(idx) + "]");

            typename map_t::pair_t& pair = const_cast<typename map_t::pair_t&>(iter.pair());
            writable_pair_t* pWritable = reinterpret_cast<writable_pair_t*>(&pair);
            EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( propName.c_str(), pWritable, PropAttr::none );
        }
    }

}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < Angle<T> > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class PropertyInstance < Angle<T> > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( Angle<T> )
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "radians", &(pClass->m_radians), PropAttr::none );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < Vector2<T> > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class PropertyInstance < Vector2<T> > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( Vector2<T> )
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "x", &(pClass->x()), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "y", &(pClass->y()), PropAttr::none );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance


///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < Vector3<T> > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class PropertyInstance < Vector3<T> > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( Vector3<T> );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "x", &(pClass->x()), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "y", &(pClass->y()), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "z", &(pClass->z()), PropAttr::none );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < Matrix4<T> > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class PropertyInstance < Matrix4<T> > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( Matrix4<T> );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m00", &(pClass->get(0,0)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m01", &(pClass->get(0,1)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m02", &(pClass->get(0,2)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m03", &(pClass->get(0,3)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m10", &(pClass->get(1,0)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m11", &(pClass->get(1,1)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m12", &(pClass->get(1,2)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m13", &(pClass->get(1,3)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m20", &(pClass->get(2,0)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m21", &(pClass->get(2,1)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m22", &(pClass->get(2,2)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m23", &(pClass->get(2,3)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m30", &(pClass->get(3,0)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m31", &(pClass->get(3,1)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m32", &(pClass->get(3,2)), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "m33", &(pClass->get(3,3)), PropAttr::none );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < StringID > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class PropertyInstance < StringID<T> > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( StringID<T> );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "ID", &(pClass->m_ID), PropAttr::readonly );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < Rect > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class PropertyInstance < Rect<T> > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( Rect<T> );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "top",   &(pClass->m_top),   PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "left",  &(pClass->m_left),  PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "bot",   &(pClass->m_bot),   PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "right", &(pClass->m_right), PropAttr::none );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < AABRect > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class PropertyInstance < AABRect<T> > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( AABRect<T> );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "lowerBound", &(pClass->m_lowerBound), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "upperBound", &(pClass->m_upperBound), PropAttr::none );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < Color3u > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <>
class PropertyInstance < Color3u > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( Color3u );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "r", &(pClass->r), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "g", &(pClass->g), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "b", &(pClass->b), PropAttr::none );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < Color4u > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <>
class PropertyInstance < Color4u > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( Color4u );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "r", &(pClass->r), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "g", &(pClass->g), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "b", &(pClass->b), PropAttr::none );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR ( "a", &(pClass->a), PropAttr::none );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance


///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < Color3f > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <>
class PropertyInstance < Color3f > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( Color3f );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR_MIN_MAX ( "r", &(pClass->r), PropAttr::none, float, 0.0f, 1.0f );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR_MIN_MAX ( "g", &(pClass->g), PropAttr::none, float, 0.0f, 1.0f );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR_MIN_MAX ( "b", &(pClass->b), PropAttr::none, float, 0.0f, 1.0f );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance

///////////////////////////////////////////////////////////////////////////////
// class PropertyInstance < Color4f > 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template <>
class PropertyInstance < Color4f > : public PropertyInstanceBase
{
    EX_DEF_PROPERTY_INSTANCE_BEGIN ( Color4f );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR_MIN_MAX ( "r", &(pClass->r), PropAttr::none, float, 0.0f, 1.0f );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR_MIN_MAX ( "g", &(pClass->g), PropAttr::none, float, 0.0f, 1.0f );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR_MIN_MAX ( "b", &(pClass->b), PropAttr::none, float, 0.0f, 1.0f );
        EX_REGISTER_SUB_PROPERTY_VALUE_PTR_MIN_MAX ( "a", &(pClass->a), PropAttr::none, float, 0.0f, 1.0f );
    EX_DEF_PROPERTY_INSTANCE_END ()
}; // end class PropertyInstance

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END PROP_INSTANCE_DEFS_HPP_1281949945
// #################################################################################
