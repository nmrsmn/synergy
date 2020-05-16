// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ENTITY_ARCHETYPE_REF_INLINE
#define SYNERGY_ENTITY_ARCHETYPE_REF_INLINE

#include "Synergy/ECS/Scene.h"

template <typename Component, typename... Args>
inline Component& Synergy::ArchetypeRef::Add(Args&&... args)
{
    return m_Scene->GetEntity(m_Id)->Add<Component>(std::forward<Args>(args)...);
}

template <typename Component>
inline void Synergy::ArchetypeRef::Remove()
{
    m_Scene->GetEntity(m_Id)->Remove<Component>();
}

#endif
