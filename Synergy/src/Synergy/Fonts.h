// Created by Niels Marsman on 03-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_FONTS_H
#define SYNERGY_FONTS_H

#include "Synergy/Core.h"

namespace Synergy
{
    class SYNERGY_API Font
    {
        
    };

    class SYNERGY_API Fonts
    {
    public:
        static Synergy::Ref<Synergy::Font> Load(const char* path) { return nullptr; }
    };
}

#endif
