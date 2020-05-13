// Created by Niels Marsman on 09-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_CONSTRAINT_ANCHOR_H
#define SYNERGY_UI_CONSTRAINT_ANCHOR_H

#include "Synergy/Core.h"

namespace Synergy::UI
{
    class Element;
}

namespace Synergy::UI::Constraint
{
    template<typename AnchorType>
    class Anchor
    {
    public:
        virtual void equals(AnchorType other) = 0;
        virtual void equals(AnchorType other, int constant) = 0;
        
        float Value() const;
        bool Activated() const;
        
    protected:
        Anchor();
        Anchor(float value);
        
    protected:
        Synergy::Ref<Synergy::UI::Element> element = nullptr;
        
        float value;
        bool activated = false;
        
        friend class Synergy::UI::Element;
    };
}

#endif
