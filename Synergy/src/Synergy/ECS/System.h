// Created by Niels Marsman on 15-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_SYSTEM_H
#define SYNERGY_ECS_SYSTEM_H

#include "Synergy/Core.h"
#include "Synergy/ECS/SystemBase.h"
#include "Synergy/Event/Events.h"

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
        virtual bool HasDestroy() const final;
        virtual bool HasEnable() const final;
        virtual bool HasDisable() const final;
        virtual bool HasLoad() const final;
        virtual bool HasUnload() const final;
        virtual bool HasReload() const final;
        virtual bool HasFrameStart() const final;
        virtual bool HasFrameEnd() const final;
        virtual bool HasFixedUpdate() const final;
        virtual bool HasPreProcess() const final;
        virtual bool HasProcess() const final;
        virtual bool HasPostProcess() const final;
        virtual bool HasUpdate() const final;
        virtual bool HasPostUpdate() const final;
        
        virtual void OnFrameStart() final;
        virtual void OnFrameEnd() final;
        
        virtual void OnUpdate(float dt) final;
        
    private:
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasInitialize> Initialize();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasInitialize> Initialize();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasDestroy> Destroy();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasDestroy> Destroy();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasEnable> Enable();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasEnable> Enable();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasDisable> Disable();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasDisable> Disable();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasLoad> Load();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasLoad> Load();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasUnload> Unload();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasUnload> Unload();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasReload> Reload();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasReload> Reload();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasFrameStart> FrameStart();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasFrameStart> FrameStart();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasFrameEnd> FrameEnd();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasFrameEnd> FrameEnd();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasFixedUpdate> FixedUpdate(float dt);
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasFixedUpdate> FixedUpdate(float dt);
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasPreProcess> PreProcess();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasPreProcess> PreProcess();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasProcess> Process();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasProcess> Process();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasPostProcess> PostProcess();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasPostProcess> PostProcess();
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasUpdate> Update(float dt);
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasUpdate> Update(float dt);
        
        template <typename U = T>
        typename std::enable_if_t<Synergy::SystemTraits<U>::HasPostUpdate> PostUpdate();
        template <typename U = T>
        typename std::enable_if_t<!Synergy::SystemTraits<U>::HasPostUpdate> PostUpdate();
        
    private:
        std::string m_Name;
        T m_Instance;
    };
}

#include "Synergy/ECS/System.inl"

#endif
