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
	_posX = 450, _posY = 780;
	_width = 12, _higth = 24;	//虽然子弹的图都是32x32，但是这个大小会控制子弹的伤害范围判定
	_scaleX = 1, _scaleY = 1;
	_color = WHITE;

	_damage = 1;
	_speedY = 15;	//让敌人子弹速度为负数即可子弹从上往下
	_speedX = 0;

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
		_speedY = -7;
		break;
	case enemyCapture:
		_type = type;
		_sprite = LoadRes::_spBullet_enemyCapture;
		_speedY = 7;
		break;
	case laser:
		_type = type;
		_sprite = LoadRes::_spBullet_enemy2;
		_width = 32, _higth = 32;
		_speedY = -4;
		break;
	case laserCapture:
		_type = type;
		_sprite = LoadRes::_spBullet_enemy2Capture;
		_width = 32, _higth = 32;
		_speedY = 4;
		break;
	case ufo:
		_type = type;
		_sprite = LoadRes::_spBullet_enemy3;
		_width = 64, _higth = 64;
		_speedY = -0.3f;
		_damage = 3;
		break;
	case ufoCapture:
		_type = type;
		_sprite = LoadRes::_spBullet_enemy3Capture;
		_width = 64, _higth = 64;
		_speedY = -0.1f;
		_damage = 3;
		break;
	case bigGun:
		_type = type;
		_sprite = LoadRes::_spBullet_enemy4;
		_width = 32, _higth = 32;
		_speedY = -4;
		_damage = 1;
		_isBigGunFirst = true;
		break;
	case bigGunCapture:
		_type = type;
		_sprite = LoadRes::_spBullet_enemy4Capture;
		_width = 32, _higth = 32;
		_speedY = 4;
		_damage = 1;
		_isBigGunFirst = true;
		break;
	}
}

void Bullet::Move()
{
	_posX -= _speedX;
	_posY -= _speedY;
	if (_posX > 0 - 64 && _posX < 450 + 64 && _posY>0 - 64 && _posY < 780 + 64) {
		if (_type != ufo && _type != ufoCapture) {
			FrameTexture(_posX, _posY, _sprite);
		}
	}
	else {
		if (_isFire == false) {
			_isFire = true;
			BulletManager::ReleaseBullet(this);
		}
	}
	//特殊子弹处理
	BulletUfo();
	BulletBigGun();
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
	case laserCapture:
		BulletManager::_bulletUpdateVector.push_back(this);
		break;
	case ufo:
		BulletManager::_bulletUpdateVector_enemy.push_back(this);
		break;
	case ufoCapture:
		BulletManager::_bulletUpdateVector.push_back(this);
		break;
	case bigGun:
		BulletManager::_bulletUpdateVector_enemy.push_back(this);
		break;
	case bigGunCapture:
		BulletManager::_bulletUpdateVector.push_back(this);
		break;
	}
}

void Bullet::FrameTexture(float x, float y, int sprite)
{
	Novice::DrawSprite((int)x, (int)y, sprite, 1, 1, 0, WHITE);
}

void Bullet::BulletUfo()
{
	if (_type == ufo) {
		//被我方子弹打中会消失
		for (Bullet* element : BulletManager::_bulletUpdateVector) {
			float myCenterX = _posX + _width / 2, myCenterY = _posY + _higth / 2;
			float bulletCenterX = element->GetPosX() + element->GetWidth(), bulletCenterY = element->GetPosY() + element->GetHigth();
			float distance = sqrtf(powf(bulletCenterX - myCenterX, 2) + powf(bulletCenterY - myCenterY, 2));
			if (distance < _width / 2 + element->GetWidth() / 2) {
				_color = RED;
				BulletManager::ReleaseBullet(this);
				BulletManager::ReleaseBullet(element);
			}
		}
	}
	if (_type == ufo || _type == ufoCapture) {
		_color -= 0x00000001;
		if (_color == WHITE - 0x000000FF) {
			BulletManager::ReleaseBullet(this);
		}
		Novice::DrawSprite((int)_posX, (int)_posY, _sprite, 1, 1, 0, _color);
	}
}

void Bullet::BulletBigGun()
{
	if (_type == bigGun && _isBigGunFirst) {
		if (Timers(1000, 0)) {
			_isBigGunFirst = false;
		}
	}
	if (_type == bigGunCapture && _isBigGunFirst) {
	}
}

