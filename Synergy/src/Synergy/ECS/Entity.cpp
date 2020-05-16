// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.


#include <typeinfo>
#include <utility>
#include <vector>

#include "Synergy/ECS/ComponentPool.h"
#include "Synergy/ECS/ComponentPoolBase.h"
#include "Synergy/ECS/Entity.h"
#include "Synergy/ECS/Scene.h"
#include "Synergy/ECS/SceneEvents.h"

namespace Synergy
{
    Entity::Entity(Synergy::Scene& scene, Synergy::EntityId id) :
        m_Id(std::move(id)),
        m_Scene(scene)
    {}

    Entity::Entity(Synergy::Entity&& original) :
        m_Components(std::move(original.m_Components)),
        m_Name(std::move(original.m_Name)),
        m_Scene(original.m_Scene),
        m_Id(original.m_Id)
    {}

    Synergy::Entity& Entity::operator=(Synergy::Entity&& original)
    {
        m_Components = std::move(original.m_Components);
        m_Name = std::move(original.m_Name);
        m_Id = original.m_Id;
        
        return *this;
    }

    Entity::~Entity()
    {}

    bool Entity::Has(std::type_index component) const
    {
        return m_Components.count(component) > 0;
    }

    Synergy::EntityId Entity::Id() const
    {
        return m_Id;
    }

    const std::string& Entity::Name() const
    {
        return m_Name;
    }

    Synergy::Entity& Entity::Name(const std::string& name)
    {
        m_Name = name;
        return *this;
    }

    Synergy::EntityId Entity::Clone(Synergy::Scene& scene, Synergy::Entity& entity) const
    {
        for (const auto& component : m_Components)
        {
            entity.m_Components.emplace(m_Scene.GetComponentPool(component.first)->Clone(component.second, scene));
        }
        
        scene.Emit(Synergy::EntitySpawnedEvent(Synergy::EntityRef(entity.Id(), &scene)));
        
        return entity.Id();
    }

}
