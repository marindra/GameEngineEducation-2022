#include "ScriptProxy.h"
#include "../GameEngine/InputHandler.h"
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

void CScriptProxy::Init(const char* filename) {
	lua_script.open_libraries(sol::lib::base);

	std::ifstream f(filename);
    std::string lua_code;

    //if (!f) {
    //    lua_script.open_libraries(sol::lib::base, sol::lib::package);
        //lua_script.script("print('File wasnt found.')");
    //}

	//InputHandler* inputHandler = new InputHandler(); <- I don't like this way! I want to share existed one!
	//lua_script.new_usertype<InputHandler>("InputHandler", "inputHandler", inputHandler, "TestInput", &(InputHandler::Test));
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

void CScriptProxy::Update() {
	//lua_script["Update"]();
}