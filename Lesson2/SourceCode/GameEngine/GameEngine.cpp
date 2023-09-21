// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"

#include "Additional files/INIReader.h"
// Added _CRT_SECURE_NO_WARNINGS due to unsafe functions in ini.h

unsigned int GetCode(const std::string& line, unsigned int defaultValue) {
    if (line.length() != 1) {
        return defaultValue;
    }

    char curSymb = line[0];
    if (curSymb >= 'a' && curSymb <= 'z') {
        return toupper(curSymb);
    }
    if (curSymb >= 'A' && curSymb <= 'Z') {
        return curSymb;
    }
    return defaultValue;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    INIReader reader("Config/actionmap.ini");
    if (reader.ParseError() < 0) {
        //std::cout << "Can't load 'actionmap.ini'\n";
        //std::cout << "Path to config: 'Config/actionmap.ini'\n";
        return 1;
    }

    const std::string goLeft = reader.Get("Keyboard", "GoLeft", "A");
    unsigned int codeLeft = GetCode(goLeft, (unsigned int)'A');

    const std::string goRight = reader.Get("Keyboard", "GoRight", "D");
    unsigned int codeRight = GetCode(goRight, (unsigned int)'D');

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();

    GameObject* cube = new CubeGameObject();
    renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());

    MSG msg = { 0 };

//    bool needToSet = false;
    float cubeXTranslate = 0.f;
    const float maxSpeedX = 2.f;
    float speedX = 0.f;

    timer.Start();
    timer.Reset();

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            switch (msg.message)
            {
            case WM_KEYDOWN:
                if (GetAsyncKeyState(codeLeft) & 0x01)
                {
                    speedX = -maxSpeedX;
                }
                else if (GetAsyncKeyState(codeRight) & 0x01) {
                    speedX = maxSpeedX;
                }
                break;
            }
        }
        else
        {
            //float t = 0;
            timer.Tick();
            //t = sin(timer.TotalTime())*2;
            cubeXTranslate += speedX * timer.DeltaTime();
            speedX = 0;

            cube->SetPosition(cubeXTranslate, 0.0f, 1.0f);

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
