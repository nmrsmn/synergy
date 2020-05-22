// Created by Niels Marsman on 18-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SANDBOX_PLACEHOLDER_H
#define SANDBOX_PLACEHOLDER_H

#include <glm/glm.hpp>

#include "Synergy/Renderer/TextureAtlas.h"

struct Placeholder
{
    Synergy::Ref<Synergy::TextureAtlas> atlas;
    
    Synergy::Ref<Synergy::TextureAtlas::Texture> base;
    Synergy::Ref<Synergy::TextureAtlas::Texture> tower;
    
    glm::vec2 size;
    
    std::function<void (void)> place;
};

class PlaceholderSystem
{
public:
    void Process(const Placeholder placeholder, const Synergy::Transform transform) const
    {
        if (placeholder.base && placeholder.tower)
        {
            glm::vec2 mouse = Synergy::Input::GetMousePosition();
            glm::vec2 inverted = { mouse.x, mouse.y };
            glm::ivec2 size { placeholder.size.x * 800.f, placeholder.size.y * 600.f };
            
            glm::ivec2 tile { inverted.x / size.x, inverted.y / size.y };
            glm::vec3 position { tile.x * placeholder.size.x, 1 - (tile.y * placeholder.size.y), 0.8f };
            
            Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { position + glm::vec3 { placeholder.size.x / 2, 0 - (placeholder.size.y / 2), .10f }, placeholder.size, placeholder.base, glm::vec4 { 1.f, 1.f, 1.f, .6f } });
            Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { position + glm::vec3 { placeholder.size.x / 2, 0 - (placeholder.size.y / 2), .15f }, placeholder.size, placeholder.tower, glm::vec4 { 1.f, 1.f, 1.f, .6f } });
        }
    }
    
    Synergy::EntitiesWith<const Placeholder, const Synergy::Transform> m_Entities;
};

#endif
