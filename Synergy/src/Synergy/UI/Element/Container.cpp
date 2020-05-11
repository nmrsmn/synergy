// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/Element/Container.h"

#include "Synergy/UI/Renderable.h"
#include "Synergy/UI/Renderer.h"

namespace Synergy::UI
{
    Synergy::Ref<Synergy::UI::Container> Container::Create(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        return Synergy::UI::Container::Create(root, {}, constraints);
    }

    Synergy::Ref<Synergy::UI::Container> Container::Create(Synergy::Ref<Synergy::UI::View> root, Synergy::UI::Container::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        struct RefEnabler : public Synergy::UI::Container
        {
            explicit RefEnabler(Synergy::Ref<Synergy::UI::View> root, Synergy::UI::Container::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : Synergy::UI::Container(root, style, constraints) { }
        };
        
        Synergy::Ref<Synergy::UI::Container> item = Synergy::CreateRef<RefEnabler>(root, style, constraints);
        Synergy::UI::Element::Emplace(item, item->parent);
        
        return item;
    }

    Synergy::Ref<Synergy::UI::Container> Container::Create(Synergy::Ref<Synergy::UI::Container> container, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        return Synergy::UI::Container::Create(container, {}, constraints);
    }

    Synergy::Ref<Synergy::UI::Container> Container::Create(Synergy::Ref<Synergy::UI::Container> container, Synergy::UI::Container::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        struct RefEnabler : public Synergy::UI::Container
        {
            explicit RefEnabler(Synergy::Ref<Synergy::UI::Container> container, Synergy::UI::Container::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : Synergy::UI::Container(container, style, constraints) { }
        };
        
        Synergy::Ref<Synergy::UI::Container> item = Synergy::CreateRef<RefEnabler>(container, style, constraints);
        Synergy::UI::Element::Emplace(item, item->parent);
        
        return item;
    }

    Container::Container(Synergy::Ref<Synergy::UI::View> root, Synergy::UI::Container::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : style(style), Synergy::UI::Element(root, constraints) { }
    Container::Container(Synergy::Ref<Synergy::UI::Container> container, Synergy::UI::Container::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : style(style), Synergy::UI::Element(container, constraints) { }
    Container::Container() : Synergy::UI::Element() { }

    void Container::Submit()
    {
        if (style.background.a > 0)
        {
            Synergy::UI::Renderer::Submit(Synergy::UI::Quad { position, size, style.background, 10.0f });
        }
        
        for (auto child : childs)
        {
            child->Submit();
        }
    }
}
