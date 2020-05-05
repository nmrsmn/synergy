// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <vector>

#include <glm/gtc/type_ptr.hpp>

#include "Synergy/Renderer/API/OpenGL/Shader.h"

namespace Synergy::Renderer::OpenGL
{
    static GLenum OpenGLShaderType(const Synergy::Shader::Type type)
    {
        if (type == Shader::Type::VERTEX)
            return GL_VERTEX_SHADER;
        
        if (type == Shader::Type::FRAGMENT)
            return GL_FRAGMENT_SHADER;
        
        SYNERGY_ASSERT(false, "Unknown Shader::Type supplied!");
        return 0;
    }

    Shader::Shader(const std::string& name, const std::unordered_map<Synergy::Shader::Type, const std::string&> sources) : Synergy::Shader(name, sources)
    {
        this->Compile();
    }

    Shader::~Shader()
    {
        glDeleteProgram(id);
    }

    void Shader::Bind() const
    {
        glUseProgram(id);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::SetInt(const std::string& name, int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::SetIntArray(const std::string& name, int* values, uint32_t count)
    {
        glUniform1iv(getUniformLocation(name), count, values);
    }

    void Shader::SetFloat(const std::string& name, float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }

    void Shader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::SetFloat4(const std::string& name, const glm::vec4& value)
    {
        glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::Compile()
    {
        GLuint program = glCreateProgram();
        
        std::unordered_map<GLenum, std::string> shaderSources;
        for (auto& entry : sources)
        {
            shaderSources[OpenGLShaderType(entry.first)] = entry.second;
        }
        
        std::vector<GLenum> shaders;
        
        for (const std::pair<GLenum, const std::string&>& entry : shaderSources)
        {
            const GLchar* source = entry.second.c_str();
            
            GLuint shader = glCreateShader(entry.first);
            glShaderSource(shader, 1, &source, 0);
            
            glCompileShader(shader);
            
            GLint compiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (compiled == GL_FALSE)
            {
                GLint length = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
                
                std::string message;
                message.reserve(length);
                
                glGetShaderInfoLog(shader, length, NULL, &message[0]);
                
                glDeleteShader(shader);
                
                SYNERGY_LOG_ERROR("{}", message.data());
                SYNERGY_ASSERT(false, "Failed to compile shader");
                break;
            }
            
            glAttachShader(program, shader);
            shaders.push_back(shader);
        }
        
        glLinkProgram(program);
        
        GLint linked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if (linked == GL_FALSE)
        {
            GLint length = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            
            std::string message;
            message.reserve(length);
            
            glGetProgramInfoLog(program, length, NULL, &message[0]);
            
            glDeleteProgram(program);
            
            for (GLuint shader : shaders)
                glDeleteShader(shader);
            
            SYNERGY_LOG_ERROR("{}", message.data());
            SYNERGY_ASSERT(false, "Failed to link shader");
            return;
        }
        
        for (GLuint shader : shaders)
        {
            glDetachShader(program, shader);
            glDeleteShader(shader);
        }
        
        id = program;
    }

    GLint Shader::getUniformLocation(const std::string& name)
    {
        if (auto location{ uniformLocations.find(name) }; location != uniformLocations.end())
        {
            return location->second;
        }
        
        GLint location = glGetUniformLocation(id, name.c_str());
        uniformLocations[name] = location;
        
        return location;
    }
}
