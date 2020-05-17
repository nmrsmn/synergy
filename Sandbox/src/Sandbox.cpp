// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy.h"

class Sandbox: public Synergy::Application
{
public:
	explicit Sandbox() : Synergy::Application(),
        m_SandboxScene { this->CreateScene("Sandbox Scene") },
        m_ButtonArchetype { this->CreateArchetype("Button") }
    {
        
    }
    
    static constexpr float ratio = 45.f / 190.f;
    
    virtual bool OnUserCreate() override
    {
        m_SandboxScene.Add<Synergy::UI::ButtonSystem>();
        
        m_Atlas = Synergy::TextureAtlas::Load("assets/textures/towerDefense_tilesheet.png", { 23, 13 });
        m_GrassTile = Synergy::TextureAtlas::Texture::Load(m_Atlas, { 1, 1 }, { 1, 1 });
        
        m_GunTowerButtonTexture = Synergy::TextureAtlas::Texture::Load(m_Atlas, { 19, 8 }, { 1, 1 });
        m_AntiAirTowerButtonTexture = Synergy::TextureAtlas::Texture::Load(m_Atlas, { 20, 8 }, { 1, 1 });
        m_RocketTowerButtonTexture = Synergy::TextureAtlas::Texture::Load(m_Atlas, { 22, 8 }, { 1, 1 });
        m_CannonTowerButtonTexture = Synergy::TextureAtlas::Texture::Load(m_Atlas, { 19, 10 }, { 1, 1 });
        
        m_ButtonTexture = Synergy::Texture::Load("assets/textures/grey_panel.png");
        m_ButtonTextureHover = Synergy::Texture::Load("assets/textures/yellow_panel.png");
        
        // Interface
        {
            glm::vec2 padding = { 10.f / 800.f, 10.f / 600.f };
            glm::vec2 size = { 50.f / 800.f, 50.f / 600.f };
            
            Synergy::Transform& transform = m_ButtonArchetype.Add<Synergy::Transform>();
            transform.scale = glm::vec3 { size.x, size.y, 1.f };
            
            Synergy::UI::Button& button = m_ButtonArchetype.Add<Synergy::UI::Button>();
            button.background.normal = m_ButtonTexture;
            button.background.hover = m_ButtonTextureHover;
            button.background.active = { { 1.f, 1.f, 1.f, 0.8f } };
            
            m_ButtonArchetype.Add<Synergy::UI::Image>();
            
            // Gun Tower
            {
                Synergy::EntityRef button = m_SandboxScene.Spawn(m_ButtonArchetype);
                Synergy::Transform& transform = button.Get<Synergy::Transform>();
                transform.position = glm::vec3 { 1 * padding.x + 0 * size.x + size.x / 2, padding.y + size.y / 2, 1.f };
                
                Synergy::UI::Image& image = button.Get<Synergy::UI::Image>();
                image.texture = m_GunTowerButtonTexture;
            }
            
            // Anti Air
            {
                Synergy::EntityRef button = m_SandboxScene.Spawn(m_ButtonArchetype);
                Synergy::Transform& transform = button.Get<Synergy::Transform>();
                transform.position = glm::vec3 { 2 * padding.x + 1 * size.x + size.x / 2, padding.y + size.y / 2, 1.f };
                
                Synergy::UI::Image& image = button.Get<Synergy::UI::Image>();
                image.texture = m_AntiAirTowerButtonTexture;
            }
            
            // Rocket
            {
                Synergy::EntityRef button = m_SandboxScene.Spawn(m_ButtonArchetype);
                Synergy::Transform& transform = button.Get<Synergy::Transform>();
                transform.position = glm::vec3 { 3 * padding.x + 2 * size.x + size.x / 2, padding.y + size.y / 2, 1.f };
                
                Synergy::UI::Image& image = button.Get<Synergy::UI::Image>();
                image.texture = m_RocketTowerButtonTexture;
            }
            
            // Cannon
            {
                Synergy::EntityRef button = m_SandboxScene.Spawn(m_ButtonArchetype);
                Synergy::Transform& transform = button.Get<Synergy::Transform>();
                transform.position = glm::vec3 { 4 * padding.x + 3 * size.x + size.x / 2, padding.y + size.y / 2, 1.f };
                
                Synergy::UI::Image& image = button.Get<Synergy::UI::Image>();
                image.texture = m_CannonTowerButtonTexture;
            }
        }
        
        // Player
        {
            
        }
        
        return true;
    }
    
    virtual bool OnUserUpdate(float deltatime) override
    {
        
        
        return true;
    }
    
	virtual ~Sandbox() = default;
    
private:
    Synergy::Scene& m_SandboxScene;
    
    Synergy::ArchetypeRef m_ButtonArchetype;
    
    
    
    
    Synergy::Ref<Synergy::TextureAtlas> m_Atlas;
    Synergy::Ref<Synergy::TextureAtlas::Texture> m_GrassTile;
    Synergy::Ref<Synergy::TextureAtlas::Texture> m_GunTowerButtonTexture;
    Synergy::Ref<Synergy::TextureAtlas::Texture> m_AntiAirTowerButtonTexture;
    Synergy::Ref<Synergy::TextureAtlas::Texture> m_RocketTowerButtonTexture;
    Synergy::Ref<Synergy::TextureAtlas::Texture> m_CannonTowerButtonTexture;
    
    Synergy::Ref<Synergy::Texture> m_ButtonTexture;
    Synergy::Ref<Synergy::Texture> m_ButtonTextureHover;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
