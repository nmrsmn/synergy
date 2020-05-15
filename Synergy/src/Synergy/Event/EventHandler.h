// Created by Niels Marsman on 15-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_EVENT_HANDLER_H
#define SYNERGY_EVENT_HANDLER_H

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
        
        // Any events
        
        template <typename T>
        inline void OnEvent(Synergy::EventCallback<T> callback)
        {
            this->Dispatcher<T>().OnEvent(callback);
        }
        
        template <typename T>
        inline void OnEvent(void (*callback) (const T&))
        {
            this->OnEvent(std::function<bool (const T&)>(callback));
        }
        
        template<typename Predicate>
        inline void OnEvent(Predicate&& predicate)
        {
            this->OnEvent(&Predicate::operator(), predicate);
        }
        
        template <typename Predicate, typename T>
        inline void OnEvent(bool (Predicate::*callback) (const T&), Predicate predicate)
        {
            this->Dispatcher<T>().OnEvent(std::function<bool (const T&)>(predicate));
        }
        
        template <typename Predicate, typename T>
        inline void OnEvent(bool (Predicate::*callback) (const T&) const, Predicate predicate)
        {
            this->Dispatcher<T>().OnEvent(std::function<bool (const T&)>(predicate));
        }
        
        // Specific events
        
        template <typename T>
        inline void OnEvent(const T& event, Synergy::EventCallback<T> callback)
        {
            this->OnEvent([callback, event] (const T& current)
            {
                if (current == event)
                    return callback(event);
                
                return false;
            });
        }
        
        template <typename T>
        inline void OnEvent(const T& event, Synergy::VoidCallback callback)
        {
            this->OnEvent([callback, event] (const T& current)
            {
                if (current == event)
                    return callback();
                
                return false;
            });
        }
        
        template <typename T>
        inline void OnEvent(const T& event, bool (*callback) (const T&))
        {
            this->OnEvent(event, std::function<bool (const T&)>(callback));
        }
        
        template <typename T>
        inline void OnEvent(const T& event, bool (*callback) (void))
        {
            this->OnEvent(event, std::function<bool (void)>(callback));
        }
        
        template <typename Predicate, typename T>
        inline void OnEvent(const T& event, Predicate&& predicate)
        {
            this->OnEvent(event, &Predicate::operator(), predicate);
        }
        
        template <typename Predicate, typename T>
        inline void OnEvent(const T& event, bool (Predicate::*callback)(const T&), Predicate predicate)
        {
            this->Dispatcher<T>().OnEvent([predicate, callback, event] (const T& current)
            {
                if (current == event)
                    return (predicate->*callback(event));
                    
                return false;
            });
        }
        
        template <typename Predicate, typename T>
        inline void OnEvent(const T& event, bool (Predicate::*callback)(void), Predicate predicate)
        {
            this->Dispatcher<T>().OnEvent([predicate, callback, event] (const T& current)
            {
                if (current == event)
                    return (predicate->*callback());
                    
                return false;
            });
        }
        
        template <typename Predicate, typename T>
        inline void OnEvent(const T& event, bool (Predicate::*callback)(const T&) const, Predicate predicate)
        {
            this->Dispatcher<T>().OnEvent([predicate, callback, event] (const T& current)
            {
                if (current == event)
                    return (predicate->*callback(event));
                    
                return false;
            });
        }
        
        template <typename Predicate, typename T>
        inline void OnEvent(const T& event, bool (Predicate::*callback)(void) const, Predicate predicate)
        {
            this->Dispatcher<T>().OnEvent([predicate, callback, event] (const T& current)
            {
                if (current == event)
                    return (predicate->*callback());
                    
                return false;
            });
        }
        
        // Next event
        
        template <typename T>
        inline void OnNextEvent(Synergy::EventCallback<T> callback)
        {
            this->Dispatcher<T>().OnNextEvent(callback);
        }
        
        template <typename T>
        inline void OnNextEvent(bool (*callback)(const T&))
        {
            this->OnNextEvent(std::function<bool (const T&)>(callback));
        }
        
        template <typename Predicate>
        inline void OnNextEvent(Predicate&& predicate)
        {
            this->OnNextEvent(&Predicate::operator(), predicate);
        }
        
        template <typename Predicate, typename T>
        inline void OnNextEvent(bool (Predicate::*callback)(const T&), Predicate predicate)
        {
            this->Dispatcher<T>().OnNextEvent(std::function<bool (const T&)>(predicate));
        }
        
        template <typename Predicate, typename T>
        inline void OnNextEvent(bool (Predicate::*callback)(const T&) const, Predicate predicate)
        {
            this->Dispatcher<T>().OnNextEvent(std::function<bool (const T&)>(predicate));
        }
        
        // Specific events
        
        template <typename T>
        inline void OnNextEvent(const T& event, Synergy::EventCallback<T> callback)
        {
            this->OnNextEvent([callback, event] (const T& current)
            {
                if (current == event)
                    return callback(event);
                
                return false;
            });
        }
        
        template <typename T>
        inline void OnNextEvent(const T& event, Synergy::VoidCallback callback)
        {
            this->OnNextEvent([callback, event] (const T& current)
            {
                if (current == event)
                    return callback();
                
                return false;
            });
        }
        
        template <typename T>
        inline void OnNextEvent(const T& event, bool (*callback)(const T&))
        {
            this->OnNextEvent(event, std::function<bool (const T&)>(callback));
        }
        
        template <typename T>
        inline void OnNextEvent(const T& event, bool (*callback)(void))
        {
            this->OnNextEvent(event, std::function<bool (void)>(callback));
        }
        
        template <typename Predicate, typename T>
        inline void OnNextEvent(const T& event, Predicate&& predicate)
        {
            this->OnNextEvent(event, &Predicate::operator(), predicate);
        }
        
        template <typename Predicate, typename T>
        inline void OnNextEvent(const T& event, bool (Predicate::*callback)(const T&), Predicate predicate)
        {
            this->Dispatcher<T>().OnEvent([predicate, callback, event] (const T& current)
            {
                if (current == event)
                    return (predicate->*callback(event));
                    
                return false;
            });
        }
        
        template <typename Predicate, typename T>
        inline void OnNextEvent(const T& event, bool (Predicate::*callback)(void), Predicate predicate)
        {
            this->Dispatcher<T>().OnEvent([predicate, callback, event] (const T& current)
            {
                if (current == event)
                    return (predicate->*callback());
                    
                return false;
            });
        }
        
        template <typename Predicate, typename T>
        inline void OnNextEvent(const T& event, bool (Predicate::*callback)(const T&) const, Predicate predicate)
        {
            this->Dispatcher<T>().OnEvent([predicate, callback, event] (const T& current)
            {
                if (current == event)
                    return (predicate->*callback(event));
                    
                return false;
            });
        }
        
        template <typename Predicate, typename T>
        inline void OnNextEvent(const T& event, bool (Predicate::*callback)(void) const, Predicate predicate)
        {
            this->Dispatcher<T>().OnEvent([predicate, callback, event] (const T& current)
            {
                if (current == event)
                    return (predicate->*callback());
                    
                return false;
            });
        }
        
        template <typename T>
        inline void Emit(const T& event)
        {
            this->Dispatcher<T>().Emit(event);
        }
        
        template <typename T>
        inline void Enqueue(const T& event)
        {
            this->Dispatcher<T>().Emit(event);
        }
        
    private:
        template <typename T>
        Synergy::EventDispatcher<T>& Dispatcher()
        {
            auto type { m_Dispatchers.find(std::type_index(typeid(T))) };
            if (type == m_Dispatchers.end())
            {
                auto result { m_Dispatchers.try_emplace(std::type_index(typeid(T)), new EventDispatcher<T> {}) };
                
                if (result.second)
                    type = result.first;
            }
            
            return *(reinterpret_cast<Synergy::EventDispatcher<T>*>(type->second.get()));
        };
        
    private:
        std::unordered_map<std::type_index, Synergy::Scope<Synergy::EventDispatcherBase>> m_Dispatchers;
    };
}

#endif
