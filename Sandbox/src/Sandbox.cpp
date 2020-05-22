// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include <unordered_map>

#include "Synergy.h"

#include "Helpers.h"
#include "Placeholder.h"
#include "TileMap.h"
#include "Tower.h"

class Sandbox: public Synergy::Application
{
public:
    enum TileType
    {
        DIRT = 1,
        SAND,
        GRASS,
        CONCRETE
    };
    
public:
	explicit Sandbox() : Synergy::Application(),
        m_CameraController(800.0f / 600.0f),
        m_SandboxScene { this->CreateScene("Sandbox Scene") },
        m_ButtonArchetype { this->CreateArchetype("Button") },
        m_TileMapArchetype { this->CreateArchetype("Button") }
    {}
    
    static constexpr float ratio = 45.f / 190.f;
    
    virtual bool OnUserCreate() override
    {
        /**
         * Add all the systems
         */
        
        m_SandboxScene.Add<Synergy::UI::ButtonSystem>();
        
        m_SandboxScene.Add<PlaceholderSystem>();
        m_SandboxScene.Add<TileMapSystem>();
        
        /**
         * Initialize resources
         */
        
        m_Atlas = Synergy::TextureAtlas::Load("assets/textures/towerDefense_tilesheet.png", { 23, 13 });
        
        m_GunTowerButtonTexture = Synergy::TextureAtlas::Texture::Load(m_Atlas, { 19, 8 }, { 1, 1 });
        m_AntiAirTowerButtonTexture = Synergy::TextureAtlas::Texture::Load(m_Atlas, { 20, 8 }, { 1, 1 });
        m_RocketTowerButtonTexture = Synergy::TextureAtlas::Texture::Load(m_Atlas, { 22, 8 }, { 1, 1 });
        m_CannonTowerButtonTexture = Synergy::TextureAtlas::Texture::Load(m_Atlas, { 19, 10 }, { 1, 1 });
        
        m_ButtonTexture = Synergy::Texture::Load("assets/textures/grey_panel.png");
        m_ButtonTextureHover = Synergy::Texture::Load("assets/textures/yellow_panel.png");
        
        /**
         * General settings
         */
        
        float ratio = 800.f / 600.f;
        float height = (600.f / m_TileMapRows) / 300.f;
        
        glm::vec2 tileSize { height / ratio, height };
        
        /**
         * Initialize Archetypes
         */
        
        // Tile Map
        {
            glm::vec2 offset { 0, 0 };
            std::vector<glm::vec2> tiles;
            
            for (uint32_t index = 0; index < m_TileMapColumns * m_TileMapRows; ++index)
            {
                glm::vec2 tile = m_TileTypes[m_TileMap[index]];
                tiles.push_back(tile + offset);
            }
            
            m_TileMapArchetype.Add<Synergy::Transform>();
            TileMap& map = m_TileMapArchetype.Add<TileMap>();
            map.size = { 37, 25 };
            map.atlas = m_Atlas;
            map.tiles = tiles;

            m_SandboxScene.Spawn(m_TileMapArchetype);
        }
        
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
            
            Synergy::ArchetypeRef m_GunTowerArchetype = this->CreateArchetype("Gun Tower");
            {
                Placeholder& placeholder = m_GunTowerArchetype.Add<Placeholder>();
                placeholder.tower = m_GunTowerButtonTexture;
                placeholder.atlas = m_Atlas;
                placeholder.size = tileSize;
                
                Synergy::Transform& transform = m_GunTowerArchetype.Add<Synergy::Transform>();
                transform.scale = glm::vec3 { tileSize.x, tileSize.y, 1.f };
            }
            
            // Gun Tower
            {
                Synergy::EntityRef entity = m_SandboxScene.Spawn(m_ButtonArchetype);
                Synergy::Transform& transform = entity.Get<Synergy::Transform>();
                transform.position = glm::vec3 { 1 * padding.x + 0 * size.x + size.x / 2, padding.y + size.y / 2, 1.f };
                
                Synergy::UI::Image& image = entity.Get<Synergy::UI::Image>();
                image.texture = m_GunTowerButtonTexture;
                
                Synergy::UI::Button& button = entity.Get<Synergy::UI::Button>();
                button.onclick = [&scene = m_SandboxScene, archetype = m_GunTowerArchetype]()
                {
                    Tower::CreatePlaceholder(scene, archetype, [archetype]()
                    {
                        SYNERGY_LOG_ERROR("Buy Gun Turret.");
                    });
                };
            }
            
            // Anti Air
            {
                Synergy::EntityRef entity = m_SandboxScene.Spawn(m_ButtonArchetype);
                Synergy::Transform& transform = entity.Get<Synergy::Transform>();
                transform.position = glm::vec3 { 2 * padding.x + 1 * size.x + size.x / 2, padding.y + size.y / 2, 1.f };
                
                Synergy::UI::Image& image = entity.Get<Synergy::UI::Image>();
                image.texture = m_AntiAirTowerButtonTexture;
                
                Synergy::UI::Button& button = entity.Get<Synergy::UI::Button>();
                button.onclick = []()
                {
                    SYNERGY_LOG_ERROR("Buy Anti Air.");
                };
            }
            
            // Rocket
            {
                Synergy::EntityRef entity = m_SandboxScene.Spawn(m_ButtonArchetype);
                Synergy::Transform& transform = entity.Get<Synergy::Transform>();
                transform.position = glm::vec3 { 3 * padding.x + 2 * size.x + size.x / 2, padding.y + size.y / 2, 1.f };
                
                Synergy::UI::Image& image = entity.Get<Synergy::UI::Image>();
                image.texture = m_RocketTowerButtonTexture;
                
                Synergy::UI::Button& button = entity.Get<Synergy::UI::Button>();
                button.onclick = []()
                {
                    SYNERGY_LOG_ERROR("Buy Rocket.");
                };
            }
            
            // Cannon
            {
                Synergy::EntityRef entity = m_SandboxScene.Spawn(m_ButtonArchetype);
                Synergy::Transform& transform = entity.Get<Synergy::Transform>();
                transform.position = glm::vec3 { 4 * padding.x + 3 * size.x + size.x / 2, padding.y + size.y / 2, 1.f };
                
                Synergy::UI::Image& image = entity.Get<Synergy::UI::Image>();
                image.texture = m_CannonTowerButtonTexture;
                
                Synergy::UI::Button& button = entity.Get<Synergy::UI::Button>();
                button.onclick = []()
                {
                    SYNERGY_LOG_ERROR("Buy Cannon.");
                };
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
    Synergy::ArchetypeRef m_TileMapArchetype;
    
    Synergy::Ref<Synergy::TextureAtlas> m_Atlas;
    Synergy::Ref<Synergy::TextureAtlas::Texture> m_GrassTile;
    Synergy::Ref<Synergy::TextureAtlas::Texture> m_GunTowerButtonTexture;
    Synergy::Ref<Synergy::TextureAtlas::Texture> m_AntiAirTowerButtonTexture;
    Synergy::Ref<Synergy::TextureAtlas::Texture> m_RocketTowerButtonTexture;
    Synergy::Ref<Synergy::TextureAtlas::Texture> m_CannonTowerButtonTexture;
    
    Synergy::Ref<Synergy::Texture> m_ButtonTexture;
    Synergy::Ref<Synergy::Texture> m_ButtonTextureHover;
    
    Synergy::CameraController m_CameraController;
    
    std::unordered_map<std::pair<Sandbox::TileType, Sandbox::TileType>, const glm::vec2, stdext::pair_hash> m_TileTypeOffsets {
        { { GRASS, DIRT },      { 0, 0 } },
        { { DIRT, GRASS },      { 0, 3 } },
        { { GRASS, SAND },      { 0, 6 } },
        { { GRASS, CONCRETE },  { 0, 9 } },
        
        { { SAND, DIRT },       { 5, 0 } },
        { { SAND, GRASS },      { 5, 3 } },
        { { DIRT, SAND },       { 5, 6 } },
        { { DIRT, CONCRETE },   { 5, 9 } },
        
        { { CONCRETE, DIRT },   { 10, 0 } },
        { { CONCRETE, GRASS },  { 10, 3 } },
        { { CONCRETE, SAND },   { 10, 6 } },
        { { SAND, CONCRETE },   { 10, 9 } },
    };
    
    std::vector<glm::vec2> m_TileTypes {
        { 0, 0 },
        { 1, 0 },
        { 2, 0 },
        { 3, 0 },
        { 4, 0 },
        { 0, 1 },
        { 1, 1 },
        { 2, 1 },
        { 3, 1 },
        { 4, 1 },
        { 0, 2 },
        { 1, 2 },
        { 2, 2 },
        { 3, 2 },
        { 4, 2 }
    };
    
    static constexpr uint8_t m_TileMapColumns = 37;
    static constexpr uint8_t m_TileMapRows = 25;
    uint8_t m_TileMap[m_TileMapRows * m_TileMapColumns] = {
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  3, 11, 11, 11, 11, 11, 11, 11,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7, 14, 14, 14, 14, 14, 14, 14,
         6,  6,  6,  6,  6,  3, 11, 11, 11, 11, 11, 11, 11, 11,  4,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7, 14,  0,  1,  1,  1,  1,  1,
         6,  6,  6,  6,  6,  7, 14, 14, 14, 14, 14, 14, 14, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  7, 14,  0,  1,  1,  1,  1,  2, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  3, 11, 11, 11, 11, 11, 11, 11, 12, 14,  5,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  7, 14, 14, 14, 14, 14, 14, 14, 14, 14,  5,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  7, 14,  0,  1,  1,  1,  1,  1,  1,  1,  9,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
        11, 11, 11, 11, 11, 12, 14,  5,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
        14, 14, 14, 14, 14, 14, 14,  5,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         1,  1,  1,  1,  1,  1,  1,  9,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  7, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7, 14, 10, 11, 11, 11, 11, 11, 11, 12, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  7, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  8,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  9,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
         6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6
    };
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
