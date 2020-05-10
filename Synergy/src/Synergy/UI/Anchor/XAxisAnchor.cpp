// Created by Niels Marsman on 09-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/Anchor/XAxisAnchor.h"

namespace Synergy::UI::Constraint
{
    void Synergy::UI::Constraint::XAxisAnchor::equals(Synergy::UI::Constraint::XAxisAnchor other)
    {
        value = other.value;
        activated = true;
    }

    void Synergy::UI::Constraint::XAxisAnchor::equals(Synergy::UI::Constraint::XAxisAnchor other, int constant)
    {
        value = other.value + constant;
        activated = true;
    }

    Synergy::UI::Constraint::XAxisAnchor::XAxisAnchor() : Synergy::UI::Constraint::Anchor<XAxisAnchor>() { }

    Synergy::UI::Constraint::XAxisAnchor::XAxisAnchor(float value) : Synergy::UI::Constraint::Anchor<XAxisAnchor>(value) { }
}
