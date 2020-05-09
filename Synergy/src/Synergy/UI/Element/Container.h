// Created by Niels Marsman on 08-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_UI_CONTAINER_H
#define SYNERGY_UI_CONTAINER_H

#include "Synergy/Core.h"
#include "Synergy/UI/Element.h"

namespace Synergy::UI
{
    class SYNERGY_API Container : public Synergy::UI::Element
    {
    public:
        void Add(Synergy::Ref<Synergy::UI::Element> element);
        
    protected:
        virtual void Submit() override;
        
    private:
        std::vector<Synergy::Ref<Synergy::UI::Element>> childs;
    };
}

#endif
