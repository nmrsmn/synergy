// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/API/OpenGL/Shader.h"

namespace Synergy::Renderer::OpenGL
{
    static GLenum OpenGLShaderType(const Synergy::Renderer::Shader::Type type)
    {
        if (type == Shader::Type::VERTEX)
            return GL_VERTEX_SHADER;
        
        if (type == Shader::Type::FRAGMENT)
            return GL_FRAGMENT_SHADER;
        
        SYNERGY_ASSERT(false, "Unknown Shader::Type supplied!");
        return 0;
    }

    Shader::Shader(const std::string& name, std::map<Synergy::Renderer::Shader::Type, const std::string&> sources): name(name)
    {
        std::unordered_map<GLenum, std::string> shaders;
        for (auto& entry : sources)
        {
            shaders[OpenGLShaderType(entry.first)] = entry.second;
        }
        
        Compile(shaders);
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

    void Shader::Compile(const std::unordered_map<GLenum, std::string>& sources)
    {
        GLuint program = glCreateProgram();
        
        std::array<GLenum, 2> shaders;
        int shaderIndex = 0;
        
        for (const std::pair<GLenum, std::string>& entry : sources)
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
            shaders[shaderIndex++] = shader;
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
}
