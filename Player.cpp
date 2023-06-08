#include "Player.h"

Player::Player()
{
	_width = 64;
	_high = 64;
	_posX = 450.f / 2;
	_posY = 780 - _high;

	_hp = 10;
	_speed = 5;
	_attackTime = 300;

	_tentaclePosX = _posX + 100;
	_tentaclePosY = _posY;

	_isCapture = false;
}

void Player::Move(char keys[])
{
	//移动部分
	if (keys[DIK_W] && keys[DIK_A]) {
		_posX -= _speed * 0.7f;
		_posY -= _speed * 0.7f;
	}
	else if (keys[DIK_W] && keys[DIK_D]) {
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
		_posY -= _speed;
	}
	else if (keys[DIK_S]) {
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
	if (_posY >= 780.f - _high) {
		_posY = 780.f - _high;
	}
}

void Player::Attack(char keys[])
{
	if (keys[DIK_SPACE] || keys[DIK_J] || Novice::IsPressMouse(0)) {
		if (Timers(_attackTime, 1)) {
			Bullet* bullet = BulletManager::AcquireBullet(Bullet::player);
			bullet->Fire(_posX + 15, _posY + 15);
		}
	}
}

void Player::CaptureEnemy()
{
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
	MoveToTarget(_tentaclePosX, _tentaclePosY, (float)mouseX, (float)mouseY, 5);

	//画3条连线来充当和触手的链接
	Novice::DrawLine((int)_posX + 32, (int)_posY + 32, (int)_tentaclePosX, (int)_tentaclePosY, RED);
	Novice::DrawLine((int)_posX + 35, (int)_posY + 35, (int)_tentaclePosX + 2, (int)_tentaclePosY + 2, BLUE);
	Novice::DrawLine((int)_posX + 30, (int)_posY + 30, (int)_tentaclePosX - 2, (int)_tentaclePosY - 2, GREEN);

	//触手头部绘图
	if (Novice::IsPressMouse(1) && _isCapture == false) {
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
				EnemyManager::ReleaseEnemy(element);
				_enemyCaptured = new Enemy(_tentaclePosX, _tentaclePosY);
			}
		}
		//触手夹子的帧动画
		FrameAnimation(_tentaclePosX - 32, _tentaclePosY - 32, LoadRes::_spAniPlayerTentaclesTwo, 100);
	}
	else if (_isCapture) {
		if (_enemyCaptured->GetIsLive() == false) {
			_isCapture = false;
			delete(_enemyCaptured);
		}
		_enemyCaptured->CaptureFire(_tentaclePosX, _tentaclePosY);
		Novice::DrawSprite((int)_tentaclePosX - 32, (int)_tentaclePosY - 32, LoadRes::_spPlayerTentaclesTwo, 1, 1, 0, WHITE);
	}
	else {
		Novice::DrawSprite((int)_tentaclePosX - 32, (int)_tentaclePosY - 32, LoadRes::_spPlayerTentaclesTwo, 1, 1, 0, WHITE);
	}
}