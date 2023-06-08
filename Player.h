#pragma once
#include "Plane.h"
class Player :
	public Plane
{
	int _attackTime;
	float _tentaclePosX, _tentaclePosY;
public:
	Player();
	void Move(char keys[]);
	void Attack(char keys[]);
	void CaptureEnemy();
};