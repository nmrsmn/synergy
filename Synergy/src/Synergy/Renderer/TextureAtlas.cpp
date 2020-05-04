// Created by Niels Marsman on 02-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/TextureAtlas.h"

namespace Synergy::Renderer
{
    TextureAtlas::Texture::Texture(TextureAtlas* atlas, uint32_t row, uint32_t column)
        : atlas(atlas), row(row), column(column), Synergy::Renderer::Texture(atlas->width, atlas->height) {}

    const std::array<const glm::vec2, 4> TextureAtlas::Texture::GetUVs() const
    {
        glm::vec2 size { 1.0 / atlas->columns, 1.0 / atlas->rows };
        glm::vec2 offset {
            size.x * column,
            ((atlas->rows - 1 - row) * size.y)
        };
        
        return {
            glm::vec2 { offset.x, offset.y },
            glm::vec2 { offset.x + size.x, offset.y },
            glm::vec2 { offset.x + size.x, offset.y + size.y },
            glm::vec2 { offset.x, offset.y + size.y }
        };
    }

    void TextureAtlas::Texture::SetData(void* data, uint32_t size)
    {
        // ASSERT?
    }

    void TextureAtlas::Texture::Activate(uint32_t slot) const
    {
        atlas->texture->Activate(slot);
    }

    void TextureAtlas::Texture::Bind() const
    {
        atlas->texture->Bind();
    }

    void TextureAtlas::Texture::Unbind() const
    {
        atlas->texture->Unbind();
    }

    bool TextureAtlas::Texture::operator==(const Synergy::Renderer::Texture& other) const
    {
        return false;
    }

    Synergy::Ref<TextureAtlas> TextureAtlas::Load(const char* path, uint32_t rows, uint32_t columns, Texture::Parameters parameters)
    {
        struct RefEnabler: public TextureAtlas
        {
            explicit RefEnabler(Synergy::Ref<Synergy::Renderer::Texture> texture, uint32_t rows, uint32_t columns): TextureAtlas(texture, rows, columns) {}
        };
        
        Synergy::Ref<Synergy::Renderer::Texture> texture = Synergy::Renderer::Texture::Load(path, parameters);
        return Synergy::CreateRef<RefEnabler>(texture, rows, columns);
    }

    const Synergy::Ref<TextureAtlas::Texture> TextureAtlas::GetTexture(uint32_t row, uint32_t column) const
    {
        return textures[(row * width) + column];
    }

    const Synergy::Ref<TextureAtlas::Texture> TextureAtlas::operator()(uint32_t row, uint32_t column) const
    {
        return this->GetTexture(row, column);
    }
    
    TextureAtlas::TextureAtlas(Synergy::Ref<Synergy::Renderer::Texture> texture, uint32_t rows, uint32_t columns)
        : texture(texture), rows(rows), columns(columns)
    {
        width = texture->GetWidth() / columns;
        height = texture->GetHeight() / rows;
        
        SYNERGY_ASSERT(width == height, "Only sqaure texture atlas cells are supported.");
        
        textures.resize(width * height);
        for (int row = 0; row < rows; ++row)
        {
            for (int column = 0; column < columns; ++column)
            {
                textures[(row * width) + column] = Synergy::CreateRef<TextureAtlas::Texture>(this, row, column);
            }
        }
    }
}
