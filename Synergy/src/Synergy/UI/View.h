// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_VIEW_H
#define SYNERGY_UI_VIEW_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/UI/Element.h"

namespace Synergy::UI
{
    class Anchors;
    class Element;
    class Container;
    class Manager;

    class SYNERGY_API View
    {
    public:
        static Synergy::Ref<Synergy::UI::View> Create(glm::vec2 size);
        
    public:
        const Synergy::UI::Constraint::Anchors Anchors() const;
        
    private:
        View(glm::vec2 size);
        
        void Submit();
        void Update(glm::vec2 size);
        
    private:
        Synergy::Ref<Synergy::UI::Container> container;
        
        friend class Synergy::UI::Container;
        friend class Synergy::UI::Element;
        friend class Synergy::UI::Manager;
    };
}

#endif
