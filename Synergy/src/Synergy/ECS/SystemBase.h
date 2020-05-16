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
        
        virtual bool HasEntities() const = 0;
        
        virtual bool HasInitialize() const = 0;
        virtual bool HasDestroy() const = 0;
        virtual bool HasEnable() const = 0;
        virtual bool HasDisable() const = 0;
        virtual bool HasLoad() const = 0;
        virtual bool HasUnload() const = 0;
        virtual bool HasReload() const = 0;
        virtual bool HasFrameStart() const = 0;
        virtual bool HasFrameEnd() const = 0;
        virtual bool HasFixedUpdate() const = 0;
        virtual bool HasPreProcess() const = 0;
        virtual bool HasProcess() const = 0;
        virtual bool HasPostProcess() const = 0;
        virtual bool HasUpdate() const = 0;
        virtual bool HasPostUpdate() const = 0;
        
        virtual void OnFrameStart() = 0;
        virtual void OnFrameEnd() = 0;
        
        virtual void OnUpdate(float dt) = 0;
    };
}

#endif
