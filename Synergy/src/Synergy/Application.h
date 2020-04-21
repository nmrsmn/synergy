// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_APPLICATION_H
#define SYNERGY_APPLICATION_H

#include <vector>

#include "Synergy/Core.h"
#include "Synergy/Input.h"
#include "Synergy/Layer.h"
#include "Synergy/Platform.h"
#include "Synergy/Renderer/RendererAPI.h"

#include "Synergy/Renderer/Shader.h"
#include "Synergy/Renderer/IndexBuffer.h"
#include "Synergy/Renderer/VertexArray.h"
#include "Synergy/Renderer/VertexArray.h"

namespace Synergy
{
    class SYNERGY_API Application
    {
    public:
        virtual ~Application() = default;
        
        bool Start();
        
    protected:
        Application();
        
        Input::State GetState(Input::Key key) { return {}; }
        
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
        
    private:
        bool running = false;
        
        std::vector<Layer*> layers;
        
        Platform* platform;
        Renderer::RendererAPI* api;
        
        friend class Platform;
        
        /* Test */
        std::string vertex_shader_source;
        std::string fragment_shader_source;
        
        Ref<Renderer::Shader> shader;
        Ref<Renderer::VertexArray> vertexArray;
        Ref<Renderer::VertexBuffer> vertexBuffer;
        Ref<Renderer::IndexBuffer> indexBuffer;
    };

    Application* CreateApplication();
}

#endif
