#include "Plane.h"


clock_t start[3] = { clock(),clock(),clock() };
clock_t end[3] = { clock(),clock(),clock() };
int Plane::Timers(int milli, int index)
{
	end[index] = clock();
	if (end[index] - start[index] > milli) {
		start[index] = end[index];
		return 1;
	}
	return 0;
}

void Plane::FrameAnimation(float x, float y, int sprite)
{
	Novice::DrawSprite((int)x, (int)y, sprite, 1, 1, 0, WHITE);
}

float Plane::GetPosX()
{
	return _posX;
}
float Plane::GetPosY()
{
	return _posY;
}


