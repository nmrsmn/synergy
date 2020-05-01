// Created by Niels Marsman on 19-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_OPENGL_VERTEXBUFFER_H
#define SYNERGY_RENDERER_OPENGL_VERTEXBUFFER_H

#include "Synergy/Core.h"
#include "Synergy/Renderer/VertexBuffer.h"

namespace Synergy::Renderer::OpenGL
{
    class SYNERGY_API VertexBuffer: public Synergy::Renderer::VertexBuffer
    {
    public:
        VertexBuffer(uint32_t size);
        virtual ~VertexBuffer();
        
        virtual void Bind() const override;
        virtual void Unbind() const override;
        
        virtual const Layout& GetLayout() const override;
        virtual void SetLayout(const Layout& layout) override;
        
        virtual void SetData(const void* data, uint32_t size) override;
        
    private:
        Layout layout;
        uint32_t id;
    };
}

#endif
