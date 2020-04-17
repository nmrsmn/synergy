// Created by Niels Marsman on 15-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy/Platform/GLFW.h"

namespace Synergy::Platforms
{
    bool GLFW::Init()
    {
        glfwInit();
        
        return true;
    }

    bool GLFW::Start()
    {   
        return true;
    }

    bool GLFW::Shutdown()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        
        return true;
    }

    bool GLFW::CreateContext()
    {
        glfwMakeContextCurrent(window);
        
        return true;
    }

    bool GLFW::CreateWindow(int x, int y, int width, int height, bool fullscreen)
    {
        window = glfwCreateWindow(width, height, "Synergy", nullptr, nullptr);
        
        return true;
    }

    bool GLFW::UpdateWindow()
    {
        return true;
    }

    bool GLFW::StartEventLoop()
    {
        return true;
    }

    bool GLFW::HandleEvent()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        return true;
    }
}
