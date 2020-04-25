// Created by Niels Marsman on 15-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_PLATFORM_GLFW_H
#define SYNERGY_PLATFORM_GLFW_H

#include <GLFW/glfw3.h>

#include "Synergy/Application.h"
#include "Synergy/Core.h"
#include "Synergy/Platform.h"

namespace Synergy::Platforms
{
    class SYNERGY_API GLFW: public Synergy::Platform
    {
    public:
        explicit GLFW(Application* application): Synergy::Platform(application) {}
        
        virtual bool Init() override;
        virtual bool Start() override;
        virtual bool Shutdown() override;
        
        virtual bool CreateContext() override;
        virtual bool CreateWindow(glm::vec2 offset, glm::vec2 size, bool fullscreen) override;
        virtual bool UpdateWindow() override;
        virtual void UpdateWindowTitle(const char* title) override;
        
        virtual bool StartEventLoop() override;
        virtual bool HandleEvent() override;
        
    private:
        GLFWwindow* window;
    };
}

#endif
