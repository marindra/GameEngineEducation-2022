#pragma once

#include <sol/sol.hpp>

#include "IScriptProxy.h"
#include "InputHandler.h"


class SCRIPTSYSTEM_API CScriptProxy final : public IScriptProxy
{
public:
	float UpdateControllable(float deltaTime, float speed, float velocity);
	void Init(const char* fileName, InputHandler* inpHndlrPtr=nullptr);
private:
	sol::state lua_script;
	InputHandler* inputHandlerPtr = nullptr;
};

