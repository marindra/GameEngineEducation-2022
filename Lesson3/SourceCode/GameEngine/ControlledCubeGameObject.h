#pragma once

#include "CubeGameObject.h"

class ControlledCubeGameObject : public CubeGameObject {
private:
	float velocityX = 1.0f;
public:
	void SetXVelocity(float velocityX);
	void Move(int directionOfXMoving, float deltaTime);
};