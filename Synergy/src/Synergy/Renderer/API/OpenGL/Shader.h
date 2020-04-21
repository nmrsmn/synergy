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
        
    private:
        void Compile(const std::unordered_map<GLenum, std::string>& sources);
        
    private:
        uint32_t id;
        std::string name;
    };
}

#endif
