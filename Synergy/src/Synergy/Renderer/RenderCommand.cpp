// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/RenderCommand.h"

namespace Synergy::Renderer
{
    RenderCommand& RenderCommand::Instance()
    {
        static RenderCommand instance;
        return instance;
    }
    
    void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
    {
        Instance().api->DrawIndexed(vertexArray);
    }
}

