// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ENTITY_ENTITIES_WITH_BASE_H
#define SYNERGY_ENTITY_ENTITIES_WITH_BASE_H

#include "Synergy/Core.h"

namespace Synergy
{
    class ComponentAggregate;
    class EntityRef;

    class EntitiesWithBase
    {
        friend class ComponentAggregate;
        
    protected:
        virtual void Set(const std::vector<Synergy::EntityRef>&) = 0;
        virtual void Push(const Synergy::EntityRef&) = 0;
        virtual void Pop(size_t) = 0;
    };
}

#endif
