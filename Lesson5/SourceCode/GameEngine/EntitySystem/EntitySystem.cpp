#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "../Tinyxml2/tinyxml2.h"

void EntitySystem::CreateEntityFromXML(const char* filename) {
    // Possible components list:
    // PositionX, PositionY, PositionZ
    // CubeMesh
    // Controllable
    // Speed
    // VelocityX, VelocityY, VelocityZ
    // Bounciness
    // BouncePlaneX, BouncePlaneY, BouncePlaneZ, BouncePlaneW
    // FrictionAmount
    // GravityX, GravityY, GravityZ
    // JumpSpeed

    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError eResult = xmlDoc.LoadFile(filename);
    assert(eResult == tinyxml2::XML_SUCCESS);

    tinyxml2::XMLNode* pRoot = xmlDoc.FirstChildElement("GameObject");
    assert(pRoot != nullptr);

    auto object = ecs.entity();

    // start parsing component for object
    if (pRoot->FirstChildElement("CubeMesh") != nullptr) {
        object.add<CubeMesh>();
    }

    // find position (x,y,z)
    tinyxml2::XMLElement* pElement1 = pRoot->FirstChildElement("PositionX");
    tinyxml2::XMLElement* pElement2 = pRoot->FirstChildElement("PositionY");
    tinyxml2::XMLElement* pElement3 = pRoot->FirstChildElement("PositionZ");
    if (pElement1 != nullptr && pElement2 != nullptr && pElement3 != nullptr) {
        // all 3 components should exist
        float position[3];
        eResult = pElement1->QueryFloatText(&position[0]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert PositionX to float

        eResult = pElement2->QueryFloatText(&position[1]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert PositionY to float

        eResult = pElement3->QueryFloatText(&position[2]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert PositionZ to float

        object.set(Position{ position[0], position[1], position[2] });
    }

    // find tag Controllable
    tinyxml2::XMLElement* pElement = pRoot->FirstChildElement("Controllable");
    if (pElement != nullptr) {
        object.add<Controllable>();
    }

    // Note: For elements requiring 3 components (x, y, z), pElement1, pElement2, pElement3 are used.
    // For elements requiring only 1 component, pElement is used. (Without number)

    pElement = pRoot->FirstChildElement("Speed");
    if (pElement != nullptr) {
        float res;
        eResult = pElement->QueryFloatText(&res);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert Speed to float
        object.set(Speed{ res });
    }

    // find velocity
    pElement1 = pRoot->FirstChildElement("VelocityX");
    pElement2 = pRoot->FirstChildElement("VelocityY");
    pElement3 = pRoot->FirstChildElement("VelocityZ");
    if (pElement1 != nullptr && pElement2 != nullptr && pElement3 != nullptr) {
        // all 3 components should exist
        float velocity[3];
        eResult = pElement1->QueryFloatText(&velocity[0]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert VelocityX to float

        eResult = pElement2->QueryFloatText(&velocity[1]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert VelocityY to float

        eResult = pElement3->QueryFloatText(&velocity[2]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert velocityZ to float

        object.set(Velocity{ velocity[0], velocity[1], velocity[2] });
    }

    // find Bounciness
    pElement = pRoot->FirstChildElement("Bounciness");
    if (pElement != nullptr) {
        float res;
        eResult = pElement->QueryFloatText(&res);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert Bounciness to float

        object.set(Bounciness{ res });
    }

    // find BouncePlaneX, BouncePlaneY, BouncePlaneZ, BouncePlaneW
    pElement1 = pRoot->FirstChildElement("BouncePlaneX");
    pElement2 = pRoot->FirstChildElement("BouncePlaneY");
    pElement3 = pRoot->FirstChildElement("BouncePlaneZ");
    tinyxml2::XMLElement* pElement4 = pRoot->FirstChildElement("BouncePlaneW");

    if (pElement1 != nullptr && pElement2 != nullptr && pElement3 != nullptr && pElement4 != nullptr) {
        float bouncePlane[4];
        eResult = pElement1->QueryFloatText(&bouncePlane[0]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert BouncePlaneX to float

        eResult = pElement2->QueryFloatText(&bouncePlane[1]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert BouncePlaneX to float

        eResult = pElement3->QueryFloatText(&bouncePlane[2]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert BouncePlaneX to float

        eResult = pElement4->QueryFloatText(&bouncePlane[3]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert BouncePlaneX to float

        object.set(BouncePlane{bouncePlane[0], bouncePlane[1], bouncePlane[2], bouncePlane[3]});

    }

    // find FrictionAmount
    pElement = pRoot->FirstChildElement("FrictionAmount");
    if (pElement != nullptr) {
        float res;
        eResult = pElement->QueryFloatText(&res);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert FrictionAmount to float

        object.set(FrictionAmount{ res });
    }

    // find GravityX, GravityY, GravityZ
    pElement1 = pRoot->FirstChildElement("GravityX");
    pElement2 = pRoot->FirstChildElement("GravityY");
    pElement3 = pRoot->FirstChildElement("GravityZ");
    if (pElement1 != nullptr && pElement2 != nullptr && pElement3 != nullptr) {
        // all 3 components should exist
        float gravity[3];
        eResult = pElement1->QueryFloatText(&gravity[0]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert GravityX to float

        eResult = pElement2->QueryFloatText(&gravity[1]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert GravityY to float

        eResult = pElement3->QueryFloatText(&gravity[2]);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert GravityZ to float

        object.set(Gravity{ gravity[0], gravity[1], gravity[2] });
    }

    // find JumpSpeed
    pElement = pRoot->FirstChildElement("JumpSpeed");
    if (pElement != nullptr) {
        float res;
        eResult = pElement->QueryFloatText(&res);
        assert(eResult == tinyxml2::XML_SUCCESS); // Check: System can convert JumpSpeed to float

        object.set(JumpSpeed{ res });
    }
}

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, CScriptProxy* scriptProxy)
{
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });
    ecs.entity("scriptProxy")
        .set(CScriptProxyPtr{ scriptProxy });

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);

    CreateEntityFromXML("../../../Assets/Configs/cube.xml");
/*    auto cubeControl = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 0.f, 0.f })
        .set(Speed{ 10.f })
        .set(FrictionAmount{ 0.9f })
        .set(JumpSpeed{ 10.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
        .set(Bounciness{ 0.3f })
        .add<Controllable>()
        .add<CubeMesh>();*/

/*    auto cubeMoving = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 3.f, 0.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 5.f })
        .set(Bounciness{ 1.f })
        .add<CubeMesh>();*/
}

void EntitySystem::Update()
{
    ecs.progress();
}