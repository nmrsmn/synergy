// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/RendererAPI.h"

#include "Synergy/Renderer/CanvasRenderer.h"
#include "Synergy/Renderer/Renderer2D.h"
#include "Synergy/UI/Renderer.h"

namespace Synergy::Renderer
{
    Synergy::Renderer::RendererAPI::API Synergy::Renderer::RendererAPI::Get()
    {
        return api;
    }

    void Synergy::Renderer::RendererAPI::InitializeRenderers(Synergy::Renderer::RendererAPI* api)
    {
        Synergy::Renderer::CanvasRenderer::Initialize(api);
        Synergy::Renderer::Renderer2D::Initialize(api);
        
        Synergy::UI::Renderer::Initialize(api);
    }
}

