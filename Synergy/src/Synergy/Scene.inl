// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_SCENE_INLINE
#define SYNERGY_SCENE_INLINE

#include "Synergy/Component/ComponentAggregate.h"
#include "Synergy/Component/ComponentPoolBase.h"
#include "Synergy/Component/ComponentPool.h"
#include "Synergy/Entity/EntitiesWith.h"
#include "Synergy/Scene.h"
#include "Synergy/System/System.h"
#include "Synergy/System/SystemBase.h"
#include "Synergy/Util/TypeList.h"

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

template <typename T, typename... Args>
void Synergy::Scene::Add(const std::string& name, Args&&... args)
{
    m_Systems.push_back(std::move(Synergy::Scope<Synergy::SystemBase>(new Synergy::System<T>(*this, name, std::forward<Args>(args)...))));
}

template <typename... Args>
Synergy::ComponentAggregate& Synergy::Scene::GetAggregate()
{
    std::vector<std::type_index> hashes { std::type_index(typeid(Args))... };
    std::sort(std::begin(hashes), std::end(hashes));
    
    for (auto& aggregate : m_Aggregates)
    {
        if (aggregate.Matches(hashes))
            return aggregate;
    }
    
    m_Aggregates.emplace_back(stdext::type_list<Args...> {});
    
    for (const auto& entity : m_Entities)
    {
        m_Aggregates.back().OnEntityCreated(Synergy::EntityRef(entity.Id(), this));
    }
    
    return m_Aggregates.back();
}

template <typename... Args>
const Synergy::ComponentAggregate& Synergy::Scene::GetAggregate() const
{
    return const_cast<Scene*>(this)->GetAggregate<Args...>();
}

template <typename... Args>
void Synergy::Scene::RegisterEntitiesWith(Synergy::EntitiesWith<Args...>& entities)
{
    this->GetAggregate<Args...>().AddEntityList(entities);
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
