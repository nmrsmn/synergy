// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/Texture.h"

#include "Synergy/Application.h"

#include "Synergy/Renderer/RendererAPI.h"
#include "Synergy/Renderer/API/OpenGL.h"

namespace Synergy::Renderer
{
    Synergy::Ref<Synergy::Renderer::Texture> Texture::Create(uint32_t width, uint32_t height)
    {
        return Synergy::Application::current->CreateTexture(width, height);
    }

    Synergy::Ref<Synergy::Renderer::Texture> Texture::Create(const char* path)
    {
        return Synergy::Application::current->CreateTexture(path);
    }
}
