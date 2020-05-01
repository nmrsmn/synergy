// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy.h"

class SandboxLayer: public Synergy::Layer
{
public:
    explicit SandboxLayer(): controller(800.0f / 600.0f), Synergy::Layer("SandboxLayer") {}
    
    virtual void OnAttach() override
    {
        texture = api->CreateTexture("assets/textures/checkerboard.png");
    }
    
    virtual void OnUpdate(float deltaTime) override
    {
        controller.Update(deltaTime);
        
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
    }
    
private:
    Synergy::Ref<Synergy::Renderer::Texture> texture;
    
    Synergy::CameraController controller;
};

class Sandbox: public Synergy::Application
{
public:
	explicit Sandbox(): Synergy::Application()
	{
        PushLayer(new SandboxLayer());
	}
    
	virtual ~Sandbox() = default;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
