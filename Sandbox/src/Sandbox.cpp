// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy.h"

class SandboxLayer: public Synergy::Layer
{
public:
    explicit SandboxLayer(): Synergy::Layer("SandboxLayer") {}
    
    virtual void OnAttach() override
    {
        texture = api->CreateTexture("assets/textures/checkerboard.png");
    }
    
    virtual void OnUpdate(float deltaTime) override
    {
        Synergy::Renderer::Renderer2D::BeginScene();
        Synergy::Renderer::Renderer2D::Submit(Synergy::Quad { {  0,  0, 1 }, { 1.0, 1.0 }, { 1, 0, 0, 1 } });
        Synergy::Renderer::Renderer2D::Submit(Synergy::Quad { { -.75f, -.75f, 0 }, { 1.0, 1.0 }, { 0, 1, 0, 1 } });
        Synergy::Renderer::Renderer2D::Submit(Synergy::Quad { { .75f, .75f, 0 }, { 1.0, 1.0 }, texture, { .2, .4, .8, 1 } });
        Synergy::Renderer::Renderer2D::EndScene();
        
        if (Synergy::Input::Get(Synergy::Input::Key::Q).pressed)
        {
            SYNERGY_LOG_ERROR("'Q' is pressed!");
        }
        
        if (Synergy::Input::Get(Synergy::Input::Key::Q).released)
        {
            SYNERGY_LOG_ERROR("'Q' is released!");
        }
        
        if (Synergy::Input::Get(Synergy::Input::Key::Q).held)
        {
            SYNERGY_LOG_ERROR("'Q' is held down!");
        }
        
        if (Synergy::Input::Get(Synergy::Input::Mouse::BUTTON_LEFT).pressed)
        {
            SYNERGY_LOG_ERROR("The left mouse button is clicked");
        }
        
        if (Synergy::Input::Get(Synergy::Input::Key::SPACE).pressed)
        {
            glm::vec2 position = Synergy::Input::GetMousePosition();
            SYNERGY_LOG_ERROR("Current mouse position: {} x {}", position.x, position.y);
        }
    }
    
private:
    Synergy::Ref<Synergy::Renderer::Texture> texture;
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
