// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ENTITY_ENTITIES_WITH_H
#define SYNERGY_ENTITY_ENTITIES_WITH_H

#include "Synergy/Core.h"
#include "Synergy/Entity/EntitiesWithBase.h"

namespace Synergy
{
    template <typename... Args>
    class ConstrainedEntityRef;

    template <typename... Args>
    class EntitiesWith : public Synergy::EntitiesWithBase
    {
    public:
        using iterator = typename std::vector<Synergy::ConstrainedEntityRef<Args...>>::iterator;
        using const_iterator = typename std::vector<Synergy::ConstrainedEntityRef<Args...>>::const_iterator;
        
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        
        Synergy::ConstrainedEntityRef<Args...>& operator[](size_t position);
        const Synergy::ConstrainedEntityRef<Args...>& operator[](size_t position) const;
        
    private:
        virtual void Set(const std::vector<Synergy::EntityRef>&) final;
        virtual void Push(const Synergy::EntityRef&) final;
        virtual void Pop(size_t) final;
        
    public:
        std::vector<Synergy::ConstrainedEntityRef<Args...>> m_Entities;
    };
}

#include "Synergy/Entity/EntitiesWith.inl"

#endif
