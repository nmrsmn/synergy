// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Entity/Entity.h"
#include "Synergy/Entity/EntityRef.h"
#include "Synergy/Scene.h"
#include "Synergy/SceneEvents.h"

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

    void EntityRef::Destroy()
    {
        m_Scene->Emit(Synergy::EntityDestroyedEvent { *this });
        m_Scene->OnNextEvent([scene = m_Scene, entity = *this] (const Synergy::FrameEndEvent& event)
        {
            scene->Destroy(entity);
        });
    }

    const std::string& EntityRef::Name() const
    {
        return m_Scene->GetEntity(m_Id)->Name();
    }

    Synergy::EntityId EntityRef::Id() const
    {
        return m_Id;
    }

    bool EntityRef::operator==(const Synergy::EntityRef& other) const
    {
        return (m_Id == other.m_Id) && (m_Scene == other.m_Scene);
    }
}
