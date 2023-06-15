#include "Level.h"

Level::Level()
{
	srand(unsigned int(time(nullptr)));
	rand_enemyTime = 0;
	rand_enemyPosX = 0;
	beforeEnemyPosX = 0;

	timeStart = clock();
	timeEnd = clock();

	_enemyWeightVec = {
		{Enemy::normal,5},
		{Enemy::laser,2},
		{Enemy::ufo,3}
	};
}

//ChatGPT提出了一个挺有意思的建议，敌人要有波次概念。
//平时就是普通出现敌人，然后一段时间就出一大波敌人，这样有紧迫感，也更符合现实
void Level::LevelDirector()
{
	timeEnd = clock();
	if (timeEnd - timeStart > rand_enemyTime) {
		timeStart = timeEnd;
		rand_enemyTime = rand() % 2001 + 1000;
		rand_enemyPosX = (float)(rand() % (450 - 64));
		while (rand_enemyPosX > beforeEnemyPosX - 30 && rand_enemyPosX < beforeEnemyPosX + 64 + 30) {
			rand_enemyPosX = (float)(rand() % (450 - 64));
		}
		beforeEnemyPosX = rand_enemyPosX;
		Enemy::EnemyType enemyType = EnemyRandom(_enemyWeightVec);
		Enemy* enemy = EnemyManager::AcquireEnemy(rand_enemyPosX, -300, enemyType);
		enemy->Fire();
	}
}

Enemy::EnemyType Level::EnemyRandom(std::vector<EnemyWeight> vec)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int sumWeight = 0;
	for (const EnemyWeight element : vec) {
		sumWeight += element.weight;
	}

	std::uniform_int_distribution<> dis(1, sumWeight);
	int randomValue = dis(gen);

	for (const EnemyWeight element : vec) {
		randomValue -= element.weight;
		if (randomValue <= 0) {
			return element.type;
		}
	}
	return Enemy::normal;//如果出问题就返回普通类型的敌人
}
