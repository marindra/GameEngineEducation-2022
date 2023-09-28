#pragma once

#include "CubeGameObject.h"

class MovingCubeGameObject : public CubeGameObject {
private:
	float startPosition[3];
	float speedZFactor = 1.0f;
	float amplitudeZ = 1.0f;
public:
	void SetStartPosition(float x, float y, float z);
	void SetSpeedZFactor(float factorZ);
	void SetAmplitudeZ(float amplitudeZ);

	void Move(float totalTime);
};