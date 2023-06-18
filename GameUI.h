﻿#pragma once
#include <Novice.h>
#include "LoadRes.h"
#include "Player.h"
#include "Level.h"

class GameUI
{
	//这个类只用来控制UI逻辑，如果想要转换界面在，在自身上设置一共开关。
	// 外面的Scene类检测到这个开关被打开就转换界面即可
	//我的UI的父类和子类都写在这里了，虽然会有点拥挤，但是UI的代码量应该都不大
	//所有东西都Public出来了，UI应该没什么问题，就不弄太复杂了
protected:
	float _posX = 0, _posY = 0;
	float _speed = 5;
	float _width = 0, _higth = 0;
	unsigned int _color = WHITE;
	void FrameTexture(float x, float y, int sprite, unsigned int color);
	void FrameTexture(float x, float y, std::map<int, LoadRes::SpriteList> sprite, int index, unsigned int color);
	bool Timers(int milli, int index);
private:
	//从Plane类偷来的计时器
	clock_t _timeStart[11] = { 0 };
	clock_t _timeEnd[11] = { 0 };
	bool _isTimeOpen[11] = { 0 };
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

class UI_SignalVessel
	:public GameUI
{
private:
	float _bottomPosX = 0, _bottomPosY = 0;
	float _numberPosX = 0, _numberPosY = 0;
	float _redPosX = 0, _redPosY = 0;
	float _signalPosX = 0, _signalPosY = 0;

	int _dangerLevelSum = 0;//从Level类中获取的危险度
	bool _isDangerAniStart = false;
public:
	UI_SignalVessel();
	void UIOpen(Level obj);
};

//开始界面对象
class UI_StartScene
	:public GameUI
{
private:
	float _titlePosX = 0, _titlePosY = 0;
	float _buttonPosX_Start = 0, _buttonPosY_Start = 0;
	float _buttonPosX_Help = 0, _buttonPosY_Help = 0;
	float _buttonW = 0, _buttonH = 0;
	float _buttonTextW_Start = 0;
	float _buttonTextW_Help = 0;
	float _helpPosX = 0, _helpPosY = 0;
public:
	UI_StartScene();
	void UIOpen();
	bool _isButton_Start = false, _isButton_Help = false;
};

//游戏结束界面对象
class UI_GameOverScene
	:public GameUI
{
private:
	float _titlePosX = 0, _titlePosY = 0;
	float _scoreX = 0, _scoreY = 0;
	float _scoreW = 0, _scoreH = 0;
	float _scoreNumIntervalX = 0;
	float _scoreNumX = 0, _scoreNumY = 0;
	bool _isScoreAniStart = 0;
	int _scoreAnimation = 0;//用来最后做一个分数滚动效果
	float _buttonPosX_Restart = 0, _buttonPosY_Restart = 0;
	float _buttonPosX_Back = 0, _buttonPosY_Back = 0;
	float _buttonW = 0, _buttonH = 0;
	float _buttonTextW_Restart = 0;
	float _buttonTextW_Back = 0;
public:
	UI_GameOverScene();
	void UIOpen(Player obj);
	bool _isButton_Restart = false;
	bool _isButton_Back = false;
	bool _isMouseCheckStart = false;//用来延迟获取鼠标坐标(不然玩家可能一下子就点到了重新开始按钮)
};
