// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_COMPONENT_COMPONENT_AGGREGATE_H
#define SYNERGY_COMPONENT_COMPONENT_AGGREGATE_H

#include <typeindex>
#include <vector>

#include "Synergy/Util/TypeList.h"

namespace Synergy
{
    class EntityRef;
    template <typename... Args>
    class EntitiesWith;
    class EntitiesWithBase;

    class ComponentAggregate
    {
    public:
        template <typename... Args>
        ComponentAggregate(stdext::type_list<Args...>);
        
        template <typename... Args>
        bool Matches() const;
        bool Matches(const std::vector<std::type_index>& types) const;
        bool Matches(const Synergy::EntityRef& entity) const;
        
        std::vector<Synergy::EntityRef>& Get();
        const std::vector<Synergy::EntityRef>& Get() const;
        
        void OnEntityCreated(const Synergy::EntityRef& entity);
        void OnEntityDestroyed(const Synergy::EntityRef& entity);
        
        template <typename... Args>
        void AddEntityList(Synergy::EntitiesWith<Args...>& list);
        
    private:
        template <typename T>
        void Add();
        template <typename T, typename T2, typename... Args>
        void Add();
        
        void Add(const Synergy::EntityRef& entity);
        
    private:
        std::vector<std::type_index> m_Components;
        std::vector<Synergy::EntityRef> m_Entities;
        std::vector<Synergy::EntitiesWithBase*> m_EntityLists;
    };
}

#include "Synergy/Component/ComponentAggregate.inl"

#endif
