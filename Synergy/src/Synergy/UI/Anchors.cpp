// Created by Niels Marsman on 09-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/Anchors.h"

namespace Synergy::UI::Constraint
{
    Synergy::UI::Constraint::Anchors::Anchors() {}

    Synergy::UI::Constraint::Anchors::Anchors(glm::vec2 size) :
        top(Synergy::UI::Constraint::YAxisAnchor(0)),
        bottom(Synergy::UI::Constraint::YAxisAnchor(size.y)),
        left(Synergy::UI::Constraint::XAxisAnchor(0)),
        right(Synergy::UI::Constraint::XAxisAnchor(size.x)),
        width(Synergy::UI::Constraint::DimensionAnchor(size.x)),
        height(Synergy::UI::Constraint::DimensionAnchor(size.y)),
        horizontal(Synergy::UI::Constraint::XAxisAnchor(0)),
        vertical(Synergy::UI::Constraint::YAxisAnchor(0))
    { }
}
