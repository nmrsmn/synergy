// Created by Niels Marsman on 09-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/Anchor.h"

#include "Synergy/UI/Anchor/DimensionAnchor.h"
#include "Synergy/UI/Anchor/XAxisAnchor.h"
#include "Synergy/UI/Anchor/YAxisAnchor.h"

namespace Synergy::UI::Constraint
{
    template<>
    float Anchor<Synergy::UI::Constraint::DimensionAnchor>::Value() const
    {
        return value;
    }

    template<>
    float Anchor<Synergy::UI::Constraint::XAxisAnchor>::Value() const
    {
        return value;
    }

    template<>
    float Anchor<Synergy::UI::Constraint::YAxisAnchor>::Value() const
    {
        return value;
    }

    template<>
    bool Anchor<Synergy::UI::Constraint::DimensionAnchor>::Activated() const
    {
        return activated;
    }

    template<>
    bool Anchor<Synergy::UI::Constraint::XAxisAnchor>::Activated() const
    {
        return activated;
    }

    template<>
    bool Anchor<Synergy::UI::Constraint::YAxisAnchor>::Activated() const
    {
        return activated;
    }

    template<>
    Anchor<Synergy::UI::Constraint::DimensionAnchor>::Anchor(float value) : value(value) { }

    template<>
    Anchor<Synergy::UI::Constraint::DimensionAnchor>::Anchor() { }

    template<>
    Anchor<Synergy::UI::Constraint::XAxisAnchor>::Anchor(float value) : value(value) { }

    template<>
    Anchor<Synergy::UI::Constraint::XAxisAnchor>::Anchor() { }

    template<>
    Anchor<Synergy::UI::Constraint::YAxisAnchor>::Anchor(float value) : value(value) { }

    template<>
    Anchor<Synergy::UI::Constraint::YAxisAnchor>::Anchor() { }
}
