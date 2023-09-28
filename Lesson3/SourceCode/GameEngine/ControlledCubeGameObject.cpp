#include "ControlledCubeGameObject.h"

void ControlledCubeGameObject::Move(int directionOfXMoving, float deltaTime) {
//	float curPosition[3];
//	for (int i = 0; i < 3; ++i) {
//		curPosition[i] = this->m_vPosition[i];
//	}

	this->SetPosition(this->m_vPosition[0] + directionOfXMoving * this->velocityX * deltaTime, this->m_vPosition[1], this->m_vPosition[2]);  // curPosition[1], curPosition[2]);
	return;
}

void ControlledCubeGameObject::SetXVelocity(float velocityX) {
	this->velocityX = velocityX;
}