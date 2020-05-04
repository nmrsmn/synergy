// Created by Niels Marsman on 21-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_RENDERER_RENDERER_H
#define SYNERGY_RENDERER_RENDERER_H

#include "Synergy/Core.h"
#include "Synergy/Renderer/Renderable.h"

namespace Synergy::Renderer
{
    template<class Derived, class Renderable>
    class SYNERGY_API Renderer
    {
    public:
        static void Submit(Renderable renderable)
        {
            Derived::SubmitRenderable(renderable);
        };
        
        static void Submit(Text text)
        {
            Derived::SubmitText(text);
        }
    };
}

#endif
