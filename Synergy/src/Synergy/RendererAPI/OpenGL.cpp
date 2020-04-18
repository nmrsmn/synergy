// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/RendererAPI/OpenGL.h"

#include <glad/glad.h>

namespace Synergy::RendererAPIs
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
    
}
