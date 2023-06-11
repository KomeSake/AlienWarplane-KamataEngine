#include "GameUI.h"

void GameUI::FrameAnimation(float x, float y, int sprite, unsigned int color)
{
	Novice::DrawSprite((int)x, (int)y, sprite, 1, 1, 0, color);
}

UI_BackGround::UI_BackGround()
{
	_posX = 0;
	_posY = 0;
	_width = 450;
	_higth = 780;
	_speed = 1;
	_color = WHITE;
}

void UI_BackGround::BgMove()
{
	_posY += _speed;
	if (_posY > 780) {
		_posY = 0;
	}
	FrameAnimation(_posX, _posY, LoadRes::_spUIBg, _color);
	FrameAnimation(_posX, _posY - _higth, LoadRes::_spUIBg, _color);
}

UI_CaptureVessel::UI_CaptureVessel()
{
	_width = 120;
	_higth = 135;
	_posX = 0;
	_posY = 780 - _higth;
	_speed = 0;
	_color = WHITE;
}

UI_HpVessel::UI_HpVessel()
{
	_width = 165;
	_higth = 108;
	_posX = 450 - _width;
	_posY = 780 - _higth;
	_speed = 0;
	_color = WHITE;
}