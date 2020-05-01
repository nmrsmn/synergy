// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_OPENGL_SHADER_H
#define SYNERGY_RENDERER_OPENGL_SHADER_H

#include <map>
#include <array>

#include <glad/glad.h>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Shader.h"

namespace Synergy::Renderer::OpenGL
{
    class SYNERGY_API Shader: public Synergy::Renderer::Shader
    {
    public:
        Shader(const std::string& name, std::map<Synergy::Renderer::Shader::Type, const std::string&> sources);
        
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
        void Compile(const std::unordered_map<GLenum, std::string>& sources);
        
        GLint getUniformLocation(const std::string& name);
        
    private:
        uint32_t id;
        std::string name;
        
        std::unordered_map<std::string, GLint> uniformLocations;
    };
}

#endif
