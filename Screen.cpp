#include "Screen.h"

void Screen::FrameAnimation(int sprite, float x, float y)
{
	Novice::DrawSprite((int)x, (int)y, sprite, 1, 1, 0, WHITE);
}
