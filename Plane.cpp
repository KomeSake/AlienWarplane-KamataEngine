#include "Plane.h"


clock_t start[5] = { 0 };
clock_t end[5] = { 0 };
bool isStart[5] = { 0 };
int Plane::Timers(int milli, int index)
{
	if (!isStart[index]) {
		start[index] = clock();
		isStart[index] = true;
	}
	end[index] = clock();
	if (end[index] - start[index] > milli) {
		isStart[index] = false;
		return 1;
	}
	return 0;
}

void Plane::MoveToTarget(float& objX, float& objY, float targetX, float targetY, float speed)
{
	float distanceX = targetX - objX;
	float distanceY = targetY - objY;
	float disToTravel = speed * 1.2f;
	float disToTarget = sqrtf(distanceX * distanceX + distanceY * distanceY);
	float moveRatio = disToTravel / disToTarget;

	if (disToTravel >= disToTarget) {
		objX = targetX;
		objY = targetY;
	}
	else {
		objX += distanceX * moveRatio;
		objY += distanceY * moveRatio;
	}
}

void Plane::FrameAnimation(float x, float y, int sprite)
{
	Novice::DrawSprite((int)x, (int)y, sprite, 1, 1, 0, WHITE);
}

float Plane::GetPosX()
{
	return _posX;
}
float Plane::GetPosY()
{
	return _posY;
}


