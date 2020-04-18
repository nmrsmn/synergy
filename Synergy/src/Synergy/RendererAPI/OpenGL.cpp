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
    
    void OpenGL::UpdateViewport(int x, int y, int width, int height)
    {
        glViewport(x, y, width, height);
    }
    
    void OpenGL::ClearBuffer(int r, int g, int b, int a, bool depth)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
}
