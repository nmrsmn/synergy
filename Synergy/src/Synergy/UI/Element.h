// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_ELEMENT_H
#define SYNERGY_UI_ELEMENT_H

#include "Synergy/Core.h"

namespace Synergy::UI
{
    class View;
    class Container;

    class SYNERGY_API Element
    {
    protected:
        virtual void Submit() = 0;
        
    protected:
        Synergy::UI::Element* parent;
        Synergy::UI::View* root;
        
        friend class Synergy::UI::View;
        friend class Synergy::UI::Container;
    };
}

#endif
