// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/UI/Element.h"

#include "Synergy/UI/Element.h"
#include "Synergy/UI/Element/Container.h"
#include "Synergy/UI/View.h"

namespace Synergy::UI
{
    void Element::Emplace(Synergy::Ref<Synergy::UI::Element> element, Synergy::Ref<Synergy::UI::Container> parent)
    {
        parent->childs.emplace_back(element);
    }

    const Synergy::UI::Constraint::Anchors Element::Anchors() const
    {
        return anchors;
    }

    Element::Element() { }
    Element::Element(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : parent(root->container)
    {
        this->Initialize(constraints);
    }

    Element::Element(Synergy::Ref<Synergy::UI::Container> parent, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints) : parent(parent)
    {
        this->Initialize(constraints);
    }

    void Element::ApplyDefaults()
    {
        anchors.top.equals(parent->anchors.top);
        anchors.bottom.equals(parent->anchors.bottom);
        anchors.left.equals(parent->anchors.left);
        anchors.right.equals(parent->anchors.right);
        
        anchors.width.equals(parent->anchors.width);
        anchors.height.equals(parent->anchors.height);
        
        anchors.horizontal.value = 0;
        anchors.vertical.value = 0;
    }

    void Element::Initialize(std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        if (parent)
        {
            
            if (constraints)
            {
                constraints(anchors);
            }
            else
            {
                this->ApplyDefaults();
            }
            this->CalculateTransform();
        }
    }

    void Element::CalculateInactiveAnchors()
    {
        if (anchors.left.activated)
        {
            anchors.right.value = anchors.left.value + anchors.width.value;
            anchors.horizontal.value = (anchors.right.value - anchors.left.value) / 2;
        }
        else if (anchors.right.activated)
        {
            anchors.left.value = anchors.right.value - anchors.width.value;
            anchors.horizontal.value = (anchors.right.value - anchors.left.value) / 2;
        }
        else if (anchors.horizontal.activated)
        {
            anchors.left.value = anchors.horizontal.value - (anchors.width.value / 2);
            anchors.right.value = anchors.horizontal.value + (anchors.width.value / 2);
        }
        
        if (anchors.top.activated)
        {
            anchors.bottom.value = anchors.top.value + anchors.height.value;
            anchors.vertical.value = (anchors.bottom.value - anchors.top.value) / 2;
        }
        else if (anchors.bottom.activated)
        {
            anchors.top.value = anchors.bottom.value - anchors.height.value;
            anchors.vertical.value = (anchors.bottom.value - anchors.top.value) / 2;
        }
        else if (anchors.vertical.activated)
        {
            anchors.top.value = anchors.vertical.value - (anchors.height.value / 2);
            anchors.bottom.value = anchors.vertical.value + (anchors.height.value / 2);
        }
    }

    void Element::CalculateTransform()
    {
        if (anchors.width.activated == false || anchors.height.activated == false)
        {
            SYNERGY_ASSERT(false, "Both the width and height constraints should be set.");
        }
        
        size = glm::vec2 { anchors.width.value / 800.0f, anchors.height.value / 600.0f };
        
        if (anchors.left.activated == false && anchors.right.activated == false && anchors.horizontal.activated == false)
        {
            SYNERGY_ASSERT(false, "Atleast one constraint on the X-axis should be set.");
        }
        
        if (anchors.top.activated == false && anchors.bottom.activated == false && anchors.vertical.activated == false)
        {
            SYNERGY_ASSERT(false, "Atleast one constraint on the Y-axis should be set.");
        }
        
        this->CalculateInactiveAnchors();
        
        float x = anchors.left.value / 800.0f;
        float y = anchors.bottom.value / 600.0f;
        
        position = glm::vec3 { x, 1 - y, 1 };
    }
}
