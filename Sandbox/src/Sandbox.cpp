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
        button = Synergy::Texture::Load("assets/textures/red_button00.png");
        
        narrow = Synergy::Fonts::Load("assets/fonts/Kenney Future Narrow.ttf", 48);
        blocks = Synergy::Fonts::Load("assets/fonts/Kenney Blocks.ttf", 10);
        
        Synergy::Texture::Parameters parameters;
        parameters.wrap = Synergy::Texture::Parameters::Wrap(Synergy::Texture::Wrap::REPEAT);
        
        atlas = Synergy::TextureAtlas::Load("assets/textures/RPGpack_sheet.png", { 20, 13 }, parameters);
        //barrel = Synergy::TextureAtlas::Texture::Load(atlas, { 1, 1 });
        //stairs = Synergy::TextureAtlas::Texture::Load(atlas, { 2, 2 });
        tree = Synergy::TextureAtlas::Texture::Load(atlas, { 0, 11 }, { 1, 2 });
        
        return true;
    }
    
    virtual bool OnUserUpdate(float deltatime) override
    {
        float ratio = 45.f / 190.f;
        
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.5, 0.1 }, { 1.0, 1.0 }, { 1, 1, 1, .1 } });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.2, 0.5 }, { 0.5, 0.5 * ratio }, button });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.6, 0.5 }, { .1, .2 }, tree });
        
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Text { "Hello world!", narrow, { 10.0, 560, 0.5 }, { 1, 1, 1, 1 } });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Text { "Copyright (c) 2020, all rights reserved Niels Marsman.", blocks, { 10, 10, 0 }, { 1, 1, 1, 1 } });
        
        return true;
    }
    
	virtual ~Sandbox() = default;
    
private:
    Synergy::Ref<Synergy::TextureAtlas> atlas;
    Synergy::Ref<Synergy::TextureAtlas::Texture> tree;
    Synergy::Ref<Synergy::TextureAtlas::Texture> barrel;
    Synergy::Ref<Synergy::TextureAtlas::Texture> stairs;
    
    Synergy::Ref<Synergy::Texture> button;
    
    Synergy::Ref<Synergy::Font> narrow;
    Synergy::Ref<Synergy::Font> blocks;
    
    Synergy::CameraController controller;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
