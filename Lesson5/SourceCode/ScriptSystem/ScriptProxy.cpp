#include "ScriptProxy.h"
#include "InputHandler.h"
#include <fstream>

void CScriptProxy::Init(const char* filename, InputHandler* inpHndlrPtr) {
	this->inputHandlerPtr = inpHndlrPtr;
	lua_script.open_libraries(sol::lib::base);

	std::ifstream f(filename);
    std::string lua_code;

	lua_script.new_usertype<InputHandler>("InputHandler", "TestInput", &InputHandler::Test);

	lua_script.script_file(filename);
}

float CScriptProxy::UpdateControllable(float deltaTime, float speed, float velocity) {
	lua_script["input"] = this->inputHandlerPtr;
	sol::protected_function updater = lua_script["UpdateMoveXForControllable"];

	auto velX = updater(deltaTime, speed, velocity);
	if (velX.valid()) {
		return (float)velX;
	}
	else {
		sol::error err = velX;
		assert(err.what());
		return 0.1f;
	}
}