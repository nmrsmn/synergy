// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy.h"

class Sandbox: public Synergy::Application
{
public:
	explicit Sandbox(): controller(800.0f / 600.0f), Synergy::Application() {}
    
    virtual bool OnUserCreate() override
    {
        texture = Synergy::Renderer::Texture::Load("assets/textures/checkerboard.png", Synergy::Renderer::Texture::Parameters(Synergy::Renderer::Texture::Filter::NEAREST, Synergy::Renderer::Texture::Wrap::REPEAT));
        button = Synergy::Renderer::Texture::Load("assets/textures/red_button00.png");
        
        atlas = Synergy::Renderer::TextureAtlas::Load("assets/textures/RPGpack_sheet.png", 13, 20);
        
        return true;
    }
    
    virtual bool OnUserUpdate(float deltatime) override
    {
        controller.Update(deltatime);

        Synergy::Renderer::Renderer2D::BeginScene(controller.GetCamera());
        Synergy::Renderer::Renderer2D::Submit(Synergy::Quad { {  0,  0, 1 }, { 1.0, 1.0 }, { 1, 0, 0, 1 } });
        Synergy::Renderer::Renderer2D::Submit(Synergy::Quad { { -.75f, -.75f, 1 }, { 1.0, 1.0 }, { 0, 1, 0, 1 } });
        Synergy::Renderer::Renderer2D::Submit(Synergy::Quad { { .75f, .75f, 1 }, { 1.0, 1.0 }, texture, { .2, .4, .8, 1 } });
        Synergy::Renderer::Renderer2D::EndScene();

        Synergy::Renderer::Renderer2D::BeginScene(controller.GetCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f)
        {
            for (float x = -5.0f; x < 5.0f; x += 0.5f)
            {
                glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
                Synergy::Renderer::Renderer2D::Submit(Synergy::Quad { { x, y }, { 0.48f, 0.48f }, color });
            }
        }
        Synergy::Renderer::Renderer2D::EndScene();
        
        float ratio = 45.f / 190.f;
        
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0, 0, 0.1 }, { 4, 3 }, { 0, 0, 0, .8 } });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0, .8, 0 }, { 1, 1 * ratio }, button });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0, .5, 0 }, { 1, 1 * ratio }, button });

        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0, 0, 0 }, { .5, .5 }, atlas->GetTexture(0, 0) });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0, -.5, 0 }, { .5, .5 }, atlas->GetTexture(1, 0) });
        
        return true;
    }
    
	virtual ~Sandbox() = default;
    
private:
    Synergy::Ref<Synergy::Renderer::TextureAtlas> atlas;
    Synergy::Ref<Synergy::Renderer::Texture> button;
    Synergy::Ref<Synergy::Renderer::Texture> texture;
    Synergy::CameraController controller;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
