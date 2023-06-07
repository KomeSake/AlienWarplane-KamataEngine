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

	_hp = 1;
	_speed = 5;

	_type = 0;

	_moveDirection = Down;
}

void Enemy::Fire()
{
	EnemyManager::_enemyUpdateVector.push_back(this);
}

void Enemy::Move()
{
	FrameAnimation(_posX, _posY, LoadRes::_spEnemy);
	_posY += _speed;
	if (_posY > 1000) {
		Dead();
	}
}

void Enemy::Dead()
{
	EnemyManager::ReleaseEnemy(this);
}

void Enemy::DamageCheck()
{
	float enemyW = 64, enemyH = 64;
	float bulletW = 32, bulletH = 32;
	for (Bullet* element : BulletManager::_bulletUpdateVector) {
		float enemyCenterX = _posX + enemyW / 2, enemyCenterY = _posY + enemyH / 2;
		float bulletCenterX = element->GetPosX() + bulletW, bulletCenterY = element->GetPosY() + bulletH;
		float distance = sqrtf(powf(bulletCenterX - enemyCenterX, 2) + powf(bulletCenterY - enemyCenterY, 2));
		if (distance < enemyW / 2 + bulletW / 2) {
			Dead();
		}
	}
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

std::vector<Enemy*> EnemyManager::_enemyUpdateVector;
std::queue<Enemy*> EnemyManager::_enemyIdiePool_normal;
void EnemyManager::EnemyUpdata()
{
	for (Enemy* element : EnemyManager::_enemyUpdateVector) {
		element->Move();
		element->DamageCheck();
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
	auto it = std::find(EnemyManager::_enemyUpdateVector.begin(), EnemyManager::_enemyUpdateVector.end(), enemy);
	switch (enemy->GetType()) {
	case 0:
		if (it != EnemyManager::_enemyUpdateVector.end()) {
			EnemyManager::_enemyUpdateVector.erase(it);
		}
		EnemyManager::_enemyIdiePool_normal.push(enemy);
		break;
	}
}
