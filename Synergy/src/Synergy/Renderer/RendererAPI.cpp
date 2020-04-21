// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/RendererAPI.h"
#include "Synergy/Renderer/RenderCommand.h"

namespace Synergy::Renderer
{
    RendererAPI::RendererAPI()
    {
        RenderCommand::Instance().api = this;
    }
}

