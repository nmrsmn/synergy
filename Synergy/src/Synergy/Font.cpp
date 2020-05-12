// Created by Niels Marsman on 03-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <algorithm>

#include "Synergy/Font.h"

namespace Synergy
{
    Synergy::Ref<Synergy::Font> Font::Load(const std::string& path, uint32_t size)
    {
        struct RefEnabler: public Font
        {
            explicit RefEnabler(const std::string& path, uint32_t size): Font(path, size) {}
        };
        
        return Synergy::CreateRef<RefEnabler>(path, size);
    }

    const Synergy::Font::Glyph Font::GetCharacter(uint16_t character)
    {
        if (auto entry { glyphs.find(character) }; entry != glyphs.end())
        {
            return entry->second;
        }
        
        SYNERGY_ASSERT(false, "Failed to get character data.");
    }

    const Synergy::Ref<Synergy::Texture> Font::Texture() const
    {
        return texture;
    }

    const uint32_t Font::Size() const
    {
        return size;
    }

    Font::Font(const std::string& path, uint32_t size) : size(size)
    {
        if (FT_New_Face(Synergy::Fonts::Instance().library, path.c_str(), 0, &face) != 0)
        {
            SYNERGY_ASSERT(false, "Failed to load font.");
            return;
        }
        
        FT_Set_Pixel_Sizes(face, 0, size);
        
        for (int character = 32; character < 128; ++character)
        {
            if (FT_Load_Char(face, character, FT_LOAD_RENDER) != 0)
            {
                SYNERGY_ASSERT(false, "Failed to load glyph.");
                continue;
            }
            
            width += face->glyph->bitmap.width + 10;
            height = std::max(height, face->glyph->bitmap.rows);
        }
        
        texture = Synergy::Texture::Create(width, height, {
            Synergy::Texture::Filter::LINEAR,
            Synergy::Texture::Wrap::CLAMP_TO_EDGE,
            Synergy::Texture::Format::RED,
            Synergy::Texture::UnpackAlignment::ONE
        });
        
        glm::vec2 offset = { 0, 0 };
        
        for (int character = 32; character < 128; character++)
        {
            if (FT_Load_Char(face, character, FT_LOAD_RENDER))
                continue;
            
            glm::vec2 size = { (int) face->glyph->bitmap.width, (int) face->glyph->bitmap.rows };
            
            texture->SetSubData(face->glyph->bitmap.buffer, offset, size);
            
            Synergy::Font::Glyph glyph;
            glyph.size.width = face->glyph->bitmap.width;
            glyph.size.height = face->glyph->bitmap.rows;
            
            glyph.advance.x = face->glyph->advance.x;
            glyph.advance.y = face->glyph->advance.y;
            
            glyph.bearing.top = face->glyph->bitmap_top;
            glyph.bearing.left = face->glyph->bitmap_left;
            
            glyph.texture.x = offset.x / (float) width;
            glyph.texture.y = offset.y;
            
            this->glyphs.insert(std::pair<char, Synergy::Font::Glyph> (character, glyph));
            
            offset.x += face->glyph->bitmap.width + 10;
        }
        
        FT_Done_Face(face);
    }
}
