// ======================================================================================
// File         : AbstractFactory.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:09:57 AM | Tuesday,August
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
// The author or Addison-Wesley Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// #################################################################################
#ifndef ABSTRACTFACTORY_H_1250525399
#define ABSTRACTFACTORY_H_1250525399
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "../Meta/HierarchyGenerators.h"

// ######################### 
namespace ex { 
// ######################### 

    ///////////////////////////////////////////////////////////////////////////////
    // Example:
    //  class Soldier { public: virtual ~Soldier() {} };
    //  class Monster { public: virtual ~Monster() {} };
    //  class SuperMonster { public: virtual ~SuperMonster() {} };
    //
    //  class SillySoldier : public Soldier {};
    //  class SillyMonster : public Monster {};
    //  class SillySuperMonster : public SuperMonster {};
    //
    //  class BadSoldier : public Soldier {};
    //  class BadMonster : public Monster {};
    //  class BadSuperMonster : public SuperMonster {};
    //
    //  typedef ex::AbstractFactory<ex::Seq<Soldier, Monster, SuperMonster>::typelist_t> AbstractEnemyFactory_t; 
    //  typedef ex::ConcreteFactory<AbstractEnemyFactory_t, ex::UnitCreator_ex_new, ex::Seq<SillySoldier, SillyMonster, SillySuperMonster>::typelist_t> EasyLevelEnemyFactory_t;
    //  typedef ex::ConcreteFactory<AbstractEnemyFactory_t, ex::UnitCreator_ex_new, ex::Seq<BadSoldier, BadMonster, BadSuperMonster>::typelist_t> HardLevelEnemyFactory_t;
    //
    //  AbstractEnemyFactory_t* pEasyFactory = ex_new EasyLevelEnemyFactory_t;
    //  AbstractEnemyFactory_t* pHardFactory = ex_new HardLevelEnemyFactory_t;
    // 
    //  Soldier* pSoldier;
    //  pSoldier = pEasyFactory->create<Soldier>();
    //  ex_delete (pSoldier);
    //  pSoldier = pHardFactory->create<Soldier>();
    //  ex_delete (pSoldier);
    //
    //  ex_delete (pEasyFactory);
    //  ex_delete (pHardFactory);
    ///////////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////////
    // class AbstractFactoryUnit 
    // 
    // Purpose: 
    //  The building block of an Abstract Factory
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template <class T>
    class AbstractFactoryUnit
    {
    public:
        virtual T* create ( TypeToType<T> ) = 0;
        virtual ~AbstractFactoryUnit () {}
    }; // end class AbstractFactoryUnit

    ///////////////////////////////////////////////////////////////////////////////
    // class AbstractFactory
    // 
    // Purpose: 
    //  Defines an Abstract Factory interface starting from a typelist
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template
    <
        class TYPE_LIST_T,
        template <class> class UNIT_T = AbstractFactoryUnit
    >
    class AbstractFactory : public GenScatterHierarchy<TYPE_LIST_T, UNIT_T>
    {
    public:
        typedef TYPE_LIST_T obj_types_t;
        
        template <class T> T* create()
        {
            UNIT_T<T>& unit = *this;
            return unit.create( TypeToType<T>() );
        }
    }; // end class AbstractFactory
    
    ///////////////////////////////////////////////////////////////////////////////
    // class UnitCreator_new 
    // 
    // Purpose: 
    //  Creates an object by invoking the new operator
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template <class T, class BASE_T>
    class UnitCreator_new : public BASE_T
    {
    private:
        typedef typename BASE_T::obj_types_t base_obj_types_t;
    
    protected:
        typedef typename base_obj_types_t::tail_t obj_types_t;
    
    public:
        typedef typename base_obj_types_t::head_t object_t;

        T* create( TypeToType<object_t> )
        {
            return new T;
        }
    }; // end class UnitCreator_new
    
