// Created by Niels Marsman on 15-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_SYSTEM_H
#define SYNERGY_ECS_SYSTEM_H

#include "Synergy/Core.h"
#include "Synergy/ECS/SystemBase.h"

namespace Synergy
{
    class Scene;

    template <typename T>
    class SYNERGY_API System : public Synergy::SystemBase
    {
    public:
        template <typename... Args>
        System(Synergy::Scene& scene, const std::string& name, Args&&... args);
        
        virtual bool HasInitialize() const final;
        
        virtual void OnFrameStart() final;
        virtual void OnFrameEnd() final;
        
        virtual void OnUpdate(float dt) final;
        
    private:
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasInitialize> Initialize();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasInitialize> Initialize();
        
    private:
        std::string m_Name;
        T m_Instance;
    };
}

#include "Synergy/ECS/System.inl"

#endif
