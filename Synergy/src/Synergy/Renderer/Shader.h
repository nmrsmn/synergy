// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_SHADER_H
#define SYNERGY_RENDERER_SHADER_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Bindable.h"

namespace Synergy
{
    class Shaders;

    class SYNERGY_API Shader: public Synergy::Renderer::Bindable
    {
    public:
        enum class SYNERGY_API Type
        {
            VERTEX = 1,
            GEOMETRY,
            FRAGMENT,
            
            // Alternatives
            PIXEL = FRAGMENT,
            
            LAST = FRAGMENT
        };
        
        enum class SYNERGY_API DataType : uint8_t
        {
            FLOAT, VEC2F, VEC3F, VEC4F, MAT3, MAT4, INT, VEC2I, VEC3I, VEC4I, BOOL,
            
            // Alternatives
            VEC2 = VEC2F,
            VEC3 = VEC3F,
            VEC4 = VEC4F
        };
        
    private:
        static Synergy::Ref<Synergy::Shader> Create(const std::string& name, const std::unordered_map<Synergy::Shader::Type, std::string> sources);

    public:
        static uint32_t DataTypeComponents(Synergy::Shader::DataType type);
        static uint32_t DataTypeSize(Synergy::Shader::DataType type);
        
        static const char* ShaderTypeName(Synergy::Shader::Type type);
        
    public:
        virtual ~Shader() = default;
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
        
    protected:
        Shader(const std::string& name);
        
        virtual void Compile(const std::unordered_map<Synergy::Shader::Type, std::string> sources) = 0;
        
    protected:
        uint32_t id;
        
        const std::string& name;
        
        friend class Synergy::Shaders;
    };
}

#endif
