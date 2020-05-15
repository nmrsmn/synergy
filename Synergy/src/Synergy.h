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

#include "Synergy/UI/Anchors.h"
#include "Synergy/UI/Constraints.h"
#include "Synergy/UI/Element.h"
#include "Synergy/UI/Element/Button.h"
#include "Synergy/UI/Element/Container.h"
#include "Synergy/UI/Element/Label.h"
#include "Synergy/UI/Manager.h"
#include "Synergy/UI/Renderer.h"
#include "Synergy/UI/Style.h"
#include "Synergy/UI/View.h"

// REFACTORED:
#include "Synergy/ECS/ComponentPoolBase.h"
#include "Synergy/ECS/ComponentPool.h"
#include "Synergy/ECS/Entity.h"
#include "Synergy/ECS/EntityId.h"
#include "Synergy/ECS/EntityRef.h"
#include "Synergy/ECS/Scene.h"
#include "Synergy/ECS/System.h"

#include "Synergy/Event/EventDispatcher.h"
#include "Synergy/Event/EventHandler.h"

#include "Synergy/Util/SlotMap.h"

// Entry point
#include "Synergy/EntryPoint.h"

#endif
