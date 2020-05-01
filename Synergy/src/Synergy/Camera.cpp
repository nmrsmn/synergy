// Created by Niels Marsman on 29-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Synergy::Camera
{
    Camera::Camera(glm::mat4 projection, glm::mat4 view)
        : projection(projection), view(view) {}

    const glm::mat4& Camera::GetViewMatrix() const
    {
        return view;
    }

    const glm::mat4& Camera::GetProjectionMatrix() const
    {
        return projection;
    }

    const glm::mat4& Camera::GetViewProjectionMatrix() const
    {
        return viewProjection;
    }

    const glm::vec3& Camera::GetPosition() const
    {
        return position;
    }

    float Camera::GetRotation() const
    {
        return rotation;
    }

    void Camera::SetPosition(glm::vec3 position)
    {
        this->position = position;
        this->UpdateViewMatrix();
    }

    void Camera::SetRotation(float rotation)
    {
        this->rotation = rotation;
        this->UpdateViewMatrix();
    }

    Orthographic::Orthographic(float left, float right, float bottom, float top)
        : Camera(glm::ortho(left, right, bottom, top, -1.0f, 1.0f), glm::mat4(1.0f))
    {
        this->UpdateProjectionMatrix();
    }
    
    void Orthographic::SetProjection(float left, float right, float bottom, float top)
    {
        projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        this->UpdateProjectionMatrix();
    }
    
    void Orthographic::UpdateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));
        
        view = glm::inverse(transform);
        this->UpdateProjectionMatrix();
    }

    void Orthographic::UpdateProjectionMatrix()
    {
        viewProjection = projection * view;
    }
}
