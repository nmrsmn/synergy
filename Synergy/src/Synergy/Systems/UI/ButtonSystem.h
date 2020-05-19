// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_SYSTEM_UI_BUTTON_SYSTEM_H
#define SYNERGY_SYSTEM_UI_BUTTON_SYSTEM_H

namespace Synergy::UI
{
    class ButtonSystem
    {
    public:
        void Process(const Synergy::Transform transform, const Synergy::UI::Button button, const Synergy::UI::Image image) const
        {
            Synergy::Ref<Synergy::Texture> background = button.background.normal.texture;
            glm::vec4 color = button.background.normal.color;
            
            glm::vec2 mouse = Synergy::Input::GetMousePosition();
            glm::vec2 normalized = glm::vec2 { mouse.x / 800.f, 1 - (mouse.y / 600.f) };
            
            glm::vec2 position { transform.position.x - transform.scale.x / 2, transform.position.y - transform.scale.y / 2 };
            
            if ((normalized.x >= position.x && normalized.x <= position.x + transform.scale.x) &&
                (normalized.y >= position.y && normalized.y <= position.y + transform.scale.y))
            {
                if (button.background.hover.texture != nullptr)
                    background = button.background.hover.texture;
                
                if (Input::Get(Input::Mouse::BUTTON_LEFT).held)
                {
                    if (button.background.active.texture != nullptr)
                        background = button.background.active.texture;
                    
                    color = button.background.active.color;
                }
                else if (Input::Get(Input::Mouse::BUTTON_LEFT).released)
                {
                    button.onclick();
                }
            }
            
            Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { transform.position, transform.scale, background, color });
            
            if (image.texture != nullptr)
            {
                glm::vec3 offset = { 0.f, 0.f, 0.1f };
                Synergy::Renderer::CanvasRenderer::Submit(Synergy::Quad { transform.position + offset, transform.scale * .8f, image.texture, color });
            }
        }
        
        Synergy::EntitiesWith<const Synergy::Transform, const Synergy::UI::Button, const Synergy::UI::Image> m_Entities;
    };
}

#endif
