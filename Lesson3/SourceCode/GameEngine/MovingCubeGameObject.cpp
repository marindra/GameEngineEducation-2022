#include "MovingCubeGameObject.h"


void MovingCubeGameObject::SetStartPosition(float x, float y, float z) {
	this->startPosition[0] = x;
	this->startPosition[1] = y;
	this->startPosition[2] = z;
}

void MovingCubeGameObject::SetSpeedZFactor(float factorZ) {
	this->speedZFactor = factorZ;
}

void MovingCubeGameObject::SetAmplitudeZ(float amplitudeZ) {
	this->amplitudeZ = amplitudeZ;
}

void MovingCubeGameObject::Move(float totalTime) {
	this->SetPosition(this->startPosition[0], this->startPosition[1],
		this->startPosition[2] + this->amplitudeZ * sinf(this->speedZFactor * totalTime));
}