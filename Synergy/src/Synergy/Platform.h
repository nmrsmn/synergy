// Created by Niels Marsman on 15-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_PLATFORM_H
#define SYNERGY_PLATFORM_H

namespace Synergy
{
    class SYNERGY_API Platform
    {
    public:
        virtual bool Init() = 0;
        virtual bool Start() = 0;
        virtual bool Shutdown() = 0;
        
        virtual bool CreateContext() = 0;
        virtual bool CreateWindow(int x, int y, int width, int height, bool fullscreen) = 0;
        virtual bool UpdateWindow() = 0;
        
        virtual bool StartEventLoop() = 0;
        virtual bool HandleEvent() = 0;
    };

    Platform* CreatePlatform();
}

#endif
