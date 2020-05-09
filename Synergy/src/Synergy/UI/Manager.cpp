// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/Manager.h"

namespace Synergy::UI
{
    void Manager::Submit(Synergy::Ref<Synergy::UI::View> root)
    {
        root->Submit();
    }
}
