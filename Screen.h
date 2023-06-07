#pragma once
#include <Novice.h>
#include "LoadRes.h"
class Screen
{
protected:
	float _posX, _posY;
public:
	void FrameAnimation(int sprite, float x, float y);
};

