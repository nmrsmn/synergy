// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERERAPI_OPENGL_H
#define SYNERGY_RENDERERAPI_OPENGL_H

#include "Synergy/Core.h"
#include "Synergy/RendererAPI.h"

namespace Synergy::RendererAPIs
{
    class SYNERGY_API OpenGL: public Synergy::RendererAPI
    {
    public:
        virtual void PrepareDevice() override;
        virtual bool CreateDevice() override;
        virtual bool DestroyDevice() override;
        
        virtual void DisplayFrame() override;
        
        virtual void PrepareRendering() override;
        
        virtual void UpdateViewport(int x, int y, int width, int height) override;
        virtual void ClearBuffer(int r, int g, int b, int a, bool depth) override;
    };
}

#endif
