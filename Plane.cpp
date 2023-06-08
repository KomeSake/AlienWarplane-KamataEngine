#include "Plane.h"

int Plane::Timers(int milli, int index)
{
	if (!_isTimeOpen[index]) {
		_timeStart[index] = clock();
		_isTimeOpen[index] = true;
	}
	_timeEnd[index] = clock();
	if (_timeEnd[index] - _timeStart[index] > milli) {
		_isTimeOpen[index] = false;
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

//感觉好像有问题，如果播放多个帧动画会出问题。
void Plane::FrameAnimation(float x, float y, int sprite[], int frameTime)
{
	if (Timers(frameTime, 0)) {
		_frameIndex++;
		if (_frameIndex > sizeof(sprite) / sizeof(sprite[0]) - 1) {
			_frameIndex = 0;
		}
	}
	Novice::DrawSprite((int)x, (int)y, sprite[_frameIndex], 1, 1, 0, WHITE);
}

float Plane::GetPosX()
{
	return _posX;
}
float Plane::GetPosY()
{
	return _posY;
}


