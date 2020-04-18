// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy/Application.h"

namespace Synergy
{
    extern Platform* CreatePlatform(Application* application);
    extern RendererAPI* CreateRendererAPI();

    Application::Application(): platform(CreatePlatform(this)), api(CreateRendererAPI())
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

    void Application::PushLayer(Layer* layer)
    {
        layers.emplace(layers.begin(), layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        layers.emplace_back(layer);
        layer->OnAttach();
    }

    void Application::PopLayer(Layer* layer) {}
    void Application::PopOverlay(Layer* layer) {}

    void Application::Run()
    {
        Prepare();
        
        if (!OnUserCreate()) running = false;
        
        while (running)
        {
            Update();
        }
        
        OnUserShutdown();
        
        for (Layer* layer : layers)
        {
            layer->OnDetach();
            delete layer;
        }
    }

    void Application::Prepare()
    {
        if (!platform->CreateContext()) return;
        
        SYNERGY_ASSERT((layers.size() > 0), "Atleast one layer should be pushed to render something.");
    }

    void Application::Update()
    {
        platform->HandleEvent();
        
        if (!OnUserUpdate()) running = false;
        
        api->UpdateViewport(0, 0, 800, 600);
        api->ClearBuffer(0, 0, 0, 255, true);
        
        for (Layer* layer : layers)
            layer->OnUpdate();
        
        api->PrepareRendering();
        
        api->DisplayFrame();
    }
}
