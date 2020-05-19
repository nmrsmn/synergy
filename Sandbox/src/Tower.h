// Created by Niels Marsman on 18-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SANDBOX_TOWER_H
#define SANDBOX_TOWER_H

#include "Synergy.h"

class Tower
{
public:
    static void CreatePlaceholder(Synergy::Scene& scene, Synergy::ArchetypeRef archetype, std::function<void (void)> place)
    {
        Synergy::EntityRef entity = scene.Spawn(archetype);
        Placeholder& placeholder = entity.Get<Placeholder>();
        placeholder.place = place;
    }
    
    static void PlaceGunTower()
    {}
    
    static void PlaceAntiAirTower()
    {}
    
    static void PlaceRocketTower()
    {}
    
    static void PlaceCannonTower()
    {}

private:
    Synergy::EntityRef m_Placeholder;
};

#endif
