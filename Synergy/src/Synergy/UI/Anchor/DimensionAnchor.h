// Created by Niels Marsman on 09-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_CONSTRAINT_DIMENSION_ANCHOR_H
#define SYNERGY_UI_CONSTRAINT_DIMENSION_ANCHOR_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/UI/Anchor.h"

namespace Synergy::UI::Constraint
{
    class Anchors;

    struct DimensionAnchor : public Synergy::UI::Constraint::Anchor<DimensionAnchor>
    {
    public:
        virtual void equals(Synergy::UI::Constraint::DimensionAnchor other);
        virtual void equals(Synergy::UI::Constraint::DimensionAnchor other, int constant);
        
        void equals(Synergy::UI::Constraint::DimensionAnchor other, float multiplier, int constant = 0);

    private:
        DimensionAnchor();
        DimensionAnchor(float value);
        
        friend class Synergy::UI::Constraint::Anchors;
    };
}

#endif
