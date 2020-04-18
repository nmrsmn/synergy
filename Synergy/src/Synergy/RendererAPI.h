// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERERAPI_H
#define SYNERGY_RENDERERAPI_H

#include <glm/glm.hpp>

namespace Synergy
{
    class SYNERGY_API RendererAPI
    {
    public:
        virtual void PrepareDevice() = 0;
        virtual bool CreateDevice() = 0;
        virtual bool DestroyDevice() = 0;
        
        virtual void DisplayFrame() = 0;
        
        virtual void PrepareRendering() = 0;
        
        virtual void UpdateViewport(glm::vec2 offset, glm::vec2 size) = 0;
        virtual void ClearBuffer(glm::vec4 color, bool depth) = 0;
    };

    RendererAPI* CreateRendererAPI();
}

#endif
