// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/View.h"

namespace Synergy::UI
{
    void View::Add(Synergy::Ref<Synergy::UI::Element> element)
    {
        childs.push_back(element);
    }

    void View::Submit()
    {
        for (auto child : childs)
        {
            child->Submit();
        }
    }

    void View::Update(glm::uvec2 parent)
    {
        // Update
        
        for (auto child : childs)
        {
            // Update the childs with the updated size.
        }
    }
}
