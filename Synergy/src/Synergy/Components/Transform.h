// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_COMPONENT_TRANSFORM_H
#define SYNERGY_COMPONENT_TRANSFORM_H

namespace Synergy
{
    struct Transform
    {
        glm::vec3 position { 0.f, 0.f, 0.f };
        glm::vec3 rotation { 0.f, 0.f, 0.f };
        glm::vec3 scale { 1.f, 1.f, 1.f };
    };
}

#endif
