// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy.h"

class Sandbox: public Synergy::Application
{
public:
	explicit Sandbox(): controller(800.0f / 600.0f), Synergy::Application() {}
    
    static constexpr float ratio = 45.f / 190.f;
    
    virtual bool OnUserCreate() override
    {
        button = Synergy::Texture::Load("assets/textures/red_button00.png");
        
        narrow = Synergy::Fonts::Load("assets/fonts/Kenney Future Narrow.ttf", 48);
        blocks = Synergy::Fonts::Load("assets/fonts/Kenney Blocks.ttf", 10);
        
        Synergy::Texture::Parameters parameters;
        parameters.wrap = Synergy::Texture::Parameters::Wrap(Synergy::Texture::Wrap::REPEAT);
        
        atlas = Synergy::TextureAtlas::Load("assets/textures/RPGpack_sheet.png", { 20, 13 }, parameters);
        tree = Synergy::TextureAtlas::Texture::Load(atlas, { 0, 11 }, { 1, 2 });
        
        root = Synergy::UI::View::Create({ 800, 600 });
        
        Synergy::UI::Label::Style titleStyle = {};
        titleStyle.font = narrow;
        titleStyle.color = glm::vec3 { 1, 1, 1 };
        titleStyle.align = Synergy::UI::Style::TextAlignment::CENTER;
        
        Synergy::UI::Label::Style copyrightStyle = {};
        copyrightStyle.font = blocks;
        copyrightStyle.color = glm::vec3 { 1, 1, 1 };
        copyrightStyle.gravity = Synergy::UI::Style::Gravity::BOTTOM;
        
        container = Synergy::UI::Container::Create(root);
        title = Synergy::UI::Label::Create(container, "Synergy", titleStyle, [=, &container = this->container](Synergy::UI::Constraint::Anchors& anchors)
        {
            anchors.top.equals(container->Anchors().top, 50);
            anchors.horizontal.equals(container->Anchors().horizontal);
            
            // TODO: Width and height should be optional.
            anchors.width.equals(container->Anchors().width, 0.5f);
            anchors.height.equals(anchors.width, ratio);
        });
        
        button1 = Synergy::UI::Button::Create(container, [=, &container = this->container, &title = this->title](Synergy::UI::Constraint::Anchors& anchors)
        {
            anchors.top.equals(title->Anchors().bottom, 50);
            anchors.horizontal.equals(container->Anchors().horizontal);
            anchors.width.equals(container->Anchors().width, 0.25f);
            anchors.height.equals(anchors.width, ratio);
        });
        
        button2 = Synergy::UI::Button::Create(container, [=, &button = this->button1](Synergy::UI::Constraint::Anchors& anchors)
        {
            anchors.top.equals(button->Anchors().bottom, button->Anchors().height.Value() / 2);
            anchors.horizontal.equals(button1->Anchors().horizontal);
            anchors.width.equals(button1->Anchors().width);
            anchors.height.equals(anchors.width, ratio);
        });
        
        label = Synergy::UI::Label::Create(container, "Copyright (c) 2020, all rights reserved Niels Marsman.", copyrightStyle, [=, &container = this->container](Synergy::UI::Constraint::Anchors& anchors)
        {
            anchors.bottom.equals(container->Anchors().bottom, -10);
            anchors.left.equals(container->Anchors().left, 10);

            // TODO: Width and height should be optional.
            anchors.width.equals(container->Anchors().width, 0.8f);
            anchors.height.equals(anchors.width, 0.05f);
        });
        
        return true;
    }
    
    virtual bool OnUserUpdate(float deltatime) override
    {
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.5, 0.1 }, { 1.0, 1.0 }, { 1, 1, 1, .1 } });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.2, 0.5 }, { 0.5, 0.5 * ratio }, this->button });
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { { 0.5, 0.6, 0.5 }, { .1, .2 }, tree });
        
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
    Synergy::Ref<Synergy::UI::Container> container;
    Synergy::Ref<Synergy::UI::Button> button1;
    Synergy::Ref<Synergy::UI::Button> button2;
    Synergy::Ref<Synergy::UI::Label> title;
    Synergy::Ref<Synergy::UI::Label> label;
    
    Synergy::CameraController controller;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
