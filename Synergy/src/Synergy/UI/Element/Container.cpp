// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/Element/Container.h"

#include "Synergy/Renderer/Renderable.h"
#include "Synergy/Renderer/CanvasRenderer.h"

namespace Synergy::UI
{
    Synergy::Ref<Synergy::UI::Container> Container::Create(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        struct RefEnabler : public Synergy::UI::Container
        {
            explicit RefEnabler(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : Synergy::UI::Container(root, constraints) { }
        };
        
        Synergy::Ref<Synergy::UI::Container> item = Synergy::CreateRef<RefEnabler>(root, constraints);
        Synergy::UI::Element::Emplace(item, item->parent);
        
        return item;
    }

    Synergy::Ref<Synergy::UI::Container> Container::Create(Synergy::Ref<Synergy::UI::Container> container, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        struct RefEnabler : public Synergy::UI::Container
        {
            explicit RefEnabler(Synergy::Ref<Synergy::UI::Container> container, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : Synergy::UI::Container(container, constraints) { }
        };
        
        Synergy::Ref<Synergy::UI::Container> item = Synergy::CreateRef<RefEnabler>(container, constraints);
        Synergy::UI::Element::Emplace(item, item->parent);
        
        return item;
    }

    Container::Container(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : Synergy::UI::Element(root, constraints) { }
    Container::Container(Synergy::Ref<Synergy::UI::Container> container, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : Synergy::UI::Element(container, constraints) { }
    Container::Container() : Synergy::UI::Element() { }

    void Container::Submit()
    {
        for (auto child : childs)
        {
            child->Submit();
        }
    }
}
