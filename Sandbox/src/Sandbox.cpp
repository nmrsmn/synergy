// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include "Synergy.h"

class Sandbox: public Synergy::Application
{
public:
	explicit Sandbox(): Synergy::Application() {}
    
    virtual bool OnUserCreate() override
    {
        return true;
    }
    
    virtual bool OnUserUpdate(float deltatime) override
    {
        return true;
    }
    
	virtual ~Sandbox() = default;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Sandbox();
}
