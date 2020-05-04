// Created by Niels Marsman on 02-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_TEXTURE_ATLAS_H
#define SYNERGY_RENDERER_TEXTURE_ATLAS_H

#include <vector>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Texture.h"

namespace Synergy::Renderer
{
    class SYNERGY_API TextureAtlas
    {
    public:
        class SYNERGY_API Texture: public Synergy::Renderer::Texture
        {
        public:
            explicit Texture(TextureAtlas* atlas, uint32_t row, uint32_t column);
            
            virtual ~Texture() = default;
            
            virtual const std::array<const glm::vec2, 4> GetUVs() const override;
            
            virtual void SetData(void* data, uint32_t size) override;
            
            virtual void Activate(uint32_t slot) const override;
            virtual void Bind() const override;
            virtual void Unbind() const override;
            
            virtual bool operator==(const Synergy::Renderer::Texture& other) const override;
            
        private:
            TextureAtlas* atlas;
            
            uint32_t column;
            uint32_t row;
        };
        
    public:
        static Synergy::Ref<TextureAtlas> Load(const char* path, uint32_t rows, uint32_t columns, Texture::Parameters parameters = Texture::Parameters());
        
    public:
        const Synergy::Ref<TextureAtlas::Texture> GetTexture(uint32_t rows, uint32_t columns) const;
        const Synergy::Ref<TextureAtlas::Texture> operator()(uint32_t rows, uint32_t columns) const;
        
    private:
        TextureAtlas(Synergy::Ref<Synergy::Renderer::Texture> texture, uint32_t rows, uint32_t columns);
        
    private:
        uint32_t columns;
        uint32_t rows;
        
        uint32_t width;
        uint32_t height;
        
        Synergy::Ref<Synergy::Renderer::Texture> texture;
        std::vector<Synergy::Ref<TextureAtlas::Texture>> textures;
    };
}

#endif
