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
	_isLive = true;

	_moveDirection = Down;
}

void Enemy::Fire()
{
	EnemyManager::_enemyUpdateVector.push_back(this);
}

void Enemy::Move()
{
	//敌机被射击，其他敌机的图像就会闪烁，不知道为什么
	if (_isLive) {
		FrameAnimation(_posX, _posY, LoadRes::_spEnemy);
		_posY += _speed;
	}
	else if (_isLive == false) {
		FrameAnimation(_posX, _posY, LoadRes::_explode);
		if (Timers(700, 0)) {
			EnemyManager::ReleaseEnemy(this);
		}
	}
	if (_posY > 1000) {
		_isLive = false;
		EnemyManager::ReleaseEnemy(this);
	}
}


void Enemy::Attack()
{
	if (_isLive) {
		if (Timers(300, 1)) {
			Bullet* bullet = BulletManager::AcquireBullet(Bullet::enemy);
			bullet->Fire(_posX + 15, _posY);
		}
	}
}

void Enemy::DamageCheck()
{
	float enemyW = 64, enemyH = 64;
	float bulletW = 32, bulletH = 32;
	if (_isLive || _posY > 30) {
		for (Bullet* element : BulletManager::_bulletUpdateVector) {
			float enemyCenterX = _posX + enemyW / 2, enemyCenterY = _posY + enemyH / 2;
			float bulletCenterX = element->GetPosX() + bulletW, bulletCenterY = element->GetPosY() + bulletH;
			float distance = sqrtf(powf(bulletCenterX - enemyCenterX, 2) + powf(bulletCenterY - enemyCenterY, 2));
			if (distance < enemyW / 2 + bulletW / 2) {
				_isLive = false;
				BulletManager::ReleaseBullet(element);
				//这里有个问题，子弹碰到敌机确实是会消失而不是消灭敌机并且穿过去
				//但是因为敌机还在播放死亡动画，导致子弹碰到死亡动画已经会被消除
				//可能还是要制作一个死亡动画的类才可以，但是现在不仔细看看不出来所以先不管了
			}
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
	//想做一个控制飞行的AI，但是还未想好怎么做，现在Move方法就是简单的直接飞
	return _moveDirection;
}

std::vector<Enemy*> EnemyManager::_enemyUpdateVector;
std::queue<Enemy*> EnemyManager::_enemyIdiePool_normal;
void EnemyManager::EnemyUpdata()
{
	for (Enemy* element : EnemyManager::_enemyUpdateVector) {
		element->DamageCheck();
		element->Attack();
		element->Move();
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
	if (it != EnemyManager::_enemyUpdateVector.end()) {
		switch (enemy->GetType()) {
		case 0:
			EnemyManager::_enemyUpdateVector.erase(it);
			EnemyManager::_enemyIdiePool_normal.push(enemy);
			break;
		}
	}
}
