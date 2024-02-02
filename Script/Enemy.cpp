#include "Enemy.h"

//------新添加敌人步骤------
//0、往头文件中的枚举添加类型
//1、初始化方法中进行具体数值修改(贴图也别忘了)
//2、新添加一个闲置敌人池子
//3、在提取和回收方法中添加对应的类型代码
//4、需要的地方直接根据EnemyManager类的静态方法，提取敌人方法，并输入对应类型即可(对应类型枚举在Enemy类)
//4.1、一般都是在Level类里面调用，这是主管关卡的类
//5、最后对对象调用Fire方法(这是决定敌人开始攻击的关键方法！)
//5.1、注意被抓的敌人是调用CapturedFire方法
//6、最后就是修改Attack和CaptureFire方法，添加相对应的敌人绘图，发射对应的子弹



Enemy::Enemy(float x, float y, int type)
{
	Initial(x, y, type);
}

void Enemy::Initial(float x, float y, int type)
{
	_posX = x;
	_posY = y;
	_higth = 64;
	_width = 64;

	_hp = 3;
	_speed = 3;
	_sprite = LoadRes::_spEnemy;
	_color = WHITE;
	_color2 = 0xFFFFFF00;

	_type = 0;
	_score = 50;
	_isLive = true;
	_isCaptureGod = true;
	_attackTime1 = 2000;
	_attackTime2 = 150;
	_bulletSum = 3;
	_bulletCount = 0;

	_moveDirection = Down;

	_isGetHurtAniStart = false;
	_getHurtPosX = 0, _getHurtPosY = 0;
	_getHurtSpeedX = 10, _getHurtSpeedY = _speed;
	_getHurtTime = 100;
	_aniMode_getHurt = 0;

	_isMessageOver_isLive = false;
	_message_isFree = 0;

	switch (type) {
	case normal:
		_type = normal;
		_score = 50;
		_hp = 3;
		_speed = 3;
		break;
	case laser:
		_type = laser;
		_score = 100;
		_sprite = LoadRes::_spEnemy2;
		_hp = 5;
		_speed = 1.5f;
		_attackTime1 = 3000;
		_attackTime2 = 100;
		_bulletSum = 10;
		break;
	case ufo:
		_type = ufo;
		_score = 30;
		_sprite = LoadRes::_spEnemy3;
		_hp = 2;
		_speed = 5;
		break;
	case bigGun:
		_type = bigGun;
		_score = 130;
		_sprite = LoadRes::_spEnemy4;
		_hp = 4;
		_speed = 0.5f;
		_attackTime1 = 3000;
		_attackTime2 = 10;
		_bulletSum = 1;
		break;
	}
}

void Enemy::Fire()
{
	EnemyManager::_enemyUpdateVector.push_back(this);
}

void Enemy::Move()
{
	//敌机被射击，其他敌机的图像就会闪烁，不知道为什么
	if (_isLive) {
		_posY += _speed;
		FrameAnimation(_posX + _width / 4, _posY - _higth / 2 - 10, LoadRes::_spAniEnemyFire, 1, 2, WHITE, 100, 0);
		//敌人的进场特效
		if (_posY + 64 >= 0 && _posY < 30) {
			unsigned int inter = (int)(256.f / (30.f / _speed));
			if (_color2 < WHITE) {
				_color2 += 0x00000001 * inter;
			}
			FrameTexture(_posX, _posY, _sprite, _color2);
		}
		else {
			FrameTexture(_posX, _posY, _sprite, _color);
		}
		GetHurtAni(_posX, _posY, -_getHurtSpeedY, RED);
	}
	else if (_isLive == false) {
		if (!Timers(200, 12)) {
			FrameTexture(_posX, _posY, _sprite, RED);
		}
		if (!Timers((int)(LoadRes::_spAniExplode.size() + 3) * 50, 16)) {
			_posY -= 0.5f;
			FrameAnimation(_posX, _posY, LoadRes::_spAniExplode, 50, 1);
		}
		else {
			SetFrameIndex(1, 0);
			EnemyManager::ReleaseEnemy(this);
		}
	}
	//敌人已经飞出屏幕
	if (_posY > 850 && _message_isFree == 0) {
		_message_isFree = 1;
	}
	else if (_posY > 1000) {
		_isLive = false;
		EnemyManager::ReleaseEnemy(this);
	}
}

