// Created by Niels Marsman on 25-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_TEXTURE_H
#define SYNERGY_RENDERER_TEXTURE_H

#include <array>

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Bindable.h"

namespace Synergy::Renderer
{
    class SYNERGY_API Texture: public Bindable
    {
    public:
        enum class Wrap
        {
            NONE = 0,
            REPEAT,
            MIRRORED_REPEAT,
            CLAMP_TO_EDGE,
            CLAMP_TO_BORDER
        };
        
        enum class Filter
        {
            NONE = 0,
            LINEAR,
            NEAREST
        };
        
        enum class Format
        {
            NONE = 0,
            RED,
            ALPHA,
            RGB,
            RGBA
        };
        
        struct Parameters
        {
            Texture::Filter filter = Texture::Filter::NEAREST;
            Texture::Format format = Texture::Format::RGBA;
            Texture::Wrap wrap = Texture::Wrap::CLAMP_TO_EDGE;
            
            Parameters() {}
            Parameters(Texture::Filter filter)
                : filter(filter) {}
            Parameters(Texture::Filter filter, Texture::Wrap wrap)
                : filter(filter), wrap(wrap) {}
            Parameters(Texture::Format format, Texture::Filter filter, Texture::Wrap wrap)
                : format(format), filter(filter), wrap(wrap) {}
        };
        
    public:
        static Ref<Texture> Create(uint32_t width, uint32_t height, Texture::Parameters parameters = Texture::Parameters());
        static Ref<Texture> Load(const char* path, Texture::Parameters parameters = Texture::Parameters());
        
    public:
        Texture(uint32_t width, uint32_t height, Texture::Parameters parameters = Texture::Parameters());
        virtual ~Texture() = default;
        
        uint32_t GetWidth() const;
        uint32_t GetHeight() const;
        
        virtual const std::array<const glm::vec2, 4> GetUVs() const;
        
        virtual void SetData(void* data, uint32_t size) = 0;
        
        virtual void Activate(uint32_t slot) const = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        virtual bool operator==(const Texture& other) const = 0;
        
    protected:
        uint32_t width;
        uint32_t height;
        
        Texture::Parameters parameters;
    };
}

#endif
