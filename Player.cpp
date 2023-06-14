﻿#include "Player.h"

Player::Player()
{
	_width = 64;
	_higth = 64;
	_posX = 450.f / 2;
	_posY = 780 - _higth;

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

	_isGetHurtAniStart = false;
	_getHurtPosX = 0, _getHurtPosY = 0;
	_getHurtSpeedX = 10, _getHurtSpeedY = 10;
	_getHurtTime = 100;
	_aniMode_getHurt = 0;
}

void Player::Move(char keys[])
{
	float spriteScaleX = 1, spriteScaleY = 1;
	//移动部分
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
	if (_posX >= 450.f - _width) {
		_posX = 450.f - _width;
	}
	if (_posY <= 0) {
		_posY = 0;
	}
	if (_posY >= 780.f - _higth) {
		_posY = 780.f - _higth;
	}

	//动画效果部分
	GetHurtAni(_posX, _posY, _getHurtSpeedY * 3, RED);
	FrameAnimation(_posX + _width / 4, _posY + _width + 5, LoadRes::_spAniPlayerFire, spriteScaleX, spriteScaleY, 100, 0);
}

void Player::Attack(char keys[])
{
	if (keys[DIK_SPACE] || keys[DIK_J] || Novice::IsPressMouse(0)) {
		if (Timers(_attackTime, 11)) {
			Bullet* bullet = BulletManager::AcquireBullet(Bullet::player);
			bullet->Fire(_posX + 15, _posY + 15);
		}
	}
}

//一个可以提前捏爆抓住敌机的机制
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
	switch (_isCaptureCD) {
	case false:
		MoveToTarget(_tentaclePosX, _tentaclePosY, (float)mouseX, (float)mouseY, _captureSpeed);
		break;
	case true:
		MoveToTarget(_tentaclePosX, _tentaclePosY, _posX + _width / 2, _posY + _higth / 2, _captureSpeed / 2);
		break;
	}

	//画3条连线来充当和触手的链接(有空改成长方体试一试)
	Novice::DrawLine((int)_posX + 32, (int)_posY + 32, (int)_tentaclePosX, (int)_tentaclePosY, RED);
	Novice::DrawLine((int)_posX + 35, (int)_posY + 35, (int)_tentaclePosX + 2, (int)_tentaclePosY + 2, BLUE);
	Novice::DrawLine((int)_posX + 30, (int)_posY + 30, (int)_tentaclePosX - 2, (int)_tentaclePosY - 2, GREEN);

	//触手的机制判断与绘图部分
	//触手可以抓人
	if (Novice::IsPressMouse(1) && !_isCapture && !_isCaptureCD) {
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
				}
			}
		}
		//触手夹子的帧动画
		FrameAnimation(_tentaclePosX - 32, _tentaclePosY - 32, LoadRes::_spAniPlayerTentaclesTwo, 100, 1);
	}
	//触手已经夹住敌人
	else if (_isCapture && !_isCaptureCD) {
		_enemyCaptured->CaptureFire(_tentaclePosX, _tentaclePosY);
		Novice::DrawSprite((int)_tentaclePosX - 32, (int)_tentaclePosY - 32, LoadRes::_spPlayerTentaclesTwo, 1, 1, 0, WHITE);
		if (_enemyCaptured->GetIsLive() == false) {
			//被抓住的敌人死亡后先播放爆炸动画，然后在更新判定条件
			if (!Timers((int)(LoadRes::_spAniExplode.size() + 2) * 50, 12)) {
				FrameAnimation(_tentaclePosX - 32, _tentaclePosY - 64, LoadRes::_spAniExplode, 50, 2);
			}
			else {
				SetFrameIndex(2, 0);
				_isCapture = false;
				_isCaptureCD = true;
				_captureSpeed = 10;
				delete(_enemyCaptured);
			}
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
		Novice::DrawSprite((int)_tentaclePosX - 32, (int)_tentaclePosY - 32, LoadRes::_spPlayerTentaclesTwo, 1, 1, 0, 0x464646FF);
	}
	//触手正常情况绘图
	else {
		Novice::DrawSprite((int)_tentaclePosX - 32, (int)_tentaclePosY - 32, LoadRes::_spPlayerTentaclesTwo, 1, 1, 0, WHITE);
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
			_hp -= element->GetDamage();
			//血没了这里需要做一个爆炸的动画效果，和传出一条死亡信息
		}
	}
}

void Player::AniPlayerUP()
{
	//玩家抓到敌人回血特效
	int frameTime = 100;
	if (_isPlayerHpPlus) {
		if (!Timers((int)LoadRes::_spAniPlayerHpPlus.size() * frameTime, 14)) {
			FrameAnimation(_posX, _posY + 7, LoadRes::_spAniPlayerHpPlus, frameTime, 3);
			FrameAnimation(_tentaclePosX - 32, _tentaclePosY - 32 + 5, LoadRes::_spAniPlayerHpPlus2, frameTime, 4);
		}
		else {
			SetFrameIndex(3, 0);
			SetFrameIndex(4, 0);
			_isPlayerHpPlus = false;
		}
	}
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
