#include "Bullet.h"

//-----新建一种子弹种类顺序-----
//0、往头文件中的枚举添加类型
//1、初始化方法中进行具体数值修改(贴图也别忘了)
//2、新添加一个闲置子弹池子
//3、在提取子弹和回收子弹方法中添加对应的类型代码
//4、Fire方法中增加对应的代码
//5、需要的地方直接根据BulletManager类的静态方法，提取子弹方法，并输入对应类型即可(对应类型枚举在Bullet类)
//6、最后对对象调用Fire方法(这是决定子弹发射的关键方法！)


Bullet::Bullet(BulletType type)
{
	Initial(type);
}

void Bullet::Initial(BulletType type)
{
	//标准初始化部分
	_posX = 450;
	_posY = 780;
	_width = 12;	//虽然子弹的图都是32x32，但是这个大小会控制子弹的伤害范围判定
	_higth = 24;

	_damage = 1;
	_speed = 15;	//让敌人子弹速度为负数即可子弹从上往下

	_type = 0;
	_sprite = LoadRes::_spBullet_player;
	_isFire = false;
	//针对类型进行特殊初始化
	switch (type) {
	case player:
		_type = type;
		_sprite = LoadRes::_spBullet_player;
		break;
	case enemy:
		_type = type;
		_sprite = LoadRes::_spBullet_enemy;
		_speed = -7;
		break;
	case enemyCapture:
		_type = type;
		_sprite = LoadRes::_spBullet_enemyCapture;
		_speed = 7;
		break;
	case laser:
		_type = type;
		_sprite = LoadRes::_spBullet_enemy2;
		_width = 32, _higth = 32;
		_speed = -4;
		break;
	}
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
	switch (_type) {
	case player:
		BulletManager::_bulletUpdateVector.push_back(this);
		break;
	case enemy:
		BulletManager::_bulletUpdateVector_enemy.push_back(this);
		break;
	case enemyCapture:
		BulletManager::_bulletUpdateVector.push_back(this);
		break;
	case laser:
		BulletManager::_bulletUpdateVector_enemy.push_back(this);
		break;
	}
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

float Bullet::GetWidth()
{
	return _width;
}

float Bullet::GetHigth()
{
	return _higth;
}

int Bullet::GetType()
{
	return _type;
}

int Bullet::GetDamage()
{
	return _damage;
}

void Bullet::SetType(int type)
{
	_type = type;
}


std::vector<Bullet*> BulletManager::_bulletUpdateVector;
std::vector<Bullet*> BulletManager::_bulletUpdateVector_enemy;
std::queue<Bullet*> BulletManager::_bulletIdiePool_player;
std::queue<Bullet*> BulletManager::_bulletIdiePool_enemy;
std::queue<Bullet*> BulletManager::_bulletIdiePool_enemyCapture;
std::queue<Bullet*> BulletManager::_bulletIdiePool_laser;
void BulletManager::BulletUpdata()
{
	for (Bullet* element : BulletManager::_bulletUpdateVector) {
		element->Move();
	}
	for (Bullet* element : BulletManager::_bulletUpdateVector_enemy) {
		element->Move();
	}
}

Bullet* BulletManager::AcquireBullet(Bullet::BulletType type)
{
	switch (type) {
	case Bullet::player:
		if (_bulletIdiePool_player.empty()) {
			Bullet* bullet = new Bullet(type);
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_player.front();
			_bulletIdiePool_player.pop();
			bullet->Initial(type);
			return bullet;
		}
		break;
	case Bullet::enemy:
		if (_bulletIdiePool_enemy.empty()) {
			Bullet* bullet = new Bullet(type);
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_enemy.front();
			_bulletIdiePool_enemy.pop();
			bullet->Initial(type);
			return bullet;
		}
		break;
	case Bullet::enemyCapture:
		if (_bulletIdiePool_enemyCapture.empty()) {
			Bullet* bullet = new Bullet(type);
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_enemyCapture.front();
			_bulletIdiePool_enemyCapture.pop();
			bullet->Initial(type);
			return bullet;
		}
		break;
	case Bullet::laser:
		if (_bulletIdiePool_laser.empty()) {
			Bullet* bullet = new Bullet(type);
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_laser.front();
			_bulletIdiePool_laser.pop();
			bullet->Initial(type);
			return bullet;
		}
		break;
	}
	return nullptr;
}

void BulletManager::ReleaseBullet(Bullet* bullet)
{
	//这里差点就忘记了，回收元素的同时，还需要将它(子弹)从Update里面拿走，不然就会一直在里面运行
	//所以这里用了一个find算法，把Update容器中想要移除的子弹进行查找
	//接着再进行对比，如果能找到就移除
	switch (bullet->GetType()) {
	case Bullet::player: {
		auto it = std::find(_bulletUpdateVector.begin(), _bulletUpdateVector.end(), bullet);
		if (it != _bulletUpdateVector.end()) {
			_bulletUpdateVector.erase(it);
		}
		_bulletIdiePool_player.push(bullet);
		break; }
	case Bullet::enemy: {
		auto it = std::find(_bulletUpdateVector_enemy.begin(), _bulletUpdateVector_enemy.end(), bullet);
		if (it != _bulletUpdateVector_enemy.end()) {
			_bulletUpdateVector_enemy.erase(it);
		}
		_bulletIdiePool_enemy.push(bullet);
		break; }
	case Bullet::enemyCapture: {
		auto it = std::find(_bulletUpdateVector.begin(), _bulletUpdateVector.end(), bullet);
		if (it != _bulletUpdateVector.end()) {
			_bulletUpdateVector.erase(it);
		}
		_bulletIdiePool_enemyCapture.push(bullet);
		break; }
	case Bullet::laser: {
		auto it = std::find(_bulletUpdateVector_enemy.begin(), _bulletUpdateVector_enemy.end(), bullet);
		if (it != _bulletUpdateVector_enemy.end()) {
			_bulletUpdateVector_enemy.erase(it);
		}
		_bulletIdiePool_laser.push(bullet);
		break; }
	}
}