// Created by Niels Marsman on 25-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_TEXTURE_H
#define SYNERGY_RENDERER_TEXTURE_H

#include "Synergy/Core.h"
#include "Synergy/Renderer/Bindable.h"

namespace Synergy::Renderer
{
    class SYNERGY_API Texture: public Bindable
    {
    public:
        virtual ~Texture() = default;
        
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        
        virtual void SetData(void* data, uint32_t size) = 0;
        
        virtual void Activate(uint32_t slot) const = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        virtual bool operator==(const Texture& other) const = 0;
    };
}

#endif
