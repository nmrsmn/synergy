// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/API/OpenGL.h"
#include "Synergy/Renderer/API/OpenGL/Shader.h"
#include "Synergy/Renderer/API/OpenGL/IndexBuffer.h"
#include "Synergy/Renderer/API/OpenGL/VertexArray.h"
#include "Synergy/Renderer/API/OpenGL/VertexBuffer.h"

#include <glad/glad.h>

namespace Synergy::Renderer::API
{
    void OpenGL::PrepareDevice()
    {
        
    }

    bool OpenGL::CreateDevice()
    {
        return true;
    }

    bool OpenGL::DestroyDevice()
    {
        return true;
    }
    
    void OpenGL::DisplayFrame()
    {
        
    }
    
    void OpenGL::PrepareRendering()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGL::UpdateViewport(glm::vec2 offset, glm::vec2 size)
    {
        glViewport(offset.x, offset.y, size.x, size.y);
    }
    
    void OpenGL::ClearBuffer(glm::vec4 color, bool depth)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Ref<VertexArray> OpenGL::CreateVertexArray()
    {
        return Synergy::CreateRef<Synergy::Renderer::OpenGL::VertexArray>();
    }
    
    Ref<VertexBuffer> OpenGL::CreateVertexBuffer(uint32_t size)
    {
        return Synergy::CreateRef<Synergy::Renderer::OpenGL::VertexBuffer>(size);
    }

    Ref<IndexBuffer> OpenGL::CreateIndexBuffer(uint32_t* indices, uint32_t count)
    {
        return Synergy::CreateRef<Synergy::Renderer::OpenGL::IndexBuffer>(indices, count);
    }

    Ref<Shader> OpenGL::CreateShader(const std::string &name, std::map<Shader::Type, const std::string&> sources)
    {
        return Synergy::CreateRef<Synergy::Renderer::OpenGL::Shader>(name, sources);
    }
}
