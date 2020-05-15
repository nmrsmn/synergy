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
    using EventCallback = std::function<bool (const T&)>;
    using VoidCallback = std::function<bool (void)>;

    struct EventDispatcherBase
    {};

    template <typename T>
    class EventDispatcher : public EventDispatcherBase
    {
    public:
        using Callback = typename Synergy::EventCallback<T>;
        
        inline void Emit(const T& event)
        {
            for (auto& callback : m_Callbacks)
            {
                if (callback(event))
                    break;
            }
            
            for (auto& callback : m_CallOnce)
            {
                if (callback(event))
                    break;
            }
            
            m_CallOnce.clear();
        }
        
        void OnEvent(Callback callback)
        {
            m_Callbacks.emplace_back(callback);
        }
        
        void OnNextEvent(Callback callback)
        {
            m_CallOnce.emplace_back(callback);
        }
        
    private:
        std::vector<Synergy::EventDispatcher<T>::Callback> m_Callbacks;
        std::vector<Synergy::EventDispatcher<T>::Callback> m_CallOnce;
    };
}

#endif
