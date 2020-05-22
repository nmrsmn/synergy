// Created by Niels Marsman on 19-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDER_QUEUE_H
#define SYNERGY_RENDER_QUEUE_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Shader.h"
#include "Synergy/Renderer/Texture.h"
#include "Synergy/Renderer/VertexArray.h"

namespace Synergy
{
    enum class SYNERGY_API RenderCommand : uint8_t
    {
        DRAW_ARRAYS,
        DRAW_INDEXED
    };

    class SYNERGY_API RenderQueue
    {
    public:
        struct SYNERGY_API Item
        {
            Synergy::RenderCommand command;
            
            glm::vec3 position;
            glm::mat4 matrix;
            
            Synergy::Ref<Synergy::Shader> shader;
            Synergy::Ref<Synergy::Renderer::VertexArray> vertexArray;
            Synergy::Ref<Synergy::Texture> texture;
            
            bool transparent;
        };
        
        union SYNERGY_API Key
        {
            struct
            {
                uint64_t layer : 2;             // Game layer, effect layer or HUD
                uint64_t viewport : 3;          // Multiplayer splitscreen, a mirror or a portal.
                uint64_t viewportLayer : 3;     // Each viewport can have its own layers like skybox, world layer or HUD
                uint64_t transparancy : 2;      // Does the renderable contain transparancy
                uint64_t material : 30;         // State settings like texture, shader or even constants
                uint64_t depth : 24;            // Distance from camera
            } opaque;
            
            struct
            {
                uint64_t layer : 2;             // Game layer, effect layer or HUD
                uint64_t viewport : 3;          // Multiplayer splitscreen, a mirror or a portal.
                uint64_t viewportLayer : 3;     // Each viewport can have its own layers like skybox, world layer or HUD
                uint64_t transparancy : 2;      // Does the renderable contain transparancy
                uint64_t depth : 24;            // Distance from camera
                uint64_t material : 30;         // State settings like texture, shader or even constants
            } transparent;
            
            uint64_t value;
        };
        
    public:
        void Add(Synergy::RenderQueue::Item item);
        void Reset();
        
        std::vector<Synergy::RenderQueue::Item> Sort();
        
    private:
        std::vector<Synergy::RenderQueue::Item> m_Items;
        std::vector<Synergy::RenderQueue::Item> m_SortedItems;
        std::vector<Synergy::RenderQueue::Key> m_SortingKeys;
        
        bool m_Sorted = false;
    };
}

#endif
