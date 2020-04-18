// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy/Application.h"

namespace Synergy
{
    extern Platform* CreatePlatform();
    extern RendererAPI* CreateRendererAPI();

    std::atomic<bool> Application::running = false;

    Application::Application(): platform(CreatePlatform()), api(CreateRendererAPI())
    {
        
    }
    
    bool Application::Start()
    {
        if (!platform->Init()) return false;
        if (!platform->CreateWindow(0, 0, 800, 600, false)) return false;
        
        platform->StartEventLoop();
        
        running = true;
        Run();
        
        if (!platform->Shutdown()) return false;
        return true;
    }

    void Application::Run()
    {
        Prepare();
        
        if (!OnUserCreate()) running = false;
        
        while (running)
        {
            Update();
        }
        
        OnUserShutdown();
    }

    void Application::Prepare()
    {
        if (!platform->CreateContext()) return;
    }

    void Application::Update()
    {
        platform->HandleEvent();
        
        if (!OnUserUpdate()) running = false;
    }
}
