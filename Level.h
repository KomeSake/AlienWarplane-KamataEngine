#pragma once
#include <ctime>
#include <random>
#include "Enemy.h"
class Level
{
private:
	int rand_enemyTime;
	float rand_enemyPosX;
	float beforeEnemyPosX;//把前一个生成的敌人坐标记下来，这样可以避免两个敌人互相盖住对方
	clock_t timeStart, timeEnd;

	struct EnemyWeight
	{
		Enemy::EnemyType type;
		int weight;
	};
	std::vector<EnemyWeight> _enemyWeightVec;

public:
	Level();
	void LevelDirector();

	Enemy::EnemyType EnemyRandom(std::vector<EnemyWeight> vec);
};