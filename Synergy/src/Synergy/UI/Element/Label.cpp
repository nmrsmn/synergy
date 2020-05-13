// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <algorithm>
#include <numeric>

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

    void Label::Update(const std::string& text)
    {
        this->Convert(text);
    }

    Label::Label(Synergy::Ref<Synergy::UI::View> root, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
        : style(style), Synergy::UI::Element(root)
    {
        this->type = Synergy::UI::Element::Type::INLINE;
        this->Initialize(constraints, [&]() { this->Convert(text); });
    }

    Label::Label(Synergy::Ref<Synergy::UI::Container> container, const std::string& text, Synergy::UI::Label::Style style, std::function<void (Synergy::UI::Constraint::Anchors&)> constraints)
        : style(style), Synergy::UI::Element(container)
    {
        this->type = Synergy::UI::Element::Type::INLINE;
        this->Initialize(constraints, [&]() { this->Convert(text); });
    }

    void Label::Convert(const std::string& text)
    {
        Synergy::UI::Label::Text structure;
        Synergy::UI::Label::Line line;
        Synergy::UI::Label::Word word;
        
        Synergy::Font::Glyph space = style.font->GetCharacter(32);
        
        glm::uvec2 max { -1, -1 };
        
        if (Anchors().width.Activated())
            max.x = Anchors().width.Value();
        
        if (Anchors().height.Activated())
            max.y = Anchors().height.Value();
        
        uint32_t lastCharacterSpacing = 0;
        
        std::string::const_iterator character;
        for (character = text.begin(); character != text.end(); character++)
        {
            Synergy::Font::Glyph glyph = style.font->GetCharacter(*character);
            
            if (*character != 32)
            {
                word.width += glyph.advance.x >> 6;
                word.characters += *character;
                
                lastCharacterSpacing = (glyph.advance.x >> 6) - glyph.size.width;
                lineHeight = std::max(lineHeight, (uint32_t) (glyph.size.height * style.size));
            }
            
            if (word.characters.size() > 0)
            {
                if (*character == 32 || character == text.end() - 1)
                {
                    uint32_t width = (word.width - lastCharacterSpacing + (line.words.size() > 0 ? space.advance.x >> 6 : 0)) * style.size;
                    
                    if (line.width + width < max.x)
                    {
                        if (line.words.size() > 0)
                            line.words.append(" ");
                        
                        line.words.append(word.characters);
                        line.width += width;
                        
                        word = {};
                    }
                    
                    if (line.width + width >= max.x || character == text.end() - 1)
                    {
                        if (line.words.size() == 0 && style.overflow == Synergy::UI::Style::Overflow::VISIBLE)
                        {
                            line.words.append(word.characters);
                            line.width = width;
                        }
                        
                        if (line.words.size() > 0)
                        {
                            structure.lines.push_back(line);
                            maxLineWidth = std::max(maxLineWidth, (uint32_t) line.width);
                            
                            line = {};
                            if (word.characters.size() > 0)
                            {
                                line.words.append(word.characters);
                                line.width = word.width;
                            }
                        }
                    }
                }
            }
        }
        
        if (!Anchors().width.Activated())
            this->size.x = maxLineWidth;
        
        if (!Anchors().height.Activated())
            this->size.y = lineHeight * structure.lines.size() * style.lineHeight;
        
        this->structure = structure;
    }

    void Label::Submit()
    {
        if (style.font && structure.lines.size() > 0)
        {
            glm::vec2 size { maxLineWidth, lineHeight };
            glm::vec3 offset { 0, 0, 0.15 };
            
            if (style.gravity == Synergy::UI::Style::Gravity::TOP)
            {
                offset.y += this->size.y - size.y;
            }
            else if (style.gravity == Synergy::UI::Style::Gravity::CENTER)
            {
                offset.y += (this->size.y - size.y) / 2;
            }
            
            Synergy::UI::Renderer::Submit(Synergy::UI::Quad { glm::vec3 { position.x, position.y, 0.8 }, this->size, { 1, 0, 0, .2 }, nullptr, 0 });
            
            for (auto line = structure.lines.rbegin(); line != structure.lines.rend(); ++line)
            {
                std::string text = (*line).words;
                
                size.x = (float) (*line).width;
                
                if (style.align == Synergy::UI::Style::TextAlignment::RIGHT)
                {
                    offset.x = this->size.x - size.x;
                }
                else if (style.align == Synergy::UI::Style::TextAlignment::CENTER)
                {
                    offset.x = (this->size.x - size.x) / 2;
                }
                
                Synergy::UI::Renderer::Submit(Synergy::UI::Quad { position + offset, size, { 1, 1, 0, .2 } });
                Synergy::UI::Renderer::Submit(Synergy::UI::Text { position + offset, { }, style.color, text, style.font, style.size });
                
                offset.y += lineHeight * style.lineHeight;
            }
        }
    }
}
