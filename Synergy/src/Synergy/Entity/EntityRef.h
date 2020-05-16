// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ENTITY_ENTITY_REF_H
#define SYNERGY_ENTITY_ENTITY_REF_H

#include <typeindex>
#include <vector>

#include "Synergy/Core.h"
#include "Synergy/Entity/EntityId.h"

namespace Synergy
{
    class Scene;
    class Entity;

    class SYNERGY_API EntityRef
    {
        friend class Scene;
        
    public:
        EntityRef(Synergy::EntityId id, Synergy::Scene* scene);
        EntityRef(const EntityRef&) = default;
        EntityRef(EntityRef&&) = default;
        
        ~EntityRef() = default;
        
        Synergy::EntityRef& operator=(const Synergy::EntityRef&) = default;

        template <typename Component>
        bool Has() const;
        
        template <typename Component, typename Next, typename... Others>
        bool Has() const;
        
        bool Has(std::type_index component) const;
        bool Has(std::vector<std::type_index>& components) const;
        
        template <typename Component>
        Component& Get();
        
        template <typename Component>
        const Component& Get() const;
        
        template <typename Component, typename... Args>
        Component& Add(Args&&... args);
        
        template <typename Component>
        void Remove();

        void Destroy();
        
        const std::string& Name() const;
        Synergy::EntityId Id() const;
        
        bool operator==(const Synergy::EntityRef& other) const;
        
    protected:
        Synergy::EntityId m_Id { 0, 0 };
        Synergy::Scene* m_Scene;
    };
}

#include "Synergy/Entity/EntityRef.inl"

#endif
