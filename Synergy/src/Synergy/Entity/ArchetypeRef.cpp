// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include "Synergy/Entity/ArchetypeRef.h"

namespace Synergy
{
    ArchetypeRef::ArchetypeRef(Synergy::EntityRef entity) : Synergy::EntityRef(entity)
    {}

    Synergy::Scene* ArchetypeRef::GetScene()
    {
        return m_Scene;
    }
}
