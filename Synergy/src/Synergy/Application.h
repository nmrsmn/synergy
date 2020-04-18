// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_APPLICATION_H
#define SYNERGY_APPLICATION_H

#include <vector>

#include "Synergy/Core.h"
#include "Synergy/Layer.h"
#include "Synergy/Platform.h"
#include "Synergy/RendererAPI.h"

namespace Synergy
{
    class SYNERGY_API Application
    {
    public:
        virtual ~Application() = default;
        
        bool Start();
        
    protected:
        Application();
        
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* layer);
        
        virtual bool OnUserCreate() { return true; }
        virtual bool OnUserUpdate() { return true; }
        virtual void OnUserShutdown() { };
        
    private:
        void Run();
        void Prepare();
        void Update();
        
        void OnEvent();
        
        friend class Platform;
        
    private:
        bool running = false;
        
        std::vector<Layer*> layers;
        
        Platform* platform;
        RendererAPI* api;
    };

    Application* CreateApplication();
}

#endif
