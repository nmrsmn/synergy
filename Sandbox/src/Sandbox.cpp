// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy.h"

class SandboxLayer: public Synergy::Layer
{
public:
    explicit SandboxLayer(): Synergy::Layer("SandboxLayer") {}
    
    virtual void OnUpdate() override
    {
        
    }
};

class Sandbox: public Synergy::Application
{
public:
	explicit Sandbox(): Synergy::Application()
	{
        PushLayer(new SandboxLayer());
	}
    
	virtual ~Sandbox() = default;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
