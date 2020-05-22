// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <stb_image.h>

#include "Synergy/Renderer/Texture.h"

#include "Synergy/Application.h"

#include "Synergy/Renderer/RendererAPI.h"
#include "Synergy/Renderer/API/OpenGL.h"
#include "Synergy/Renderer/API/OpenGL/Texture.h"

namespace Synergy
{
    Synergy::Ref<Synergy::Texture> Texture::Create(uint32_t width, uint32_t height, Synergy::Texture::Parameters parameters)
    {
        switch (Synergy::Renderer::RendererAPI::Get())
        {
            case Synergy::Renderer::RendererAPI::API::OpenGL:
                struct RefEnabler: public Synergy::Renderer::OpenGL::Texture
                {
                    explicit RefEnabler(uint32_t width, uint32_t height, Synergy::Texture::Parameters parameters): Synergy::Renderer::OpenGL::Texture(width, height, parameters) { }
                };
                
                return Synergy::CreateRef<RefEnabler>(width, height, parameters);
            default: break;
        }
        
        SYNERGY_ASSERT(false, "Textures aren't supported in the currently selected RendererAPI.");
        return nullptr;
    }

    Synergy::Ref<Synergy::Texture> Texture::Load(const char* path, Synergy::Texture::Parameters parameters)
    {
        int width, height, channels;
        bool transparancy = false;
        
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path, &width, &height, &channels, 0);
        SYNERGY_ASSERT(data, stbi_failure_reason());
        
        parameters.format = channels == 4 ? Synergy::Texture::Format::RGBA : Synergy::Texture::Format::RGB;
        
        if (channels == 4)
        {
            for (int index = 0; index < width * height; ++index)
            {
                if (data[index * 4 + 3] != 255)
                {
                    transparancy = true;
                    break;
                }
            }
        }
        
        Synergy::Ref<Texture> texture = Synergy::Texture::Create(width, height, parameters);
        texture->SetData(data, width * height * channels);
        texture->m_HasTransparancy = transparancy;
        
        stbi_image_free(data);
        
        return texture;
    }

    Texture::Texture(uint32_t width, uint32_t height, Texture::Parameters parameters)
        : width(width), height(height), parameters(parameters) { }
    
    const uint32_t Texture::GetWidth() const
    {
        return width;
    }

    const uint32_t Texture::GetHeight() const
    {
        return height;
    }

    const bool Texture::HasTransparancy() const
    {
        return m_HasTransparancy;
    }
    
    const glm::vec2* Texture::GetUVs() const
    {
        static constexpr glm::vec2 uvs[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        
        return uvs;
    }
}