void Enemy::Attack(float x, float y, bool isCapture)
{
	if (_isLive && _posY > 30) {
		if (!Timers(_attackTime1, 17)) {
			if (_bulletCount < _bulletSum) {
				if (Timers(_attackTime2, 13)) {
					_bulletCount++;
					Bullet* bullet1 = nullptr;
					Bullet* bullet2 = nullptr;
					Bullet* bullet3 = nullptr;
					Bullet* bullet4 = nullptr;
					Bullet* bullet5 = nullptr;
					if (!isCapture) {
						//敌人本身发射状态
						switch (_type) {
						case normal:
							bullet1 = BulletManager::AcquireBullet(Bullet::enemy);
							Novice::PlayAudio(LoadRes::_adEnemyShout, 0, 0.5f);
							break;
						case laser:
							bullet1 = BulletManager::AcquireBullet(Bullet::laser);
							Novice::PlayAudio(LoadRes::_adShoutLaser, 0, 0.05f);
							break;
						case ufo:
							bullet1 = BulletManager::AcquireBullet(Bullet::ufo);
							Novice::PlayAudio(LoadRes::_adShoutUfo, 0, 0.2f);
							break;
						case bigGun:
							bullet1 = BulletManager::AcquireBullet(Bullet::bigGun);
							bullet2 = BulletManager::AcquireBullet(Bullet::bigGun);
							bullet2->SetSpeed(0, 0, -bullet2->GetSpeed(1));
							bullet3 = BulletManager::AcquireBullet(Bullet::bigGun);
							bullet3->SetSpeed(0, 0, bullet3->GetSpeed(1));
							bullet4 = BulletManager::AcquireBullet(Bullet::bigGun);
							bullet4->SetSpeed(0, 0, -bullet4->GetSpeed(1));
							bullet4->SetSpeed(0, 1, 0);
							bullet5 = BulletManager::AcquireBullet(Bullet::bigGun);
							bullet5->SetSpeed(0, 0, bullet5->GetSpeed(1));
							bullet5->SetSpeed(0, 1, 0);
							Novice::PlayAudio(LoadRes::_adShoutBigGun, 0, 0.2f);
							break;
						}
					}
					else {
						//被捕获状态发射
						switch (_type) {
						case normal:
							bullet1 = BulletManager::AcquireBullet(Bullet::enemyCapture);
							Novice::PlayAudio(LoadRes::_adEnemyShout, 0, 0.5f);
							break;
						case laser:
							bullet1 = BulletManager::AcquireBullet(Bullet::laserCapture);
							Novice::PlayAudio(LoadRes::_adShoutLaser, 0, 0.05f);
							break;
						case ufo:
							bullet1 = BulletManager::AcquireBullet(Bullet::ufoCapture);
							Novice::PlayAudio(LoadRes::_adShoutUfo, 0, 0.2f);
							break;
						case bigGun:
							bullet1 = BulletManager::AcquireBullet(Bullet::bigGunCapture);
							bullet2 = BulletManager::AcquireBullet(Bullet::bigGunCapture);
							bullet2->SetSpeed(0, 0, -bullet2->GetSpeed(1));
							bullet3 = BulletManager::AcquireBullet(Bullet::bigGunCapture);
							bullet3->SetSpeed(0, 0, bullet3->GetSpeed(1));
							bullet4 = BulletManager::AcquireBullet(Bullet::bigGunCapture);
							bullet4->SetSpeed(0, 0, -bullet4->GetSpeed(1));
							bullet4->SetSpeed(0, 1, 0);
							bullet5 = BulletManager::AcquireBullet(Bullet::bigGunCapture);
							bullet5->SetSpeed(0, 0, bullet5->GetSpeed(1));
							bullet5->SetSpeed(0, 1, 0);
							Novice::PlayAudio(LoadRes::_adShoutBigGun, 0, 0.2f);
							break;
						}
					}
					if (bullet1 != nullptr) {
						bullet1->Fire(x, y);
					}
					if (bullet2 != nullptr) {
						bullet2->Fire(x, y);
					}
					if (bullet3 != nullptr) {
						bullet3->Fire(x, y);
					}
					if (bullet4 != nullptr) {
						bullet4->Fire(x, y);
					}
					if (bullet5 != nullptr) {
						bullet5->Fire(x, y);
					}
				}
			}
		}
		else {
			_bulletCount = 0;
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
				Novice::PlayAudio(LoadRes::_adHitEnemy, 0, 0.2f);
				if (_hp <= 0) {
					_isLive = false;
					Novice::PlayAudio(LoadRes::_adEnemyDead, 0, 0.2f);
				}
			}
		}
	}
}

