#include "JumpingCubeGameObject.h"

void JumpingCubeGameObject::SetStartPosition(float x, float y, float z) {
	this->startPosition[0] = x;
	this->startPosition[1] = y;
	this->startPosition[2] = z;

	this->floorLevel = y;

	this->SetPosition(x, y, z);
}
void JumpingCubeGameObject::SetStartSpeedY(float speed) {
	this->startSpeedY = speed;
}

void JumpingCubeGameObject::Move(float deltaTime) {
	float curY = this->m_vPosition[1];
	if (curY <= this->floorLevel) {
		this->curSpeedY = this->startSpeedY;
		curY = this->floorLevel;
	}

	float futureSpeedY = this->curSpeedY + gAcceleration * deltaTime;
	float newY = curY + (this->curSpeedY + futureSpeedY) / 2.0f * deltaTime;

	//if (newY <= this->floorLevel) {
	//	newY = this->floorLevel;
	//}

	this->curSpeedY = futureSpeedY;
	this->SetPosition(this->m_vPosition[0], newY, this->m_vPosition[2]);
}