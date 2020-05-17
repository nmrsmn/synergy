// Created by Niels Marsman on 15-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_EVENT_EVENT_DISPATCHER_H
#define SYNERGY_EVENT_EVENT_DISPATCHER_H

#include <functional>
#include <vector>

#include "Synergy/Core.h"

namespace Synergy
{
    template <typename T>
    using EventCallback = std::function<void (const T&)>;
    using VoidCallback = std::function<void (void)>;

    struct EventDispatcherBase
    {};

    template <typename T>
    class EventDispatcher : public EventDispatcherBase
    {
    public:
        using Callback = typename Synergy::EventCallback<T>;
        
        inline void Emit(const T& event);
        
        void OnEvent(Callback callback);
        void OnNextEvent(Callback callback);
        
    private:
        std::vector<Synergy::EventDispatcher<T>::Callback> m_Callbacks;
        std::vector<Synergy::EventDispatcher<T>::Callback> m_CallOnce;
    };

    template <typename T>
    inline void EventDispatcher<T>::Emit(const T& event)
    {
        for (auto& callback : m_Callbacks)
        {
            callback(event);
        }
        
        for (auto& callback : m_CallOnce)
        {
            callback(event);
        }
        
        m_CallOnce.clear();
    }

    template <typename T>
    inline void EventDispatcher<T>::OnEvent(EventDispatcher<T>::Callback callback)
    {
        m_Callbacks.emplace_back(callback);
    }

    template <typename T>
    inline void EventDispatcher<T>::OnNextEvent(EventDispatcher<T>::Callback callback)
    {
        m_CallOnce.emplace_back(callback);
    }
}

#endif