bool Bullet::Timers(int milli, int index)
{
	if (!_isTimeOpen[index]) {
		_timeStart[index] = clock();
		_isTimeOpen[index] = true;
	}
	_timeEnd[index] = clock();
	if (_timeEnd[index] - _timeStart[index] > milli) {
		_isTimeOpen[index] = false;
		return 1;
	}
	return 0;
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

float Bullet::GetSpeed(int xy)
{
	switch (xy) {
	case 0:
		return _speedX;
		break;
	case 1:
		return _speedY;
		break;
	}
	return 0.0f;
}

void Bullet::SetType(int type)
{
	_type = type;
}

void Bullet::SetSpeed(int type, int xy, float num)
{
	switch (xy) {
	case 0:
		switch (type) {
		case 0:
			_speedX = num;
			break;
		case 1:
			_speedX = _speedX * num;
			break;
		}
		break;
	case 1:
		switch (type) {
		case 0:
			_speedY = num;
			break;
		case 1:
			_speedY = _speedY * num;
			break;
		}
		break;
	}
}


std::vector<Bullet*> BulletManager::_bulletUpdateVector;
std::vector<Bullet*> BulletManager::_bulletUpdateVector_enemy;
std::queue<Bullet*> BulletManager::_bulletIdiePool_player;
std::queue<Bullet*> BulletManager::_bulletIdiePool_enemy;
std::queue<Bullet*> BulletManager::_bulletIdiePool_enemyCapture;
std::queue<Bullet*> BulletManager::_bulletIdiePool_laser;
std::queue<Bullet*> BulletManager::_bulletIdiePool_laserCapture;
std::queue<Bullet*> BulletManager::_bulletIdiePool_ufo;
std::queue<Bullet*> BulletManager::_bulletIdiePool_ufoCapture;
std::queue<Bullet*> BulletManager::_bulletIdiePool_bigGun;
std::queue<Bullet*> BulletManager::_bulletIdiePool_bigGunCapture;
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
	case Bullet::laserCapture:
		if (_bulletIdiePool_laserCapture.empty()) {
			Bullet* bullet = new Bullet(type);
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_laserCapture.front();
			_bulletIdiePool_laserCapture.pop();
			bullet->Initial(type);
			return bullet;
		}
		break;
	case Bullet::ufo:
		if (_bulletIdiePool_ufo.empty()) {
			Bullet* bullet = new Bullet(type);
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_ufo.front();
			_bulletIdiePool_ufo.pop();
			bullet->Initial(type);
			return bullet;
		}
		break;
	case Bullet::ufoCapture:
		if (_bulletIdiePool_ufoCapture.empty()) {
			Bullet* bullet = new Bullet(type);
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_ufoCapture.front();
			_bulletIdiePool_ufoCapture.pop();
			bullet->Initial(type);
			return bullet;
		}
		break;
	case Bullet::bigGun:
		if (_bulletIdiePool_bigGun.empty()) {
			Bullet* bullet = new Bullet(type);
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_bigGun.front();
			_bulletIdiePool_bigGun.pop();
			bullet->Initial(type);
			return bullet;
		}
		break;
	case Bullet::bigGunCapture:
		if (_bulletIdiePool_bigGunCapture.empty()) {
			Bullet* bullet = new Bullet(type);
			return bullet;
		}
		else {
			Bullet* bullet = _bulletIdiePool_bigGunCapture.front();
			_bulletIdiePool_bigGunCapture.pop();
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
	case Bullet::laserCapture: {
		auto it = std::find(_bulletUpdateVector.begin(), _bulletUpdateVector.end(), bullet);
		if (it != _bulletUpdateVector.end()) {
			_bulletUpdateVector.erase(it);
		}
		_bulletIdiePool_laserCapture.push(bullet);
		break; }
	case Bullet::ufo: {
		auto it = std::find(_bulletUpdateVector_enemy.begin(), _bulletUpdateVector_enemy.end(), bullet);
		if (it != _bulletUpdateVector_enemy.end()) {
			_bulletUpdateVector_enemy.erase(it);
		}
		_bulletIdiePool_ufo.push(bullet);
		break; }
	case Bullet::ufoCapture: {
		auto it = std::find(_bulletUpdateVector.begin(), _bulletUpdateVector.end(), bullet);
		if (it != _bulletUpdateVector.end()) {
			_bulletUpdateVector.erase(it);
		}
		_bulletIdiePool_ufoCapture.push(bullet);
		break; }
	case Bullet::bigGun: {
		auto it = std::find(_bulletUpdateVector_enemy.begin(), _bulletUpdateVector_enemy.end(), bullet);
		if (it != _bulletUpdateVector_enemy.end()) {
			_bulletUpdateVector_enemy.erase(it);
		}
		_bulletIdiePool_bigGun.push(bullet);
		break; }
	case Bullet::bigGunCapture: {
		auto it = std::find(_bulletUpdateVector.begin(), _bulletUpdateVector.end(), bullet);
		if (it != _bulletUpdateVector.end()) {
			_bulletUpdateVector.erase(it);
		}
		_bulletIdiePool_bigGunCapture.push(bullet);
		break; }
	}
}