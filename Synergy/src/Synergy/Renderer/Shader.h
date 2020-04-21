// Created by Niels Marsman on 20-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_SHADER_H
#define SYNERGY_RENDERER_SHADER_H

#include "Synergy/Core.h"
#include "Synergy/Renderer/Bindable.h"

namespace Synergy::Renderer
{
    class SYNERGY_API Shader: public Bindable
    {
    public:
        enum class SYNERGY_API Type
        {
            VERTEX,
            FRAGMENT,
            
            // Alternatives
            PIXEL = FRAGMENT
        };
        
        enum class SYNERGY_API DataType : uint8_t
        {
            FLOAT, VEC2F, VEC3F, VEC4F, MAT3, MAT4, INT, VEC2I, VEC3I, VEC4I, BOOL,
            
            // Alternatives
            VEC2 = VEC2F,
            VEC3 = VEC3F,
            VEC4 = VEC4F
        };

    public:
        static uint32_t DataTypeComponents(DataType type);
        static uint32_t DataTypeSize(DataType type);
        
    public:
        virtual ~Shader() = default;
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
}

#endif