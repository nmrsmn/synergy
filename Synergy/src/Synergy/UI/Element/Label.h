// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_LABEL_H
#define SYNERGY_UI_LABEL_H

#include "Synergy/Core.h"
#include "Synergy/Font.h"
#include "Synergy/UI/Anchors.h"
#include "Synergy/UI/Element.h"
#include "Synergy/UI/Style.h"
#include "Synergy/UI/View.h"

namespace Synergy::UI
{
    class SYNERGY_API Label : public Synergy::UI::Element
    {
    public:
        struct Style
        {
            Synergy::Ref<Synergy::Font> font;
            glm::vec3 color = { 1, 1, 1 };
            Synergy::UI::Style::TextAlignment align = Synergy::UI::Style::TextAlignment::LEFT;
            Synergy::UI::Style::Gravity gravity = Synergy::UI::Style::Gravity::TOP;
        };

    public:
        static Synergy::Ref<Synergy::UI::Label> Create(Synergy::Ref<Synergy::UI::View> root, const std::string& text, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        static Synergy::Ref<Synergy::UI::Label> Create(Synergy::Ref<Synergy::UI::View> root, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        static Synergy::Ref<Synergy::UI::Label> Create(Synergy::Ref<Synergy::UI::Container> container, const std::string& text, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        static Synergy::Ref<Synergy::UI::Label> Create(Synergy::Ref<Synergy::UI::Container> container, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        
    protected:
        Label(Synergy::Ref<Synergy::UI::View> root, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        Label(Synergy::Ref<Synergy::UI::Container> container, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        
        virtual void Submit() override;

    public:
        Synergy::UI::Label::Style style;
        
    private:
        const std::string text;
    };
}

#endif
