// Created by Niels Marsman on 01-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_CANVAS_RENDERER_H
#define SYNERGY_RENDERER_CANVAS_RENDERER_H

#include "Synergy/Core.h"
#include "Synergy/Camera.h"
#include "Synergy/Renderer/Renderable.h"
#include "Synergy/Renderer/RendererAPI.h"
#include "Synergy/Renderer/Renderer.h"

namespace Synergy::Renderer
{
    class SYNERGY_API CanvasRenderer: public Renderer<CanvasRenderer, Renderable2D>
    {
    private:
        static CanvasRenderer& Instance();
        
    public:
        CanvasRenderer(const CanvasRenderer&) = delete;
        CanvasRenderer& operator=(const CanvasRenderer&) = delete;
        
    private:
        CanvasRenderer() {}
        
        void Initialize();
        
        static void Initialize(RendererAPI* api);
        
        static void SubmitRenderable(Renderable2D renderable);
        static void SubmitText(Text text);
        
    private:
        RendererAPI* api;
        
        friend class Renderer<CanvasRenderer, Renderable2D>;
        friend class RendererAPI;
    };
}

#endif
