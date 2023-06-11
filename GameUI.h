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
	//现在捕获的UI没能体现触手回到飞机后需要再生CD
	//我的想法是把UI中那个胚胎来做一个从下往上慢慢出现的动画
	//但是不管我怎么弄，好像都会出现问题，还是等有空再弄吧
};

class UI_HpVessel
	:public GameUI
{
public:
	UI_HpVessel();
	void UIStart(Player obj);
};
