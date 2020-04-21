// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/RendererAPI.h"
#include "Synergy/Renderer/Renderer2D.h"

namespace Synergy::Renderer
{
    void RendererAPI::InitializeRenderers(RendererAPI* api)
    {
        Renderer2D::Initialize(api);
        //Renderer3D::Initialize(this);
    }
}

