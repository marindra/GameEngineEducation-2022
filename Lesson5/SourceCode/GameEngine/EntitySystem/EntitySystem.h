#pragma once

#include "flecs.h"
#include "RenderEngine.h"
#include "../ScriptSystem/InputHandler.h"
#include "../ScriptSystem/ScriptProxy.h"

class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, CScriptProxy* scriptProxy);

	void Update();
private:
	flecs::world ecs;
};

