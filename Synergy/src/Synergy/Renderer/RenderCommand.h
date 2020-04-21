// Created by Niels Marsman on 21-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_RNDER_COMMAND_H
#define SYNERGY_RENDERER_RNDER_COMMAND_H

#include "Synergy/Core.h"
#include "Synergy/Renderer/RendererAPI.h"

namespace Synergy::Renderer
{
    class SYNERGY_API RenderCommand
    {
    private:
        static RenderCommand& Instance();
        
    public:
        RenderCommand(const RenderCommand&) = delete;
        RenderCommand& operator=(const RenderCommand&) = delete;
        
        static void DrawIndexed(const Ref<VertexArray>& vertexArray);
        
    private:
        RenderCommand() {}
        
    private:
        RendererAPI* api;
        
        friend class Renderer::RendererAPI;
    };
}

#endif
