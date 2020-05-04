// Created by Niels Marsman on 03-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Fonts.h"
#include "Synergy/Font.h"

namespace Synergy
{
    Synergy::Ref<Synergy::Font> Fonts::Load(const std::string& path, uint32_t size)
    {
        return Instance().LoadFont(path, size);
    }
    
    Fonts& Fonts::Instance()
    {
        static Fonts instance;
        return instance;
    }
    
    Fonts::Fonts()
    {
        if (FT_Init_FreeType(&library))
        {
            SYNERGY_ASSERT(false, "Failed to initialize FreeType library.");
        }
    }

    Fonts::~Fonts()
    {
        FT_Done_FreeType(library);
    }

    Synergy::Ref<Synergy::Font> Fonts::LoadFont(const std::string& path, uint32_t size)
    {
        std::string name = path + ":" + std::to_string(size);
        
        if (auto font { fonts.find(name) }; font != fonts.end())
        {
            return font->second;
        }
        
        fonts[name] = Synergy::Font::Load(path, size);
        return fonts[name];
    }
}
