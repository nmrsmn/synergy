// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_LAYER_H
#define SYNERGY_LAYER_H

namespace Synergy
{
    class SYNERGY_API Layer
    {
    public:
        Layer(const char* name = ""): name(name) {}
        virtual ~Layer() = default;
        
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float deltaTime) {}
        
    protected:
        const char* name;
    };
}

#endif
