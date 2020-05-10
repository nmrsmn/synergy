// Created by Niels Marsman on 09-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_CONSTRAINT_ANCHORS_H
#define SYNERGY_UI_CONSTRAINT_ANCHORS_H

#include <variant>

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/UI/Anchor.h"
#include "Synergy/UI/Anchor/DimensionAnchor.h"
#include "Synergy/UI/Anchor/XAxisAnchor.h"
#include "Synergy/UI/Anchor/YAxisAnchor.h"

namespace Synergy::UI
{
    class View;
}

namespace Synergy::UI::Constraint
{
    typedef std::variant<Synergy::UI::Constraint::XAxisAnchor, Synergy::UI::Constraint::YAxisAnchor, Synergy::UI::Constraint::DimensionAnchor> AnyAnchor;
        
    struct Anchors
    {
    public:
        Anchors();
        
    private:
        Anchors(glm::vec2 size);
        
    public:
        Synergy::UI::Constraint::YAxisAnchor top;
        Synergy::UI::Constraint::YAxisAnchor bottom;
        Synergy::UI::Constraint::XAxisAnchor left;
        Synergy::UI::Constraint::XAxisAnchor right;
        
        Synergy::UI::Constraint::XAxisAnchor horizontal;
        Synergy::UI::Constraint::YAxisAnchor vertical;
        
        Synergy::UI::Constraint::DimensionAnchor width;
        Synergy::UI::Constraint::DimensionAnchor height;
        
        friend class Synergy::UI::View;
    };
}

#endif
