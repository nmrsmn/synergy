// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include <iostream>

#include "Synergy.h"

class Sandbox: public Synergy::Application
{
public:
	explicit Sandbox(): controller(800.0f / 600.0f), Synergy::Application() {}
    
    virtual bool OnUserCreate() override
    {
        atlas = Synergy::Renderer::TextureAtlas::Load("assets/textures/RPGpack_sheet.png", 13, 20);
        
        button = Synergy::Renderer::Texture::Load("assets/textures/red_button00.png");
        
        narrow = Synergy::Fonts::Load("assets/fonts/Kenney Future Narrow.ttf", 48);
        blocks = Synergy::Fonts::Load("assets/fonts/Kenney Blocks.ttf", 10);
        
        std::string batch_vertex_shader_source = R"(
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

        std::string batch_fragment_shader_source = R"(
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
        
        std::string canvas_vertex_shader_source = R"(
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
                gl_Position = u_projection_view * vec4(a_position, 1.0);
            }
        )";

        std::string canvas_fragment_shader_source = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec4 v_color;
            in vec2 v_uv;

            uniform sampler2D u_texture;
            
            void main()
            {
                color = texture(u_texture, v_uv) * v_color;
            }
        )";
        
        std::string text_vertex_shader_source = R"(
            #version 330 core

            layout(location = 0) in vec4 a_vertex;
            
            out vec2 v_uv;
        
            uniform mat4 u_projection_view;

            void main()
            {
                gl_Position = u_projection_view * vec4(a_vertex.xy, 0.0, 1.0);
                v_uv = a_vertex.zw;
            }
        )";

        std::string text_fragment_shader_source = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec2 v_uv;

            uniform sampler2D u_texture;
            uniform vec4 u_text_color;
            
            void main()
            {
                vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, v_uv).r);
                color = u_text_color * sampled;
            }
        )";
        
        auto a = Synergy::ResourcePack::Create();
        a->Add("vertex", batch_vertex_shader_source);
        a->Add("fragment", batch_fragment_shader_source);
        a->Save("assets/shaders/BatchRenderer.shader");
        
        auto b = Synergy::ResourcePack::Create();
        b->Add("vertex", canvas_vertex_shader_source);
        b->Add("fragment", canvas_fragment_shader_source);
        b->Save("assets/shaders/CanvasRenderer.shader");
        
        auto c = Synergy::ResourcePack::Create();
        c->Add("vertex", text_vertex_shader_source);
        c->Add("fragment", text_fragment_shader_source);
        c->Save("assets/shaders/TextRenderer.shader");
        
        auto d = Synergy::ResourcePack::Create();
        d->Add("assets/shaders/BatchRenderer.shader");
        d->Add("assets/shaders/CanvasRenderer.shader");
        d->Add("assets/shaders/TextRenderer.shader");
        d->Save("assets/shaders/synergy.shaders");
        
        auto e = Synergy::ResourcePack::Load("assets/shaders/synergy.shaders");
        auto f = e->Parse("assets/shaders/TextRenderer.shader");
        
        f->Read("fragment", [](Synergy::ResourcePack::Buffer buffer) -> bool
        {
            for (std::vector<char>::const_iterator item = buffer.memory.begin(); item != buffer.memory.end(); ++item)
                std::cout << *item;
            
            std::cout << std::endl << std::endl << std::endl;
            
            return true;
        });
        
        return true;
    }
    
    virtual bool OnUserUpdate(float deltatime) override
    {
        float ratio = 45.f / 190.f;
        
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.5, 0.1 }, { 1.0, 1.0 }, { 1, 1, 1, .1 } });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.2, 0.5 }, { 0.5, 0.5 * ratio }, button });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.6, 0.5 }, { 0.1, 0.1 }, atlas->GetTexture(11, 1) });
        
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Text { "Hello world!", narrow, { 10.0, 560, 0.5 }, { 1, 1, 1, 1 } });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Text { "Copyright (c) 2020, all rights reserved Niels Marsman.", blocks, { 10, 10, 0 }, { 1, 1, 1, 1 } });
        
        return true;
    }
    
	virtual ~Sandbox() = default;
    
private:
    Synergy::Ref<Synergy::Renderer::TextureAtlas> atlas;
    
    Synergy::Ref<Synergy::Font> narrow;
    Synergy::Ref<Synergy::Font> blocks;
    
    Synergy::Ref<Synergy::Renderer::Texture> button;
    Synergy::CameraController controller;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
