// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ENTITY_ARCHETYPE_REF_H
#define SYNERGY_ENTITY_ARCHETYPE_REF_H

#include "Synergy/Core.h"
#include "Synergy/ECS/EntityRef.h"

namespace Synergy
{
    class SYNERGY_API ArchetypeRef : public Synergy::EntityRef
    {
        friend class Application;
        friend class Scene;

    public:
        ArchetypeRef(const Synergy::ArchetypeRef&) = default;
        ArchetypeRef(Synergy::ArchetypeRef&&) = default;
        ArchetypeRef() = delete;
        
        using EntityRef::EntityRef;
        using EntityRef::operator==;
        using EntityRef::Get;
        using EntityRef::Has;
        using EntityRef::Id;
        using EntityRef::Name;
        
        template <typename Component, typename... Args>
        Component& Add(Args&&... args);
        
        template <typename Component>
        void Remove();
        
    private:
        Synergy::Scene* GetScene();
        ArchetypeRef(Synergy::EntityRef entity);
    };
}

#include "Synergy/Entity/ArchetypeRef.inl"

#endif
