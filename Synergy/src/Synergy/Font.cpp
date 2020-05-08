// Created by Niels Marsman on 03-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

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

    const Synergy::Font::Character Font::GetCharacter(unsigned char character)
    {
        if (auto entry { characters.find(character) }; entry != characters.end())
        {
            return entry->second;
        }
        
        SYNERGY_ASSERT(false, "Failed to get character data.");
    }

    Font::Font(const std::string& path, uint32_t size)
    {
        if (FT_New_Face(Synergy::Fonts::Instance().library, path.c_str(), 0, &face) != 0)
        {
            SYNERGY_ASSERT(false, "Failed to load font.");
        }
        
        FT_Set_Pixel_Sizes(face, 0, size);
        
        for (unsigned char character = 0; character < 128; ++character)
        {
            if (this->characters.find(character) != this->characters.end())
                continue;
            
            this->Cache(character);
        }
        
        FT_Done_Face(face);
    }

    Synergy::Font::Character Font::Cache(const char character)
    {
        if (FT_Load_Char(face, character, FT_LOAD_RENDER) != 0)
        {
            SYNERGY_ASSERT(false, "Failed to load glyph.");
        }
        
        Synergy::Texture::Parameters parameters = {
            Synergy::Texture::Filter::LINEAR,
            Synergy::Texture::Wrap::CLAMP_TO_EDGE,
            Synergy::Texture::Format::RED
        };
        
        Synergy::Ref<Synergy::Texture> texture = Synergy::Texture::Create(face->glyph->bitmap.width, face->glyph->bitmap.rows, parameters);
        texture->SetData(face->glyph->bitmap.buffer, face->glyph->bitmap.width * face->glyph->bitmap.rows);
        
        Character instance = {
            texture,
            glm::ivec2 { face->glyph->bitmap.width, face->glyph->bitmap.rows },
            glm::ivec2 { face->glyph->bitmap_left, face->glyph->bitmap_top },
            (uint32_t) face->glyph->advance.x
        };
        
        this->characters.insert(std::pair<char, Synergy::Font::Character> (character, instance));
        
        return instance;
    }
}
