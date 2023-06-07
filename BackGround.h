#pragma once
#include "Screen.h"
class BackGround :
	public Screen
{
	int _width, _higth;
	int _speed;
public:
	BackGround();
	void BgMove();
};

