// Created by Niels Marsman on 15-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include <glad/glad.h>

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
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        SYNERGY_ASSERT(status, "Failed to initialize glad!");
        
        return true;
    }

    bool GLFW::CreateWindow(int x, int y, int width, int height, bool fullscreen)
    {
        window = glfwCreateWindow(width, height, "Synergy", nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        
        glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
        {
            Platform* platform = (Platform*) glfwGetWindowUserPointer(window);
            platform->CloseWindow();
        });
        
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
