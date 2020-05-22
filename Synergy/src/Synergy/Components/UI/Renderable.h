// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_COMPONENT_UI_RENDERABLE_H
#define SYNERGY_COMPONENT_UI_RENDERABLE_H

#include <glm/glm.hpp>

namespace Synergy::UI
{
    struct Background
    {
        glm::vec4 color { 1, 1, 1, 1 };
        Synergy::Ref<Synergy::Texture> texture { nullptr };
        
        Background() {}
        Background(glm::vec4 color) : color(color) {}
        Background(Synergy::Ref<Synergy::Texture> texture) : texture(texture) {}
    };

    struct Button
    {
        struct
        {
            Synergy::UI::Background normal;
            Synergy::UI::Background hover;
            Synergy::UI::Background active;
        } background;
        
        std::function<void (void)> onclick;
    };

    struct Image
    {
        Synergy::Ref<Synergy::Texture> texture;
    };

    struct Text
    {
        enum class Align
        {
            LEFT,
            CENTER,
            RIGHT
        };
        
        std::string text;
        Synergy::UI::Text::Align align = Synergy::UI::Text::Align::LEFT;
    };
}

#endif
