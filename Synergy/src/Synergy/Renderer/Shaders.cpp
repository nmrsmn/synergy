// Created by Niels Marsman on 04-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/Shaders.h"

#include "Synergy/ResourcePack.h"

namespace Synergy
{
    Synergy::Ref<Synergy::Shader> Shaders::Load(const char* name)
    {
        return Instance().LoadShader(name);
    }

    Synergy::Ref<Synergy::Shader> Shaders::Load(const char* name, Synergy::Shader::FileList files, bool overwrite)
    {
        return Instance().LoadShader(name, files, overwrite);
    }

    Synergy::Ref<Synergy::Shader> Shaders::Load(const char* name, Synergy::Ref<Synergy::ResourcePack> pack, Synergy::Shader::FileList files, bool overwrite)
    {
        return Instance().LoadShader(name, pack, files, overwrite);
    }

    Synergy::Ref<Synergy::Shader> Shaders::Load(const char* name, Synergy::Shader::SourceMap sources, bool overwrite)
    {
        return Instance().LoadShader(name, sources, overwrite);
    }
    
    Shaders Shaders::Instance()
    {
        static Shaders instance;
        return instance;
    }

    Shaders::Shaders()
    {
        if (Synergy::Shaders::LoadShader("BatchRenderer.shader", {
                { Synergy::Shader::Type::VERTEX, "./assets/shaders/BatchRenderer.vertex" },
                { Synergy::Shader::Type::FRAGMENT, "./assets/shaders/BatchRenderer.fragment" }
            }) == nullptr)
        {
            SYNERGY_ASSERT(false, "Failed to load `BatchRenderer.shader`.");
        }
        
        if (Synergy::Shaders::LoadShader("CanvasRenderer.shader", {
                { Synergy::Shader::Type::VERTEX, "./assets/shaders/CanvasRenderer.vertex" },
                { Synergy::Shader::Type::FRAGMENT, "./assets/shaders/CanvasRenderer.fragment" }
            }) == nullptr)
        {
            SYNERGY_ASSERT(false, "Failed to load `CanvasRenderer.shader`.");
        }
        
        if (Synergy::Shaders::LoadShader("TextRenderer.shader", {
                { Synergy::Shader::Type::VERTEX, "./assets/shaders/TextRenderer.vertex" },
                { Synergy::Shader::Type::FRAGMENT, "./assets/shaders/TextRenderer.fragment" }
            }) == nullptr)
        {
            SYNERGY_ASSERT(false, "Failed to create `TextRenderer.shader`.");
        }
    }

    Shaders::~Shaders()
    {
        
    }

    Synergy::Ref<Synergy::Shader> Shaders::LoadShader(const char* name)
    {
        if (auto shader { shaders.find(name) }; shader != shaders.end())
        {
            return shader->second;
        }
        
        SYNERGY_ASSERT(false, "Failed to load shader.");
        
        return nullptr;
    }

    Synergy::Ref<Synergy::Shader> Shaders::LoadShader(const char* name, Synergy::Shader::FileList files, bool overwrite)
    {
        if (overwrite == false)
        {
            if (auto shader { shaders.find(name) }; shader != shaders.end())
            {
                return shader->second;
            }
        }
        
        std::string sources[files.size()];
        Synergy::Shader::SourceMap map;
        
        unsigned short index = 0;
        for (auto entry : files)
        {
            std::ifstream stream(entry.second, std::ios::in | std::ios::binary);
            if (stream)
            {
                stream.seekg(0, std::ios::end);
                sources[index].resize(stream.tellg());
                stream.seekg(0, std::ios::beg);
                stream.read(&sources[index][0], sources[index].size());
                stream.close();
                
                map.insert({ entry.first, sources[index++] });
            }
        }
        
        Synergy::Ref<Synergy::Shader> shader = Synergy::Shader::Create(map);
        shaders.insert({ name, shader });
        
        return shader;
    }

    Synergy::Ref<Synergy::Shader> Shaders::LoadShader(const char* name, Synergy::Ref<Synergy::ResourcePack> pack, Synergy::Shader::FileList files, bool overwrite)
    {
        if (overwrite == false)
        {
            if (auto shader { shaders.find(name) }; shader != shaders.end())
            {
                return shader->second;
            }
        }
        
        std::string sources[files.size()];
        Synergy::Shader::SourceMap map;
        
        unsigned short index = 0;
        for (auto entry : files)
        {
            Synergy::ResourcePack::Buffer buffer = pack->Read(entry.second);
            if (buffer.memory.size() > 0)
            {
                sources[index] = std::string(buffer.memory.begin(), buffer.memory.end());
                map.insert({ entry.first, sources[index++] });
            }
        }
        
        Synergy::Ref<Synergy::Shader> shader = Synergy::Shader::Create(map);
        shaders.insert({ name, shader });
        
        return shader;
    }

    Synergy::Ref<Synergy::Shader> Shaders::LoadShader(const char* name, Synergy::Shader::SourceMap sources, bool overwrite)
    {
        if (overwrite == false)
        {
            if (auto shader { shaders.find(name) }; shader != shaders.end())
            {
                return shader->second;
            }
        }
        
        Synergy::Ref<Synergy::Shader> shader = Synergy::Shader::Create(sources);
        shaders.insert({ name, shader });
        
        return shader;
    }
}
