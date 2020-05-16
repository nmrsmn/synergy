// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_COMPONENT_COMPONENT_AGGREGATE_INLINE
#define SYNERGY_COMPONENT_COMPONENT_AGGREGATE_INLINE

#include "Synergy/Entity/EntitiesWith.h"
#include "Synergy/Entity/EntitiesWithBase.h"

template <typename... Args>
inline Synergy::ComponentAggregate::ComponentAggregate(stdext::type_list<Args...>)
{
    this->Add<Args...>();
}

template <typename... Args>
inline bool Synergy::ComponentAggregate::Matches() const
{
    if (sizeof...(Args) != m_Components.size())
        return false;
    
    std::vector<std::type_index> hashes { std::type_index(typeid(Args))... };
    std::sort(std::begin(hashes), std::end(hashes));
    
    return std::equal(std::begin(hashes), std::end(hashes), std::begin(m_Components));
}

template <typename... Args>
inline void Synergy::ComponentAggregate::AddEntityList(Synergy::EntitiesWith<Args...>& list)
{
    SYNERGY_ASSERT(this->Matches<Args...>(), "Only a verified list can be added.");
    
    m_EntityLists.push_back(&list);
    m_EntityLists.back()->Set(m_Entities);
}

template <typename T>
inline void Synergy::ComponentAggregate::Add()
{
    SYNERGY_ASSERT(!std::is_reference_v<T>, "References may not be used as components.");
    
    m_Components.push_back(std::type_index(typeid(T)));
}

template <typename T, typename Next, typename... Args>
inline void Synergy::ComponentAggregate::Add()
{
    this->Add<T>();
    this->Add<Next, Args...>();
    
    std::sort(std::begin(m_Components), std::end(m_Components));
}

#endif
