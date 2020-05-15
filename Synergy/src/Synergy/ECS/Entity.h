// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_ENTITY_H
#define SYNERGY_ECS_ENTITY_H

#include <string>
#include <typeindex>
#include <unordered_map>

#include "Synergy/Core.h"
#include "Synergy/ECS/EntityId.h"

namespace Synergy
{
    class Scene;

    class SYNERGY_API Entity
    {
        friend class Scene;
        
    public:
        Entity(Synergy::Scene& scene, Synergy::EntityId id = { 0, 0 });
        Entity(const Synergy::Entity&) = default;
        Entity(Synergy::Entity&&);
        
        Synergy::Entity& operator=(Synergy::Entity&&);
        
        ~Entity();
        
        template <typename Component>
        bool Has() const;
        
        template <typename Component, typename Next, typename... Others>
        bool Has() const;
        
        bool Has(std::type_index component) const;
        
        template <typename Component>
        Component& Get();
        
        template <typename Component>
        const Component& Get() const;
        
        template <typename Component, typename... Args>
        Component& Add(Args&&... args);
        
        Synergy::EntityId Id() const;
        
        const std::string& Name() const;
        Synergy::Entity& Name(const std::string& name);
        
    private:
        Synergy::EntityId Clone(Synergy::Scene& scene, Synergy::Entity& entity) const;
        
    private:
        std::string m_Name { "Unnamed Entity" };
        Synergy::EntityId m_Id { 0, 0 };
        Synergy::Scene& m_Scene;
        
        std::unordered_map<std::type_index, Synergy::EntityId> m_Components;
    };

}

#include "Synergy/ECS/Entity.inl"

#endif
