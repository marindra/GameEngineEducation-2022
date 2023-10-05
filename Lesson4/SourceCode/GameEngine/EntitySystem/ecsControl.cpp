#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "ecsMesh.h"
#include "flecs.h"
#include "../InputHandler.h"

void register_ecs_control_systems(flecs::world &ecs)
{
  static auto inputQuery = ecs.query<InputHandlerPtr>();
  ecs.system<Velocity, const Speed, const Controllable>()
    .each([&](flecs::entity e, Velocity &vel, const Speed &spd, const Controllable &)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        float deltaVel = 0.f;
        if (input.ptr->GetInputState().test(eIC_GoLeft))
          deltaVel -= spd;
        if (input.ptr->GetInputState().test(eIC_GoRight))
          deltaVel += spd;
        vel.x += deltaVel * e.delta_time();
      });
    });

  ecs.system<const Position, Velocity, const Controllable, const BouncePlane, const JumpSpeed>()
    .each([&](const Position &pos, Velocity &vel, const Controllable &, const BouncePlane &plane, const JumpSpeed &jump)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        constexpr float planeEpsilon = 0.1f;
        if (plane.x*pos.x + plane.y*pos.y + plane.z*pos.z < plane.w + planeEpsilon)
          if (input.ptr->GetInputState().test(eIC_Jump))
            vel.y = jump.val;
      });
    });

  ecs.system<const CubeCreator, const Position>()
      .each([&](flecs::entity e, const CubeCreator&, const Position& pos)
      {
        inputQuery.each([&](InputHandlerPtr input)
        {
                if (input.ptr->GetInputState().test(eIC_GoLeft)) {
                    auto cube1 = e.world().entity()
                        .set(Position{ pos.x, pos.y, pos.z })
                        .set(Velocity{ 0.f, 0.f, 5.f })
                        .set(Gravity{ 0.f, -9.8065f, 0.f })
                        .set(Bounciness{ .3f })
                        .set(BouncePlane{ 0.f, 1.f, 0.f, -2.f})
                        .add<CubeMesh>();
                }/**/
        });
      });
}

