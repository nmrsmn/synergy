// Created by Niels Marsman on 25-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/API/OpenGL/Texture.h"

#include <stb_image.h>

namespace Synergy::Renderer::OpenGL
{
    Texture::Texture(uint32_t width, uint32_t height)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
        
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        glTextureStorage2D(id, 1, internalFormat, width, height);
        
        glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    Texture::Texture(const char* path): path(path)
    {
        int width, height, channels;
        
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path, &width, &height, &channels, 0);
        SYNERGY_ASSERT(data, "Failed to load image!");
        
        this->width = width;
        this->height = height;
        
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        
        SYNERGY_ASSERT(internalFormat & dataFormat, "Format not supported!");
        
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        glTextureStorage2D(id, 1, internalFormat, width, height);

        glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(id, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    
    uint32_t Texture::GetWidth() const
    {
        return width;
    }

    uint32_t Texture::GetHeight() const
    {
        return height;
    }
    
    void Texture::SetData(void* data, uint32_t size)
    {
        uint32_t bitsPerPixel = dataFormat == GL_RGBA ? 4 : 3;
        SYNERGY_ASSERT(size == width * height * bitsPerPixel, "Data must be the entire texture!");
        
        glTextureSubImage2D(id, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
    }
    
    void Texture::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, id);
    }
    
    bool Texture::operator==(const Synergy::Renderer::Texture& other) const
    {
        return id == ((Texture&) other).id;
    }
}
