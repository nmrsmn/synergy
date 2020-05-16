// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_ENTITY_REF_INLINE
#define SYNERGY_ECS_ENTITY_REF_INLINE

#include "Synergy/ECS/Entity.h"
#include "Synergy/ECS/Scene.h"
#include "Synergy/ECS/SceneEvents.h"

template <typename Component>
bool Synergy::EntityRef::Has() const
{
    return this->Has(std::type_index(typeid(Component)));
}

template <typename Component, typename Next, typename... Others>
bool Synergy::EntityRef::Has() const
{
    return this->Has<Component>() && this->Has<Next>()
        && this->Has<Others...>();
}

template <typename Component>
Component& Synergy::EntityRef::Get()
{
    return m_Scene->GetEntity(m_Id)->Get<Component>();
}

template <typename Component>
const Component& Synergy::EntityRef::Get() const
{
    return m_Scene->GetEntity(m_Id)->Get<Component>();
}

template <typename Component, typename... Args>
Component& Synergy::EntityRef::Add(Args&&... args)
{
    if (this->Has<Component>())
        return this->Get<Component>();

    Component& component { m_Scene->GetEntity(m_Id)->Add<Component>(std::forward<Args>(args)...) };
    
    m_Scene->Emit(Synergy::ComponentAddedEvent { *this, std::type_index(typeid(Component)) });
    
    return component;
}

template <typename Component>
void Synergy::EntityRef::Remove()
{
    if (!this->Has<Component>())
        return;
    
    m_Scene->Emit(Synergy::ComponentRemovedEvent { *this, std::type_index(typeid(Component)) });
    m_Scene->OnNextEvent([=] (const Synergy::FrameEndEvent& event)
    {
        auto a = m_Scene->GetEntity(m_Id)->Remove<Component>();
    });
}

#endif
