// Created by Niels Marsman on 03-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_FONTS_H
#define SYNERGY_FONTS_H

#include <unordered_map>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Synergy/Core.h"

namespace Synergy
{
    class Font;

    class SYNERGY_API Fonts
    {
    public:
        static Synergy::Ref<Synergy::Font> Load(const std::string& path, uint32_t size);
        
    private:
        static Fonts& Instance();
        
    public:
        Fonts(const Fonts&) = delete;
        Fonts& operator=(const Fonts&) = delete;
        
        ~Fonts();
        
    private:
        Fonts();
        
        Synergy::Ref<Synergy::Font> LoadFont(const std::string& path, uint32_t size);
        
    private:
        FT_Library library;
        
        std::unordered_map<std::string, Synergy::Ref<Synergy::Font>> fonts;
        
        friend class Synergy::Font;
    };
}

#endif
