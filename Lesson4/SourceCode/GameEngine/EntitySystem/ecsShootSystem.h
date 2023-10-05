#pragma once
#include "flecs.h"

struct CubeCreator {};
struct Recharge { int shotCount; float time; };
struct ShotsCounter { int shotCount = 0; };
struct Shoot { float livingTimeAfterBounce; };

struct RemoveOnEnd {}; // remove timer at the end
struct DestroyOnEnd {}; // destroy object when time runs out

void register_ecs_shooting_systems(flecs::world& ecs);