// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_LOGGER_H
#define SYNERGY_LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Synergy/Core.h"

namespace Synergy
{
    class SYNERGY_API Logger
    {
    public:
        static void Init();
        
        inline static Ref<spdlog::logger>& Client() { return clientLogger; }
        inline static Ref<spdlog::logger>& Engine() { return engineLogger; }
        
    private:
        static bool initialized;
        
        static Ref<spdlog::logger> clientLogger;
        static Ref<spdlog::logger> engineLogger;
    };
}

#define SYNERGY_LOG_TRACE(...)    SPDLOG_LOGGER_TRACE(::Synergy::Logger::Engine(), __VA_ARGS__)
#define SYNERGY_LOG_INFO(...)     SPDLOG_LOGGER_INFO(::Synergy::Logger::Engine(), __VA_ARGS__)
#define SYNERGY_LOG_WARN(...)     SPDLOG_LOGGER_WARN(::Synergy::Logger::Engine(), __VA_ARGS__)
#define SYNERGY_LOG_ERROR(...)    SPDLOG_LOGGER_ERROR(::Synergy::Logger::Engine(), __VA_ARGS__)
#define SYNERGY_LOG_FATAL(...)    SPDLOG_LOGGER_CRITICAL(::Synergy::Logger::Engine(), __VA_ARGS__)

#define LOG_TRACE(...)    SPDLOG_LOGGER_TRACE(::Synergy::Logger::Client(), __VA_ARGS__)
#define LOG_INFO(...)     SPDLOG_LOGGER_INFO(::Synergy::Logger::Client(), __VA_ARGS__)
#define LOG_WARN(...)     SPDLOG_LOGGER_WARN(::Synergy::Logger::Client(), __VA_ARGS__)
#define LOG_ERROR(...)    SPDLOG_LOGGER_ERROR(::Synergy::Logger::Client(), __VA_ARGS__)
#define LOG_FATAL(...)    SPDLOG_LOGGER_CRITICAL(::Synergy::Logger::Client(), __VA_ARGS__)

#endif
