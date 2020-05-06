// Created by Niels Marsman on 04-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_SHADERS_H
#define SYNERGY_RENDERER_SHADERS_H

#include <unordered_map>

#include "Synergy/Core.h"
#include "Synergy/Renderer/Shader.h"

namespace Synergy
{
    class SYNERGY_API Shaders
    {
    public:
        static Synergy::Ref<Synergy::Shader> Load(const std::string& name);
        static Synergy::Ref<Synergy::Shader> Load(const std::string& name, const std::string& file);
        static Synergy::Ref<Synergy::Shader> Load(const std::string& name, const std::unordered_map<Synergy::Shader::Type, std::string> sources);
        
    private:
        static Shaders Instance();
        
    private:
        static const char* SHADER_RESOURCE_PACK;
        static const char* SHADER_RESOURCE_PACK_SHADERS[];
        
    private:
        Shaders();
        ~Shaders();
        
        Synergy::Ref<Synergy::Shader> LoadShader(const std::string& name);
        Synergy::Ref<Synergy::Shader> LoadShader(const std::string& name, const std::string& file);
        Synergy::Ref<Synergy::Shader> LoadShader(const std::string& name, const std::unordered_map<Synergy::Shader::Type, std::string> sources);
        
    private:
        std::unordered_map<std::string_view, Synergy::Ref<Synergy::Shader>> shaders;
    };
}

#endif
