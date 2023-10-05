#pragma once
#include "flecs.h"

struct CubeCreator { float coolDownTime = 0.01f; };
struct Recharge { int shotCount; float time; };
struct ShotsCounter { int shotCount = 0; };
struct Shoot { float livingTimeAfterBounce; };

struct Target {};
struct TargetWithAdding { int addShotCount = 1; };

struct RemoveOnEnd {}; // remove timer at the end
struct DestroyOnEnd {}; // destroy object when time runs out
struct DestroyIt {};

void register_ecs_shooting_systems(flecs::world& ecs);