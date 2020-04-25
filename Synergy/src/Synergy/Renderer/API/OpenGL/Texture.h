// Created by Niels Marsman on 25-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_OPENGL_TEXTURE_H
#define SYNERGY_RENDERER_OPENGL_TEXTURE_H

#include <glad/glad.h>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Texture.h"

namespace Synergy::Renderer::OpenGL
{
    class SYNERGY_API Texture: public Synergy::Renderer::Texture
    {
    public:
        Texture(uint32_t width, uint32_t height);
        Texture(const char* path);
        
        virtual ~Texture() = default;
        
        virtual uint32_t GetWidth() const override;
        virtual uint32_t GetHeight() const override;
        
        virtual void SetData(void* data, uint32_t size) override;
        
        virtual void Activate(uint32_t slot) const override;
        virtual void Bind() const override;
        virtual void Unbind() const override;
        
        virtual bool operator==(const Synergy::Renderer::Texture& other) const override;
        
    private:
        uint32_t id;
        uint32_t width, height;
        const char* path;
        
        GLenum internalFormat, dataFormat;
    };
}

#endif
