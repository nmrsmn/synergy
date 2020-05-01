// Created by Niels Marsman on 25-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/API/OpenGL/Texture.h"

#include <stb_image.h>

namespace Synergy::Renderer::OpenGL
{
    Texture::Texture(uint32_t width, uint32_t height): width(width), height(height)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
        
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    Texture::Texture(const char* path): path(path)
    {
        int width, height, channels;
        
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path, &width, &height, &channels, 0);
        SYNERGY_ASSERT(data, stbi_failure_reason());
        
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
        
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
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
        
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void Texture::Activate(uint32_t slot) const
    {
        SYNERGY_ASSERT(slot < 16, "Only 16 texture slots supported");
        glActiveTexture(GL_TEXTURE0 + slot);
    }
    
    void Texture::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Texture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    bool Texture::operator==(const Synergy::Renderer::Texture& other) const
    {
        return id == ((Texture&) other).id;
    }
}
