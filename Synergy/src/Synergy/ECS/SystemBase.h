// Created by Niels Marsman on 15-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_SYSTEM_BASE_H
#define SYNERGY_ECS_SYSTEM_BASE_H

#include "Synergy/Core.h"
#include "Synergy/ECS/SystemTraits.h"

namespace Synergy
{
    class SYNERGY_API SystemBase
    {
    public:
        virtual ~SystemBase() {}
        
        virtual bool HasInitialize() const = 0;
        
        virtual void OnFrameStart() = 0;
        virtual void OnFrameEnd() = 0;
        
        virtual void OnUpdate(float dt) = 0;
    };
}

#endif
