// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy.h"

struct Transform
{
    glm::vec3 position { 0.f, 0.f, 0.f };
    glm::vec3 rotation { 0.f, 0.f, 0.f };
    glm::vec3 scale { 1.f, 1.f, 1.f };
};

class Sandbox: public Synergy::Application
{
public:
	explicit Sandbox() : m_SandboxScene(this->CreateScene("Sandbox Scene")), controller(800.0f / 600.0f), Synergy::Application() {}
    
    static constexpr float ratio = 45.f / 190.f;
    
    virtual bool OnUserCreate() override
    {
        Synergy::EntityRef entity = m_SandboxScene.CreateEntity("Button");
        entity.Add<Transform>();
        
        button = Synergy::Texture::Load("assets/textures/red_button00.png");
        
        narrow = Synergy::Fonts::Load("assets/fonts/Kenney Future Narrow.ttf", 48);
        blocks = Synergy::Fonts::Load("assets/fonts/Kenney Blocks.ttf", 10);
        
        Synergy::Texture::Parameters parameters;
        parameters.wrap = Synergy::Texture::Parameters::Wrap(Synergy::Texture::Wrap::REPEAT);
        
        atlas = Synergy::TextureAtlas::Load("assets/textures/RPGpack_sheet.png", { 20, 13 }, parameters);
        //barrel = Synergy::TextureAtlas::Texture::Load(atlas, { 1, 1 });
        //stairs = Synergy::TextureAtlas::Texture::Load(atlas, { 2, 2 });
        tree = Synergy::TextureAtlas::Texture::Load(atlas, { 0, 11 }, { 1, 2 });
        
        root = Synergy::UI::View::Create({ 800, 600 });
        
        container1 = Synergy::UI::Container::Create(root);
        container2 = Synergy::UI::Container::Create(container1, { button }, [&container = this->container1](Synergy::UI::Constraint::Anchors& anchors)
        {
            anchors.vertical.equals(container->Anchors().vertical);
            anchors.horizontal.equals(container->Anchors().horizontal);
            anchors.width.equals(container->Anchors().width, 0.7f);
            anchors.height.equals(container->Anchors().height, 0.8f);
        });
        
        button1 = Synergy::UI::Button::Create(container1, [=, &container = this->container1](Synergy::UI::Constraint::Anchors& anchors)
        {
            anchors.top.equals(container->Anchors().top, 50);
            anchors.horizontal.equals(container->Anchors().horizontal);
            anchors.width.equals(container->Anchors().width, 0.25f);
            anchors.height.equals(anchors.width, ratio);
        });
        
        button2 = Synergy::UI::Button::Create(container1, [=, &button = this->button1](Synergy::UI::Constraint::Anchors& anchors)
        {
            anchors.top.equals(button->Anchors().bottom, button->Anchors().height.Value() / 2);
            anchors.horizontal.equals(button1->Anchors().horizontal);
            anchors.width.equals(button1->Anchors().width);
            anchors.height.equals(anchors.width, ratio);
        });
        
        return true;
    }
    
    virtual bool OnUserUpdate(float deltatime) override
    {
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.5, 0.1 }, { 1.0, 1.0 }, { 1, 1, 1, .1 } });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.2, 0.5 }, { 0.5, 0.5 * ratio }, this->button });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.6, 0.5 }, { .1, .2 }, tree });
        
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Text { "Hello world!", narrow, { 10.0, 560, 0.5 }, { 1, 1, 1, 1 } });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Text { "Copyright (c) 2020, all rights reserved Niels Marsman.", blocks, { 10, 10, 0 }, { 1, 1, 1, 1 } });
        
        Synergy::UI::Manager::Submit(root);
        
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
    
    Synergy::Ref<Synergy::UI::View> root;
    Synergy::Ref<Synergy::UI::Container> container1;
    Synergy::Ref<Synergy::UI::Container> container2;
    Synergy::Ref<Synergy::UI::Button> button1;
    Synergy::Ref<Synergy::UI::Button> button2;
    
    Synergy::CameraController controller;
    
    Synergy::Scene m_SandboxScene;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
