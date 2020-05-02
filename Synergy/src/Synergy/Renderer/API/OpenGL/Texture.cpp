// Created by Niels Marsman on 25-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/API/OpenGL/Texture.h"

namespace Synergy::Renderer::OpenGL
{
    Texture::Texture(uint32_t width, uint32_t height, Texture::Parameters parameters): Synergy::Renderer::Texture(width, height, parameters)
    {
        internalFormat = Texture::GetInternalFormat(parameters.format);
        dataFormat = Texture::GetDataFormat(parameters.format);
        
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Texture::GetFilter(parameters.filter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Texture::GetFilter(parameters.filter));
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Texture::GetWrap(parameters.wrap));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Texture::GetWrap(parameters.wrap));
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

    uint32_t Texture::GetBitsPerPixel(Texture::Format format)
    {
        switch (format)
        {
            case Texture::Format::RGB: return 3;
            case Texture::Format::RGBA: return 4;
            default: SYNERGY_ASSERT(false, "Unsupported texture format.");
        }
    }

    GLenum Texture::GetInternalFormat(Texture::Format format)
    {
        switch (format)
        {
            case Texture::Format::RGB: return GL_RGB8;
            case Texture::Format::RGBA: return GL_RGBA8;
            default: SYNERGY_ASSERT(false, "Unsupported internal texture format.");
        }
    }

    GLenum Texture::GetDataFormat(Texture::Format format)
    {
        switch (format)
        {
            case Texture::Format::RGB: return GL_RGB;
            case Texture::Format::RGBA: return GL_RGBA;
            default: SYNERGY_ASSERT(false, "Unsupported data texture format.");
        }
    }

    GLenum Texture::GetFilter(Texture::Filter filter)
    {
        switch (filter)
        {
            case Texture::Filter::LINEAR: return GL_LINEAR;
            case Texture::Filter::NEAREST: return GL_NEAREST;
            default: SYNERGY_ASSERT(false, "Unsupported texture filter.");
        }
    }

    GLenum Texture::GetWrap(Texture::Wrap wrap)
    {
        switch (wrap)
        {
            case Texture::Wrap::REPEAT: return GL_REPEAT;
            case Texture::Wrap::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
            case Texture::Wrap::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
            case Texture::Wrap::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
            default: SYNERGY_ASSERT(false, "Unsupported wrap mode.");
        }
    }
}
