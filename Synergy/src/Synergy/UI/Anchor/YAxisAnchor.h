// Created by Niels Marsman on 09-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_CONSTRAINT_Y_AXIS_ANCHOR_H
#define SYNERGY_UI_CONSTRAINT_Y_AXIS_ANCHOR_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/UI/Anchor.h"

namespace Synergy::UI::Constraint
{
    class Anchors;

    struct YAxisAnchor : public Synergy::UI::Constraint::Anchor<YAxisAnchor>
    {
    public:
        virtual void equals(Synergy::UI::Constraint::YAxisAnchor other);
        virtual void equals(Synergy::UI::Constraint::YAxisAnchor other, int constant);
        
    private:
        YAxisAnchor();
        YAxisAnchor(float value);
        
        friend class Synergy::UI::Constraint::Anchors;
    };
}

#endif
