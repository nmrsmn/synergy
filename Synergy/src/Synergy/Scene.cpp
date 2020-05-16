// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <utility>

#include "Synergy/Component/ComponentPoolBase.h"
#include "Synergy/Component/ComponentPool.h"
#include "Synergy/Entity/ArchetypeRef.h"
#include "Synergy/Entity/Entity.h"
#include "Synergy/Entity/EntityRef.h"
#include "Synergy/Scene.h"
#include "Synergy/SceneEvents.h"
#include "Synergy/System/SystemBase.h"

namespace Synergy
{
    Scene::Scene(std::string name) :
        m_Name(std::move(name))
    {
        this->OnEvent([&] (const Synergy::EntitySpawnedEvent& event)
        {
            for (auto& aggregate : m_Aggregates)
            {
                aggregate.OnEntityCreated(event.entity);
            }
        });
        
        this->OnEvent([&] (const Synergy::EntityDestroyedEvent& event)
        {
            for (auto& aggregate : m_Aggregates)
            {
                aggregate.OnEntityDestroyed(event.entity);
            }
        });
        
        this->OnEvent([&] (const Synergy::ComponentAddedEvent& event)
        {
            for (auto& aggregate : m_Aggregates)
            {
                aggregate.OnEntityCreated(event.entity);
            }
        });
        
        this->OnEvent([&] (const Synergy::ComponentRemovedEvent& event)
        {
            for (auto& aggregate : m_Aggregates)
            {
                aggregate.OnEntityDestroyed(event.entity);
            }
        });
    }

    Synergy::Entity* Scene::GetEntity(Synergy::EntityId id)
    {
        if (auto entity { m_Entities.find(id) }; entity != m_Entities.end())
            return &(*entity);
        
        return nullptr;
    }

    const Synergy::Entity* Scene::GetEntity(Synergy::EntityId id) const
    {
        if (auto entity { m_Entities.find(id) }; entity != m_Entities.end())
            return &(*entity);
        
        return nullptr;
    }

    Synergy::EntityRef Scene::Spawn(Synergy::ArchetypeRef archetype)
    {
        return Spawn(Synergy::EntityRef { archetype.Id(), archetype.GetScene() });
    }

    Synergy::EntityRef Scene::Spawn(Synergy::EntityRef reference)
    {
        std::string name { reference.Name() };
        
        Synergy::EntityRef entity { this->CreateEntity(name) };
        reference.m_Scene->m_Entities[reference.m_Id].Clone(*this, m_Entities[entity.m_Id]);
        
        return entity;
    }
    
    void Scene::Update(float dt)
    {
        this->Emit(Synergy::FrameStartEvent {});
        this->Emit(Synergy::UpdateEvent { dt });
        this->Emit(Synergy::FrameEndEvent {});
    }

    Synergy::EntityRef Scene::CreateEntity(const std::string& name)
    {
        auto id { m_Entities.emplace(*this) };
        
        const std::string& entityName = name;
        
        m_Entities[id].Name(entityName);
        m_Entities[id].m_Id = id;
        
        return EntityRef(id, this);
    }

    Synergy::ComponentPoolBase* Scene::GetComponentPool(std::type_index component)
    {
        if (auto pool { m_Components.find(component) }; pool != m_Components.end())
            return pool->second.get();
        
        return nullptr;
    }

    void Scene::Destroy(Synergy::EntityRef entity)
    {
        m_Entities.erase(entity.Id());
    }
}
