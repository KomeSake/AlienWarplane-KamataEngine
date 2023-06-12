#include "Level.h"

Level::Level()
{
	srand(unsigned int(time(nullptr)));
	rand_enemyTime = 0;
	rand_enemyPosX = 0;
	beforeEnemyPosX = 0;

	timeStart = clock();
	timeEnd = clock();
}


//不手动做关卡了，时间来不及了！现在用随机数来设计敌人的出现就好了！


void Level::LevelDirector()
{
	timeEnd = clock();
	if (timeEnd - timeStart > rand_enemyTime) {
		timeStart = timeEnd;
		rand_enemyTime = rand() % 2001 + 1000;
		rand_enemyPosX = (float)(rand() % (450 - 64));
		while (rand_enemyPosX > beforeEnemyPosX - 10 && rand_enemyPosX < beforeEnemyPosX + 64 + 10) {
			rand_enemyPosX = (float)(rand() % (450 - 64));
		}
		beforeEnemyPosX = rand_enemyPosX;
		Enemy* enemy = EnemyManager::AcquireEnemy(rand_enemyPosX, -300, Enemy::laser);
		enemy->Fire();
	}
}