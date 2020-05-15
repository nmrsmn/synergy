// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_ENTITY_INLINE
#define SYNERGY_ECS_ENTITY_INLINE

#include "Synergy/ECS/Scene.h"

template <typename Component>
bool Synergy::Entity::Has() const
{
    return m_Components.count(std::type_index(typeid(std::decay_t<Component>)));
}

template <typename Component, typename Next, typename... Others>
bool Synergy::Entity::Has() const
{
    return this->Has<Component>() && this->Has<Next>()
        && this->Has<Others...>();
}

template <typename Component>
Component& Synergy::Entity::Get()
{
    static const std::type_index index = std::type_index(typeid(std::decay_t<Component>));
    return m_Scene.GetComponent<std::decay_t<Component>>(m_Components[index]);
}

template <typename Component>
const Component& Synergy::Entity::Get() const
{
    auto component { m_Components.find(std::type_index(typeid(Component))) };
    
    if (component != m_Components.end())
    {
        return component;
    }
    
    SYNERGY_ASSERT(component != m_Components.end(), "Tried to get a component from an entity which doesn't have that component.");
    return nullptr;
}

template <typename Component, typename... Args>
Component& Synergy::Entity::Add(Args&&... args)
{
    SYNERGY_ASSERT(this->Has<Component>() == false, "An entity may only be associated with a single instance of each component.");
    
    auto& pool = m_Scene.GetComponentPool<Component>();
    Synergy::EntityId handle = pool.m_Components.emplace(std::forward<Args>(args)...);
    
    auto component { m_Components.find(std::type_index(typeid(Component))) };
    if (component != m_Components.end())
    {
        component->second = handle;
    }
    else
    {
        m_Components.emplace(std::type_index(typeid(Component)), handle);
    }
    
    return this->Get<Component>();
}

#endif