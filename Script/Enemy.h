﻿#pragma once
#include <queue>
#include "Plane.h"
#include "Bullet.h"

class Enemy :
	public Plane
{
public:
	static enum EnemyType {
		null,
		normal,
		laser,
		ufo,
		bigGun,
	}enemyType;

	Enemy(float x, float y, int type);
	void Initial(float x, float y, int type);
	void Fire();//一开始调用这个方法
	void Move();
	void Attack(float x, float y, bool isCapture);
	void DamageCheck();
	//绘画的x，y坐标
	void CaptureFire(float x, float y);

	int GetType();
	bool GetIsLive();
	void SetIsLive(bool live);
	int GetScore();
	float GetWidth();
	float GetHigth();

	//可以修改敌人攻击频率；每轮攻击持续时间，每轮攻击时间，每轮子弹数量
	void SetAttackValue(int attackTime1, int attackTime2, int bulletSum);

	//给信息管理发信息(信息要不断读取和修改就不管理起来了)
	bool _isMessageOver_isLive = false;		//发送死亡信息，以此来给玩家回血
	int _message_isFree = 0;				//发送逃逸信息；0：初始化，1：已逃逸，2：信息发送完成
protected:
	unsigned int _color2 = WHITE;
	int _type = 0;
	bool _isLive = true;
	bool _isCaptureGod = true;

	int _attackTime1 = 0;		//每轮攻击持续时间(从攻击开始计算)
	int _attackTime2 = 0;		//每轮攻击时间
	int _bulletSum = 0;			//每轮子弹数量
	int	_bulletCount = 0;		//这个不需要改
	enum Direction {
		Down, Left, Right, LeftDown, RightDown
	}_moveDirection;
	Direction MoveAI();//这个还在想，要不要通过写一个AI来控制敌人的飞行轨道，现在就是直接飞有点太无聊了

	int _score = 0;//自己被击败时的分数(不要设置这么大，因为死亡前每帧都会读取这个分数)
};

// 需要设计的功能
// 敌人移动：通过路线类的方向指示器，更改自己的方向同时移动
// 路线图系统：通过界面上的Y轴，决定在什么地方要变更方向。
// 写多种类的路线，这样敌人只需要直接调用就知道自己接下来要往哪里走
// 关卡管理器：通过时间来控制出现的敌人配置
// 重要！要写几个敌人的队列，然后把所有闲置的敌人都塞进去，需要的时候就去找敌人来当演员
// 伤害遍历系统，这个不会写在这个类里面，但是也是要做的工作（和子弹一样，放到一个UpData方法中不但检测即可）

class EnemyManager
{
public:
	static std::vector<Enemy*> _enemyUpdateVector;
	static void EnemyUpdata();

	static std::queue<Enemy*> _enemyIdiePool_normal;
	static std::queue<Enemy*> _enemyIdiePool_laser;
	static std::queue<Enemy*> _enemyIdiePool_ufo;
	static std::queue<Enemy*> _enemyIdiePool_bigGun;

	static Enemy* AcquireEnemy(float bornX, float bornY, Enemy::EnemyType type);
	static void ReleaseEnemy(Enemy* enemy);
};