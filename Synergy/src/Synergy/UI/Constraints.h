// Created by Niels Marsman on 09-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_CONSTRAINTS_H
#define SYNERGY_UI_CONSTRAINTS_H

#include "Synergy/Core.h"

#include "Synergy/UI/Anchors.h"
#include "Synergy/UI/Element.h"

namespace Synergy::UI
{
    class SYNERGY_API Constraints
    {
    public:
        static void Set(std::initializer_list<Synergy::UI::Constraint::AnyAnchor> list);
    };
}

#endif
