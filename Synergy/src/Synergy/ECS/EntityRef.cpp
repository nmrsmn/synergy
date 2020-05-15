// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/ECS/EntityRef.h"

#include "Synergy/ECS/Entity.h"
#include "Synergy/ECS/Scene.h"

namespace Synergy
{
    EntityRef::EntityRef(Synergy::EntityId id, Synergy::Scene* scene) :
        m_Id(std::move(id)),
        m_Scene(scene)
    {}
    
    bool EntityRef::Has(std::type_index component) const
    {
        return m_Scene->GetEntity(m_Id)->Has(component);
    }

    bool EntityRef::Has(std::vector<std::type_index>& components) const
    {
        const Synergy::Entity* entity { m_Scene->GetEntity(m_Id) };
        
        if (entity == nullptr)
            return false;
        
        for (const auto& component : components)
        {
            if (entity->Has(component) == false)
                return false;
        }
        
        return true;
    }

    const std::string& EntityRef::Name() const
    {
        return m_Scene->GetEntity(m_Id)->Name();
    }
}
