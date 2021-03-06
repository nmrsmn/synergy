// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_RENDERERAPI_H
#define SYNERGY_RENDERER_RENDERERAPI_H

#include <map>

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Shader.h"
#include "Synergy/Renderer/Texture.h"
#include "Synergy/Renderer/IndexBuffer.h"
#include "Synergy/Renderer/VertexArray.h"
#include "Synergy/Renderer/VertexBuffer.h"

namespace Synergy::Renderer
{
    class SYNERGY_API RendererAPI
    {
    public:
        enum class API
        {
            OpenGL = 1,
            Vulkan = 2
        };
        
    public:
        static API Get();
        
    public:
        virtual void PrepareDevice() = 0;
        virtual bool CreateDevice() = 0;
        virtual bool DestroyDevice() = 0;
        
        virtual void DisplayFrame() = 0;
        
        virtual void PrepareRendering() = 0;
        
        virtual void UpdateViewport(glm::vec2 offset, glm::vec2 size) = 0;
        virtual void ClearBuffer(glm::vec4 color, bool depth) = 0;
        
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) = 0;
        virtual void DrawArrays(uint32_t count) = 0;
        
        virtual Ref<VertexArray> CreateVertexArray() = 0;
        virtual Ref<VertexBuffer> CreateVertexBuffer(uint32_t size) = 0;
        virtual Ref<IndexBuffer> CreateIndexBuffer(uint32_t* indices, uint32_t count) = 0;
        
    protected:
        void InitializeRenderers(RendererAPI* api);
        
    protected:
        static API api;
    };

    RendererAPI* CreateRendererAPI();
}

#endif
