﻿#pragma once
#include <Novice.h>
#include <ctime>
#include <map>
#include "Bullet.h"

class Plane
{
protected:
	//不要忘了初始化呀！就算是头文件初始化也没问题的！
	float _posX = 0;
	float _posY = 0;
	float _width = 0;
	float _higth = 0;

	int _hp = 0;
	float _speed = 0;
	int _sprite = 0;
	unsigned int _color = WHITE;

	bool _isGetHurtAniStart = false;						//初次进入函数判断
	float _getHurtPosX = 0, _getHurtPosY = 0;				//用以记录原始位置
	float _getHurtSpeedX = 0, _getHurtSpeedY = 0;			//每帧抖动速度
	int _getHurtTime = 0;									//动画播放时长
	int _aniMode_getHurt = 0;								//0：不播放，1：播放开始，2：播放中

public:
	//计时器有一个很奇怪的Bug，如果在一个if里面使用两个计时器，首先执行的计时器的定时如果比下面的计时器小，就会在第二轮使用这个计时器的时候，立马返回true。
	// 这会导致一个问题，第一轮确实是没问题的，但是第二轮会立马输出一个true，然后在重新计时
	// 解决方法也很简单，就是避免两个计时器在同一个判断中，放开即可(但是为什么啊！草泥马！)
	//0~10号位是用来给Plane类用的；0：受伤抖动反馈、
	int Timers(int milli, int index);
	int FrameTimers(int milli, int index);
	void MoveToTarget(float& objX, float& objY, float targetX, float targetY, float speed);

	//受伤抖动动画(坐标x，坐标y，移动Y距离，变化颜色);函数需放在对象移动方法中，通过播放的int来控制
	void GetHurtAni(float& x, float& y, float dirY, unsigned int color);

	void FrameTexture(float x, float y, int sprite, unsigned int color);
	//如果想要下次播放从第0帧开始，那么调用SetFrameIndex方法设置一下(注意时间不是百分百准确的，需要自行微调一下)
	void FrameAnimation(float x, float y, std::map<int, LoadRes::SpriteList> sprite, int frameTime, int index);
	void FrameAnimation(float x, float y, std::map<int, LoadRes::SpriteList> sprite, float scaleX, float scaleY, unsigned int color, int frameTime, int index);
	float GetPosX();
	float GetPosY();
	//0：直接设置数值，1：倍率式设置数值
	void SetHp(int type, float num);
	int GetHp();
	unsigned int GetColor();
	//将指定计时器立马重新开始计时
	void RestartTimers(bool isTimeOpen, int index);
	//输入当前使用的播放序号，需要改的帧数值
	void SetFrameIndex(int index, int num);
	//设置自己设置的代码特效，输入值和代号；0:受伤抖动
	void SetAniMode(int value, int index);

private:
	//给帧动画用的
	int _frameIndex[31] = { 0 };
	clock_t _frame_timeStart[31] = { 0 };
	clock_t _frame_timeEnd[31] = { 0 };
	bool _frame_isTimeOpen[31] = { 0 };
	//不要再随随便便弄全局变量了！全局变量只有一个！
	//想要通过这种对象方法来制作游戏，那就必须要要写类的成员变量！
	//以下是用于计时器的变量,0~10号位是用来给Plan类用的
	clock_t _timeStart[31] = { 0 };
	clock_t _timeEnd[31] = { 0 };
	bool _isTimeOpen[31] = { 0 };
};

