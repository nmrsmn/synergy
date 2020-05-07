// Created by Niels Marsman on 04-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_SHADERS_H
#define SYNERGY_RENDERER_SHADERS_H

#include <unordered_map>

#include "Synergy/Core.h"
#include "Synergy/ResourcePack.h"
#include "Synergy/Renderer/Shader.h"

namespace Synergy
{
    class SYNERGY_API Shaders
    {
    public:
        static Synergy::Ref<Synergy::Shader> Load(const char* name);
        static Synergy::Ref<Synergy::Shader> Load(const char* name, Synergy::Shader::FileList files, bool overwrite = false);
        static Synergy::Ref<Synergy::Shader> Load(const char* name, Synergy::Ref<Synergy::ResourcePack> pack, Synergy::Shader::FileList files, bool overwrite = false);
        static Synergy::Ref<Synergy::Shader> Load(const char* name, Synergy::Shader::SourceMap sources, bool overwrite = false);
        
    private:
        static Shaders Instance();
        
    private:
        Shaders();
        ~Shaders();
        
        Synergy::Ref<Synergy::Shader> LoadShader(const char* name);
        Synergy::Ref<Synergy::Shader> LoadShader(const char* name, Synergy::Shader::FileList files, bool overwrite = false);
        Synergy::Ref<Synergy::Shader> LoadShader(const char* name, Synergy::Ref<Synergy::ResourcePack> pack, Synergy::Shader::FileList files, bool overwrite = false);
        Synergy::Ref<Synergy::Shader> LoadShader(const char* name, Synergy::Shader::SourceMap sources, bool overwrite = false);
        
    private:
        std::unordered_map<const char*, Synergy::Ref<Synergy::Shader>> shaders;
    };
}

#endif
