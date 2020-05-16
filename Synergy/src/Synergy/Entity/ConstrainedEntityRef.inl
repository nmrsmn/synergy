// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ENTITY_CONSTRAINED_ENTITY_REF_INLINE
#define SYNERGY_ENTITY_CONSTRAINED_ENTITY_REF_INLINE

template <typename... Args>
Synergy::ConstrainedEntityRef<Args...>::ConstrainedEntityRef(const Synergy::EntityRef& entity) :
    m_Entity(entity)
{}

template <typename... Args>
template <typename Component, typename>
Component& Synergy::ConstrainedEntityRef<Args...>::Get()
{
  return this->GetMutable<Component, Args...>();
}

template <typename... Args>
template <typename Component, typename>
const Component& Synergy::ConstrainedEntityRef<Args...>::Get() const
{
  return this->GetImmutable<Component, Args...>();
}

template <typename... Args>
template <typename Predicate>
void Synergy::ConstrainedEntityRef<Args...>::Invoke(Predicate&& predicate)
{
    predicate(Get<Args>()...);
}
template <typename... Args>
template <typename R, typename C>
void Synergy::ConstrainedEntityRef<Args...>::Invoke(R (C::*method)(Args...) const, const C& instance)
{
    (instance.*method)(Get<Args>()...);
}

template <typename... Args>
template <typename Component, typename T>
Component& Synergy::ConstrainedEntityRef<Args...>::GetMutable()
{
    if constexpr(std::is_same_v<Component, T>)
    {
        return m_Entity.Get<Component>();
    }
}

template <typename... Args>
template <typename Component, typename T, typename Next, typename... Others>
Component& Synergy::ConstrainedEntityRef<Args...>::GetMutable()
{
    if constexpr(std::is_same_v<Component, T>)
    {
        return m_Entity.Get<Component>();
    }
    else if constexpr(sizeof...(Others))
    {
        return this->GetMutable<Component, Next, Others...>();
    }
    else
    {
        return this->GetMutable<Component, Next>();
    }
}

template <typename... Args>
template <typename Component, typename T>
const Component& Synergy::ConstrainedEntityRef<Args...>::GetImmutable() const
{
    if constexpr(std::is_same_v<Component, T>)
    {
        return m_Entity.Get<Component>();
    }
}

template <typename... Args>
template <typename Component, typename T, typename Next, typename... Others>
const Component& Synergy::ConstrainedEntityRef<Args...>::GetImmutable() const
{
    if constexpr(std::is_same_v<Component, T>)
    {
        return m_Entity.Get<Component>();
    }
    else if constexpr(sizeof...(Others))
    {
        return this->GetImmutable<Component, Next, Others...>();
    }
    else
    {
        return this->GetImmutable<Component, Next>();
    }
}

#endif
