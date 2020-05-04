// Created by Niels Marsman on 19-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_RENDERER2D_H
#define SYNERGY_RENDERER_RENDERER2D_H

#include "Synergy/Core.h"
#include "Synergy/Camera.h"
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
        
        static void BeginScene(const Synergy::Camera::Camera& camera);
        static void EndScene();
        
    private:
        Renderer2D() {}
        
        void Initialize();
        
        static void Initialize(RendererAPI* api);
        
        static void Flush();
        static void FlushAndReset();
        
        static void SubmitRenderable(Renderable2D renderable);
        static void SubmitText(Text text);
        
    private:
        RendererAPI* api;
        
        friend class Renderer<Renderer2D, Renderable2D>;
        friend class RendererAPI;
        
        std::string vertex_shader_source = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;
            layout(location = 2) in vec2 a_uv;
            layout(location = 3) in float a_texture_index;
        
            out vec4 v_color;
            out vec2 v_uv;
            out float v_texture_index;
        
            uniform mat4 u_view_projection;

            void main()
            {
                v_color = a_color;
                v_uv = a_uv;
                v_texture_index = a_texture_index;
                gl_Position = u_view_projection * vec4(a_position, 1.0);
            }
        )";

        std::string fragment_shader_source = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec4 v_color;
            in vec2 v_uv;
            in float v_texture_index;

            uniform sampler2D u_textures[16];
            
            void main(){
                color = texture(u_textures[int(v_texture_index)], v_uv) * v_color;
            }
        )";
    };
}

#endif
