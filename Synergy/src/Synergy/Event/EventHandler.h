// Created by Niels Marsman on 15-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_EVENT_HANDLER_H
#define SYNERGY_EVENT_HANDLER_H

#include <functional>
#include <typeindex>
#include <unordered_map>

#include "Synergy/Core.h"
#include "Synergy/Event/EventDispatcher.h"

namespace Synergy
{
    class EventHandler
    {
    public:
        EventHandler() = default;
        EventHandler(const Synergy::EventHandler&) = delete;
        EventHandler(Synergy::EventHandler&&) = default;

        template <typename T>
        using Callback = Synergy::EventCallback<T>;
        
        // Any events
        
        template<typename T>
        inline void OnEvent(Synergy::EventCallback<T> callback);
        
        template <typename T>
        inline void OnEvent(void (*callback) (const T&));

        template <typename Predicate>
        inline void OnEvent(Predicate&& predicate);
        
        template <typename Predicate, typename T>
        inline void OnEvent(void (Predicate::*callback) (const T&), Predicate predicate);

        template <typename Predicate, typename T>
        inline void OnEvent(void (Predicate::*callback) (const T&) const, Predicate predicate);
        
        // Specific events
        
        template <typename T>
        inline void OnEvent(const T& event, Synergy::EventCallback<T> callback);
        
        template <typename T>
        inline void OnEvent(const T& event, Synergy::VoidCallback callback);
        
        template <typename T>
        inline void OnEvent(const T& event, void (*callback) (const T&));

        template <typename T>
        inline void OnEvent(const T& event, void (*callback) (void));
        
        template <typename T, typename Predicate>
        inline void OnEvent(const T& event, Predicate&& predicate);
        
        template <typename Predicate, typename T>
        inline void OnEvent(const T& event, void (Predicate::*callback) (const T&), Predicate predicate);
        
        template <typename Predicate, typename T>
        inline void OnEvent(const T& event, void (Predicate::*callback) (void), Predicate predicate);

        template <typename Predicate, typename T>
        inline void OnEvent(const T& event, void (Predicate::*callback) (const T&) const, Predicate predicate);

        template <typename Predicate, typename T>
        inline void OnEvent(const T& event, void (Predicate::*callback) (void) const, Predicate predicate);
        
        // Only next event
        
        template<typename T>
        inline void OnNextEvent(Synergy::EventCallback<T> callback);
        
        template <typename T>
        inline void OnNextEvent(void (*callback) (const T&));

        template <typename Predicate>
        inline void OnNextEvent(Predicate&& predicate);
        
        template <typename Predicate, typename T>
        inline void OnNextEvent(void (Predicate::*callback) (const T&), Predicate predicate);

        template <typename Predicate, typename T>
        inline void OnNextEvent(void (Predicate::*callback) (const T&) const, Predicate predicate);
        
        // Only on specific next event
        
        template <typename T>
        inline void OnNextEvent(const T& event, Synergy::EventCallback<T> callback);
        
        template <typename T>
        inline void OnNextEvent(const T& event, Synergy::VoidCallback callback);
        
        template <typename T>
        inline void OnNextEvent(const T& event, void (*callback) (const T&));

        template <typename T>
        inline void OnNextEvent(const T& event, void (*callback) (void));
        
        template <typename T, typename Predicate>
        inline void OnNextEvent(const T& event, Predicate&& predicate);
        
        template <typename Predicate, typename T>
        inline void OnNextEvent(const T& event, void (Predicate::*callback) (const T&), Predicate predicate);
        
        template <typename Predicate, typename T>
        inline void OnNextEvent(const T& event, void (Predicate::*callback) (void), Predicate predicate);

        template <typename Predicate, typename T>
        inline void OnNextEvent(const T& event, void (Predicate::*callback) (const T&) const, Predicate predicate);

        template <typename Predicate, typename T>
        inline void OnNextEvent(const T& event, void (Predicate::*callback) (void) const, Predicate predicate);
        
        template <typename T>
        inline void Emit(const T& event);

        template <typename T>
        inline void Enqueue(const T& event);

    private:
        template <typename T>
        inline Synergy::EventDispatcher<T>& Dispatcher();
        
    private:
        std::unordered_map<std::type_index, Synergy::Scope<Synergy::EventDispatcherBase>> m_Dispatchers;
    };

    template<typename T>
    inline void EventHandler::OnEvent(Synergy::EventCallback<T> callback)
    {
        this->Dispatcher<T>().OnEvent(callback);
    }
    
    template <typename T>
    inline void EventHandler::OnEvent(void (*callback) (const T&))
    {
        this->OnEvent(std::function<bool (const T&)>(callback));
    }

    template<typename Predicate>
    inline void EventHandler::OnEvent(Predicate&& predicate)
    {
        this->OnEvent(&Predicate::operator(), predicate);
    }

    template <typename Predicate, typename T>
    inline void EventHandler::OnEvent(void (Predicate::*callback) (const T&), Predicate predicate)
    {
        this->Dispatcher<T>().OnEvent(std::function<void (const T&)>(predicate));
    }

    template <typename Predicate, typename T>
    inline void EventHandler::OnEvent(void (Predicate::*callback) (const T&) const, Predicate predicate)
    {
        this->Dispatcher<T>().OnEvent(std::function<void (const T&)>(predicate));
    }

    template <typename T>
    inline void EventHandler::OnEvent(const T& event, Synergy::EventCallback<T> callback)
    {
        this->OnEvent([callback, event] (const T& current)
        {
            if (current == event)
                callback(event);
        });
    }
    
    template <typename T>
    inline void EventHandler::OnEvent(const T& event, Synergy::VoidCallback callback)
    {
        this->OnEvent([callback, event] (const T& current)
        {
            if (current == event)
                callback();
        });
    }

