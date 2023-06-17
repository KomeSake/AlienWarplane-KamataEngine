#include "Level.h"

Level::Level()
{
	srand(unsigned int(time(nullptr)));
	_rand_enemyTime = 0;
	_rand_enemyTimeMax = 2001, _rand_enemyTimeMin = 1000;
	_rand_enemyPosX = 0;
	_beforeEnemyPosX = 0;

	_isDangerLevel = false;
	_dangerLevelSum = 0;
	_dangerLevelOne = 10;
	_dangerLevelTwo = 20;
	_dangerLevelThree = 30;

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
	//危险度计算部分
	if (!_isDangerLevel) {
		if (Timers(30000, 1)) {
			if (_dangerLevelSum >= _dangerLevelThree) {
				_rand_enemyTimeMax = 101, _rand_enemyTimeMin = 50;
				Novice::ConsolePrintf("Enemy Comeing! Level3! Level:%d\n", _dangerLevelSum);
			}
			else if (_dangerLevelSum >= _dangerLevelTwo) {
				_rand_enemyTimeMax = 301, _rand_enemyTimeMin = 200;
				Novice::ConsolePrintf("Enemy Comeing! Level2! Level:%d\n", _dangerLevelSum);
			}
			else if (_dangerLevelSum >= _dangerLevelOne) {
				_rand_enemyTimeMax = 501, _rand_enemyTimeMin = 300;
				Novice::ConsolePrintf("Enemy Comeing! Level1! Level:%d\n", _dangerLevelSum);
			}
			else {
				_rand_enemyTimeMax = 1001, _rand_enemyTimeMin = 500;
				_dangerLevelSum += 20;
				Novice::ConsolePrintf("Enemy Comeing! Level0! Level:%d\n", _dangerLevelSum);
			}
			_isDangerLevel = true;
			_rand_enemyTime = 0;//重置一下敌人生成的间隔时间，让它立马开始
		}
	}
	else if (_isDangerLevel) {
		if (Timers(5000, 2)) {
			_rand_enemyTimeMax = 2001, _rand_enemyTimeMin = 1000;
			_dangerLevelSum -= 10;
			if (_dangerLevelSum >= 30) {
				_dangerLevelSum = 20;
			}
			_isDangerLevel = false;
		}
	}
	//根据随机时间生成敌人
	if (Timers(_rand_enemyTime, 0)) {
		_rand_enemyTime = rand() % _rand_enemyTimeMax + _rand_enemyTimeMin;
		_rand_enemyPosX = (float)(rand() % (450 - 64));
		while (_rand_enemyPosX > _beforeEnemyPosX - 30 && _rand_enemyPosX < _beforeEnemyPosX + 64 + 30) {
			_rand_enemyPosX = (float)(rand() % (450 - 64));
		}
		_beforeEnemyPosX = _rand_enemyPosX;
		Enemy::EnemyType enemyType = EnemyRandom(_enemyWeightVec);
		Enemy* enemy = EnemyManager::AcquireEnemy(_rand_enemyPosX, -300, enemyType);
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

bool Level::Timers(int milli, int index)
{
	if (!_isTimeOpen[index]) {
		_timeStart[index] = clock();
		_isTimeOpen[index] = true;
	}
	_timeEnd[index] = clock();
	if (_timeEnd[index] - _timeStart[index] > milli) {
		_isTimeOpen[index] = false;
		return true;
	}
	return false;
}

void Level::DangerLevelPlus(int value)
{
	_dangerLevelSum += value;
}
