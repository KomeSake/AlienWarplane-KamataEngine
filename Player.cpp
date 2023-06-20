#include "Player.h"

Player::Player()
{
	_width = 64;
	_higth = 64;
	_posX = 450.f / 2;
	_posY = 780 - _higth;
	_sprite = LoadRes::_spPlayer;

	_hp = 12;
	_speed = 4;
	_color = WHITE;
	_attackTime = 300;

	_enemyCaptured = nullptr;

	_tentaclePosX = _posX + 100;
	_tentaclePosY = _posY;

	_isCapture = false;
	_isCaptureCD = false;
	_captureCDTime = 5000;
	_capturedValue = 0;
	_captureSpeed = 10;
	_isPlayerHpPlus = false;

	_captureDamageCount = 0;
	_iscaptureDamage = false;
	_captureEnemyType = Enemy::null;
	_isCaptureBoomAni = false;

	_isGetHurtAniStart = false;
	_getHurtPosX = 0, _getHurtPosY = 0;
	_getHurtSpeedX = 10, _getHurtSpeedY = 10;
	_getHurtTime = 100;
	_aniMode_getHurt = 0;

	_scoreSum = 0;
	_isAutoShoot = false, _isEasyMode = false;
}

void Player::Move(char keys[])
{
	float spriteScaleX = 1, spriteScaleY = 1;
	//移动部分
	if (_hp > 0) {
		if (keys[DIK_W] && keys[DIK_A]) {
			spriteScaleY = 2;
			_posX -= _speed * 0.7f;
			_posY -= _speed * 0.7f;
		}
		else if (keys[DIK_W] && keys[DIK_D]) {
			spriteScaleY = 2;
			_posX += _speed * 0.7f;
			_posY -= _speed * 0.7f;
		}
		else if (keys[DIK_S] && keys[DIK_A]) {
			_posX -= _speed * 0.7f;
			_posY += _speed * 0.7f;
		}
		else if (keys[DIK_S] && keys[DIK_D]) {
			_posX += _speed * 0.7f;
			_posY += _speed * 0.7f;
		}
		else if (keys[DIK_W]) {
			spriteScaleY = 2;
			_posY -= _speed;
		}
		else if (keys[DIK_S]) {
			spriteScaleY = 0.7f;
			_posY += _speed;
		}
		else if (keys[DIK_A]) {
			_posX -= _speed;
		}
		else if (keys[DIK_D]) {
			_posX += _speed;
		}
		//画面内限制部分
		if (_posX <= 0) {
			_posX = 0;
		}
		else if (_posX >= 450.f - _width) {
			_posX = 450.f - _width;
		}
		if (_posY <= 0) {
			_posY = 0;
		}
		else if (_posY >= 780.f - _higth) {
			_posY = 780.f - _higth;
		}
	}
	else {
		//被打爆，缓缓的往下飞
		_posY += 1;
		_tentaclePosY += 2;
	}

	//动画效果部分
	GetHurtAni(_posX, _posY, _getHurtSpeedY * 3, RED);
	FrameAnimation(_posX + _width / 4, _posY + _width + 5, LoadRes::_spAniPlayerFire, spriteScaleX, spriteScaleY, WHITE, 100, 0);
	if (_iscaptureDamage) {
		if (PlayerAndTentaclePlus()) {
			_sprite = LoadRes::_spPlayer2;
		}
		else {
			_sprite = LoadRes::_spPlayer;
		}
	}
	else {
		_sprite = LoadRes::_spPlayer;
	}
}

