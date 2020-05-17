// Created by Niels Marsman on 05-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#ifndef SYNERGY_H
#define SYNERGY_H

#include "Synergy/Core.h"
#include "Synergy/Application.h"
#include "Synergy/Input.h"
#include "Synergy/Platform.h"

#include "Synergy/CameraController.h"

#include "Synergy/Renderer/CanvasRenderer.h"
#include "Synergy/Renderer/Renderer2D.h"
#include "Synergy/Renderer/Texture.h"
#include "Synergy/Renderer/TextureAtlas.h"

#include "Synergy/ResourcePack.h"

#include "Synergy/Renderer/Shaders.h"

#include "Synergy/Fonts.h"
#include "Synergy/Font.h"

// REFACTORED:
#include "Synergy/Components/Transform.h"
#include "Synergy/Components/UI/Renderable.h"
#include "Synergy/Entity/ArchetypeRef.h"
#include "Synergy/Entity/EntitiesWith.h"
#include "Synergy/Entity/Entity.h"
#include "Synergy/Entity/EntityId.h"
#include "Synergy/Entity/EntityRef.h"
#include "Synergy/Event/EventDispatcher.h"
#include "Synergy/Event/EventHandler.h"
#include "Synergy/Scene.h"
#include "Synergy/System/System.h"
#include "Synergy/Systems/UI/ButtonSystem.h"
#include "Synergy/Util/SlotMap.h"

// Entry point
#include "Synergy/EntryPoint.h"

#endif
