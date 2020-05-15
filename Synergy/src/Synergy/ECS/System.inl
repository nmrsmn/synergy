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
    // Events
}

template <typename T>
bool Synergy::System<T>::HasInitialize() const
{
    return SystemTraits<T>::HasInitialize;
}

template <typename T>
inline void Synergy::System<T>::OnFrameStart()
{
    
}

template <typename T>
inline void Synergy::System<T>::OnFrameEnd()
{
    
}

template <typename T>
inline void Synergy::System<T>::OnUpdate(float dt)
{
    
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


#endif
