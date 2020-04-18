// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERERAPI_H
#define SYNERGY_RENDERERAPI_H

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
        
        virtual void UpdateViewport(int x, int y, int width, int height) = 0;
        virtual void ClearBuffer(int r, int g, int b, int a, bool depth) = 0;
    };

    RendererAPI* CreateRendererAPI();
}

#endif
