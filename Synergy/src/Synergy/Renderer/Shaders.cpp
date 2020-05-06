// Created by Niels Marsman on 04-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <unordered_map>

#include "Synergy/Renderer/Shaders.h"

#include "Synergy/ResourcePack.h"

namespace Synergy
{
    const char* Shaders::SHADER_RESOURCE_PACK = "assets/shaders/Synergy.shaders";
    const char* Shaders::SHADER_RESOURCE_PACK_SHADERS[] = {
        "assets/shaders/BatchRenderer.shader",
        "assets/shaders/CanvasRenderer.shader",
        "assets/shaders/TextRenderer.shader"
    };
    
    Synergy::Ref<Synergy::Shader> Shaders::Load(const std::string& name)
    {
        return Instance().LoadShader(name);
    }

    Synergy::Ref<Synergy::Shader> Shaders::Load(const std::string& name, const std::string& file)
    {
        return Instance().LoadShader(name, file);
    }

    Synergy::Ref<Synergy::Shader> Shaders::Load(const std::string& name, const std::unordered_map<Synergy::Shader::Type, std::string> sources)
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
        const std::vector<Synergy::Shader::Type> types = {
            Synergy::Shader::Type::VERTEX, Synergy::Shader::Type::GEOMETRY, Synergy::Shader::Type::FRAGMENT
        };
        
        Synergy::Ref<Synergy::ResourcePack> pack = Synergy::ResourcePack::Load(Shaders::SHADER_RESOURCE_PACK);
        
        for (auto name : Shaders::SHADER_RESOURCE_PACK_SHADERS)
        {
            Synergy::ResourcePack::Buffer buffer = pack->Read(name);
            Synergy::Ref<Synergy::ResourcePack> shader = Synergy::ResourcePack::Load(&buffer);
            
            std::unordered_map<Synergy::Shader::Type, std::string> sources;
            
            for (auto type : types)
            {
                Synergy::ResourcePack::Buffer buffer = shader->Read(Synergy::Shader::ShaderTypeName(type));
                if (buffer.memory.size() > 0)
                {
                    std::string source = std::string(buffer.memory.begin(), buffer.memory.end());
                    sources.insert({ type, source });
                }
            }
            
            shaders.insert({ name, Synergy::Shader::Create(name, sources) });
        }
        
        char a = 'a';
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

    Synergy::Ref<Synergy::Shader> Shaders::LoadShader(const std::string& name, const std::unordered_map<Synergy::Shader::Type, std::string> sources)
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
