// Created by Niels Marsman on 29-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_CAMERA_CONTROLLER_H
#define SYNERGY_CAMERA_CONTROLLER_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/Camera.h"

namespace Synergy
{
    class SYNERGY_API CameraController
    {
    private:
        static float cameraTranslationSpeed;
        static float cameraRotationSpeed;
        
    public:
        CameraController(float ratio);
        
        const Synergy::Camera::Orthographic& GetCamera() const;
        
        void Update(float deltaTime);
        
    private:
        float zoom = 1;
        float ratio;
        
        Synergy::Camera::Orthographic camera;
        
        glm::vec3 position = { 0, 0, 0 };
        float rotation;
    };
}

#endif
