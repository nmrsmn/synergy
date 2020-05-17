// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_COMPONENT_COMPONENT_POOL_H
#define SYNERGY_COMPONENT_COMPONENT_POOL_H

#include <tuple>
#include <typeindex>

#include "Synergy/Core.h"
#include "Synergy/Component/ComponentPoolBase.h"
#include "Synergy/Entity/Entity.h"
#include "Synergy/Entity/EntityId.h"
#include "Synergy/Util/SlotMap.h"

namespace Synergy
{
    class Entity;
    class Scene;

    template <typename Component>
    class SYNERGY_API ComponentPool: public ComponentPoolBase
    {
        friend class Entity;
        friend class Scene;
        
    public:
        ComponentPool() = default;
        ComponentPool(Synergy::Scene& scene);
        ~ComponentPool() = default;
        
        virtual void* Get(Synergy::EntityId id) final;
        virtual Synergy::EntityId Clone(Synergy::EntityId id) final;
        virtual std::pair<std::type_index, Synergy::EntityId> Clone(Synergy::EntityId id, Synergy::Scene& scene) final;
        
    private:
        virtual void Erase(Synergy::EntityId id) final;
        
    private:
        stdext::slot_map<Component> m_Components;
    };

    template <typename Component>
    inline ComponentPool<Component>::ComponentPool(Synergy::Scene& scene)
    {}

    template <typename Component>
    inline void* ComponentPool<Component>::Get(Synergy::EntityId id)
    {
        return &m_Components[id];
    }

    template <typename Component>
    inline Synergy::EntityId ComponentPool<Component>::Clone(Synergy::EntityId id)
    {
        return m_Components.insert(m_Components[id]);
    }

    template <typename Component>
    inline std::pair<std::type_index, Synergy::EntityId> ComponentPool<Component>::Clone(Synergy::EntityId id, Synergy::Scene& scene)
    {
        return std::make_pair(std::type_index(typeid(Component)), scene.GetComponentPool<Component>().m_Components.insert(this->m_Components[id]));
    }

    template <typename Component>
    inline void ComponentPool<Component>::Erase(Synergy::EntityId id)
    {
        m_Components.erase(id);
    }
}

#endif
