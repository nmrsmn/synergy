// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ENTRYPOINT_H
#define SYNERGY_ENTRYPOINT_H

#include "Synergy/Platform/GLFW.h"
#include "Synergy/RendererAPI/OpenGL.h"

#ifdef SYNERGY_DEBUG
    #import <iostream>
#endif

extern Synergy::Application* Synergy::CreateApplication();

int main(int argc, char** argv)
{
    Synergy::Logger::Init();
    
    auto application = Synergy::CreateApplication();
    application->Start();
    
    delete application;

    #ifdef SYNERGY_DEBUG
        SYNERGY_LOG_ERROR("Press any key to continue...");
        std::cin.get();
    #endif
    
    return 0;
}

Synergy::Platform* Synergy::CreatePlatform()
{
    return new Synergy::Platforms::GLFW();
}

Synergy::RendererAPI* Synergy::CreateRendererAPI()
{
    return new Synergy::RendererAPIs::OpenGL();
}

#endif
