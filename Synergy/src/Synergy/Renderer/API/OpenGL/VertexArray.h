// Created by Niels Marsman on 21-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_OPENGL_VERTEX_ARRAY_H
#define SYNERGY_RENDERER_OPENGL_VERTEX_ARRAY_H

#include "Synergy/Core.h"
#include "Synergy/Renderer/VertexArray.h"

namespace Synergy::Renderer::OpenGL
{
    class SYNERGY_API VertexArray: public Synergy::Renderer::VertexArray
    {
    public:
        VertexArray();
        virtual ~VertexArray();
        
        virtual void Bind() const;
        virtual void Unbind() const;
        
        virtual void AddVertexBuffer(const Ref<Synergy::Renderer::VertexBuffer> buffer);
        virtual void SetIndexBuffer(const Ref<Synergy::Renderer::IndexBuffer> buffer);
        
        virtual const std::vector<Ref<Synergy::Renderer::VertexBuffer>> GetVertexBuffers() const;
        virtual const Ref<Synergy::Renderer::IndexBuffer> GetIndexBuffer() const;
        
    private:
        uint32_t id;
        uint32_t vertexBufferIndex = 0;
        
        std::vector<Ref<Synergy::Renderer::VertexBuffer>> vertexBuffers;
        Ref<Synergy::Renderer::IndexBuffer> indexBuffer;
    };
}

#endif
