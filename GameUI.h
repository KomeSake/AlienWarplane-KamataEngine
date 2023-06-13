#pragma once
#include <Novice.h>
#include "LoadRes.h"
#include "Player.h"

class GameUI
{
	//我的UI的父类和子类都写在这里了，虽然会有点拥挤，但是UI的代码量应该都不大
public:
	float _posX = 0, _posY = 0;
	float _speed = 5;
	float _width = 0, _higth = 0;
	unsigned int _color = WHITE;
	void FrameAnimation(float x, float y, int sprite, unsigned int color);
};

class UI_BackGround :
	public GameUI
{
public:
	UI_BackGround();
	void BgMove();
};

class UI_CaptureVessel
	:public GameUI
{
public:
	UI_CaptureVessel();
	void UIStart(Player obj);
private:
	float _cdSpeed = 0, _cdMove = 0;
};

class UI_HpVessel
	:public GameUI
{
public:
	UI_HpVessel();
	void UIStart(Player obj);
};
