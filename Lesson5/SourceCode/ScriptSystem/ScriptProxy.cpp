#include "ScriptProxy.h"
#include "InputHandler.h"
#include <fstream>

/*class Foo {
public:
	int bark = 200;
	int mrr = 20;

	bool isBarkMrr() {
		return this->bark == this->mrr;
	}

	bool isBarkNum(int num) {
		return this->bark == num;
	}
};*/

void CScriptProxy::Init(const char* filename, InputHandler* inpHndlrPtr) {
	this->inputHandlerPtr = inpHndlrPtr;
	lua_script.open_libraries(sol::lib::base);

	std::ifstream f(filename);
    std::string lua_code;

	lua_script.new_usertype<InputHandler>("InputHandler", "TestInput", &InputHandler::Test);

	lua_script.script_file(filename);

/*	Foo foo;
	lua_script["foo"] = &foo;
	Foo& foo2 = lua_script["foo"];
	foo2.bark = 32;
	assert(foo.bark == 32); //Yappi!

	lua_script.new_usertype<Foo>("Foo", "bark", &Foo::bark);
	lua_script.script("assert(foo.bark==32)\nfoo.bark=20");
	assert(foo.isBarkMrr());

	lua_script["Test"] = &Foo::isBarkNum;
	lua_script.script("assert(Test(foo,20))");*/
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