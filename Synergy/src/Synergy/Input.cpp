// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Input.h"

namespace Synergy
{
    Input& Input::Instance()
    {
        static Input instance;
        return instance;
    }

    Input::State Input::Get(Input::Key key)
    {
        return Instance().keyboardCurrentState[(int) key];
    }

    Input::State Input::Get(Input::Mouse button)
    {
        return Instance().mouseCurrentState[(int) button];
    }

    void UpdateInputStates(Input::State* states, bool* previous, bool* current, uint32_t count)
    {
        for (uint32_t index = 0; index < count; index++)
        {
            states[index].pressed = false;
            states[index].released = false;
            
            if (current[index] != previous[index])
            {
                if (current[index])
                {
                    states[index].pressed = !states[index].held;
                    states[index].held = true;
                }
                else
                {
                    states[index].released = true;
                    states[index].held = false;
                }
            }
            
            previous[index] = current[index];
        }
    }

    void Input::UpdateState()
    {
        UpdateInputStates(keyboardCurrentState, keyboardPreviousState, keyboardNextState, 256);
        UpdateInputStates(mouseCurrentState, mousePreviousState, mouseNextState, 8);
    }
}
