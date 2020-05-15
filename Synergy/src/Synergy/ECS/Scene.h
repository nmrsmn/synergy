// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_SCENE_H
#define SYNERGY_ECS_SCENE_H

#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "Synergy/Core.h"
#include "Synergy/ECS/EntityId.h"
#include "Synergy/Event/EventHandler.h"
#include "Synergy/Util/SlotMap.h"

namespace Synergy
{
    class Application;
    template <typename T>
    class ComponentPool;
    class ComponentPoolBase;
    class Entity;
    class EntityRef;
    class SystemBase;

    class SYNERGY_API Scene : public Synergy::EventHandler
    {   
        friend class Application;
        template <typename T>
        friend class ComponentPool;
        friend class Entity;
        friend class EntityRef;
        
    public:
        Scene(std::string name = "Unnamed Scene");
        
        template <typename T>
        T& GetComponent(EntityId entity);
        
        template <typename T>
        const T& GetComponent(EntityId entity) const;
        
        void* GetComponent(EntityId component, std::type_index type);
        
        Synergy::Entity* GetEntity(Synergy::EntityId id);
        const Synergy::Entity* GetEntity(Synergy::EntityId id) const;
        
        Synergy::EntityRef Spawn(Synergy::EntityRef reference);
        
        template <typename T, typename... Args>
        void Add(const std::string& name = "Unnamed System", Args&&... args);
        
        void Update(float dt);
        
        Synergy::EntityRef CreateEntity(const std::string& name);

    protected:
        template <typename T>
        Synergy::ComponentPool<T>& GetComponentPool();
        
        template <typename T>
        const Synergy::ComponentPool<T>& GetComponentPool() const;
        
        Synergy::ComponentPoolBase* GetComponentPool(std::type_index component);
        
    private:
        std::string m_Name { "Unnamed Scene" };
        
        stdext::slot_map<Synergy::Entity> m_Entities;
        std::unordered_map<std::type_index, Synergy::Scope<Synergy::ComponentPoolBase>> m_Components;
        std::vector<Synergy::Scope<Synergy::SystemBase>> m_Systems;
    };
}

#include "Synergy/ECS/Scene.inl"

#endif
