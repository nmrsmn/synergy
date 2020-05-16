// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <algorithm>
#include <functional>

#include "Synergy/ECS/ComponentAggregate.h"

#include "Synergy/ECS/EntitiesWithBase.h"
#include "Synergy/ECS/EntityRef.h"

namespace Synergy
{
    bool ComponentAggregate::Matches(const std::vector<std::type_index>& types) const
    {
        if (types.size() != m_Components.size())
            return false;
        
        return std::equal(std::cbegin(types), std::cend(types), std::cbegin(m_Components));
    }

    bool ComponentAggregate::Matches(const Synergy::EntityRef& entity) const
    {
        for (const auto& component : m_Components)
        {
            if (!entity.Has(component))
                return false;
        }
        
        return true;
    }

    std::vector<Synergy::EntityRef>& ComponentAggregate::Get()
    {
        return m_Entities;
    }

    const std::vector<Synergy::EntityRef>& ComponentAggregate::Get() const
    {
        return m_Entities;
    }

    void ComponentAggregate::OnEntityCreated(const Synergy::EntityRef& entity)
    {
        if (!entity.Has(m_Components))
            return;
        
        this->Add(entity);
    }

    void ComponentAggregate::OnEntityDestroyed(const Synergy::EntityRef& entity)
    {
        if (!this->Matches(entity))
            return;
        
        auto item { std::find(std::begin(m_Entities), std::end(m_Entities), entity) };
        
        if (item == m_Entities.end())
            return;
        
        auto index { std::distance(std::begin(m_Entities), item) };
        
        *item = m_Entities.back();
        m_Entities.pop_back();
        
        for (auto list : m_EntityLists)
        {
            list->Pop(index);
        }
    }

    void ComponentAggregate::Add(const Synergy::EntityRef& entity)
    {
        m_Entities.push_back(entity);
        for (auto list : m_EntityLists)
        {
            list->Push(entity);
        }
    }
}
