#pragma once

#include "CubeGameObject.h"

class JumpingCubeGameObject : public CubeGameObject {
private:
	const float gAcceleration = -9.8f;

	float floorLevel = 0.0f;
	float startPosition[3];
	float startSpeedY = 5.0f;
	float curSpeedY = 0.0f;
public:
	void SetStartPosition(float x, float y, float z);
	void SetStartSpeedY(float speedY);

	void Move(float deltaTime);
};