// Created by Niels Marsman on 04-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/Shaders.h"

namespace Synergy
{
    Synergy::Ref<Synergy::Shader> Shaders::Load(const std::string& name)
    {
        return Instance().LoadShader(name);
    }

    Synergy::Ref<Synergy::Shader> Shaders::Load(const std::string& name, const std::string& file)
    {
        return Instance().LoadShader(name, file);
    }

    Synergy::Ref<Synergy::Shader> Shaders::Load(const std::string& name, const std::unordered_map<Synergy::Shader::Type, const std::string&> sources)
    {
        return Instance().LoadShader(name, sources);
    }
    
    Shaders Shaders::Instance()
    {
        static Shaders instance;
        return instance;
    }

    Shaders::Shaders()
    {
        
    }

    Shaders::~Shaders()
    {
        
    }

    Synergy::Ref<Synergy::Shader> Shaders::LoadShader(const std::string& name)
    {
        if (auto shader { shaders.find(name) }; shader != shaders.end())
        {
            return shader->second;
        }
        
        SYNERGY_ASSERT(false, "Failed to load shader.");
        
        return nullptr;
    }

    Synergy::Ref<Synergy::Shader> Shaders::LoadShader(const std::string& name, const std::string& file)
    {
        if (auto shader { shaders.find(name) }; shader != shaders.end())
        {
            return shader->second;
        }
        
        SYNERGY_ASSERT(false, "Loading shaders from file (using Synergy::ResourcePack) isn't supported yet.");
        
        return nullptr;
    }

    Synergy::Ref<Synergy::Shader> Shaders::LoadShader(const std::string& name, const std::unordered_map<Synergy::Shader::Type, const std::string&> sources)
    {
        if (auto shader { shaders.find(name) }; shader != shaders.end())
        {
            return shader->second;
        }
        
        Synergy::Ref<Synergy::Shader> shader = Synergy::Shader::Create(name, sources);
        shaders.insert({ name, shader });
        
        return shader;
    }
}
