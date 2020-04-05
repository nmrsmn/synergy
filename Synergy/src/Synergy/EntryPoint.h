// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ENTRYPOINT_H
#define SYNERGY_ENTRYPOINT_H

#ifdef SYNERGY_DEBUG
    #import <iostream>
#endif

extern Synergy::Application* Synergy::CreateApplication();

int main(int argc, char** argv)
{
    auto application = Synergy::CreateApplication();
    application->Start();
    
    delete application;

    #ifdef SYNERGY_DEBUG
        std::cout << "Press another key to exit..." << std::endl;
        std::cin.get();
    #endif
}

#endif
