// Created by Niels Marsman on 27-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy.h"

class GameLayer: public Synergy::Layer
{
    
};

class Snake: public Synergy::Application
{
public:
	explicit Snake(): Synergy::Application()
	{
        PushLayer(new GameLayer());
	}
    
	virtual ~Snake() = default;
};

Synergy::Application* Synergy::CreateApplication()
{
    return new Snake();
}
