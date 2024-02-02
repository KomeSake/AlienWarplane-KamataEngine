#pragma once
#include <ctime>
#include <random>
#include "Enemy.h"
class Level
{
private:
	//从Plane类中拿来的计时器
	clock_t _timeStart[11] = { 0 };
	clock_t _timeEnd[11] = { 0 };
	bool _isTimeOpen[11] = { 0 };

	int _rand_enemyTime = 0;
	int _rand_enemyTimeMin = 0, _rand_enemyTimeMax = 0;
	float _rand_enemyPosX = 0;
	float _beforeEnemyPosX = 0;//把前一个生成的敌人坐标记下来，这样可以避免两个敌人互相盖住对方

	int _dangerLevelSum = 0;//危险度
	int _dangerLevelOne = 0, _dangerLevelTwo = 0, _dangerLevelThree = 0;
	bool _isDangerLevel = false;
	bool _isDangerMarningAni = false;//给界面的危险度提示用
	int _levelTime = 0;//波次间隔时间

	struct EnemyWeight
	{
		Enemy::EnemyType type;
		int weight;
	};
	std::vector<EnemyWeight> _enemyWeightVec;

public:
	Level();
	bool Timers(int milli, int index);
	void LevelDirector();
	Enemy::EnemyType EnemyRandom(std::vector<EnemyWeight> vec);

	int GetDangerLevelSum();
	int GetDangerLevelMax1();
	int GetDangerLevelMax2();
	int GetDangerLevelMax3();
	void DangerLevelPlus(int value);
	bool GetDangerMarningAni();
	void SetDangerMarningAni(bool taf);
};