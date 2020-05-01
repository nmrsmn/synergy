// Created by Niels Marsman on 21-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_VERTEX_ARRAY_H
#define SYNERGY_RENDERER_VERTEX_ARRAY_H

#include <vector>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Bindable.h"
#include "Synergy/Renderer/VertexBuffer.h"
#include "Synergy/Renderer/IndexBuffer.h"

namespace Synergy::Renderer
{
    class SYNERGY_API VertexArray: public Bindable
    {
    public:
        virtual ~VertexArray() = default;
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        virtual void AddVertexBuffer(const Ref<VertexBuffer> buffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer> buffer) = 0;
        
        virtual const std::vector<Ref<VertexBuffer>> GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer> GetIndexBuffer() const = 0;
    };
}

#endif
