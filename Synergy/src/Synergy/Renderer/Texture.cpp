// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <stb_image.h>

#include "Synergy/Renderer/Texture.h"

#include "Synergy/Application.h"

#include "Synergy/Renderer/RendererAPI.h"
#include "Synergy/Renderer/API/OpenGL.h"

namespace Synergy::Renderer
{
    Synergy::Ref<Texture> Texture::Create(uint32_t width, uint32_t height, Texture::Parameters parameters)
    {
        return Synergy::Application::current->CreateTexture(width, height, parameters);
    }

    Synergy::Ref<Texture> Texture::Load(const char* path, Texture::Parameters parameters)
    {
        int width, height, channels;
        
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path, &width, &height, &channels, 0);
        SYNERGY_ASSERT(data, stbi_failure_reason());
        
        parameters.format = channels == 4 ? Texture::Format::RGBA : Texture::Format::RGB;
        
        Synergy::Ref<Texture> texture = Synergy::Application::current->CreateTexture(width, height, parameters);
        texture->SetData(data, width * height * channels);
        
        stbi_image_free(data);
        
        return texture;
    }

    Texture::Texture(uint32_t width, uint32_t height, Texture::Parameters parameters)
        : width(width), height(height), parameters(parameters) {}
    
    uint32_t Texture::GetWidth() const
    {
        return width;
    }

    uint32_t Texture::GetHeight() const
    {
        return height;
    }

    const std::array<const glm::vec2, 4> Texture::GetUVs() const
    {
        return { glm::vec2 { 0.0f, 0.0f }, glm::vec2 { 1.0f, 0.0f }, glm::vec2 { 1.0f, 1.0f }, glm::vec2 { 0.0f, 1.0f } };
    }
}
