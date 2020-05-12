// Created by Niels Marsman on 11-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_RENDERABLE_H
#define SYNERGY_UI_RENDERABLE_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/Fonts.h"
#include "Synergy/Renderer/Texture.h"

namespace Synergy::UI
{
    struct SYNERGY_API Renderable
    {
        glm::vec3 position;
        glm::vec2 size;
        glm::vec4 color;
    };

    struct SYNERGY_API Quad: public Synergy::UI::Renderable
    {
        Synergy::Ref<Synergy::Texture> texture;
        float radius;
    };

    struct SYNERGY_API Text: public Synergy::UI::Renderable
    {
        const std::string& text;
        Synergy::Ref<Synergy::Font> font;
        float scale;
    };
}

#endif
