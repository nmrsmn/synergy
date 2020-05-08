// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/Element/Container.h"

namespace Synergy::UI
{
    void Container::Add(Synergy::Ref<Synergy::UI::Element> element)
    {
        if (element->parent == nullptr && element->root == nullptr)
        {
            childs.push_back(element);
            element->parent = this;
        }
        else
        {
            SYNERGY_ASSERT(false, "Synergy::UI::Element can only be embedded in one Synergy::UI::Container.");
        }
    }

    void Container::Submit()
    {
        for (auto child : childs)
        {
            child->Submit();
        }
    }
}
