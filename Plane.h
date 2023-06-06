#pragma once
#include <Novice.h>
#include <ctime>
#include "Bullet.h"

class Plane
{
protected:
	float _posX;
	float _posY;
	float _width;
	float _high;

	int _hp;
	float _speed;

	int Timers(int milli, int index);

public:
	void FrameAnimation(float x, float y, int sprite);
	float GetPosX();
	float GetPosY();
};

