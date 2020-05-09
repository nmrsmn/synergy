// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_VIEW_H
#define SYNERGY_UI_VIEW_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"
#include "Synergy/UI/Element.h"

namespace Synergy::UI
{
    class Manager;

    class SYNERGY_API View
    {
    public:
        void Add(Synergy::Ref<Synergy::UI::Element> element);
        
    private:
        void Submit();
        void Update(glm::uvec2 parent);
        
    private:
        std::vector<Synergy::Ref<Synergy::UI::Element>> childs;
        
        friend class Synergy::UI::Manager;
    };
}

#endif
