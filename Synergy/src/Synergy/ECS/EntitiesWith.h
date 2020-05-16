// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_ENTITIES_WITH_H
#define SYNERGY_ECS_ENTITIES_WITH_H

#include "Synergy/Core.h"
#include "Synergy/ECS/EntitiesWithBase.h"

namespace Synergy
{
    template <typename... Args>
    class EntitiesWith : public Synergy::EntitiesWithBase
    {
    public:
        
    private:
        virtual void Set(const std::vector<Synergy::EntityRef>&) final;
        virtual void Push(const Synergy::EntityRef&) final;
        
    private:
        std::vector<Synergy::EntityRef> m_Entities;
    };
}

#endif
