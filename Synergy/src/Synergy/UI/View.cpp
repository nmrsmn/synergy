// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/View.h"

#include "Synergy/UI/Anchors.h"
#include "Synergy/UI/Element/Container.h"

namespace Synergy::UI
{
    Synergy::Ref<Synergy::UI::View> View::Create(glm::vec2 size)
    {
        struct RefEnabler : public Synergy::UI::View
        {
            explicit RefEnabler(glm::vec2 size) : Synergy::UI::View(size) { }
        };
        
        return Synergy::CreateRef<RefEnabler>(size);
    }

    const Synergy::UI::Constraint::Anchors View::Anchors() const
    {
        return container->anchors;
    }

    View::View(glm::vec2 size)
    {
        struct RefEnabler : public Synergy::UI::Container
        {
            explicit RefEnabler() : Synergy::UI::Container() { }
        };
        
        this->container = Synergy::CreateRef<RefEnabler>();
        this->container->anchors = Synergy::UI::Constraint::Anchors(size);
    }

    void View::Submit()
    {
        container->Submit();
    }

    void View::Update(glm::vec2 size)
    {
        container->anchors = Synergy::UI::Constraint::Anchors(size);
        
        for (auto child : container->childs)
        {
            // Update the childs with the updated size.
        }
    }
}