void Player::Attack(char keys[])
{
	if (keys[DIK_SPACE] || Novice::IsPressMouse(0) || _isAutoShoot) {
		if (Timers(_attackTime, 11)) {
			Bullet* bullet1 = nullptr;
			float bulletX = 15, bulletY = 15;
			Bullet* bullet2 = nullptr;
			float bullet2X = 15, bullet2Y = 15;
			Bullet* bullet3 = nullptr;
			float bullet3X = 15, bullet3Y = 15;
			Bullet* bullet4 = nullptr;
			float bullet4X = 15, bullet4Y = 15;
			Bullet* bullet5 = nullptr;
			float bullet5X = 15, bullet5Y = 15;
			//是否是吸收状态
			if (_iscaptureDamage) {
				//吸收状态下，还捕获了相同类型的敌人,而且触手和自己重合，触发合体技！
				if (PlayerAndTentaclePlus()) {
					switch (_captureEnemyType) {
					case Enemy::normal:
						bullet1 = BulletManager::AcquireBullet(Bullet::enemyCapture);
						bulletX = -1;
						bullet2 = BulletManager::AcquireBullet(Bullet::enemyCapture);
						bullet2X = 31;
						_attackTime = 150;
						break;
					case Enemy::laser:
						bullet1 = BulletManager::AcquireBullet(Bullet::laserCapture);
						bullet1->SetSpeed(1, 1, 3);
						_attackTime = 50;
						break;
					case Enemy::ufo:
						bullet1 = BulletManager::AcquireBullet(Bullet::ufoCapture);
						bullet1->SetSpeed(0, 1, 10);
						bullet1->SetDamage(2);
						bullet2 = BulletManager::AcquireBullet(Bullet::ufoCapture);
						bullet2->SetSpeed(0, 1, 10);
						bullet2->SetSpeed(0, 0, -5);
						bullet2->SetDamage(2);
						bullet3 = BulletManager::AcquireBullet(Bullet::ufoCapture);
						bullet3->SetSpeed(0, 1, 10);
						bullet3->SetSpeed(0, 0, 5);
						bullet3->SetDamage(2);
						_attackTime = 600;
						break;
					case Enemy::bigGun:
						bullet1 = BulletManager::AcquireBullet(Bullet::bigGunCapture);
						bullet2 = BulletManager::AcquireBullet(Bullet::bigGunCapture);
						bullet2->SetSpeed(0, 0, -bullet2->GetSpeed(1) / 4);
						bullet3 = BulletManager::AcquireBullet(Bullet::bigGunCapture);
						bullet3->SetSpeed(0, 0, bullet3->GetSpeed(1) / 4);
						bullet4 = BulletManager::AcquireBullet(Bullet::bigGunCapture);
						bullet4->SetSpeed(0, 0, -bullet4->GetSpeed(1) / 3);
						bullet5 = BulletManager::AcquireBullet(Bullet::bigGunCapture);
						bullet5->SetSpeed(0, 0, bullet5->GetSpeed(1) / 3);
						_attackTime = 700;
						break;
					}
				}
				//单纯只是吸收状态
				else {
					switch (_captureEnemyType) {
					case Enemy::normal:
						bullet1 = BulletManager::AcquireBullet(Bullet::enemyCapture);
						_attackTime = 300;
						break;
					case Enemy::laser:
						bullet1 = BulletManager::AcquireBullet(Bullet::laserCapture);
						_attackTime = 300;
						break;
					case Enemy::ufo:
						bullet1 = BulletManager::AcquireBullet(Bullet::ufoCapture);
						bullet1->SetSpeed(0, 1, 10);
						bullet1->SetDamage(2);
						_attackTime = 600;
						bulletX -= 15;
						bulletY -= 20;
						break;
					case Enemy::bigGun:
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
						_attackTime = 1500;
						break;
					}
				}
			}
			//不是吸收状态下的正常子弹
			else {
				bullet1 = BulletManager::AcquireBullet(Bullet::player);
				_attackTime = 300;
			}

			if (bullet1 != nullptr) {
				bullet1->Fire(_posX + bulletX, _posY + bulletY);
			}
			if (bullet2 != nullptr) {
				bullet2->Fire(_posX + bullet2X, _posY + bullet2Y);
			}
			if (bullet3 != nullptr) {
				bullet3->Fire(_posX + bullet3X, _posY + bullet3Y);
			}
			if (bullet4 != nullptr) {
				bullet4->Fire(_posX + bullet4X, _posY + bullet4Y);
			}
			if (bullet5 != nullptr) {
				bullet5->Fire(_posX + bullet5X, _posY + bullet5Y);
			}
		}
	}
}

