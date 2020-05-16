// Created by Niels Marsman on 16-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_SCENE_EVENTS_H
#define SYNERGY_ECS_SCENE_EVENTS_H

namespace Synergy
{
    struct EntitySpawnedEvent
    {
        EntitySpawnedEvent(Synergy::EntityRef entity) : entity(entity) {}
        EntitySpawnedEvent(const Synergy::EntitySpawnedEvent&) = default;
        
        Synergy::EntityRef entity;
    };

    struct EntityDestroyedEvent
    {
        EntityDestroyedEvent(Synergy::EntityRef entity) : entity(entity) {}
        EntityDestroyedEvent(const Synergy::EntityDestroyedEvent&) = default;
        
        Synergy::EntityRef entity;
    };

    struct ComponentAddedEvent
    {
        const Synergy::EntityRef entity;
        std::type_index component;
    };

    struct ComponentRemovedEvent
    {
        const Synergy::EntityRef entity;
        std::type_index component;
    };

    struct FrameStartEvent {};
    struct FrameEndEvent {};

    struct UpdateEvent
    {
        float dt;
    };
}

#endif
