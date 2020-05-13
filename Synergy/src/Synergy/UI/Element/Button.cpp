// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/Element/Button.h"

#include "Synergy/Renderer/Renderable.h"
#include "Synergy/UI/Element/Container.h"
#include "Synergy/UI/Renderer.h"

namespace Synergy::UI
{
    Synergy::Ref<Synergy::UI::Button> Button::Create(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        struct RefEnabler : public Synergy::UI::Button
        {
            explicit RefEnabler(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : Synergy::UI::Button(root, constraints) { }
        };
        
        Synergy::Ref<Synergy::UI::Button> button = Synergy::CreateRef<RefEnabler>(root, constraints);
        Synergy::UI::Element::Emplace(button, button->parent);
        
        return button;
    }

    Synergy::Ref<Synergy::UI::Button> Button::Create(Synergy::Ref<Synergy::UI::Container> container, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        struct RefEnabler : public Synergy::UI::Button
        {
            explicit RefEnabler(Synergy::Ref<Synergy::UI::Container> container, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : Synergy::UI::Button(container, constraints) { }
        };
        
        Synergy::Ref<Synergy::UI::Button> button = Synergy::CreateRef<RefEnabler>(container, constraints);
        Synergy::UI::Element::Emplace(button, button->parent);
        
        return button;
    }

    Button::Button(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : Synergy::UI::Element(root)
    {
        this->Initialize(constraints);
    }

    Button::Button(Synergy::Ref<Synergy::UI::Container> container, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : Synergy::UI::Element(container)
    {
        this->Initialize(constraints);
    }
    
    void Button::Submit()
    {
        //Synergy::UI::Renderer::Submit(Synergy::Quad { position, size, { 1, 0, 0, 1 } });
    };
}
