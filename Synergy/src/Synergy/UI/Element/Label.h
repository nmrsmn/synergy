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
        struct Word
        {
            std::string characters = "";
            uint16_t width = 0;
        };
        
        struct Line
        {
            std::string words = "";
            uint16_t width = 0;
        };
        
        struct Text
        {
            std::vector<Synergy::UI::Label::Line> lines;
        };
        
        struct Style
        {
            Synergy::Ref<Synergy::Font> font;
            glm::vec4 color = { 1, 1, 1, 1 };
            float size = 1.0f;
            float lineHeight = 1.8f;
            Synergy::UI::Style::TextAlignment align = Synergy::UI::Style::TextAlignment::LEFT;
            Synergy::UI::Style::Gravity gravity = Synergy::UI::Style::Gravity::TOP;
            Synergy::UI::Style::Overflow overflow = Synergy::UI::Style::Overflow::HIDDEN;
        };

    public:
        static Synergy::Ref<Synergy::UI::Label> Create(Synergy::Ref<Synergy::UI::View> root, const std::string& text, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        static Synergy::Ref<Synergy::UI::Label> Create(Synergy::Ref<Synergy::UI::View> root, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        static Synergy::Ref<Synergy::UI::Label> Create(Synergy::Ref<Synergy::UI::Container> container, const std::string& text, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        static Synergy::Ref<Synergy::UI::Label> Create(Synergy::Ref<Synergy::UI::Container> container, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        
    public:
        void Update(const std::string& text);
        
    protected:
        Label(Synergy::Ref<Synergy::UI::View> root, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        Label(Synergy::Ref<Synergy::UI::Container> container, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints = nullptr);
        
        void Convert(const std::string& text);
        
        virtual void Submit() override;

    public:
        Synergy::UI::Label::Style style;
        
    private:
        Synergy::UI::Label::Text structure;
        
        uint32_t maxLineWidth = 0;
        uint32_t lineHeight = 0;
        
        std::string text;
    };
}

#endif
