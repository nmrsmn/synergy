// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <algorithm>

#include "Synergy/UI/Element/Label.h"

#include "Synergy/UI/Renderable.h"
#include "Synergy/UI/Renderer.h"

namespace Synergy::UI
{
    Synergy::Ref<Synergy::UI::Label> Label::Create(Synergy::Ref<Synergy::UI::View> root, const std::string& text, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        return Synergy::UI::Label::Create(root, text, {}, constraints);
    }

    Synergy::Ref<Synergy::UI::Label> Label::Create(Synergy::Ref<Synergy::UI::View> root, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        struct RefEnabler : public Synergy::UI::Label
        {
            explicit RefEnabler(Synergy::Ref<Synergy::UI::View> root, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
                : Synergy::UI::Label(root, text, style, constraints) { }
        };
        
        Synergy::Ref<Synergy::UI::Label> item = Synergy::CreateRef<RefEnabler>(root, text, style, constraints);
        Synergy::UI::Element::Emplace(item, item->parent);
        
        return item;
    }

    Synergy::Ref<Synergy::UI::Label> Label::Create(Synergy::Ref<Synergy::UI::Container> container, const std::string& text, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        return Synergy::UI::Label::Create(container, text, {}, constraints);
    }

    Synergy::Ref<Synergy::UI::Label> Label::Create(Synergy::Ref<Synergy::UI::Container> container, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
    {
        struct RefEnabler : public Synergy::UI::Label
        {
            explicit RefEnabler(Synergy::Ref<Synergy::UI::Container> container, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
                : Synergy::UI::Label(container, text, style, constraints) { }
        };
        
        Synergy::Ref<Synergy::UI::Label> item = Synergy::CreateRef<RefEnabler>(container, text, style, constraints);
        Synergy::UI::Element::Emplace(item, item->parent);
        
        return item;
    }

    Label::Label(Synergy::Ref<Synergy::UI::View> root, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
        : style(style), text(text), Synergy::UI::Element(root, constraints) { }

    Label::Label(Synergy::Ref<Synergy::UI::Container> container, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
        : style(style), text(text), Synergy::UI::Element(container, constraints) { }

    void Label::Update(const std::string& text)
    {
        this->text = text;
    }

    void Label::Submit()
    {
        Synergy::UI::Renderer::Submit(Synergy::UI::Quad { position, size, { 1, 0, 0, .2 } });
        
        if (style.font)
        {
            glm::vec2 size { 0, 0 };
            glm::vec3 offset { 0, 0, 0.05 };
            
            float last = 0;
            for (const char character : text)
            {
                Synergy::Font::Glyph glyph = style.font->GetCharacter(character);
                last = (glyph.advance.x >> 6) - glyph.size.width;
                size.x += glyph.advance.x >> 6;
                size.y = std::max(size.y, (float) glyph.size.height);
            }
            
            size.x -= last;
            size *= style.size;
            
            if (style.align == Synergy::UI::Style::TextAlignment::RIGHT)
            {
                offset.x = this->size.x - size.x;
            }
            else if (style.align == Synergy::UI::Style::TextAlignment::CENTER)
            {
                offset.x = (this->size.x - size.x) / 2;
            }
            
            if (style.gravity == Synergy::UI::Style::Gravity::TOP)
            {
                offset.y = this->size.y - size.y;
            }
            else if (style.gravity == Synergy::UI::Style::Gravity::CENTER)
            {
                offset.y = (this->size.y - size.y) / 2;
            }
            
            Synergy::UI::Renderer::Submit(Synergy::UI::Quad { position + offset, size, { 1, 1, 0, .2 } });
            Synergy::UI::Renderer::Submit(Synergy::UI::Text { position + offset, { }, style.color, text, style.font, style.size });
        }
    };
}
