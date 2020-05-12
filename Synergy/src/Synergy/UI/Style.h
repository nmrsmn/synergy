// Created by Niels Marsman on 11-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_STYLE_H
#define SYNERGY_UI_STYLE_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Texture.h"

namespace Synergy::UI
{
    struct Style
    {
        struct Background
        {
            glm::vec4 color { 1, 1, 1, 1 };
            Synergy::Ref<Synergy::Texture> texture { nullptr };
            
            Background(glm::vec4 color) : color(color) { }
            Background(Synergy::Ref<Synergy::Texture> texture, glm::vec4 color = { 1, 1, 1, 1 }) : texture(texture), color(color) { }
        };
        
        enum class TextAlignment
        {
            NONE = 0,
            LEFT,
            CENTER,
            RIGHT
        };
        
        enum class Gravity
        {
            NONE = 0,
            TOP,
            CENTER,
            BOTTOM
        };
    };
}

#endif
