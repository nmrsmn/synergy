// Created by Niels Marsman on 29-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/CameraController.h"
#include "Synergy/Input.h"

namespace Synergy
{
    float CameraController::cameraTranslationSpeed = 5.0f;
    float CameraController::cameraRotationSpeed = 180.0f;

    CameraController::CameraController(float ratio)
        : ratio(ratio), camera(-ratio * zoom, ratio * zoom, -zoom, zoom) {}

    const Synergy::Camera::Orthographic& CameraController::GetCamera() const
    {
        return camera;
    }
    
    void CameraController::Update(float deltaTime)
    {
        if (Input::Get(Input::Key::A).held)
        {
            position.x -= cos(glm::radians(rotation)) * CameraController::cameraTranslationSpeed * deltaTime;
            position.y -= sin(glm::radians(rotation)) * CameraController::cameraTranslationSpeed * deltaTime;
        }
        else if (Input::Get(Input::Key::D).held)
        {
            position.x += cos(glm::radians(rotation)) * CameraController::cameraTranslationSpeed * deltaTime;
            position.y += sin(glm::radians(rotation)) * CameraController::cameraTranslationSpeed * deltaTime;
        }
        
        if (Input::Get(Input::Key::W).held)
        {
            position.x += -sin(glm::radians(rotation)) * CameraController::cameraTranslationSpeed * deltaTime;
            position.y += cos(glm::radians(rotation)) * CameraController::cameraTranslationSpeed * deltaTime;
        }
        else if (Input::Get(Input::Key::S).held)
        {
            position.x -= -sin(glm::radians(rotation)) * CameraController::cameraTranslationSpeed * deltaTime;
            position.y -= cos(glm::radians(rotation)) * CameraController::cameraTranslationSpeed * deltaTime;
        }
        
        if (Input::Get(Input::Key::Q).held)
        {
            rotation += CameraController::cameraRotationSpeed * deltaTime;
        }
        if (Input::Get(Input::Key::E).held)
        {
            rotation -= CameraController::cameraRotationSpeed * deltaTime;
        }
        
        if (rotation > 180.0f) rotation -= 360.0f;
        if (rotation <= -180.0f) rotation += 360.0f;
        
        camera.SetRotation(rotation);
        camera.SetPosition(position);
    }
}