    template <typename T>
    inline void EventHandler::OnEvent(const T& event, void (*callback) (const T&))
    {
        this->OnEvent(event, std::function<void (const T&)>(callback));
    }
    
    template <typename T>
    inline void EventHandler::OnEvent(const T& event, void (*callback) (void))
    {
        this->OnEvent(event, std::function<void (void)>(callback));
    }

    template <typename T, typename Predicate>
    inline void EventHandler::OnEvent(const T& event, Predicate&& predicate)
    {
        this->OnEvent(event, &Predicate::operator(), predicate);
    }
    
    template <typename Predicate, typename T>
    inline void EventHandler::OnEvent(const T& event, void (Predicate::*callback) (const T&), Predicate predicate)
    {
        this->Dispatcher<T>().OnEvent(std::function<void (const T&)>(predicate));
    }
    
    template <typename Predicate, typename T>
    inline void EventHandler::OnEvent(const T& event, void (Predicate::*callback) (void), Predicate predicate)
    {
        this->Dispatcher<T>().OnEvent(std::function<void (void)>(predicate));
    }

    template <typename Predicate, typename T>
    inline void EventHandler::OnEvent(const T& event, void (Predicate::*callback) (const T&) const, Predicate predicate)
    {
        this->Dispatcher<T>().OnEvent(std::function<void (const T&)>(predicate));
    }

    template <typename Predicate, typename T>
    inline void EventHandler::OnEvent(const T& event, void (Predicate::*callback) (void) const, Predicate predicate)
    {
        this->Dispatcher<T>().OnEvent(std::function<void (void)>(predicate));
    }

    template <typename T>
    inline void EventHandler::OnNextEvent(Synergy::EventCallback<T> callback)
    {
        this->Dispatcher<T>().OnNextEvent(callback);
    }
    
    template <typename T>
    inline void EventHandler::OnNextEvent(void (*callback)(const T&))
    {
        this->OnNextEvent(std::function<void (const T&)>(callback));
    }
    
    template <typename Predicate>
    inline void EventHandler::OnNextEvent(Predicate&& predicate)
    {
        this->OnNextEvent(&Predicate::operator(), predicate);
    }
    
    template <typename Predicate, typename T>
    inline void EventHandler::OnNextEvent(void (Predicate::*callback)(const T&), Predicate predicate)
    {
        this->Dispatcher<T>().OnNextEvent(std::function<void (const T&)>(predicate));
    }
    
    template <typename Predicate, typename T>
    inline void EventHandler::OnNextEvent(void (Predicate::*callback)(const T&) const, Predicate predicate)
    {
        this->Dispatcher<T>().OnNextEvent(std::function<void (const T&)>(predicate));
    }

    template <typename T>
    inline void EventHandler::OnNextEvent(const T& event, Synergy::EventCallback<T> callback)
    {
        this->OnNextEvent([callback, event] (const T& current)
        {
            if (current == event)
                callback(event);
        });
    }
    
    template <typename T>
    inline void EventHandler::OnNextEvent(const T& event, Synergy::VoidCallback callback)
    {
        this->OnNextEvent([callback, event] (const T& current)
        {
            if (current == event)
                callback();
        });
    }

    template <typename T>
    inline void EventHandler::OnNextEvent(const T& event, void (*callback)(const T&))
    {
        this->OnNextEvent(event, std::function<void (const T&)>(callback));
    }

    template <typename T>
    inline void EventHandler::OnNextEvent(const T& event, void (*callback)(void))
    {
        this->OnNextEvent(event, std::function<void (void)>(callback));
    }

    template <typename T, typename Predicate>
    inline void EventHandler::OnNextEvent(const T& event, Predicate&& predicate)
    {
        this->OnNextEvent(event, &Predicate::operator(), predicate);
    }

    template <typename Predicate, typename T>
    inline void EventHandler::OnNextEvent(const T& event, void (Predicate::*callback)(const T&), Predicate predicate)
    {
        this->Dispatcher<T>().OnNextEvent(event, std::function<void (const T&)>(predicate));
    }

    template <typename Predicate, typename T>
    inline void EventHandler::OnNextEvent(const T& event, void (Predicate::*callback)(void), Predicate predicate)
    {
        this->Dispatcher<T>().OnNextEvent(event, std::function<void (void)>(predicate));
    }
    
    template <typename Predicate, typename T>
    inline void EventHandler::OnNextEvent(const T& event, void (Predicate::*callback)(const T&) const, Predicate predicate)
    {
        this->Dispatcher<T>().OnNextEvent(event, std::function<void (const T&)>(predicate));
    }
    
    template <typename Predicate, typename T>
    inline void EventHandler::OnNextEvent(const T& event, void (Predicate::*callback)(void) const, Predicate predicate)
    {
        this->Dispatcher<T>().OnNextEvent(event, std::function<void (void)>(predicate));
    }

    template <typename T>
    inline void EventHandler::Emit(const T& event)
    {
        this->Dispatcher<T>().Emit(event);
    }

    template <typename T>
    inline void EventHandler::Enqueue(const T& event)
    {
        this->Dispatcher<T>().Emit(event);
    }

    template <typename T>
    inline Synergy::EventDispatcher<T>& EventHandler::Dispatcher()
    {
        auto type { m_Dispatchers.find(std::type_index(typeid(T))) };
        if (type == m_Dispatchers.end())
        {
            auto result { m_Dispatchers.try_emplace(std::type_index(typeid(T)), new EventDispatcher<T> {}) };
            
            if (result.second)
                type = result.first;
        }
        
        return *(reinterpret_cast<Synergy::EventDispatcher<T>*>(type->second.get()));
    }
}

#endif
