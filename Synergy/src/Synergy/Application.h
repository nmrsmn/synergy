// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_APPLICATION_H
#define SYNERGY_APPLICATION_H

#include "Synergy/Core.h"
#include "Synergy/Platform.h"
#include "Synergy/RendererAPI.h"

namespace Synergy
{
    class SYNERGY_API Application
    {
    public:
        virtual ~Application() = default;
        
        bool Start();
        
        virtual bool OnUserCreate() { return true; }
        virtual bool OnUserUpdate() { return true; }
        virtual void OnUserShutdown() { };
        
    protected:
        Application();
        
    private:
        void Run();
        void Prepare();
        void Update();
        
    private:
        static std::atomic<bool> running;
        Platform* platform;
        RendererAPI* api;
    };

    Application* CreateApplication();
}

#endif
