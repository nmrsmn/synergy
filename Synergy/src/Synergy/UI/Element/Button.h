// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_BUTTON_H
#define SYNERGY_UI_BUTTON_H

#include "Synergy/Core.h"
#include "Synergy/UI/Element.h"

namespace Synergy::UI
{
    class SYNERGY_API Button : public Synergy::UI::Element
    {
    public:
        static Synergy::Ref<Synergy::UI::Button> Create(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        static Synergy::Ref<Synergy::UI::Button> Create(Synergy::Ref<Synergy::UI::Container> container, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        
    protected:
        Button(Synergy::Ref<Synergy::UI::View> root, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        Button(Synergy::Ref<Synergy::UI::Container> container, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        
    protected:
        virtual void Submit() override;
    };
}

#endif
