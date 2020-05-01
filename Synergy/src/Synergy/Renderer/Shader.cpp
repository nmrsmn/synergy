// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Renderer/Shader.h"

namespace Synergy::Renderer
{
    uint32_t Shader::DataTypeComponents(Shader::DataType type)
    {
        switch (type)
        {
            case Shader::DataType::FLOAT: case Shader::DataType::INT: case Shader::DataType::BOOL: return 1;
            case Shader::DataType::VEC2F: case Shader::DataType::VEC2I: return 2;
            case Shader::DataType::VEC3F: case Shader::DataType::VEC3I: return 3;
            case Shader::DataType::VEC4F: case Shader::DataType::VEC4I: return 4;
            case Shader::DataType::MAT3: return 3 * 3;
            case Shader::DataType::MAT4: return 4 * 4;
        }
        
        SYNERGY_ASSERT(false, "Unknown Shader::DataType supplied!");
        return 0;
    }

    uint32_t Shader::DataTypeSize(Shader::DataType type)
    {
        switch (type)
        {
            case Shader::DataType::BOOL: return 1;
            case Shader::DataType::FLOAT: case Shader::DataType::INT: return 4;
            case Shader::DataType::VEC2F: return DataTypeComponents(type) * DataTypeSize(Shader::DataType::FLOAT);
            case Shader::DataType::VEC3F: return DataTypeComponents(type) * DataTypeSize(Shader::DataType::FLOAT);
            case Shader::DataType::VEC4F: return DataTypeComponents(type) * DataTypeSize(Shader::DataType::FLOAT);
            case Shader::DataType::VEC2I: return DataTypeComponents(type) * DataTypeSize(Shader::DataType::INT);
            case Shader::DataType::VEC3I: return DataTypeComponents(type) * DataTypeSize(Shader::DataType::INT);
            case Shader::DataType::VEC4I: return DataTypeComponents(type) * DataTypeSize(Shader::DataType::INT);
            case Shader::DataType::MAT3: return DataTypeComponents(type) * DataTypeSize(Shader::DataType::FLOAT);
            case Shader::DataType::MAT4: return DataTypeComponents(type) * DataTypeSize(Shader::DataType::FLOAT);
        }
        
        SYNERGY_ASSERT(false, "Unknown Shader::DataType supplied!");
        return 0;
    }
}

