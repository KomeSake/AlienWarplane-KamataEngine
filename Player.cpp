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

void Player::Attack(char keys[])
{
	if (keys[DIK_SPACE] || keys[DIK_J]) {
		if (Timers(_attackTime, 0)) {
			Bullet* bullet = BulletManager::AcquireBullet(0);
			bullet->Fire(_posX + 15, _posY + 15);
		}
	}
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