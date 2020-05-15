// Created by Niels Marsman on 15-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_EVENTS_H
#define SYNERGY_EVENTS_H

namespace Synergy
{
    struct FrameStartEvent {};
    struct FrameEndEvent {};

    struct UpdateEvent {
        float dt;
    };
}

#endif
