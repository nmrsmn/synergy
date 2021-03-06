// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ENTRYPOINT_H
#define SYNERGY_ENTRYPOINT_H

#include "Synergy/Platform/GLFW.h"
#include "Synergy/Renderer/API/OpenGL.h"

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

Synergy::Platform* Synergy::CreatePlatform(Application* application)
{
    return new Synergy::Platforms::GLFW(application);
}

Synergy::Renderer::RendererAPI* Synergy::Renderer::CreateRendererAPI()
{
    return new Synergy::Renderer::API::OpenGL();
}

#endif
