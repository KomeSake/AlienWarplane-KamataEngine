#pragma once
#include "Plane.h"
#include "Enemy.h"
class Player :
	public Plane
{
public:
	Player();
	void Move(char keys[]);
	void Attack(char keys[]);
	void CaptureEnemy();
private:
	int _attackTime = 0;
	float _tentaclePosX = 0, _tentaclePosY = 0;
	bool _isCapture = false;
};