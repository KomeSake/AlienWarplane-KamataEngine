#include "Enemy.h"

Enemy::Enemy(float x, float y)
{
	Initial(x, y);
}

void Enemy::Initial(float x, float y)
{
	_posX = x;
	_posY = y;
	_high = 64;
	_width = 64;

	_hp = 3;
	_speed = 5;

	_type = 0;

	_moveDirection = Down;
}

void Enemy::Fire()
{
	EnemyManager::_bulletUpdateVector.push_back(this);
}

void Enemy::Move()
{
	_posY += _speed;
	if (_posY > 1000) {
		Dead();
	}
}

void Enemy::Dead()
{
	EnemyManager::ReleaseEnemy(this);
}


float Enemy::GetPosX()
{
	return _posX;
}

float Enemy::GetPosY()
{
	return _posY;
}

int Enemy::GetType()
{
	return _type;
}

Enemy::Direction Enemy::MoveAI()
{

	return _moveDirection;
}

std::vector<Enemy*> EnemyManager::_bulletUpdateVector;
std::queue<Enemy*> EnemyManager::_enemyIdiePool_normal;
void EnemyManager::EnemyUpdata()
{
	for (Enemy* element : EnemyManager::_bulletUpdateVector) {
		element->Move();
		element->FrameAnimation(element->GetPosX(), element->GetPosY(), LoadRes::_spEnemy);
	}
}

Enemy* EnemyManager::AcquireEnemy(int enemyType, float bornX, float bornY)
{
	switch (enemyType) {
	case 0:
		if (EnemyManager::_enemyIdiePool_normal.empty()) {
			Enemy* enemy = new Enemy(bornX, bornY);
			return enemy;
		}
		else {
			Enemy* enemy = EnemyManager::_enemyIdiePool_normal.front();
			enemy->Initial(bornX, bornY);
			EnemyManager::_enemyIdiePool_normal.pop();
			return enemy;
		}
		break;
	}
	return nullptr;
}

void EnemyManager::ReleaseEnemy(Enemy* enemy)
{
	auto it = std::find(EnemyManager::_bulletUpdateVector.begin(), EnemyManager::_bulletUpdateVector.end(), enemy);
	switch (enemy->GetType()) {
	case 0:
		if (it != EnemyManager::_bulletUpdateVector.end()) {
			EnemyManager::_bulletUpdateVector.erase(it);
		}
		EnemyManager::_enemyIdiePool_normal.push(enemy);
		break;
	}
}
