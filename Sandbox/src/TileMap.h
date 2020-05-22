// Created by Niels Marsman on 17-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SANDBOX_TILE_MAP_H
#define SANDBOX_TILE_MAP_H

#include <glm/glm.hpp>

struct TileMap
{
    Synergy::Ref<Synergy::TextureAtlas> atlas;
    
    glm::vec2 size { 0, 0 };
    glm::vec2 tile { 0, 0 };
    
    std::vector<glm::vec2> tiles;
};

class TileMapSystem
{
public:
    void FrameStart()
    {
        m_CameraController.Update(1 / 60);
    }
    
    void PreProcess()
    {
        Synergy::Renderer::Renderer2D::BeginScene(m_CameraController.GetCamera());

        float ratio = 800.f / 600.f;
        
        if (m_Entities.begin() != m_Entities.end())
        {
            const auto& map = m_Entities[0].Get<const TileMap>();

            float height = (600.f / map.size.y) / 300.f;
            glm::vec2 tileSize { height * ratio, height };
            
            uint32_t count = 0;
            for (const auto& tile : map.tiles)
            {
                uint32_t index = tile.x * 1000 + tile.y;
                if (auto item { m_TileTextures.find(index) }; item == m_TileTextures.end())
                {
                    m_TileTextures.insert({ index, Synergy::TextureAtlas::Texture::Load(map.atlas, tile, { 1, 1 }) });
                }

                glm::vec2 offset { count % (int) map.size.x, count / (int) map.size.x };
                glm::vec3 position { (offset.x * tileSize.x + tileSize.x / 2) - ratio, 1 - (offset.y * tileSize.y + tileSize.y / 2), .5f };

                Synergy::Renderer::Renderer2D::Submit(Synergy::Quad { position, tileSize, m_TileTextures[index] });

                count++;
            }
        }
        
        Synergy::Renderer::Renderer2D::EndScene();
    }
    
    Synergy::EntitiesWith<const TileMap> m_Entities;
    
private:
    std::unordered_map<uint32_t, Synergy::Ref<Synergy::TextureAtlas::Texture>> m_TileTextures;
    
    Synergy::CameraController m_CameraController { 800.f / 600.f };
};

#endif