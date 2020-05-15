// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_SCENE_INLINE
#define SYNERGY_ECS_SCENE_INLINE

#include "Synergy/ECS/ComponentPoolBase.h"
#include "Synergy/ECS/ComponentPool.h"

template <typename T>
T& Synergy::Scene::GetComponent(Synergy::EntityId entity)
{
    return this->GetComponentPool<std::decay_t<T>>().m_Components[entity];
}

template <typename T>
const T& Synergy::Scene::GetComponent(Synergy::EntityId entity) const
{
    return this->GetComponentPool<std::decay_t<T>>().m_Components[entity];
}

template <typename T>
Synergy::ComponentPool<T>& Synergy::Scene::GetComponentPool()
{
    std::type_index index { std::type_index(typeid(T)) };
    
    if (auto component { m_Components.find(index) }; component != m_Components.end())
    {
        return *reinterpret_cast<Synergy::ComponentPool<T>*>(component->second.get());
    }
    else
    {
        Synergy::Scope<Synergy::ComponentPoolBase>& pointer { m_Components[index] };
        pointer.reset(new ComponentPool<T>(*this));
        
        return *reinterpret_cast<Synergy::ComponentPool<T>*>(pointer.get());
    }
}

template <typename T>
const Synergy::ComponentPool<T>& Synergy::Scene::GetComponentPool() const
{
    return const_cast<Scene*>(this)->GetComponentPool<T>();
}

#endif
