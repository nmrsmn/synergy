// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_BUTTON_H
#define SYNERGY_UI_BUTTON_H

#include "Synergy/Core.h"
#include "Synergy/UI/Element.h"

namespace Synergy::UI
{
    class SYNERGY_API Button : public Synergy::UI::Element
    {
    protected:
        virtual void Submit() override;
    };
}

#endif
