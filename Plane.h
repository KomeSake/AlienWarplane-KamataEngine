#pragma once
#include <Novice.h>
#include <ctime>
#include "Bullet.h"

class Plane
{
protected:
	//不要忘了初始化呀！就算是头文件初始化也没问题的！
	float _posX = 0;
	float _posY = 0;
	float _width = 0;
	float _high = 0;

	int _hp = 0;
	float _speed = 0;

	int Timers(int milli, int index);


public:
	void MoveToTarget(float& objX, float& objY, float targetX, float targetY, float speed);
	void FrameAnimation(float x, float y, int sprite);
	float GetPosX();
	float GetPosY();
};

