// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Synergy/Application.h"

namespace Synergy
{
    extern Platform* CreatePlatform(Application* application);
    extern Renderer::RendererAPI* CreateRendererAPI();

    Application::Application(): platform(CreatePlatform(this)), api(Renderer::CreateRendererAPI()) {}
    
    bool Application::Start()
    {
        if (!platform->Init()) return false;
        if (!platform->CreateWindow({ 0, 0 }, { 800, 600 }, false)) return false;
        
        platform->StartEventLoop();
        
        running = true;
        Run();
        
        if (!platform->Shutdown()) return false;
        return true;
    }

    void Application::PushLayer(Layer* layer)
    {
        layers.emplace(layers.begin(), layer);
        layer->api = api;
    }

    void Application::PushOverlay(Layer* layer)
    {
        layers.emplace_back(layer);
        layer->api = api;
    }

    void Application::PopLayer(Layer* layer) {}
    void Application::PopOverlay(Layer* layer) {}

    void Application::Run()
    {
        Prepare();
        
        std::chrono::time_point<std::chrono::system_clock> point1, point2;
        point1 = std::chrono::system_clock::now();
        point2 = std::chrono::system_clock::now();
        
        float frameTimer = 0.f;
        uint32_t frameCount = 0;
                
        if (!OnUserCreate()) running = false;
        
        for (Layer* layer : layers)
            layer->OnAttach();
        
        while (running)
        {
            point2 = std::chrono::system_clock::now();
            std::chrono::duration<float> difference = point2 - point1;
            point1 = point2;
            
            float deltaTime = difference.count();
            
            platform->HandleEvent();
            platform->UpdateKeyStates();
            
            if (!OnUserUpdate(deltaTime)) running = false;
            
            api->UpdateViewport({ 0, 0 }, { 800, 600 });
            api->ClearBuffer({ 0, 0, 0, 1 }, true);
            
            for (Layer* layer : layers)
                layer->OnUpdate(deltaTime);
            
            api->DisplayFrame();
            platform->UpdateWindow();
            
            frameTimer += deltaTime;
            frameCount++;
            
            if (frameTimer >= 1.0f)
            {
                frameTimer -= 1.0f;
                std::string title = "Synergy - Game Engine - FPS: " + std::to_string(frameCount);
                platform->UpdateWindowTitle(title.c_str());
                frameCount = 0;
            }
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
        
        api->PrepareRendering();
        
        SYNERGY_ASSERT((layers.size() > 0), "Atleast one layer should be pushed to render something.");
    }
}
