// Created by Niels Marsman on 19-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/API/OpenGL/VertexArray.h"

#include <glad/glad.h>

namespace Synergy::Renderer::OpenGL
{
    static GLenum OpenGLDataType(const Synergy::Renderer::Shader::DataType type)
    {
        switch (type)
        {
            case Shader::DataType::FLOAT: case Shader::DataType::VEC2F: case Shader::DataType::VEC3F: case Shader::DataType::VEC4F:
            case Shader::DataType::MAT3: case Shader::DataType::MAT4: return GL_FLOAT;
                
            case Shader::DataType::INT: case Shader::DataType::VEC2I: case Shader::DataType::VEC3I: case Shader::DataType::VEC4I: return GL_INT;
                
            case Shader::DataType::BOOL: return GL_BOOL;
        }
        
        SYNERGY_ASSERT(false, "Unknown Shader::DataType supplied!");
        return 0;
    }

    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &id);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(id);
    }
    
    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const Ref<VertexBuffer> buffer)
    {
        SYNERGY_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex buffer has no layout");
        
        glBindVertexArray(id);
        buffer->Bind();
        
        const VertexBuffer::Layout& layout = buffer->GetLayout();
        for (const VertexBuffer::Layout::Element& element : layout.GetElements())
        {
            GLint components = Shader::DataTypeComponents(element.type);
            GLenum type = OpenGLDataType(element.type);
            GLboolean normalized = element.normalized ? GL_TRUE : GL_FALSE;
            
            glEnableVertexAttribArray(vertexBufferIndex);
            glVertexAttribPointer(vertexBufferIndex, components, type, normalized, layout.GetStride(), (const void*) element.offset);
            vertexBufferIndex++;
        }
        
        vertexBuffers.push_back(buffer);
    }

    void VertexArray::SetIndexBuffer(const Ref<IndexBuffer> buffer)
    {
        glBindVertexArray(id);
        buffer->Bind();
        
        indexBuffer = buffer;
    }

    const std::vector<Ref<VertexBuffer>> VertexArray::GetVertexBuffers() const
    {
        return vertexBuffers;
    }

    const Ref<IndexBuffer> VertexArray::GetIndexBuffer() const
    {
        return indexBuffer;
    }
}
