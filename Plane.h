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
	void MoveToTarget(float& objX, float& objY, float targetX, float targetY, float speed);
public:
	void FrameAnimation(float x, float y, int sprite);
	void FrameAnimation(float x, float y, int sprite[], int frameTime);
	float GetPosX();
	float GetPosY();

private:
	//不要再随随便便弄全局变量了！全局变量只有一个！
	//想要通过这种对象方法来制作游戏，那就必须要要写类的成员变量！
	//以下是用于计时器的变量,0号位是用来给帧动画用的
	clock_t _timeStart[6] = { 0 };
	clock_t _timeEnd[6] = { 0 };
	bool _isTimeOpen[6] = { 0 };

	//给帧动画用的
	int _frameIndex = 0;
};

