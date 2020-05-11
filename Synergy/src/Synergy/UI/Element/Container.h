// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_CONTAINER_H
#define SYNERGY_UI_CONTAINER_H

#include <functional>

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/UI/Anchors.h"
#include "Synergy/UI/Element.h"
#include "Synergy/UI/View.h"

namespace Synergy::UI
{
    class SYNERGY_API Container : public Synergy::UI::Element
    {
    public:
        struct Style
        {
            glm::vec4 background { 1, 1, 1, 0 };
            float radius { 0 };
        };
        
    public:
        static Synergy::Ref<Synergy::UI::Container> Create(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        static Synergy::Ref<Synergy::UI::Container> Create(Synergy::Ref<Synergy::UI::View> root, Synergy::UI::Container::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        static Synergy::Ref<Synergy::UI::Container> Create(Synergy::Ref<Synergy::UI::Container> container, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        static Synergy::Ref<Synergy::UI::Container> Create(Synergy::Ref<Synergy::UI::Container> container, Synergy::UI::Container::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        
    protected:
        Container(Synergy::Ref<Synergy::UI::View> root, Synergy::UI::Container::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        Container(Synergy::Ref<Synergy::UI::Container> container, Synergy::UI::Container::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        
        virtual void Submit() override;
        
    private:
        Container();
        
    public:
        Synergy::UI::Container::Style style;
        
    private:
        std::vector<Synergy::Ref<Synergy::UI::Element>> childs;
        
        friend class Synergy::UI::View;
        friend class Synergy::UI::Element;
    };
}

#endif
