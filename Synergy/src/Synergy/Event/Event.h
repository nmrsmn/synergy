// Created by Niels Marsman on 24-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_EVENT_H
#define SYNERGY_EVENT_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"

namespace Synergy
{
    struct WindowResizedEvent
    {
        glm::vec2 size;
    };
}

#endif
