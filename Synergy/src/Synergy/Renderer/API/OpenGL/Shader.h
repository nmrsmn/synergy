// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_OPENGL_SHADER_H
#define SYNERGY_RENDERER_OPENGL_SHADER_H

#include <unordered_map>

#include <glad/glad.h>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Shader.h"

namespace Synergy::Renderer::OpenGL
{
    class SYNERGY_API Shader: public Synergy::Shader
    {
    public:
        virtual ~Shader();
        
        virtual void Bind() const override;
        virtual void Unbind() const override;
        
        virtual void SetInt(const std::string& name, int value) override;
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
        virtual void SetFloat(const std::string& name, float value) override;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
        
    private:
        Shader(const std::string& name, const std::unordered_map<Synergy::Shader::Type, std::string> sources);
        
        virtual void Compile(const std::unordered_map<Synergy::Shader::Type, std::string> sources) override;
        
        GLint getUniformLocation(const std::string& name);
        
    private:
        std::unordered_map<std::string, GLint> uniformLocations;
        
        friend class Synergy::Shader;
    };
}

#endif
