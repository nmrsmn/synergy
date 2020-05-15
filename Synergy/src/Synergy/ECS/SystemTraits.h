// Created by Niels Marsman on 15-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_SYSTEM_TRAITS_H
#define SYNERGY_ECS_SYSTEM_TRAITS_H

#include "Synergy/Core.h"
#include "Synergy/ECS/Detectors.h"

namespace Synergy
{
    template <typename System>
    struct SystemTraits
    {
        static constexpr bool HasInitialize = has_initialize_member<System>::value;
    };
}

#endif
