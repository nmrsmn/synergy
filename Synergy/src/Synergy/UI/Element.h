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
        enum class Type
        {
            BLOCK,
            INLINE
        };
        
    protected:
        static void Emplace(Synergy::Ref<Synergy::UI::Element> element, Synergy::Ref<Synergy::UI::Container> parent);
        
    public:
        const Synergy::UI::Constraint::Anchors Anchors() const;
        
    protected:
        Element();
        Element(Synergy::Ref<Synergy::UI::View> root);
        Element(Synergy::Ref<Synergy::UI::Container> parent);
        
        void Initialize(std::function<void (Synergy::UI::Constraint::Anchors&)> constraints, std::function<void ()> onInit = nullptr);
        
        virtual void ApplyDefaults();
        virtual void Submit() = 0;
        
    private:
        void CalculateInactiveAnchors();
        void CalculateTransform();
        
    protected:
        Synergy::Ref<Synergy::UI::Container> parent;
        
        Synergy::UI::Constraint::Anchors anchors;
        Synergy::UI::Element::Type type = Synergy::UI::Element::Type::BLOCK;

        bool dirty = true;
        bool initialized = false;
        
        glm::vec3 position;
        glm::vec2 size;
        
        friend class Synergy::UI::View;
        friend class Synergy::UI::Container;
    };
}

#endif
