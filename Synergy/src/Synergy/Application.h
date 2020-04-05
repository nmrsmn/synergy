// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_APPLICATION_H
#define SYNERGY_APPLICATION_H

#include "Synergy/Core.h"

namespace Synergy
{
    class Application
    {
    public:
        virtual ~Application() = default;
        
        void Start();
        
    protected:
        Application();
    };

    Application* CreateApplication();
}

#endif
