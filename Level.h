#pragma once
#include <ctime>
#include "Enemy.h"
class Level
{
public:
	Level();
	void LevelDirector();
private:
	int rand_enemyTime;
	float rand_enemyPosX;
	float beforeEnemyPosX;//把前一个生成的敌人坐标记下来，这样可以避免两个敌人互相盖住对方
	clock_t timeStart, timeEnd;
};