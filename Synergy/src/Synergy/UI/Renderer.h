// Created by Niels Marsman on 10-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_RENDERER_H
#define SYNERGY_UI_RENDERER_H

#include "Synergy/Core.h"
#include "Synergy/Camera.h"
#include "Synergy/Renderer/RendererAPI.h"
#include "Synergy/Renderer/Renderer.h"

#include "Synergy/UI/Element.h"
#include "Synergy/UI/Renderable.h"

namespace Synergy::UI
{
    class SYNERGY_API Renderer
    {
    public:
        static void Submit(Synergy::UI::Quad quad);
        static void Submit(Synergy::UI::Text text);
        
    private:
        static Synergy::UI::Renderer& Instance();
        
        static void Initialize(Synergy::Renderer::RendererAPI* api);
        
    public:
        Renderer(const Synergy::UI::Renderer&) = delete;
        Renderer& operator=(const Synergy::UI::Renderer&) = delete;
        
    private:
        Renderer();
        
        void Initialize();
        
    private:
        Synergy::Renderer::RendererAPI* api;
        
        friend class Synergy::Renderer::RendererAPI;
    };
}

#endif
