// Created by Niels Marsman on 09-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/Anchor/YAxisAnchor.h"

namespace Synergy::UI::Constraint
{
    void Synergy::UI::Constraint::YAxisAnchor::equals(Synergy::UI::Constraint::YAxisAnchor other)
    {
        value = other.value;
        activated = true;
    }

    void Synergy::UI::Constraint::YAxisAnchor::equals(Synergy::UI::Constraint::YAxisAnchor other, int constant)
    {
        value = other.value + constant;
        activated = true;
    }

    Synergy::UI::Constraint::YAxisAnchor::YAxisAnchor() : Synergy::UI::Constraint::Anchor<YAxisAnchor>() { }

    Synergy::UI::Constraint::YAxisAnchor::YAxisAnchor(float value) : Synergy::UI::Constraint::Anchor<YAxisAnchor>(value) { }
}
