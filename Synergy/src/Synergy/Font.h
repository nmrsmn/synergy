// Created by Niels Marsman on 03-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_FONT_H
#define SYNERGY_FONT_H

#include <unordered_map>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Synergy/Core.h"
#include "Synergy/Fonts.h"
#include "Synergy/Renderer/Texture.h"

namespace Synergy
{
    class SYNERGY_API Font
    {
    public:
        struct SYNERGY_API Glyph
        {
            struct {
                uint16_t width = 0;
                uint16_t height = 0;
            } size;
            
            struct {
                uint16_t x = 0;
                uint16_t y = 0;
            } advance;
            
            struct {
                float top = 0;
                float left = 0;
            } bearing;
            
            struct {
                float x = 0;
                float y = 0;
            } texture;
        };
        
    private:
        static Synergy::Ref<Synergy::Font> Load(const std::string& path, uint32_t size);
        
    public:
        const Synergy::Font::Glyph GetCharacter(uint16_t character);
        const Synergy::Ref<Synergy::Texture> Texture() const;
        
        const uint32_t Size() const;
        
    private:
        Font(const std::string& path, uint32_t size);
        
    private:
        Synergy::Ref<Synergy::Texture> texture;
        
        FT_Face face;
        uint32_t size;
        
        uint32_t width = 0;
        uint32_t height = 0;
        
        std::unordered_map<uint16_t, Synergy::Font::Glyph> glyphs;
        
        friend class Fonts;
    };
}

#endif
