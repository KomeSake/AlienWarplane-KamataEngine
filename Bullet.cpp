#include "Bullet.h"

Bullet::Bullet()
{
	Initial();
}

void Bullet::Initial()
{
	_posX = 450;
	_posY = 780;

	_damage = 1;
	_speed = 15;

	_type = 0;
	_sprite = LoadRes::_spbullet;
	_isFire = false;
}

void Bullet::Move()
{
	_posY -= _speed;
	if (_posX > 0 - 50 && _posX < 450 + 50 && _posY>0 - 50 && _posY < 780 + 50) {
		FrameAnimation(_posX, _posY, _sprite);
	}
	else {
		if (_isFire == false) {
			BulletManager::ReleaseBullet(this);
			_isFire = true;
		}
	}
}

void Bullet::FrameAnimation(float x, float y, int sprite)
{
	Novice::DrawSprite((int)x, (int)y, sprite, 1, 1, 0, WHITE);
}

void Bullet::Fire(float x, float y)
{
	_posX = x;
	_posY = y;
	BulletManager::_bulletUpdateVector.push_back(this);
}


int Bullet::GetSprite()
{
	return _sprite;
}

float Bullet::GetPosX()
{
	return _posX;
}

float Bullet::GetPosY()
{
	return _posY;
}

int Bullet::GetType()
{
	return _type;
}

void Bullet::SetType(int type)
{
	_type = type;
}

BulletPool::BulletPool(int initialSum)
{
	for (int i = 0; i < initialSum; i++) {
		Bullet* bullet = new Bullet;
		pool.push(bullet);
	}
}

BulletPool::~BulletPool()
{
	while (!pool.empty()) {
		Bullet* bullet = pool.front();
		pool.pop();
		delete bullet;
	}
}

//Bullet* BulletPool::AcquireBullet()
//{
//	if (pool.empty()) {
//		Bullet* bullet = new Bullet();
//		//Novice::ConsolePrintf("Bullet Born!\n");
//		return bullet;
//	}
//	else {
//		Bullet* bullet = pool.front();
//		pool.pop();
//		//Novice::ConsolePrintf("Bullet Get!\n");
//		return bullet;
//	}
//}

//void BulletPool::ReleaseBullet(Bullet* bullet)
//{
//	pool.push(bullet);
//}



std::vector<Bullet*> BulletManager::_bulletUpdateVector;
std::queue<Bullet*> BulletManager::_bulletIdiePool_normal;
std::queue<Bullet*> BulletManager::_bulletIdiePool_enemy;
std::queue<Bullet*> BulletManager::_bulletIdiePool_laser;
void BulletManager::BulletUpdata()
{
	for (Bullet* element : BulletManager::_bulletUpdateVector) {
		element->Move();
	}
}

Bullet* BulletManager::AcquireBullet(int type)
{
	switch (type) {
	case 0:
		if (_bulletIdiePool_normal.empty()) {
			Bullet* bullet = new Bullet();
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_normal.front();
			_bulletIdiePool_normal.pop();
			bullet->Initial();
			return bullet;
			break;
		}
	case 1:
		if (_bulletIdiePool_enemy.empty()) {
			Bullet* bullet = new Bullet();
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_enemy.front();
			_bulletIdiePool_enemy.pop();
			bullet->Initial();
			return bullet;
			break;
		}
	case 2:
		if (_bulletIdiePool_laser.empty()) {
			Bullet* bullet = new Bullet();
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_laser.front();
			_bulletIdiePool_laser.pop();
			bullet->Initial();
			return bullet;
			break;
		}
	}
	return nullptr;
}

void BulletManager::ReleaseBullet(Bullet* bullet)
{
	//这里差点就忘记了，回收元素的同时，还需要将它(子弹)从Update里面拿走，不然就会一直在里面运行
	//所以这里用了一个find算法，把Update容器中想要移除的子弹进行查找
	//接着再进行对比，如果能找到就移除
	auto it = std::find(_bulletUpdateVector.begin(), _bulletUpdateVector.end(), bullet);
	switch (bullet->GetType()) {
	case 0:
		if (it != _bulletUpdateVector.end()) {
			_bulletUpdateVector.erase(it);
		}
		_bulletIdiePool_normal.push(bullet);
		break;
	case 1:
		if (it != _bulletUpdateVector.end()) {
			_bulletUpdateVector.erase(it);
		}
		_bulletIdiePool_enemy.push(bullet);
		break;
	case 2:
		if (it != _bulletUpdateVector.end()) {
			_bulletUpdateVector.erase(it);
		}
		_bulletIdiePool_laser.push(bullet);
		break;
	}
}