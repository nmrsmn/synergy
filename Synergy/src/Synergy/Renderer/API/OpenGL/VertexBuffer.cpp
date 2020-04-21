// Created by Niels Marsman on 19-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/API/OpenGL/VertexBuffer.h"

#include <glad/glad.h>

namespace Synergy::Renderer::OpenGL
{
    VertexBuffer::VertexBuffer(uint32_t size)
    {
        glGenBuffers(1, &id);
        
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &id);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    const VertexBuffer::Layout& VertexBuffer::GetLayout() const
    {
        return layout;
    }

    void VertexBuffer::SetLayout(const VertexBuffer::Layout& layout)
    {
        this->layout = layout;
    }

    void VertexBuffer::SetData(const void* data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
}
