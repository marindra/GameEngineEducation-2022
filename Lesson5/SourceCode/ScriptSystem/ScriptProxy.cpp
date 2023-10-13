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
	lua_script.open_libraries(sol::lib::base);

	std::ifstream f(filename);
    std::string lua_code;

	//InputHandler* inputHandler = new InputHandler(); <- I don't like this way! I want to share existed one!
	//lua_script.new_usertype<InputHandler>("InputHandler", "inputHandler", inputHandler, "TestInput", &(InputHandler::Test));

	lua_script["inputHandler"] = inpHndlrPtr;
	lua_script["Test"] = &InputHandler::Test;

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
	float result = lua_script["Update"](deltaTime, speed, velocity);
	return result;
}