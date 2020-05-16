// Created by Niels Marsman on 15-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_SYSTEM_INLINE
#define SYNERGY_ECS_SYSTEM_INLINE

template <typename T>
template <typename... Args>
inline Synergy::System<T>::System(Synergy::Scene& scene, const std::string& name, Args&&... args) :
    m_Instance(std::forward<Args>(args)...),
    m_Name(name)
{
    if constexpr(Synergy::SystemTraits<T>::HasEntities)
        this->RegisterEntities(scene);
    
    scene.OnEvent([&] (const Synergy::UpdateEvent& event)
    {
        this->OnUpdate(event.dt);
    });
    
    if constexpr(Synergy::SystemTraits<T>::HasFrameStart)
        scene.OnEvent([&] (const Synergy::FrameStartEvent& event)
        {
            this->OnStartFrame();
        });
    
    if constexpr(Synergy::SystemTraits<T>::HasFrameEnd)
        scene.OnEvent([&] (const Synergy::FrameEndEvent& event)
        {
            this->OnEndFrame();
        });
    
    if constexpr(Synergy::SystemTraits<T>::HasInitialize)
        this->Initialize();
}

template <typename T>
bool Synergy::System<T>::HasEntities() const
{
    return SystemTraits<T>::HasEntities;
}

template <typename T>
bool Synergy::System<T>::HasInitialize() const
{
    return SystemTraits<T>::HasInitialize;
}

template <typename T>
bool Synergy::System<T>::HasDestroy() const
{
    return Synergy::SystemTraits<T>::HasDestroy;
}

template <typename T>
bool Synergy::System<T>::HasEnable() const
{
    return Synergy::SystemTraits<T>::HasEnable;
}

template <typename T>
bool Synergy::System<T>::HasDisable() const
{
    return Synergy::SystemTraits<T>::HasDisable;
}

template <typename T>
bool Synergy::System<T>::HasLoad() const
{
    return Synergy::SystemTraits<T>::HasLoad;
}

template <typename T>
bool Synergy::System<T>::HasUnload() const
{
    return Synergy::SystemTraits<T>::HasUnload;
}

template <typename T>
bool Synergy::System<T>::HasReload() const
{
    return Synergy::SystemTraits<T>::HasReload;
}

template <typename T>
bool Synergy::System<T>::HasFrameStart() const
{
    return Synergy::SystemTraits<T>::HasFrameStart;
}

template <typename T>
bool Synergy::System<T>::HasFrameEnd() const
{
    return Synergy::SystemTraits<T>::HasFrameEnd;
}

template <typename T>
bool Synergy::System<T>::HasFixedUpdate() const
{
    return Synergy::SystemTraits<T>::HasFixedUpdate;
}

template <typename T>
bool Synergy::System<T>::HasPreProcess() const
{
    return Synergy::SystemTraits<T>::HasPreProcess;
}

template <typename T>
bool Synergy::System<T>::HasProcess() const
{
    return Synergy::SystemTraits<T>::HasProcess;
}

template <typename T>
bool Synergy::System<T>::HasPostProcess() const
{
    return Synergy::SystemTraits<T>::HasPostProcess;
}

template <typename T>
bool Synergy::System<T>::HasUpdate() const
{
    return Synergy::SystemTraits<T>::HasUpdate;
}

template <typename T>
bool Synergy::System<T>::HasPostUpdate() const
{
    return Synergy::SystemTraits<T>::HasPostUpdate;
}

template <typename T>
inline void Synergy::System<T>::OnFrameStart()
{
    if constexpr(Synergy::SystemTraits<T>::HasFrameStart)
        this->FrameStart();
}

template <typename T>
inline void Synergy::System<T>::OnFrameEnd()
{
    if constexpr(Synergy::SystemTraits<T>::HasFrameEnd)
        this->FrameEnd();
}

template <typename T>
inline void Synergy::System<T>::OnUpdate(float dt)
{
    if constexpr(Synergy::SystemTraits<T>::HasPreProcess)   this->PreProcess();
    if constexpr(Synergy::SystemTraits<T>::HasProcess)      this->Process();
    if constexpr(Synergy::SystemTraits<T>::HasPostProcess)  this->PostProcess();
    if constexpr(Synergy::SystemTraits<T>::HasUpdate)       this->Update();
    if constexpr(Synergy::SystemTraits<T>::HasPostUpdate)   this->PostUpdate();
}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasInitialize> Synergy::System<T>::Initialize()
{
    m_Instance.Initialize();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasInitialize> Synergy::System<T>::Initialize()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasDestroy> Synergy::System<T>::Destroy()
{
    m_Instance.Destroy();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasDestroy> Synergy::System<T>::Destroy()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasEnable> Synergy::System<T>::Enable()
{
    m_Instance.Enable();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasEnable> Synergy::System<T>::Enable()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasDisable> Synergy::System<T>::Disable()
{
    m_Instance.Disable();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasDisable> Synergy::System<T>::Disable()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasLoad> Synergy::System<T>::Load()
{
    m_Instance.Load();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasLoad> Synergy::System<T>::Load()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasUnload> Synergy::System<T>::Unload()
{
    m_Instance.Unload();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasUnload> Synergy::System<T>::Unload()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasReload> Synergy::System<T>::Reload()
{
    m_Instance.Reload();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasReload> Synergy::System<T>::Reload()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasFrameStart> Synergy::System<T>::FrameStart()
{
    m_Instance.FrameStart();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasFrameStart> Synergy::System<T>::FrameStart()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasFrameEnd> Synergy::System<T>::FrameEnd()
{
    m_Instance.FrameEnd();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasFrameEnd> Synergy::System<T>::FrameEnd()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasFixedUpdate> Synergy::System<T>::FixedUpdate(float dt)
{
    m_Instance.FixedUpdate(dt);
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasFixedUpdate> Synergy::System<T>::FixedUpdate(float dt)
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasPreProcess> Synergy::System<T>::PreProcess()
{
    m_Instance.PreProcess();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasPreProcess> Synergy::System<T>::PreProcess()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasProcess> Synergy::System<T>::Process()
{
    for (auto entity : m_Instance.m_Entities)
    {
        entity.Invoke([&] (auto&&... args)
        {
            m_Instance.Process(std::forward<decltype(args)>(args)...);
        });
    }
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasProcess> Synergy::System<T>::Process()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasPostProcess> Synergy::System<T>::PostProcess()
{
    m_Instance.PostProcess();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasPostProcess> Synergy::System<T>::PostProcess()
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasUpdate> Synergy::System<T>::Update(float dt)
{
    m_Instance.Update(dt);
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasUpdate> Synergy::System<T>::Update(float dt)
{}

template <typename T>
template <typename U>
typename std::enable_if_t<Synergy::SystemTraits<U>::HasPostUpdate> Synergy::System<T>::PostUpdate()
{
    m_Instance.PostUpdate();
}

template <typename T>
template <typename U>
typename std::enable_if_t<!Synergy::SystemTraits<U>::HasPostUpdate> Synergy::System<T>::PostUpdate()
{}

template <typename T>
void Synergy::System<T>::RegisterEntities(Synergy::Scene& scene)
{
    scene.RegisterEntitiesWith(m_Instance.m_Entities);
}

#endif
