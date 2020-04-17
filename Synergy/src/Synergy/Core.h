// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include <memory>

#include "Synergy/Logger.h"

#ifndef SYNERGY_CORE_H
#define SYNERGY_CORE_H

// Platform
#if defined(_WIN32) || defined(_WIN64)
    #define SYNERGY_PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "iOS simulator not supported."
    #elif TARGET_OS_IPHONE
        #define SYNERGY_PLATFORM_IOS
        #error "iOS is not supported yet."
    #elif TARGET_OS_MAC
        #define SYNERGY_PLATFORM_MACOS
    #else
        #error "Uknown Apple platform."
    #endif
#elif defined(__ANDROID__)
    #define SYNERGY_PLATFORM_ANDROID
    #error "Android is not supported yet."
#elif defined(__linux__)
    #define SYNERGY_PLATFORM_LINUX
#else
    #error "Unknown platform."
#endif

// Platform specific settings and defines
#if defined SYNERGY_PLATFORM_WINDOWS
    #define SYNERGY_DEBUGBREAK { __debugbreak(); }
    #if defined SYNERGY_SHARED_LIBRARY
        #define SYNERGY_API __declspec(dllexport)
    #elif defined SYNERGY_STATIC_LIBRARY
        #define SYNERGY_API
    #else
        #define SYNERGY_API __declspec(dllimport)
    #endif
#elif defined SYNERGY_PLATFORM_LINUX
    #include <signal.h>
    #define SYNERGY_DEBUGBREAK { raise(SIGTRAP); }
    #ifdef SYNERGY_SHARED_LIBRARY
        #define SYNERGY_API __attribute__((visibility("default")))
    #else
        #define SYNERGY_API
    #endif
#elif defined SYNERGY_PLATFORM_MACOS
    #define SYNERGY_DEBUGBREAK { __builtin_trap(); }
    #ifdef SYNERGY_SHARED_LIBRARY
        #define SYNERGY_API __attribute__((visibility("default")))
    #else
        #define SYNERGY_API
    #endif
#else
    #error "Unsupported platform"
#endif

// Debug and release settings and defines
#ifndef SPDLOG_ACTIVE_LEVEL
    #if defined SYNERGY_DEBUG
        #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
        #define SYNERGY_ENABLE_ASSERTS
    #elif defined SYNERGY_RELEASE
        #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
    #else
        #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
    #endif
#endif

// Asserts
#ifdef SYNERGY_ENABLE_ASSERTS
    #define SYNERGY_ASSERT_WITH_MESSAGE(file, line, expression, ...) if (!expression) { SYNERGY_LOG_ERROR("Assertion Failed: {0} @ {1}:{2}", __VA_ARGS__, file, line); SYNERGY_DEBUGBREAK }
    #define SYNERGY_ASSERT_WITHOUT_MESSAGE(file, line, expression) if (!expression) { SYNERGY_LOG_ERROR("Assertion Failed @ {0}:{1}", file, line); SYNERGY_DEBUGBREAK }
    #define SYNERGY_RESOLVE_ASSERTION(_1, _2, WHICH_, ...) WHICH_
    #define SYNERGY_CREATE_ASSERTION(...) SYNERGY_RESOLVE_ASSERTION(__VA_ARGS__, SYNERGY_ASSERT_WITH_MESSAGE, SYNERGY_ASSERT_WITHOUT_MESSAGE)

    #define SYNERGY_ASSERT(...) SYNERGY_CREATE_ASSERTION(__VA_ARGS__)(__FILE__, __LINE__, __VA_ARGS__)
#else
    #define SYNERGY_ASSERT(...)
#endif

// Other
namespace Synergy
{
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#endif
