// Created by Niels Marsman on 25-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_OPENGL_TEXTURE_H
#define SYNERGY_RENDERER_OPENGL_TEXTURE_H

#include <glad/glad.h>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Texture.h"

namespace Synergy::Renderer::OpenGL
{
    class SYNERGY_API Texture: public Synergy::Texture
    {
    public:
        explicit Texture(uint32_t width, uint32_t height, Synergy::Texture::Parameters parameters = {});
        
        virtual ~Texture() = default;
        
        virtual void SetData(void* data, uint32_t size) override;
        
        virtual void Activate(uint32_t slot) const override;
        virtual void Bind() const override;
        virtual void Unbind() const override;
        
        virtual bool operator==(const Synergy::Texture& other) const override;
        
    private:
        static uint32_t GetBitsPerPixel(Synergy::Texture::Format format);
        static GLenum GetInternalFormat(Synergy::Texture::Format format);
        static GLenum GetDataFormat(Synergy::Texture::Format format);
        static GLenum GetFilter(Synergy::Texture::Filter filter);
        static GLenum GetWrap(Synergy::Texture::Wrap wrap);
        
    private:
        uint32_t id;
        GLenum internalFormat, dataFormat;
    };
}

#endif
