// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

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
