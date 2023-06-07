#include "BackGround.h"

BackGround::BackGround()
{
	_posX = 0;
	_posY = 0;
	_width = 450;
	_higth = 780;
	_speed = 1;
}

void BackGround::BgMove()
{
	_posY += _speed;
	if (_posY > 780) {
		_posY = 0;
	}
	FrameAnimation(LoadRes::_spBg, _posX, _posY);
	FrameAnimation(LoadRes::_spBg, _posX, _posY - _higth);
}
