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
        static constexpr bool HasEntities = has_entities<System>::value;
        static constexpr bool HasInitialize = has_initialize_member<System>::value;
        static constexpr bool HasDestroy = has_destroy_member<System>::value;
        static constexpr bool HasEnable = has_enable_member<System>::value;
        static constexpr bool HasDisable = has_disable_member<System>::value;
        static constexpr bool HasLoad = has_load_member<System>::value;
        static constexpr bool HasUnload = has_unload_member<System>::value;
        static constexpr bool HasReload = has_reload_member<System>::value;
        static constexpr bool HasFrameStart = has_frame_start_member<System>::value;
        static constexpr bool HasFrameEnd = has_frame_end_member<System>::value;
        static constexpr bool HasFixedUpdate = has_fixed_update_member<System>::value;
        static constexpr bool HasPreProcess = has_pre_process_member<System>::value;
        static constexpr bool HasProcess = has_process_member<System>::value;
        static constexpr bool HasPostProcess = has_post_process_member<System>::value;
        static constexpr bool HasUpdate = has_update_member<System>::value;
        static constexpr bool HasPostUpdate = has_post_update_member<System>::value;
    };
}

#endif
