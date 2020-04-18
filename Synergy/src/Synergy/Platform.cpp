// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Application.h"

namespace Synergy
{
    void Platform::CloseWindow()
    {
        application->running = false;
    }
}