    ///////////////////////////////////////////////////////////////////////////////
    // class UnitCreator_ex_new 
    // 
    // Purpose: 
    //  Creates an object by invoking the new operator
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template <class T, class BASE_T>
    class UnitCreator_ex_new : public BASE_T
    {
    private:
        typedef typename BASE_T::obj_types_t base_obj_types_t;
    
    protected:
        typedef typename base_obj_types_t::tail_t obj_types_t;
    
    public:
        typedef typename base_obj_types_t::head_t object_t;

        T* create( TypeToType<object_t> )
        {
            return ex_new T;
        }
    }; // end class UnitCreator_ex_new

#if 0
    ///////////////////////////////////////////////////////////////////////////////
    // class TPrototypeFactoryUnit
    // 
    // Purpose: 
    //  Creates an object by cloning a prototype
    //  There is a difference between the implementation herein and the one described
    //      in the book: GetPrototype and SetPrototype use the helper friend 
    //      functions DoGetPrototype and DoSetPrototype. The friend functions avoid
    //      name hiding issues. Plus, GetPrototype takes a reference to pointer
    //      instead of returning the pointer by value.
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template < class CONCRETE_PRODUCT_T, class BASE_T >
    class TPrototypeFactoryUnit : public BASE_T
    {
    private:
        typedef typename BASE_T::obj_types_t base_obj_types_t;
    
    protected:
        typedef typename base_obj_types_t::tail_t obj_types_t;

    public:
        typedef typename base_obj_types_t::head_t object_t;

        TPrototypeFactoryUnit(object_t* p = 0)
            : m_pPrototype(p)
        {}

        template <class CP, class Base1>
        friend void DoGetPrototype(const TPrototypeFactoryUnit<CP, Base1>& me,
                                   typename Base1::obj_types_t::head_t*& pPrototype);

        template <class CP, class Base1>
        friend void DoSetPrototype(TPrototypeFactoryUnit<CP, Base1>& me,
                                   typename Base1::obj_types_t::head_t* pObj);

        template <class U>
        void GetPrototype(U*& p)
        { return DoGetPrototype(*this, p); }
        
        template <class U>
        void SetPrototype(U* pObj)
        { DoSetPrototype(*this, pObj); }
        
        object_t* create( TypeToType<object_t> )
        {
            ex_assert(m_pPrototype,"m_pPrototype can't be NULL");
            return m_pPrototype->clone();
        }
        
    private:
        object_t* m_pPrototype;
    }; // end class TPrototypeFactoryUnit

    template <class CP, class BASE_T>
    inline void DoGetPrototype(const TPrototypeFactoryUnit<CP, BASE_T>& me,
                               typename BASE_T::obj_types_t::head_t*& pPrototype)
    { pPrototype = me.m_pPrototype; }

    template <class CP, class BASE_T>
    inline void DoSetPrototype(TPrototypeFactoryUnit<CP, BASE_T>& me,
                               typename BASE_T::obj_types_t::head_t* pObj)
    { me.m_pPrototype = pObj; }
#endif

    ///////////////////////////////////////////////////////////////////////////////
    // class ConcreteFactory
    // 
    // Purpose: 
    //  Implements an AbstractFactory interface
    // 
    ///////////////////////////////////////////////////////////////////////////////

    template
    <
        class ABSTRACT_FACTORY_T,
        template <class, class> class CREATOR_T = UnitCreator_ex_new,
        class TYPE_LIST_T = typename ABSTRACT_FACTORY_T::obj_types_t
    >
    class ConcreteFactory 
        : public GenLinearHierarchy< typename typelist::Reverse<TYPE_LIST_T>::result_t, CREATOR_T, ABSTRACT_FACTORY_T >
    {
    public:
        typedef typename ABSTRACT_FACTORY_T::obj_types_t obj_types_t;
        typedef TYPE_LIST_T concrete_obj_types_t;
    }; // end class ConcreteFactory 

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END ABSTRACTFACTORY_H_1250525399
// #################################################################################
