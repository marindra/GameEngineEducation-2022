#pragma once

#include <sol/sol.hpp>

#include "IScriptProxy.h"


class SCRIPTSYSTEM_API CScriptProxy final : public IScriptProxy
{
public:
	void Update();
	void Init(const char* fileName);
private:
	sol::state lua_script;
};

