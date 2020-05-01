// Created by Niels Marsman on 19-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_OPENGL_INDEX_BUFFER_H
#define SYNERGY_RENDERER_OPENGL_INDEX_BUFFER_H

#include "Synergy/Core.h"
#include "Synergy/Renderer/IndexBuffer.h"

namespace Synergy::Renderer::OpenGL
{
    class SYNERGY_API IndexBuffer: public Synergy::Renderer::IndexBuffer
    {
    public:
        IndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~IndexBuffer();
        
        virtual void Bind() const override;
        virtual void Unbind() const override;
        
        virtual uint32_t GetCount() const override;
        
    private:
        uint32_t id;
        uint32_t count;
    };
}

#endif