void Player::CaptureEnemy()
{
	//触手移动部分
	//鼠标坐标和触手坐标计算
	int mouseX = 0, mouseY = 0;
	Novice::GetMousePosition(&mouseX, &mouseY);
	if (mouseX > 450) {
		mouseX = 450;
	}
	else if (mouseX < 0) {
		mouseX = 0;
	}
	if (mouseY > 780) {
		mouseY = 780;
	}
	else if (mouseY < 0) {
		mouseY = 0;
	}
	if (_hp > 0) {
		switch (_isCaptureCD) {
		case false:
			MoveToTarget(_tentaclePosX, _tentaclePosY, (float)mouseX, (float)mouseY, _captureSpeed);
			break;
		case true:
			MoveToTarget(_tentaclePosX, _tentaclePosY, _posX + _width / 2, _posY + _higth / 2, _captureSpeed / 2);
			break;
		}
		//画连线来充当和触手的链接
		Novice::DrawLine((int)_posX + 32, (int)_posY + 29, (int)_tentaclePosX, (int)_tentaclePosY - 3, BLUE);
		Novice::DrawLine((int)_posX + 32, (int)_posY + 30, (int)_tentaclePosX, (int)_tentaclePosY - 2, RED);
		Novice::DrawLine((int)_posX + 32, (int)_posY + 31, (int)_tentaclePosX, (int)_tentaclePosY - 1, BLUE);
		Novice::DrawLine((int)_posX + 32, (int)_posY + 32, (int)_tentaclePosX, (int)_tentaclePosY, RED);
		Novice::DrawLine((int)_posX + 32, (int)_posY + 33, (int)_tentaclePosX, (int)_tentaclePosY + 1, BLUE);
		Novice::DrawLine((int)_posX + 32, (int)_posY + 34, (int)_tentaclePosX, (int)_tentaclePosY + 2, RED);
		Novice::DrawLine((int)_posX + 32, (int)_posY + 35, (int)_tentaclePosX, (int)_tentaclePosY + 3, BLUE);
	}

	//触手的机制判断与绘图部分
	//触手可以抓人阶段
	if (Novice::IsPressMouse(1) && !_isCapture && !_isCaptureCD) {
		_captureDamageCount = 0;//将夹爆被抓敌人计数归零
		//碰撞判断
		float tentacleW = 64, tentacleH = 64;
		float enemyW = 64, enemyH = 64;
		for (Enemy* element : EnemyManager::_enemyUpdateVector) {
			float tentacleCenterX = _tentaclePosX + tentacleW / 2, tentacleCenterY = _tentaclePosY + tentacleH / 2;
			float enemyCenterX = element->GetPosX() + enemyW, enemyCenterY = element->GetPosY() + enemyH;
			float distance = sqrtf(powf(tentacleCenterX - enemyCenterX, 2) + powf(tentacleCenterY - enemyCenterY, 2));
			if (distance < tentacleW / 2 + enemyW / 2) {
				//碰撞后发生的效果
				_isCapture = true;
				_hp++;
				_isPlayerHpPlus = true;
				EnemyManager::ReleaseEnemy(element);
				_enemyCaptured = new Enemy(_tentaclePosX, _tentaclePosY, element->GetType());
				//根据抓住敌人类型做一些变化
				switch (element->GetType()) {
				case Enemy::normal:
					_enemyCaptured->SetHp(1, 2);
					_captureSpeed = 5;
					break;
				case Enemy::laser:
					_enemyCaptured->SetHp(1, 1.5f);
					_captureSpeed = 2;
					break;
				case Enemy::ufo:
					_enemyCaptured->SetHp(1, 0.5f);
					break;
				case Enemy::bigGun:
					_captureSpeed = 1.5f;
					break;
				}
			}
		}
		//触手夹子的帧动画
		FrameAnimation(_tentaclePosX - 32, _tentaclePosY - 32, LoadRes::_spAniPlayerTentacles, 100, 1);
	}
	//触手已经夹住敌人阶段
	else if (_isCapture && !_isCaptureCD) {
		_enemyCaptured->CaptureFire(_tentaclePosX, _tentaclePosY);
		Novice::DrawSprite((int)_tentaclePosX - 32, (int)_tentaclePosY - 32, LoadRes::_spPlayerTentacles, 1, 1, 0, WHITE);
		if (_enemyCaptured->GetIsLive() == false) {
			//被抓住的敌人死亡后先播放爆炸动画，然后在更新判定条件
			if (!Timers((int)(LoadRes::_spAniExplode.size() + 2) * 50, 12)) {
				FrameAnimation(_tentaclePosX - 32, _tentaclePosY - 64, LoadRes::_spAniExplode, 50, 2);
			}
			else {
				SetFrameIndex(2, 0);
				_isCaptureCD = true;
				_captureSpeed = 10;
				delete(_enemyCaptured);
			}
		}
		//按住右键捏爆抓住的敌人(需要持续按住，一共1500毫秒)
		if (Novice::IsPressMouse(1)) {
			if (Timers(500, 15)) {
				_captureDamageCount++;
				_enemyCaptured->SetAniMode(1, 0);
				if (_captureDamageCount >= 3) {
					_iscaptureDamage = true;
					_captureEnemyType = (Enemy::EnemyType)(_enemyCaptured->GetType());
					_isCaptureBoomAni = true;
					//因为不想播放敌人的爆炸特效，所以下面的代码其实是把销毁敌人的操作复制拷贝了一份
					_isCaptureCD = true;
					_captureSpeed = 10;
					delete(_enemyCaptured);
				}
			}
		}
		else {
			_captureDamageCount = 0;
		}
	}
	//触手爆炸，CD阶段
	else if (_isCaptureCD) {
		if (_capturedValue >= 4) {
			if (Timers(_captureCDTime, 13)) {
				_isCaptureCD = false;
				_isCapture = false;
				_capturedValue = 0;
			}
		}
		Novice::DrawSprite((int)_tentaclePosX - 32, (int)_tentaclePosY - 32, LoadRes::_spPlayerTentacles, 1, 1, 0, 0x464646FF);
	}
	//触手正常情况绘图阶段
	else {
		Novice::DrawSprite((int)_tentaclePosX - 32, (int)_tentaclePosY - 32, LoadRes::_spPlayerTentacles, 1, 1, 0, WHITE);
	}
}

