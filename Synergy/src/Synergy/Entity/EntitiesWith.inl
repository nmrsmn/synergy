// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ENTITY_ENTITIES_WITH_INLINE
#define SYNERGY_ENTITY_ENTITIES_WITH_INLINE

#include "Synergy/Entity/ConstrainedEntityRef.h"

template <typename... Args>
typename Synergy::EntitiesWith<Args...>::iterator Synergy::EntitiesWith<Args...>::begin()
{
    return m_Entities.begin();
}

template <typename... Args>
typename Synergy::EntitiesWith<Args...>::iterator Synergy::EntitiesWith<Args...>::end()
{
    return m_Entities.end();
}

template <typename... Args>
typename Synergy::EntitiesWith<Args...>::const_iterator Synergy::EntitiesWith<Args...>::begin() const
{
    return m_Entities.cbegin();
}

template <typename... Args>
typename Synergy::EntitiesWith<Args...>::const_iterator Synergy::EntitiesWith<Args...>::end() const
{
    return m_Entities.cend();
}

template <typename... Args>
typename Synergy::EntitiesWith<Args...>::const_iterator Synergy::EntitiesWith<Args...>::cbegin() const
{
    return m_Entities.cbegin();
}

template <typename... Args>
typename Synergy::EntitiesWith<Args...>::const_iterator Synergy::EntitiesWith<Args...>::cend() const
{
    return m_Entities.cend();
}

template <typename... Args>
Synergy::ConstrainedEntityRef<Args...>& Synergy::EntitiesWith<Args...>::operator[](size_t position)
{
    return m_Entities[position];
}

template <typename... Args>
const Synergy::ConstrainedEntityRef<Args...>& Synergy::EntitiesWith<Args...>::operator[](size_t position) const
{
    return m_Entities[position];
}

template <typename... Args>
inline void Synergy::EntitiesWith<Args...>::Set(const std::vector<Synergy::EntityRef>& entities)
{
    m_Entities.assign(entities.begin(), entities.end());
}

template <typename... Args>
inline void Synergy::EntitiesWith<Args...>::Push(const Synergy::EntityRef& entity)
{
    m_Entities.push_back(entity);
}

template <typename... Args>
inline void Synergy::EntitiesWith<Args...>::Pop(size_t index)
{
    m_Entities[index] = m_Entities.back();
    m_Entities.pop_back();
}

#endif
