// Created by Niels Marsman on 02-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/TextureAtlas.h"

namespace Synergy
{
    Synergy::Ref<Synergy::TextureAtlas::Texture> Synergy::TextureAtlas::Texture::Load(Synergy::Ref<Synergy::TextureAtlas> atlas, const glm::uvec2& coordinates, const glm::uvec2& tiles)
    {
        struct RefEnabler: public Synergy::TextureAtlas::Texture
        {
            explicit RefEnabler(Synergy::Ref<Synergy::TextureAtlas> atlas, const glm::vec2& min, const glm::vec2& max): Synergy::TextureAtlas::Texture(atlas, min, max) {}
        };
        
        glm::vec2 min = {
            (coordinates.x * atlas->tile.x) / (float) atlas->texture->GetWidth(),
            1 - (((coordinates.y + 1) * atlas->tile.y) / (float) atlas->texture->GetHeight())
        };
        
        glm::vec2 max = {
            ((coordinates.x + tiles.x) * atlas->tile.x) / (float) atlas->texture->GetWidth(),
            1 - (((coordinates.y + 1 - tiles.y) * atlas->tile.y) / (float) atlas->texture->GetHeight())
        };
        
        return Synergy::CreateRef<RefEnabler>(atlas, min, max);
    }

    const glm::vec2* Synergy::TextureAtlas::Texture::GetUVs() const
    {
        return uvs;
    }

    void Synergy::TextureAtlas::Texture::Activate(uint32_t slot) const
    {
        atlas->texture->Activate(slot);
    }

    void Synergy::TextureAtlas::Texture::Bind() const
    {
        atlas->texture->Bind();
    }

    void Synergy::TextureAtlas::Texture::Unbind() const
    {
        atlas->texture->Unbind();
    }

    bool Synergy::TextureAtlas::Texture::operator==(const Synergy::Texture& other) const
    {
        return false;
    }

    Synergy::TextureAtlas::Texture::Texture(Synergy::Ref<Synergy::TextureAtlas> atlas, const glm::vec2& min, const glm::vec2& max)
        : atlas(atlas), Synergy::Texture(atlas->atlas.x, atlas->atlas.y)
    {
        uvs[0] = { min.x, min.y };
        uvs[1] = { max.x, min.y };
        uvs[2] = { max.x, max.y };
        uvs[3] = { min.x, max.y };
    }

    void Synergy::TextureAtlas::Texture::SetData(void* data, uint32_t size)
    {
        SYNERGY_ASSERT(false, "Data can't be set on a TextureAtlas::Texture");
    }

    void Synergy::TextureAtlas::Texture::SetSubData(void* data, glm::uvec2 offset, glm::uvec2 size)
    {
        SYNERGY_ASSERT(false, "SubData can't be set on a TextureAtlas::Texture");
    }
    
    Synergy::Ref<TextureAtlas> TextureAtlas::Load(const char* path, const glm::uvec2& size, Synergy::Texture::Parameters parameters)
    {
        struct RefEnabler: public TextureAtlas
        {
            explicit RefEnabler(Synergy::Ref<Synergy::Texture> texture, const glm::uvec2& size): TextureAtlas(texture, size) {}
        };
        
        Synergy::Ref<Synergy::Texture> texture = Synergy::Texture::Load(path, parameters);
        return Synergy::CreateRef<RefEnabler>(texture, size);
    }
    
    TextureAtlas::TextureAtlas(Synergy::Ref<Synergy::Texture> texture, const glm::uvec2& size)
        : texture(texture), atlas(size)
    {
        tile = glm::uvec2 {
            texture->GetWidth() / atlas.x,
            texture->GetHeight() / atlas.y
        };
        
        SYNERGY_ASSERT(tile.x == tile.y, "Only sqaure texture atlas cells are supported.");
    }
}
