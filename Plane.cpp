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

int Plane::FrameTimers(int milli, int index)
{
	if (!_frame_isTimeOpen[index]) {
		_frame_timeStart[index] = clock();
		_frame_isTimeOpen[index] = true;
	}
	_frame_timeEnd[index] = clock();
	if (_frame_timeEnd[index] - _frame_timeStart[index] > milli) {
		_frame_isTimeOpen[index] = false;
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
	//卧槽我之前写的这个什么傻逼方法，直接输入一个对象进来不就好了吗！
	//还用得着用什么引用参数嘛！
	if (_aniMode_getHurt == 1) {
		_aniMode_getHurt = 2;
		_getHurtPosX = x, _getHurtPosY = y;
	}
	if (_aniMode_getHurt == 2) {
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
		if (Timers(_getHurtTime, 0)) {
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

void Plane::FrameAnimation(float x, float y, std::map<int, int> sprite, int frameTime, int index)
{
	if (FrameTimers(frameTime, index)) {
		_frameIndex[index]++;
	}
	if (_frameIndex[index] > (int)sprite.size() - 1 || _frameIndex[index] < 0) {
		_frameIndex[index] = 0;
	}
	Novice::DrawSprite((int)x, (int)y, sprite[_frameIndex[index]], 1, 1, 0, WHITE);
}

void Plane::FrameAnimation(float x, float y, std::map<int, int> sprite, float scaleX, float scaleY, int frameTime, int index)
{
	if (FrameTimers(frameTime, index)) {
		_frameIndex[index]++;
	}
	if (_frameIndex[index] > (int)sprite.size() - 1 || _frameIndex[index] < 0) {
		_frameIndex[index] = 0;
	}
	Novice::DrawSprite((int)x, (int)y, sprite[_frameIndex[index]], scaleX, scaleY, 0, WHITE);
}

void Plane::FrameAnimation_New(float x, float y, std::map<int, LoadRes::SpriteList> sprite, int frameTime, int index)
{
	if (FrameTimers(frameTime, index)) {
		_frameIndex[index]++;
	}
	if (_frameIndex[index] > (int)sprite.size() - 1 || _frameIndex[index] < 0) {
		_frameIndex[index] = 0;
	}
	int arrSprite = sprite[_frameIndex[index]].sprite;
	int arrW = sprite[_frameIndex[index]].w, arrH = sprite[_frameIndex[index]].h;
	int arrX = sprite[_frameIndex[index]].x, arrY = sprite[_frameIndex[index]].y;
	Novice::DrawSpriteRect((int)x, (int)y, arrX, arrY, arrH, arrH, arrSprite, ((float)arrH / (float)arrW), 1, 0, WHITE);
}

float Plane::GetPosX()
{
	return _posX;
}
float Plane::GetPosY()
{
	return _posY;
}

void Plane::SetHp(int type, float num)
{
	switch (type) {
	case 0:
		_hp = (int)num;
		break;
	case 1:
		_hp = (int)(_hp * num);
		break;
	}
}

int Plane::GetHp()
{
	return _hp;
}

unsigned int Plane::GetColor()
{
	return _color;
}

void Plane::SetFrameIndex(int index, int num)
{
	_frameIndex[index] = num;
}


