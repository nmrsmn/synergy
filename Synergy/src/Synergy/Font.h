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
        struct SYNERGY_API Character
        {
            Synergy::Ref<Synergy::Renderer::Texture> texture;
            glm::vec2 size;
            glm::vec2 bearing;
            uint32_t advance;
        };
        
    private:
        static Synergy::Ref<Synergy::Font> Load(const std::string& path, uint32_t size);
        
    public:
         const Synergy::Font::Character GetCharacter(unsigned char character);
        
    private:
        Font(const std::string& path, uint32_t size);
        
        Synergy::Font::Character Cache(const char character);
        
    private:
        FT_Face face;
        
        std::unordered_map<unsigned char, Synergy::Font::Character> characters;
        
        friend class Fonts;
    };
}

#endif
