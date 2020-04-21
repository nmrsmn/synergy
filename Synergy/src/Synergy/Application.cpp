// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Synergy/Application.h"

namespace Synergy
{
    extern Platform* CreatePlatform(Application* application);
    extern Renderer::RendererAPI* CreateRendererAPI();

    Application::Application(): platform(CreatePlatform(this)), api(Renderer::CreateRendererAPI())
    {
        vertex_shader_source = R"(
            #version 330 core
            
            layout(location = 0) in vec3 vertexPosition_modelspace;
            
            void main()
            {
                gl_Position.xyz = vertexPosition_modelspace;
                gl_Position.w = 1.0;
            }
        )";
        
        fragment_shader_source = R"(
            #version 330 core
            out vec3 color;
            void main(){
              color = vec3(1,0,0);
            }
        )";
    }
    
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
        
        /**
         * Simple test
         */
        
        vertexArray = api->CreateVertexArray();
        
        // An array of 3 vectors which represents 3 vertices
        static const GLfloat g_vertex_buffer_data[] = {
           -1.0f, -1.0f, 0.0f,
           1.0f, -1.0f, 0.0f,
           0.0f,  1.0f, 0.0f,
        };
        
        vertexBuffer = api->CreateVertexBuffer(sizeof(g_vertex_buffer_data));
        vertexBuffer->SetLayout({
            { Renderer::Shader::DataType::VEC3, "position" }
        });
        
        uint32_t indices[3] = { 0, 1, 2 };
        indexBuffer = api->CreateIndexBuffer(indices, 3);
        
        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);
        
        std::map<Renderer::Shader::Type, const std::string&> sources = {
            { Renderer::Shader::Type::VERTEX, vertex_shader_source },
            { Renderer::Shader::Type::FRAGMENT, fragment_shader_source }
        };
        
        shader = api->CreateShader("Test", sources);
                
        if (!OnUserCreate()) running = false;
        
        while (running)
        {
            //Update();
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            shader->Bind();
  
            vertexBuffer->SetData(g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
            
            Renderer::RenderCommand::DrawIndexed(vertexArray);
            
            api->DisplayFrame();
            platform->UpdateWindow();
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
        platform->UpdateKeyStates();
        
        if (!OnUserUpdate()) running = false;
        
        api->UpdateViewport({ 0, 0 }, { 800, 600 });
        api->ClearBuffer({ 0, 0, 0, 1 }, true);
        api->PrepareRendering();
        
        for (Layer* layer : layers)
            layer->OnUpdate();
        
        api->DisplayFrame();
        platform->UpdateWindow();
    }
}
