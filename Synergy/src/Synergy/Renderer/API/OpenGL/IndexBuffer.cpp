// Created by Niels Marsman on 19-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/API/OpenGL/IndexBuffer.h"

#include <glad/glad.h>

namespace Synergy::Renderer::OpenGL
{
    IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) : count(count)
    {
        glGenBuffers(1, &id);
        
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &id);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t IndexBuffer::GetCount() const
    {
        return count;
    }
}
