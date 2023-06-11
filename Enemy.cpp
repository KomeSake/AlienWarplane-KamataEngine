#include "Enemy.h"
Enemy::Enemy(float x, float y)
{
	Initial(x, y);
}

void Enemy::Initial(float x, float y)
{
	_posX = x;
	_posY = y;
	_higth = 64;
	_width = 64;

	_hp = 3;
	_speed = 3;
	_color = WHITE;

	_type = 0;
	_isLive = true;
	_attackTime_normal1 = 2000;
	_attackTime_normal2 = 150;
	_normalCount = 0;
	_normalSum = 3;

	_moveDirection = Down;

	_isGetHurtAniStart = false;
	_getHurtPosX = 0, _getHurtPosY = 0;
	_getHurtSpeedX = 10, _getHurtSpeedY = _speed;
	_getHurtTime = 100;
	_aniMode_getHurt = 0;

	_isMessageOver_isLive = false;
}

void Enemy::Fire()
{
	EnemyManager::_enemyUpdateVector.push_back(this);
}

void Enemy::Move()
{
	//敌机被射击，其他敌机的图像就会闪烁，不知道为什么
	if (_isLive) {
		FrameAnimation(_posX + _width / 4, _posY - _higth / 2 - 10, LoadRes::_spAniEnemyFire, 1, 2, 100, 0);
		FrameAnimation(_posX, _posY, LoadRes::_spEnemy, _color);
		_posY += _speed;
		GetHurtAni(_posX, _posY, -_getHurtSpeedY, RED);
	}
	else if (_isLive == false) {
		if (!Timers(200, 12)) {
			FrameAnimation(_posX, _posY, LoadRes::_spEnemy, RED);
		}
		if (!Timers((int)(LoadRes::_spAniExplode.size()) * 50, 16)) {
			FrameAnimation(_posX, _posY, LoadRes::_spAniExplode, 50, 1);
		}
		else {
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
		if (!Timers(_attackTime_normal1, 17)) {
			if (_normalCount < _normalSum) {
				if (Timers(_attackTime_normal2, 13)) {
					_normalCount++;
					Bullet* bullet = BulletManager::AcquireBullet(Bullet::enemy);
					bullet->Fire(_posX + 16, _posY);
				}
			}
		}
		else {
			_normalCount = 0;
		}
	}
}

void Enemy::DamageCheck()
{
	if (_isLive && _posY > 30) {
		for (Bullet* element : BulletManager::_bulletUpdateVector) {
			float enemyCenterX = _posX + _width / 2, enemyCenterY = _posY + _higth / 2;
			float bulletCenterX = element->GetPosX() + element->GetWidth(), bulletCenterY = element->GetPosY() + element->GetHigth();
			float distance = sqrtf(powf(bulletCenterX - enemyCenterX, 2) + powf(bulletCenterY - enemyCenterY, 2));
			if (distance < _width / 2 + element->GetWidth() / 2) {
				BulletManager::ReleaseBullet(element);
				_hp = _hp - element->GetDamage();
				_aniMode_getHurt = 1;
				if (_hp <= 0) {
					_isLive = false;
				}
			}
		}
	}
}

void Enemy::CaptureFire(float x, float y)
{
	_color = 0xcfc0eaFF;//被捕获的敌人加一层紫色
	//碰撞检测部分(输入的触手坐标是从中心开始的，不要忘记了)
	if (Timers(100, 14)) {
		for (Bullet* element : BulletManager::_bulletUpdateVector_enemy) {
			//敌人坐标要特殊处理，因为输入的触手坐标是从中心开始
			float enemyCenterX = x, enemyCenterY = y - _higth;
			float bulletCeneterX = element->GetPosX() + element->GetWidth() / 2, bulletCeneterY = element->GetPosY() + element->GetHigth() / 2;
			float distacne = sqrtf(powf(enemyCenterX - bulletCeneterX, 2) + powf(enemyCenterY - bulletCeneterY, 2));
			if (distacne < _width / 2 + element->GetWidth() / 2) {
				BulletManager::ReleaseBullet(element);
				_hp = _hp - element->GetDamage();
				_aniMode_getHurt = 1;
				_color = RED;
				if (_hp <= 0) {
					_isLive = false;
				}
			}
		}
	}
	if (_isLive == true) {
		//子弹发射部分
		if (!Timers(_attackTime_normal1, 17)) {
			if (_normalCount < _normalSum) {
				if (Timers(_attackTime_normal2, 13)) {
					_normalCount++;
					Bullet* bullet = BulletManager::AcquireBullet(Bullet::player);
					bullet->Fire(x - 32.f / 2, y - 64 - 10);
				}
			}
		}
		else {
			_normalCount = 0;
		}
		//绘图部分(到时候按照类型做个switch即可)
		GetHurtAni(x, y, 0, RED);
		Novice::DrawSprite((int)x + 32, (int)y, LoadRes::_spEnemy, 1, 1, 3.14159f, _color);
	}
}

int Enemy::GetType()
{
	return _type;
}

bool Enemy::GetIsLive()
{
	return _isLive;
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
