// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_MANAGER_H
#define SYNERGY_UI_MANAGER_H

#include "Synergy/Core.h"

#include "Synergy/UI/View.h"

namespace Synergy::UI
{
    class Element;

    class SYNERGY_API Manager
    {
    public:
        static void Submit(Synergy::Ref<Synergy::UI::View> root);
    };
}

#endif
