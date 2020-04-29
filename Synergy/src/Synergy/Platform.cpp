// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Application.h"
#include "Synergy/Platform.h"

namespace Synergy
{
    void Platform::CloseWindow()
    {
        application->running = false;
    }

    void Platform::UpdateKeyStates()
    {
        Input::Instance().UpdateState();
    }

    void Platform::UpdateKeyState(Input::Key key, bool state)
    {
        Input::Instance().keyboardNextState[(int) key] = state;
    }

    void Platform::UpdateMouseState(uint8_t button, bool state)
    {
        Input::Instance().mouseNextState[button] = state;
    }

    void Platform::UpdateMousePosition(glm::vec2 position)
    {
        Input::Instance().mousePositionCurrent = position;
    }

    void Platform::UpdateWindowSize(glm::vec2 size)
    {
        application->UpdateWindowSize(size);
    }
}
