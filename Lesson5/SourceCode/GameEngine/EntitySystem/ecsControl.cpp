#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
//#include "../ScriptSystem/InputHandler.h"
#include "ScriptProxy.h"

void register_ecs_control_systems(flecs::world &ecs)
{
  static auto scriptsQuery = ecs.query<CScriptProxyPtr>();
  ecs.system<Velocity, const Speed, const Controllable>()
    .each([&](flecs::entity e, Velocity &vel, const Speed &spd, const Controllable &)
    {
      scriptsQuery.each([&](CScriptProxyPtr scriptProxy_ptr)
      {
              vel.x = scriptProxy_ptr.ptr->UpdateControllable(e.delta_time(), spd, vel.x);
        // need to add Script Here!
      });
    });

/*  static auto inputQuery = ecs.query<InputHandlerPtr>();
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
    });*/
}

