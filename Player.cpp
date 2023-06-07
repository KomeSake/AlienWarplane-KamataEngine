#include "Player.h"

Player::Player()
{
	_posX = 450.f / 2;
	_posY = 780 - _high;
	_width = 64;
	_high = 64;

	_hp = 10;
	_speed = 5;
	_attackTime = 300;
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
	if (keys[DIK_SPACE] || keys[DIK_J]) {
		if (Timers(_attackTime, 0)) {
			Bullet* bullet = BulletManager::AcquireBullet(0);
			bullet->Fire(_posX + 15, _posY + 15);
		}
	}
}

float posX = 0, posY = 0;
void Player::CaptureEnemy()
{
	int mouseX = 0, mouseY = 0;
	if (Novice::IsPressMouse(1)) {
		Novice::GetMousePosition(&mouseX, &mouseY);
		MoveToTarget(posX, posY, (float)mouseX, (float)mouseY, 5);
	}
	Novice::DrawLine((int)_posX + 32, (int)_posY + 32, (int)posX, (int)posY, RED);
	Novice::DrawLine((int)_posX + 35, (int)_posY + 35, (int)posX + 2, (int)posY + 2, BLUE);
	Novice::DrawLine((int)_posX + 30, (int)_posY + 30, (int)posX - 2, (int)posY - 2, GREEN);

	Novice::DrawSprite((int)posX - 32, (int)posY - 32, LoadRes::_spPlayerTentacles02, 1, 1, 0, WHITE);
}