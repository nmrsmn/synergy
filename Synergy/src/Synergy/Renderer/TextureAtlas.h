// Created by Niels Marsman on 02-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_TEXTURE_ATLAS_H
#define SYNERGY_RENDERER_TEXTURE_ATLAS_H

#include <vector>

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Texture.h"

namespace Synergy
{
    class SYNERGY_API TextureAtlas
    {
    public:
        class SYNERGY_API Texture: public Synergy::Texture
        {
        public:
            static Synergy::Ref<Synergy::TextureAtlas::Texture> Load(Synergy::Ref<Synergy::TextureAtlas> atlas, const glm::uvec2& coordinates, const glm::uvec2& tiles = { 1, 1 });
            
        public:
            virtual ~Texture() = default;
            
            virtual const glm::vec2* GetUVs() const override;
            
            virtual void Activate(uint32_t slot) const override;
            virtual void Bind() const override;
            virtual void Unbind() const override;
            
            virtual bool operator==(const Synergy::Texture& other) const override;
            
        private:
            Texture(Synergy::Ref<Synergy::TextureAtlas> atlas, const glm::vec2& min, const glm::vec2& max);

            virtual void SetData(void* data, uint32_t size) override;
            virtual void SetSubData(void* data, glm::uvec2 offset, glm::uvec2 size) override;
                
        private:
            Synergy::Ref<Synergy::TextureAtlas> atlas;
            glm::vec2 uvs[4];
        };
        
    public:
        static Synergy::Ref<TextureAtlas> Load(const char* path, const glm::uvec2& size, Synergy::Texture::Parameters parameters = {});
        
    private:
        TextureAtlas(Synergy::Ref<Synergy::Texture> texture, const glm::uvec2& size);
        
    private:
        glm::uvec2 atlas;
        glm::uvec2 tile;
        
        Synergy::Ref<Synergy::Texture> texture;
    };
}

#endif
