// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_APPLICATION_H
#define SYNERGY_APPLICATION_H

#include <unordered_map>
#include <vector>

#include "Synergy/Core.h"
#include "Synergy/Input.h"
#include "Synergy/Layer.h"
#include "Synergy/Platform.h"
#include "Synergy/Renderer/RendererAPI.h"

namespace Synergy
{
    class ArchetypeRef;
    class Scene;

    class SYNERGY_API Application
    {
    public:
        virtual ~Application() = default;
        
        bool Start();
        
        Synergy::ArchetypeRef CreateArchetype(const std::string& name = "Unnamed Entity");
        
        Synergy::Scene& CreateScene(const std::string& name);
        Synergy::Scene& GetScene(const std::string& name);
        
    protected:
        Application();
        
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        
        virtual bool OnUserCreate() { return true; }
        virtual bool OnUserUpdate(float) { return true; }
        virtual void OnUserShutdown() { };
        
    private:
        void Run();
        void Prepare();
        
        void OnEvent();
        
        void UpdateWindowSize(glm::vec2 size);
        void UpdateViewPort();
        
    private:
        bool running = false;
        
        std::vector<Layer*> layers;
        
        glm::vec2 windowSize = { 800, 600 };
        glm::vec2 viewportPosition = { 0, 0 };
        glm::vec2 viewportSize = { 0, 0 };
        
        Platform* platform;
        Renderer::RendererAPI* api;
        
        std::unordered_map<std::string, Synergy::Scene> m_Scenes;
        
        friend class Platform;
        
    public:
        static Renderer::RendererAPI* current;
    };

    Application* CreateApplication();
}

#endif
