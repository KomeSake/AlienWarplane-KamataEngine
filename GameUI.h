#pragma once
#include <Novice.h>
#include "LoadRes.h"
#include "Player.h"

class GameUI
{
	//我的UI的父类和子类都写在这里了，虽然会有点拥挤，但是UI的代码量应该都不大
	//所有东西都Public出来了，UI应该没什么问题，就不弄太复杂了
public:
	float _posX = 0, _posY = 0;
	float _speed = 5;
	float _width = 0, _higth = 0;
	unsigned int _color = WHITE;
	void FrameAnimation(float x, float y, int sprite, unsigned int color);
};

//游戏界面对象
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
	void UIOpen(Player obj);
private:
	float _cdSpeed = 0, _cdMove = 0;
};

class UI_HpVessel
	:public GameUI
{
public:
	UI_HpVessel();
	void UIOpen(Player obj);
};

//开始界面对象
class UI_StartScene
	:public GameUI
{
public:
	float _titlePosX = 0, _titlePosY = 0;
	float _buttonPosX_Start = 0, _buttonPosY_Start = 0;
	float _buttonPosX_Help = 0, _buttonPosY_Help = 0;
	float _buttonW = 0, _buttonH = 0;
	float _buttonTextW_Start = 0;
	float _buttonTextW_Help = 0;
	UI_StartScene();
	void UIOpen();
};
