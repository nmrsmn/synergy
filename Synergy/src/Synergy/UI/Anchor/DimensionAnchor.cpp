// Created by Niels Marsman on 09-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/Anchor/DimensionAnchor.h"

namespace Synergy::UI::Constraint
{
    void Synergy::UI::Constraint::DimensionAnchor::equals(Synergy::UI::Constraint::DimensionAnchor other)
    {
        value = other.value;
        activated = true;
    }

    void Synergy::UI::Constraint::DimensionAnchor::equals(Synergy::UI::Constraint::DimensionAnchor other, int constant)
    {
        value = other.value + constant;
        activated = true;
    }

    void Synergy::UI::Constraint::DimensionAnchor::equals(Synergy::UI::Constraint::DimensionAnchor other, float multiplier, int constant)
    {
        value = other.value * multiplier + constant;
        activated = true;
    }

    Synergy::UI::Constraint::DimensionAnchor::DimensionAnchor() : Synergy::UI::Constraint::Anchor<DimensionAnchor>() { }
    
    Synergy::UI::Constraint::DimensionAnchor::DimensionAnchor(float value) : Synergy::UI::Constraint::Anchor<DimensionAnchor>(value) { }
}