//专门为了被抓敌人做的攻击方法，有些东西我直接都整合到这个方法里面了
void Enemy::CaptureFire(float x, float y)
{
	_color = 0x7300ffFF;//被捕获的敌人加一层紫色
	if (Timers(700, 13)) {
		//给一小段无敌时间，不然很容易一抓到就被自己刚刚射的敌人子弹打死
		_isCaptureGod = false;
	}
	//碰撞检测部分(输入的触手坐标是从中心开始的，不要忘记了)
	if (Timers(100, 14) && !_isCaptureGod) {
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
		Attack(x - 32.f / 2, y - 64 - 10, true);
		//绘图部分
		GetHurtAni(x, y, 0, RED);
		switch (_type) {
		case normal:
			Novice::DrawSprite((int)x + 32, (int)y, LoadRes::_spEnemy, 1, 1, 3.14159f, _color);
			break;
		case laser:
			Novice::DrawSprite((int)x + 32, (int)y, LoadRes::_spEnemy2, 1, 1, 3.14159f, _color);
			break;
		case ufo:
			Novice::DrawSprite((int)x + 32, (int)y, LoadRes::_spEnemy3, 1, 1, 3.14159f, _color);
			break;
		case bigGun:
			Novice::DrawSprite((int)x + 32, (int)y, LoadRes::_spEnemy4, 1, 1, 3.14159f, _color);
			break;
		}
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

void Enemy::SetIsLive(bool live)
{
	_isLive = live;
}

int Enemy::GetScore()
{
	return _score;
}

float Enemy::GetWidth()
{
	return _width;
}

float Enemy::GetHigth()
{
	return _higth;
}

void Enemy::SetAttackValue(int attackTime1, int attackTime2, int bulletSum)
{
	_attackTime1 = attackTime1;
	_attackTime2 = attackTime2;
	_bulletSum = bulletSum;
}

Enemy::Direction Enemy::MoveAI()
{
	//想做一个控制飞行的AI，但是还未想好怎么做，现在Move方法就是简单的直接飞
	return _moveDirection;
}

std::vector<Enemy*> EnemyManager::_enemyUpdateVector;
std::queue<Enemy*> EnemyManager::_enemyIdiePool_normal;
std::queue<Enemy*> EnemyManager::_enemyIdiePool_laser;
std::queue<Enemy*> EnemyManager::_enemyIdiePool_ufo;
std::queue<Enemy*> EnemyManager::_enemyIdiePool_bigGun;
void EnemyManager::EnemyUpdata()
{
	for (Enemy* element : EnemyManager::_enemyUpdateVector) {
		element->DamageCheck();
		element->Attack(element->GetPosX() + 16, element->GetPosY(), false);
		element->Move();
	}
}

Enemy* EnemyManager::AcquireEnemy(float bornX, float bornY, Enemy::EnemyType type)
{
	switch (type) {
	case Enemy::normal:
		if (EnemyManager::_enemyIdiePool_normal.empty()) {
			Enemy* enemy = new Enemy(bornX, bornY, type);
			return enemy;
		}
		else {
			Enemy* enemy = EnemyManager::_enemyIdiePool_normal.front();
			enemy->Initial(bornX, bornY, type);
			EnemyManager::_enemyIdiePool_normal.pop();
			return enemy;
		}
		break;
	case Enemy::laser:
		if (EnemyManager::_enemyIdiePool_laser.empty()) {
			Enemy* enemy = new Enemy(bornX, bornY, type);
			return enemy;
		}
		else {
			Enemy* enemy = EnemyManager::_enemyIdiePool_laser.front();
			enemy->Initial(bornX, bornY, type);
			EnemyManager::_enemyIdiePool_laser.pop();
			return enemy;
		}
		break;
	case Enemy::ufo:
		if (EnemyManager::_enemyIdiePool_ufo.empty()) {
			Enemy* enemy = new Enemy(bornX, bornY, type);
			return enemy;
		}
		else {
			Enemy* enemy = EnemyManager::_enemyIdiePool_ufo.front();
			enemy->Initial(bornX, bornY, type);
			EnemyManager::_enemyIdiePool_ufo.pop();
			return enemy;
		}
		break;
	case Enemy::bigGun:
		if (EnemyManager::_enemyIdiePool_bigGun.empty()) {
			Enemy* enemy = new Enemy(bornX, bornY, type);
			return enemy;
		}
		else {
			Enemy* enemy = EnemyManager::_enemyIdiePool_bigGun.front();
			enemy->Initial(bornX, bornY, type);
			EnemyManager::_enemyIdiePool_bigGun.pop();
			return enemy;
		}
		break;
	}
	return nullptr;
}

void EnemyManager::ReleaseEnemy(Enemy* enemy)
{
	switch (enemy->GetType()) {
	case Enemy::normal: {
		auto it = std::find(EnemyManager::_enemyUpdateVector.begin(), EnemyManager::_enemyUpdateVector.end(), enemy);
		if (it != EnemyManager::_enemyUpdateVector.end()) {
			EnemyManager::_enemyUpdateVector.erase(it);
			EnemyManager::_enemyIdiePool_normal.push(enemy);
		}
		break; }
	case Enemy::laser: {
		auto it = std::find(EnemyManager::_enemyUpdateVector.begin(), EnemyManager::_enemyUpdateVector.end(), enemy);
		if (it != EnemyManager::_enemyUpdateVector.end()) {
			EnemyManager::_enemyUpdateVector.erase(it);
			EnemyManager::_enemyIdiePool_laser.push(enemy);
		}
		break; }
	case Enemy::ufo: {
		auto it = std::find(EnemyManager::_enemyUpdateVector.begin(), EnemyManager::_enemyUpdateVector.end(), enemy);
		if (it != EnemyManager::_enemyUpdateVector.end()) {
			EnemyManager::_enemyUpdateVector.erase(it);
			EnemyManager::_enemyIdiePool_ufo.push(enemy);
		}
		break; }
	case Enemy::bigGun: {
		auto it = std::find(EnemyManager::_enemyUpdateVector.begin(), EnemyManager::_enemyUpdateVector.end(), enemy);
		if (it != EnemyManager::_enemyUpdateVector.end()) {
			EnemyManager::_enemyUpdateVector.erase(it);
			EnemyManager::_enemyIdiePool_bigGun.push(enemy);
		}
		break; }
	}
}

