// Created by Niels Marsman on 14-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_COMPONENT_COMPONENT_POOL_BASE_H
#define SYNERGY_COMPONENT_COMPONENT_POOL_BASE_H

#include <tuple>
#include <typeindex>

#include "Synergy/Core.h"
#include "Synergy/Entity/EntityId.h"

namespace Synergy
{
    class Entity;
    class Scene;

    class SYNERGY_API ComponentPoolBase
    {
        friend class Entity;
        
    public:
        ComponentPoolBase() = default;
        ComponentPoolBase(const Synergy::ComponentPoolBase&) = delete;
        ComponentPoolBase(Synergy::ComponentPoolBase&&) = default;
        virtual ~ComponentPoolBase() = default;
        
        virtual void* Get(Synergy::EntityId id) = 0;
        virtual Synergy::EntityId Clone(Synergy::EntityId id) = 0;
        virtual std::pair<std::type_index, Synergy::EntityId> Clone(Synergy::EntityId id, Synergy::Scene& scene) = 0;
        
    private:
        virtual void Erase(Synergy::EntityId id) = 0;
    };
}

#endif
