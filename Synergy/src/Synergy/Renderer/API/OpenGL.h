// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_API_OPENGL_H
#define SYNERGY_RENDERER_API_OPENGL_H

#include "Synergy/Core.h"
#include "Synergy/Renderer/RendererAPI.h"

namespace Synergy::Renderer::API
{
    class SYNERGY_API OpenGL: public Synergy::Renderer::RendererAPI
    {
    public:
        virtual void PrepareDevice() override;
        virtual bool CreateDevice() override;
        virtual bool DestroyDevice() override;
        
        virtual void DisplayFrame() override;
        
        virtual void PrepareRendering() override;
        
        virtual void UpdateViewport(glm::vec2 offset, glm::vec2 size) override;
        virtual void ClearBuffer(glm::vec4 color, bool depth) override;
        
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) override;
        virtual void DrawArrays(uint32_t count) override;
        
        virtual Ref<VertexArray> CreateVertexArray() override;
        virtual Ref<VertexBuffer> CreateVertexBuffer(uint32_t size) override;
        virtual Ref<IndexBuffer> CreateIndexBuffer(uint32_t* indices, uint32_t count) override;
        
        virtual Ref<Shader> CreateShader(const std::string& name, std::map<Shader::Type, const std::string&> sources) override;
        
        virtual Ref<Texture> CreateTexture(uint32_t width, uint32_t height, Texture::Parameters parameters = Texture::Parameters()) override;
    };
}

#endif
