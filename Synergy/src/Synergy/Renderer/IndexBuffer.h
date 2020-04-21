// Created by Niels Marsman on 19-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_INDEXBUFFER_H
#define SYNERGY_RENDERER_INDEXBUFFER_H

#include "Synergy/Core.h"
#include "Synergy/Renderer/Bindable.h"

namespace Synergy::Renderer
{
    class SYNERGY_API IndexBuffer: public Bindable
    {
    public:
        virtual ~IndexBuffer() = default;
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        virtual uint32_t GetCount() const = 0;
    };
}

#endif
