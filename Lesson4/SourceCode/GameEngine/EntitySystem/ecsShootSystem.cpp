#include "ecsShootSystem.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "ecsMesh.h"
#include "flecs.h"
#include "../InputHandler.h"

void register_ecs_shooting_systems(flecs::world& ecs)
{
    static auto inputQuery = ecs.query<InputHandlerPtr>();
    ecs.system<const CubeCreator, Position, ShotsCounter*, Recharge const*>()
      .each([&](flecs::entity e, const CubeCreator& creator, Position& pos, ShotsCounter* counter, Recharge const* recharger)
      {
        if (e.has<TinyTimer>()) {
          return;
        }

        inputQuery.each([&](InputHandlerPtr input)
        {
          if (input.ptr->GetInputState().test(eIC_Jump)) {
            auto cube = e.world().entity()
                .set(Position{ pos.x, pos.y, pos.z })
                .set(Velocity{ 0.f, 0.f, 5.f })
                .set(FrictionAmount{ 0.7f })
                .set(Gravity{ 0.f, -9.8065f, 0.f })
                //.set(Bounciness{ .1f }) - shoots ignore Bounciness
                .set(BouncePlane{ 0.f, 1.f, 0.f, 0.1f })
                .set(Shoot{ 5.f })
                .add<DestroyOnEnd>()
                .add<CubeMesh>();

            e.set(TinyTimer{ creator.coolDownTime })
                .add<RemoveOnEnd>();

            if (counter && recharger) {
              --counter->shotCount;
              if (counter->shotCount <= 0) {
                counter->shotCount = recharger->shotCount;
                e.set<TinyTimer>({ recharger->time });
                e.add<RemoveOnEnd>();
              }
            }
          }
        });
      });

    ecs.system<TinyTimer, const RemoveOnEnd>()
      .each([&](flecs::entity e, TinyTimer& value, const RemoveOnEnd&)
      {
        if (value.leastTime > 0) {
          return;
        }
        e.remove<RemoveOnEnd>();
        e.remove<TinyTimer>();

      });

    ecs.system<TinyTimer, const DestroyOnEnd>()
      .each([&](flecs::entity e, TinyTimer& value, const DestroyOnEnd&)
      {
        if (value.leastTime > 0) {
          return;
        }

        e.remove<TinyTimer>()
          .remove<DestroyOnEnd>()
          .add<DestroyIt>();
      });

    ecs.system<const DestroyIt, RenderProxyPtr* >()
      .each([&](flecs::entity e, const DestroyIt&, RenderProxyPtr* meshPtr)
      {
        //need to delete explicitly!
        if (meshPtr) {
            delete meshPtr->ptr;
        }
        e.destruct();
      });

    ecs.system<const Shoot, Velocity, Position, const BouncePlane>()
      .each([&](flecs::entity e, const Shoot & val, Velocity& vel, Position &pos, const BouncePlane &plane)
      {
        float dotPos = plane.x * pos.x + plane.y * pos.y + plane.z * pos.z;
        float dotVel = plane.x * vel.x + plane.y * vel.y + plane.z * vel.z;
        if (dotPos < plane.w)
        {
            pos.x -= (dotPos - plane.w) * plane.x;
            pos.y -= (dotPos - plane.w) * plane.y;
            pos.z -= (dotPos - plane.w) * plane.z;

            vel.x -= plane.x * dotVel;
            vel.y -= plane.y * dotVel;
            vel.z -= plane.z * dotVel;


            if (!e.has<TinyTimer>()) {
                e.set(TinyTimer{ val.livingTimeAfterBounce });
            }
        }
      });

    static auto targets = ecs.query<const Target, const Position>();
    ecs.system<const Shoot, const Position>()
      .each([&](flecs::entity e, const Shoot&, const Position& shootPos) {
        targets.each([&](const Target&, const Position& targetPos) {
            if (abs(shootPos.x - targetPos.x) <= 2.f && abs(shootPos.y - targetPos.y) <= 2.f && abs(shootPos.z - targetPos.z) <= 2.f) {
                e.add<DestroyIt>();
            }
            });
      });

    static auto targetsWithAdd = ecs.query<const TargetWithAdding, const Position>();
    static auto myCubeCreator = ecs.query<const CubeCreator, ShotsCounter>();
    ecs.system<const Shoot, const Position>()
      .each([&](flecs::entity e, const Shoot&, const Position& shootPos) {
        targetsWithAdd.each([&](const TargetWithAdding& val, const Position& targetPos) {
            if (abs(shootPos.x - targetPos.x) <= 2.f && abs(shootPos.y - targetPos.y) <= 2.f && abs(shootPos.z - targetPos.z) <= 2.f) {
                //need to add.. maybe like this? I need to think...
                myCubeCreator.each([&](const CubeCreator&, ShotsCounter & cnt) {
                    cnt.shotCount += val.addShotCount;
                    });
                e.add<DestroyIt>();
            }
            });
      });
}