// Created by Niels Marsman on 01-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_CANVAS_RENDERER_H
#define SYNERGY_RENDERER_CANVAS_RENDERER_H

#include "Synergy/Core.h"
#include "Synergy/Camera.h"
#include "Synergy/Renderer/Renderable.h"
#include "Synergy/Renderer/RendererAPI.h"
#include "Synergy/Renderer/Renderer.h"

namespace Synergy::Renderer
{
    class SYNERGY_API CanvasRenderer: public Renderer<CanvasRenderer, Renderable2D>
    {
    private:
        static CanvasRenderer& Instance();
        
    public:
        CanvasRenderer(const CanvasRenderer&) = delete;
        CanvasRenderer& operator=(const CanvasRenderer&) = delete;
        
    private:
        CanvasRenderer() {}
        
        void Initialize();
        
        static void Initialize(RendererAPI* api);
        
        static void SubmitRenderable(Renderable2D renderable);
        
    private:
        RendererAPI* api;
        
        friend class Renderer<CanvasRenderer, Renderable2D>;
        friend class RendererAPI;
        
        std::string vertex_shader_source = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;
            layout(location = 2) in vec2 a_uv;
        
            out vec4 v_color;
            out vec2 v_uv;
        
            uniform mat4 u_projection_view;

            void main()
            {
                v_color = a_color;
                v_uv = a_uv;
                gl_Position = vec4(a_position, 1.0);
            }
        )";

        std::string fragment_shader_source = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec4 v_color;
            in vec2 v_uv;

            uniform sampler2D u_texture;
            
            void main(){
                color = texture(u_texture, v_uv) * v_color;
            }
        )";
    };
}

#endif
