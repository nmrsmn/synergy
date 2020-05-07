// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/RendererAPI.h"

#include "Synergy/Renderer/CanvasRenderer.h"
#include "Synergy/Renderer/Renderer2D.h"

namespace Synergy::Renderer
{
    Synergy::Renderer::RendererAPI::API RendererAPI::Get()
    {
        return api;
    }

    void RendererAPI::InitializeRenderers(RendererAPI* api)
    {
        CanvasRenderer::Initialize(api);
        Renderer2D::Initialize(api);
    }
}

