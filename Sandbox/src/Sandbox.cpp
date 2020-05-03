// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy.h"

class Sandbox: public Synergy::Application
{
public:
	explicit Sandbox(): controller(800.0f / 600.0f), Synergy::Application() {}
    
    virtual bool OnUserCreate() override
    {
        button = Synergy::Renderer::Texture::Load("assets/textures/red_button00.png");
        font = Synergy::Fonts::Load("assets/fonts/Kenney Future Narrow.ttf");
        
        return true;
    }
    
    virtual bool OnUserUpdate(float deltatime) override
    {
        float ratio = 45.f / 190.f;
        
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0, 0, 0.1 }, { 4, 3 }, { 0, 0, 0, .8 } });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0, .5, 0 }, { 1, 1 * ratio }, button });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0, .2, 0 }, { 1, 1 * ratio }, button });
        
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Text { "Hello world!", { 0, .8, 0 }, { 1, .8, 1, 1 } });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Text { "Hello world!", { 0, .8, 0 }, { 1, .8, 1, 1 } });
        
        return true;
    }
    
	virtual ~Sandbox() = default;
    
private:
    Synergy::Ref<Synergy::Font> font;
    
    Synergy::Ref<Synergy::Renderer::Texture> button;
    Synergy::CameraController controller;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
