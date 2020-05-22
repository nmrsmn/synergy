// Created by Niels Marsman on 25-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_TEXTURE_H
#define SYNERGY_RENDERER_TEXTURE_H

#include <array>

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Bindable.h"

namespace Synergy
{
    class SYNERGY_API Texture: public Synergy::Renderer::Bindable
    {
    public:
        enum class Filter
        {
            LINEAR,
            NEAREST
        };
        
        enum class Format
        {
            RED,
            ALPHA,
            RGB,
            RGBA
        };
        
        enum class Wrap
        {
            REPEAT,
            MIRRORED_REPEAT,
            MIRROR_ONCE,
            CLAMP_TO_EDGE,
            CLAMP_TO_BORDER
        };
        
        struct Parameters
        {
            struct Filter
            {
                Synergy::Texture::Filter minify = Synergy::Texture::Filter::NEAREST;
                Synergy::Texture::Filter magnify = Synergy::Texture::Filter::NEAREST;
                
                Filter() { }
                Filter(Synergy::Texture::Filter filter) : minify(filter), magnify(filter) { }
                Filter(Synergy::Texture::Filter minify, Synergy::Texture::Filter magnify) : minify(minify), magnify(magnify) { }
            };
            
            struct Wrap
            {
                union { Synergy::Texture::Wrap u, s; };
                union { Synergy::Texture::Wrap v, t; };
                
                Wrap(): u(Synergy::Texture::Wrap::CLAMP_TO_EDGE), v(Synergy::Texture::Wrap::CLAMP_TO_EDGE) { }
                Wrap(Synergy::Texture::Wrap wrap): u(wrap), v(wrap) { }
                Wrap(Synergy::Texture::Wrap u, Synergy::Texture::Wrap v): u(u), v(v) { }
            };
            
            Synergy::Texture::Parameters::Filter filter = {};
            Synergy::Texture::Parameters::Wrap wrap = {};
            Synergy::Texture::Format format = Synergy::Texture::Format::RGBA;
            
            Parameters() { }
            Parameters(Synergy::Texture::Parameters::Filter filter) : filter(filter) { }
            Parameters(Synergy::Texture::Parameters::Filter filter, Synergy::Texture::Parameters::Wrap wrap): filter(filter), wrap(wrap) { }
            Parameters(Synergy::Texture::Parameters::Filter filter, Synergy::Texture::Parameters::Wrap wrap, Synergy::Texture::Format format): filter(filter), format(format), wrap(wrap) { }
        };
        
    public:
        static Synergy::Ref<Synergy::Texture> Create(uint32_t width, uint32_t height, Synergy::Texture::Parameters parameters = {});
        static Synergy::Ref<Synergy::Texture> Create(uint32_t width, uint32_t height, const void* data, Synergy::Texture::Parameters parameters = {});
        static Synergy::Ref<Synergy::Texture> Load(const char* path, Synergy::Texture::Parameters parameters = {});
    
    public:
        virtual ~Texture() = default;
        
        const uint32_t GetWidth() const;
        const uint32_t GetHeight() const;
        
        const bool HasTransparancy() const;
        
        virtual const glm::vec2* GetUVs() const;
        
        virtual void SetData(void* data, uint32_t size) = 0;
        
        virtual void Activate(uint32_t slot) const = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        virtual bool operator==(const Synergy::Texture& other) const = 0;
        
    protected:
        Texture(uint32_t width, uint32_t height, Synergy::Texture::Parameters parameters = {});
        
    protected:
        uint32_t width;
        uint32_t height;
        
        bool m_HasTransparancy = false;
        
        Texture::Parameters parameters;
    };
}

#endif
