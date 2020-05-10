// Created by Niels Marsman on 10-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_RENDERER_H
#define SYNERGY_UI_RENDERER_H

#include "Synergy/Core.h"
#include "Synergy/Camera.h"
#include "Synergy/Renderer/Renderable.h"
#include "Synergy/Renderer/RendererAPI.h"
#include "Synergy/Renderer/Renderer.h"

namespace Synergy::UI
{
    class SYNERGY_API Renderer: public Synergy::Renderer::Renderer<Synergy::UI::Renderer, Synergy::Renderer::Renderable2D>
    {
    private:
        static Synergy::UI::Renderer& Instance();
        
        static void Initialize(Synergy::Renderer::RendererAPI* api);
        
        static void SubmitRenderable(Synergy::Renderer::Renderable2D renderable);
        static void SubmitText(Synergy::Text text);
        
    public:
        Renderer(const Synergy::UI::Renderer&) = delete;
        Renderer& operator=(const Synergy::UI::Renderer&) = delete;
        
    private:
        Renderer();
        
        void Initialize();
        
    private:
        Synergy::Renderer::RendererAPI* api;
        
        friend class Synergy::Renderer::Renderer<Synergy::UI::Renderer, Synergy::Renderer::Renderable2D>;
        friend class Synergy::Renderer::RendererAPI;
    };
}

#endif
