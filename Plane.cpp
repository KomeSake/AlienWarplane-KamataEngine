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

void Plane::GetHurtAni(float& x, float& y, float travelY, unsigned int color)
{
	//现在想到的办法还是利用计时器，如果在计时内，就调用这个动画
	//超过计时器时间(即是计时器返回1了)，就不调用这个动画
	//所以在动画之内，我需要做的就是让播放着不断左右晃动
	//并且使用插值移动到我想要的Y轴距离(Y+或者Y-)
	//还是有问题，那我到底要如何调用呢？正常想法肯定是调用一次这个方法，它就自己会运动了
	//可以有一个返回值，代表这个动画已经播放完了，播完了就把falg恢复

	if (_aniMode_getHurt == 1) {
		_aniMode_getHurt = 2;
		_getHurtPosX = x, _getHurtPosY = y;
	}
	else if (_aniMode_getHurt == 2) {
		x += _getHurtSpeedX;
		if (x >= _getHurtPosX + 5) {
			_getHurtSpeedX = -_getHurtSpeedX;
		}
		if (x <= _getHurtPosX - 5) {
			_getHurtSpeedX = -_getHurtSpeedX;
		}

		if (travelY < 0) {
			if (y > _getHurtPosY + travelY) {
				y -= _getHurtSpeedY;
			}
		}
		else if (travelY > 0) {
			if (y < _getHurtPosY + travelY) {
				y += _getHurtSpeedY;
			}
		}
		_color = color;
		if (Timers(_getHurtTime, 5)) {
			_aniMode_getHurt = 0;
			x = _getHurtPosX;
			_color = WHITE;
		}
	}
}

void Plane::FrameAnimation(float x, float y, int sprite, unsigned int color)
{
	Novice::DrawSprite((int)x, (int)y, sprite, 1, 1, 0, color);
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

unsigned int Plane::GetColor()
{
	return _color;
}


