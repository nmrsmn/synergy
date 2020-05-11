// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_ELEMENT_H
#define SYNERGY_UI_ELEMENT_H

#include "Synergy/Core.h"
#include "Synergy/UI/Anchors.h"

namespace Synergy::UI
{
    class View;
    class Container;

    class SYNERGY_API Element
    {
    public:
        struct Style
        {
            
        };
        
    protected:
        static void Emplace(Synergy::Ref<Synergy::UI::Element> element, Synergy::Ref<Synergy::UI::Container> parent);
        
    public:
        const Synergy::UI::Constraint::Anchors Anchors() const;
        
    protected:
        Element();
        Element(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        Element(Synergy::Ref<Synergy::UI::Container> parent, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        
        virtual void Submit() = 0;
        
        virtual void ApplyDefaults();
        
    private:
        void Initialize(std::function<void (Synergy::UI::Constraint::Anchors&)> constraints);
        void CalculateInactiveAnchors();
        void CalculateTransform();
        
    protected:
        Synergy::Ref<Synergy::UI::Container> parent;
        Synergy::UI::Constraint::Anchors anchors;

        bool dirty = true;
        bool initialized = false;
        
        glm::vec3 position;
        glm::vec2 size;
        
        friend class Synergy::UI::View;
        friend class Synergy::UI::Container;
    };
}

#endif