void Player::DamageCheck()
{
	for (Bullet* element : BulletManager::_bulletUpdateVector_enemy) {
		float playerCenterX = _posX + _width / 2, playerCenterY = _posY + _higth / 2;
		float bulletCeneterX = element->GetPosX() + element->GetWidth() / 2, bulletCeneterY = element->GetPosY() + element->GetHigth() / 2;
		float distacne = sqrtf(powf(playerCenterX - bulletCeneterX, 2) + powf(playerCenterY - bulletCeneterY, 2));
		if (distacne < _width / 2 + element->GetWidth() / 2) {
			BulletManager::ReleaseBullet(element);
			_aniMode_getHurt = 1;
			if (!_isEasyMode) {
				_iscaptureDamage = false;
				_captureEnemyType = Enemy::null;
			}
			_hp -= element->GetDamage();
		}
	}
}

void Player::AniPlayerUP()
{
	//玩家抓到敌人回血特效
	int frameTime = 100;
	if (_isPlayerHpPlus) {
		if (!Timers((int)LoadRes::_spAniPlayerHpPlus.size() * frameTime, 14)) {
			FrameAnimation(_posX + 3, _posY + 7, LoadRes::_spAniPlayerHpPlus, frameTime, 3);
			FrameAnimation(_tentaclePosX - 30, _tentaclePosY - 32 + 5, LoadRes::_spAniPlayerHpPlus, frameTime, 4);
		}
		else {
			SetFrameIndex(3, 0);
			SetFrameIndex(4, 0);
			_isPlayerHpPlus = false;
		}
	}
	//玩家死亡爆炸特效
	if (_hp <= 0) {
		FrameAnimation(_posX, _posY, LoadRes::_spAniExplode, 50, 5);
		FrameAnimation(_tentaclePosX - 32, _tentaclePosY - 32, LoadRes::_spAniExplode, 50, 5);
	}
	//触手抓爆敌人，吸收特效
	if (_isCaptureBoomAni) {
		if (!Timers((int)LoadRes::_spAniPlayerHpPlus2.size() * frameTime, 16)) {
			FrameAnimation(_tentaclePosX - 30, _tentaclePosY - 32, LoadRes::_spAniPlayerHpPlus2, 1, 1, WHITE, frameTime, 6);
		}
		else {
			SetFrameIndex(6, 0);
			_isCaptureBoomAni = false;
		}
	}
}

void Player::EasyModeValue()
{
	if (_isEasyMode) {
		_hp = _hp * 2;
	}
}

int Player::GetSprite()
{
	return _sprite;
}

int Player::GetHp()
{
	return _hp;
}

int Player::GetCapturedValue()
{
	return _capturedValue;
}

void Player::CapturedValueAdd()
{
	if (_capturedValue < 4) {
		_capturedValue++;
	}
}

bool Player::GetIsCapture()
{
	return _isCapture;
}

bool Player::GetIsCaptureCD()
{
	return _isCaptureCD;
}

int Player::GetCaptureCDTime()
{
	return _captureCDTime;
}

int Player::GetScoreSum()
{
	return _scoreSum;
}

void Player::SetScorePlus(int value)
{
	_scoreSum += value;
}

Enemy::EnemyType Player::GetCaptureEnemyType()
{
	return _captureEnemyType;
}

void Player::SetAutoShoot(bool taf)
{
	_isAutoShoot = taf;
}

void Player::SetEasyMode(bool taf)
{
	_isEasyMode = taf;
}

bool Player::PlayerAndTentaclePlus()
{
	if (_captureEnemyType == _enemyCaptured->GetType() && !_isCaptureCD && _isCapture) {
		if (_tentaclePosX > _posX - 32 && _tentaclePosX < _posX + 64 + 32
			&& _tentaclePosY > _posY - 64 && _tentaclePosY < _posY + 64) {
			return true;
		}
	}
	return false;
}
