// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_CONSTRAINED_ENTITY_REF_H
#define SYNERGY_ECS_CONSTRAINED_ENTITY_REF_H

#include "Synergy/Core.h"
#include "Synergy/ECS/EntityRef.h"

namespace Synergy
{
    template <typename... Args>
    class ConstrainedEntityRef
    {
    public:
        ConstrainedEntityRef(const Synergy::EntityRef& entity);
        ConstrainedEntityRef(const ConstrainedEntityRef&) = default;
        ~ConstrainedEntityRef() = default;
        
        template <typename Component, typename = std::enable_if_t<!std::is_const_v<Component>>>
        Component& Get();

        template <typename Component, typename = std::enable_if_t<std::is_const_v<Component>>>
        const Component& Get() const;
        
        template <typename Predicate>
        void Invoke(Predicate&& p);
        
        template <typename R, typename C>
        void Invoke(R (C::*method)(Args...) const, const C& instance);
        
    private:
        template <typename Component, typename T>
        Component& GetMutable();
        
        template <typename Component, typename T, typename Next, typename... Others>
        Component& GetMutable();
        
        template <typename Component, typename T>
        const Component& GetImmutable() const;
        
        template <typename Component, typename T, typename Next, typename... Others>
        const Component& GetImmutable() const;
        
    private:
        Synergy::EntityRef m_Entity;
    };
}

#include "Synergy/ECS/ConstrainedEntityRef.inl"

#endif
