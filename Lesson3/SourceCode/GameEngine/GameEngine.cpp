// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <vector>

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "ControlledCubeGameObject.h"
#include "MovingCubeGameObject.h"
#include "JumpingCubeGameObject.h"
#include "GameTimer.h"
#include "InputHandler.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();
    InputHandler* inputHandler = new InputHandler();

    std::vector<JumpingCubeGameObject*> jumpCubes;
    std::vector<MovingCubeGameObject*> movingCubes;
    std::vector<ControlledCubeGameObject*> controlledCubes;

    srand(time(NULL));

    // create random type for each of 100 cubes
    for (float xCoord = -5.f; xCoord < 5.1f; xCoord += 1.f) {
        for (float zCoord = -3.5f; zCoord < 6.6f; zCoord += 1.f) {
            int type = rand() % 3;
            switch (type) {
            case 0:
            {
                JumpingCubeGameObject* jumpCube = new JumpingCubeGameObject();
                jumpCube->SetStartPosition(xCoord, 0.0f, zCoord);
                jumpCubes.push_back(jumpCube);  // (std::move(jumpCube));
                break;
            }
            case 1:
            {
                MovingCubeGameObject* movCube = new MovingCubeGameObject();
                movCube->SetStartPosition(xCoord, 0.0f, zCoord);
                movingCubes.push_back(movCube);  // (std::move(movingCube))
                break;
            }
            case 2:
            {
                ControlledCubeGameObject* contrCube = new ControlledCubeGameObject();
                contrCube->SetPosition(xCoord, 0.0f, zCoord);
                controlledCubes.push_back(contrCube);  // (std::move(contrCube));
            }
            }
        }
    }

    for (int i = 0; i < jumpCubes.size(); ++i) {
        renderThread->EnqueueCommand(RC_CreateCubeRenderObject, jumpCubes[i]->GetRenderProxy());
    }
    for (int i = 0; i < movingCubes.size(); ++i) {
        renderThread->EnqueueCommand(RC_CreateCubeRenderObject, movingCubes[i]->GetRenderProxy());
    }
    for (int i = 0; i < controlledCubes.size(); ++i) {
        renderThread->EnqueueCommand(RC_CreateCubeRenderObject, controlledCubes[i]->GetRenderProxy());
    }

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            inputHandler->Update();

            timer.Tick();
              
            int xMovingDirection = 0;
            if (inputHandler->GetInputState().test(eIC_GoLeft))
                xMovingDirection -= 1;
            if (inputHandler->GetInputState().test(eIC_GoRight))
                xMovingDirection += 1;

            //cube->SetPosition(0.f, 0.f, 6.5f);
            //cube->Move(xMovingDirection, timer.DeltaTime());
            for (int i = 0; i < jumpCubes.size(); ++i) {
                jumpCubes[i]->Move(timer.DeltaTime());
            }
            for (int i = 0; i < movingCubes.size(); ++i) {
                movingCubes[i]->Move(timer.TotalTime());
            }
            for (int i = 0; i < controlledCubes.size(); ++i) {
                controlledCubes[i]->Move(xMovingDirection, timer.DeltaTime());
            }


            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
