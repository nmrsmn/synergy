// Created by Niels Marsman on 19-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_RENDERER2D_H
#define SYNERGY_RENDERER_RENDERER2D_H

#include "Synergy/Core.h"
#include "Synergy/Renderer/Renderable.h"
#include "Synergy/Renderer/RendererAPI.h"
#include "Synergy/Renderer/Renderer.h"

namespace Synergy::Renderer
{
    class SYNERGY_API Renderer2D: public Renderer<Renderer2D, Renderable2D>
    {
    private:
        static Renderer2D& Instance();
        
    public:
        Renderer2D(const Renderer2D&) = delete;
        Renderer2D& operator=(const Renderer2D&) = delete;
        
        static void BeginScene();
        static void EndScene();
        
    private:
        Renderer2D() {}
        
        void Initialize();
        
        static void Initialize(RendererAPI* api);
        
        static void Flush();
        static void FlushAndReset();
        
        static void SubmitRenderable(Renderable2D renderable);
        
    private:
        RendererAPI* api;
        
        friend class Renderer<Renderer2D, Renderable2D>;
        friend class RendererAPI;
        
        std::string vertex_shader_source = R"(
            #version 330 core

            layout(location = 0) in vec3 position;
            layout(location = 1) in vec4 color;

            void main()
            {
                gl_Position = vec4(position, 1.0);
            }
        )";

        std::string fragment_shader_source = R"(
            #version 330 core
            out vec3 color;
            void main(){
                color = vec3(1,0,0);
            }
        )";
    };
}

#endif
