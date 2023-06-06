#pragma once
#include "Plane.h"
class Player :
	public Plane
{
	int _attackTime;
public:
	Player();
	void Move(char keys[]);
	void Attack(char keys[]);
};