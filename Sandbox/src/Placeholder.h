// Created by Niels Marsman on 18-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SANDBOX_PLACEHOLDER_H
#define SANDBOX_PLACEHOLDER_H

#include <glm/glm.hpp>

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
        // Get
        glm::vec2 mouse = Synergy::Input::GetMousePosition();
        glm::vec2 normalized = glm::vec2 { mouse.x / 800.f, 1 - (mouse.y / 600.f) };
        
        Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { normalized, transform.scale, glm::vec4 { 1.f, 1.f, 1.f, .8f } });
    }
    
    
    Synergy::EntitiesWith<const Placeholder, const Synergy::Transform> m_Entities;
};

#endif
