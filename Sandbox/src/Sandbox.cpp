// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy.h"

struct Transform
{
    glm::vec3 position { 0.f, 0.f, 0.f };
    glm::vec3 rotation { 0.f, 0.f, 0.f };
    glm::vec3 scale { 1.f, 1.f, 1.f };
};

struct SpriteRenderer
{
    Synergy::Ref<Synergy::Texture> texture { nullptr };
    glm::vec4 color { 1, 1, 1, 1 };
};

struct RenderSystem
{
    void PreProcess()
    {
        SYNERGY_LOG_ERROR("Dit is een test");
    }
    
    void PostProcess()
    {
        SYNERGY_LOG_ERROR("Render");
    }
    
    Synergy::EntitiesWith<const SpriteRenderer> m_Sprites;
};

class Sandbox: public Synergy::Application
{
public:
	explicit Sandbox() : m_SandboxScene(this->CreateScene("Sandbox Scene")), Synergy::Application() {}
    
    static constexpr float ratio = 45.f / 190.f;
    
    virtual bool OnUserCreate() override
    {
        m_Atlas = Synergy::TextureAtlas::Load("assets/textures/RPGpack_sheet.png", { 20, 13 });
        m_GrassTile = Synergy::TextureAtlas::Texture::Load(m_Atlas, { 1, 1 }, { 1, 1 });
        
        Synergy::EntityRef quad = m_SandboxScene.CreateEntity("Quad");
        Transform transform = quad.Add<Transform>();
        SpriteRenderer renderer = quad.Add<SpriteRenderer>();
        renderer.texture = m_GrassTile;
        
        m_SandboxScene.Add<RenderSystem>();
        
        return true;
    }
    
    virtual bool OnUserUpdate(float deltatime) override
    {
        return true;
    }
    
	virtual ~Sandbox() = default;
    
private:
    Synergy::Ref<Synergy::TextureAtlas> m_Atlas;
    Synergy::Ref<Synergy::TextureAtlas::Texture> m_GrassTile;
    
    Synergy::Scene& m_SandboxScene;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
