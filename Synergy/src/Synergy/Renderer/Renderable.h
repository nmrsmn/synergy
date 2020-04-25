// Created by Niels Marsman on 21-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_RENDERABLE_H
#define SYNERGY_RENDERER_RENDERABLE_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Texture.h"

namespace Synergy::Renderer
{
    struct SYNERGY_API Renderable
    {
    
    };

    struct SYNERGY_API Renderable2D : public Renderable
    {
        Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)
            : position(position), size(size), color(color) { }
        
        Renderable2D(glm::vec3 position, glm::vec2 size, Ref<Texture> texture)
            : position(position), size(size), texture(texture) { }
        
        Renderable2D(glm::vec3 position, glm::vec2 size, Ref<Texture> texture, glm::vec4 color)
            : position(position), size(size), color(color), texture(texture) { }
        
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 size;
        
        Ref<Texture> texture;
    };
    
    struct SYNERGY_API Renderable3D : public Renderable
    {
        
    };
}

namespace Synergy
{
    struct SYNERGY_API Quad: public Renderer::Renderable2D
    {
        Quad(glm::vec2 position, glm::vec2 size, glm::vec4 color) : Renderer::Renderable2D(glm::vec3(position, 1.0), size, color) {}
        Quad(glm::vec2 position, glm::vec2 size, glm::vec3 color) : Renderer::Renderable2D(glm::vec3(position, 1.0), size, glm::vec4(color, 1.0)) {}
        
        Quad(glm::vec2 position, glm::vec2 size, Ref<Renderer::Texture> texture) : Renderer::Renderable2D(glm::vec3(position, 1.0), size, texture, glm::vec4(1.0)) {}
        Quad(glm::vec2 position, glm::vec2 size, Ref<Renderer::Texture> texture, glm::vec4 color) : Renderer::Renderable2D(glm::vec3(position, 1.0), size, texture) {}
        Quad(glm::vec2 position, glm::vec2 size, Ref<Renderer::Texture> texture, glm::vec3 color) : Renderer::Renderable2D(glm::vec3(position, 1.0), size, texture, glm::vec4(color, 1.0)) {}
        
        Quad(glm::vec3 position, glm::vec2 size, glm::vec4 color) : Renderer::Renderable2D(position, size, color) {}
        Quad(glm::vec3 position, glm::vec2 size, glm::vec3 color) : Renderer::Renderable2D(position, size, glm::vec4(color, 1.0)) {}
        
        Quad(glm::vec3 position, glm::vec2 size, Ref<Renderer::Texture> texture) : Renderer::Renderable2D(position, size, texture, glm::vec4(1.0)) {}
        Quad(glm::vec3 position, glm::vec2 size, Ref<Renderer::Texture> texture, glm::vec4 color) : Renderer::Renderable2D(position, size, texture, color) {}
        Quad(glm::vec3 position, glm::vec2 size, Ref<Renderer::Texture> texture, glm::vec3 color) : Renderer::Renderable2D(position, size, texture, glm::vec4(color, 1.0)) {}
        
    };
}

#endif
