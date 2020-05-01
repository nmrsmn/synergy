// Created by Niels Marsman on 19-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_BINDABLE_H
#define SYNERGY_RENDERER_BINDABLE_H

namespace Synergy::Renderer
{
    class SYNERGY_API Bindable
    {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
}

#endif
