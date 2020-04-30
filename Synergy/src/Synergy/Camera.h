// Created by Niels Marsman on 29-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_CAMERA_H
#define SYNERGY_CAMERA_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"

namespace Synergy::Camera
{
    class SYNERGY_API Camera
    {
    public:
        const glm::mat4& GetViewMatrix() const;
        const glm::mat4& GetProjectionMatrix() const;
        const glm::mat4& GetViewProjectionMatrix() const;
        
        const glm::vec3& GetPosition() const;
        float GetRotation() const;
        
        void SetPosition(glm::vec3 position);
        void SetRotation(float rotation);
        
    protected:
        Camera(glm::mat4 projection, glm::mat4 view);
        
        virtual void UpdateViewMatrix() = 0;
        virtual void UpdateProjectionMatrix() = 0;
        
    protected:
        glm::vec3 position = glm::vec3(0.0f);
        float rotation = 0.0f;
        
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 viewProjection = glm::mat4(1.0f);
    };

    class SYNERGY_API Orthographic: public Synergy::Camera::Camera
    {
    public:
        Orthographic(float left, float right, float bottom, float top);
        
        void SetProjection(float left, float right, float bottom, float top);
        
    private:
        virtual void UpdateViewMatrix() override;
        virtual void UpdateProjectionMatrix() override;
    };
}

#endif
