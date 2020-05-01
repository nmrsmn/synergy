// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include <spdlog/sinks/stdout_color_sinks.h>

#include "Synergy/Logger.h"

namespace Synergy
{
    bool Logger::initialized = false;

    Ref<spdlog::logger> Logger::clientLogger;
    Ref<spdlog::logger> Logger::engineLogger;

    void Logger::Init()
    {
        if (initialized)
            return;
        
        spdlog::set_pattern("%^[%T.%e] %n: %v%$");
        
        clientLogger = spdlog::stdout_color_mt("Application");
        clientLogger->set_level(spdlog::level::trace);
        
        engineLogger = spdlog::stdout_color_mt("SynergyEngine");
        engineLogger->set_level(spdlog::level::trace);
        
        initialized = true;
    }
}
