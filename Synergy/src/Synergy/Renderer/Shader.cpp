// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/Shader.h"

#include "Synergy/Renderer/RendererAPI.h"
#include "Synergy/Renderer/API/OpenGL/Shader.h"

namespace Synergy
{
    Synergy::Ref<Synergy::Shader> Shader::Create(const Synergy::Shader::SourceMap sources)
    {
        switch (Synergy::Renderer::RendererAPI::Get())
        {
            case Synergy::Renderer::RendererAPI::API::OpenGL:
                struct RefEnabler: public Synergy::Renderer::OpenGL::Shader
                {
                    explicit RefEnabler(const Synergy::Shader::SourceMap sources): Synergy::Renderer::OpenGL::Shader(sources) { }
                };
                
                return Synergy::CreateRef<RefEnabler>(sources);
            default: break;
        }
        
        SYNERGY_ASSERT(false, "Shaders aren't supported in the currently selected RendererAPI.");
        return nullptr;
    }

    uint32_t Shader::DataTypeComponents(Synergy::Shader::DataType type)
    {
        switch (type)
        {
            case Synergy::Shader::DataType::FLOAT: case Synergy::Shader::DataType::INT: case Synergy::Shader::DataType::BOOL: return 1;
            case Synergy::Shader::DataType::VEC2F: case Synergy::Shader::DataType::VEC2I: return 2;
            case Synergy::Shader::DataType::VEC3F: case Synergy::Shader::DataType::VEC3I: return 3;
            case Synergy::Shader::DataType::VEC4F: case Synergy::Shader::DataType::VEC4I: return 4;
            case Synergy::Shader::DataType::MAT3: return 3 * 3;
            case Synergy::Shader::DataType::MAT4: return 4 * 4;
        }
        
        SYNERGY_ASSERT(false, "Unknown Shader::DataType supplied.");
        return 0;
    }

    uint32_t Shader::DataTypeSize(Synergy::Shader::DataType type)
    {
        switch (type)
        {
            case Synergy::Shader::DataType::BOOL: return 1;
            case Synergy::Shader::DataType::FLOAT: case Synergy::Shader::DataType::INT: return 4;
            case Synergy::Shader::DataType::VEC2F: return DataTypeComponents(type) * DataTypeSize(Synergy::Shader::DataType::FLOAT);
            case Synergy::Shader::DataType::VEC3F: return DataTypeComponents(type) * DataTypeSize(Synergy::Shader::DataType::FLOAT);
            case Synergy::Shader::DataType::VEC4F: return DataTypeComponents(type) * DataTypeSize(Synergy::Shader::DataType::FLOAT);
            case Synergy::Shader::DataType::VEC2I: return DataTypeComponents(type) * DataTypeSize(Synergy::Shader::DataType::INT);
            case Synergy::Shader::DataType::VEC3I: return DataTypeComponents(type) * DataTypeSize(Synergy::Shader::DataType::INT);
            case Synergy::Shader::DataType::VEC4I: return DataTypeComponents(type) * DataTypeSize(Synergy::Shader::DataType::INT);
            case Synergy::Shader::DataType::MAT3: return DataTypeComponents(type) * DataTypeSize(Synergy::Shader::DataType::FLOAT);
            case Synergy::Shader::DataType::MAT4: return DataTypeComponents(type) * DataTypeSize(Synergy::Shader::DataType::FLOAT);
        }
        
        SYNERGY_ASSERT(false, "Unknown Shader::DataType supplied.");
        return 0;
    }

    const uint32_t Shader::Id() const
    {
        return m_Id;
    }
}

