﻿#include "GameUI.h"

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

	_cdMove = 0;
	_cdSpeed = 0;
}

void UI_CaptureVessel::UIStart(Player obj)
{
	FrameAnimation(_posX, _posY, LoadRes::_spUICaptureVessel[0], _color);
	switch (obj.GetCapturedValue()) {
	case 1:
		FrameAnimation(_posX, _posY, LoadRes::_spUICaptureVessel[1], _color);
		break;
	case 2:
		FrameAnimation(_posX, _posY, LoadRes::_spUICaptureVessel[2], _color);
		break;
	case 3:
		FrameAnimation(_posX, _posY, LoadRes::_spUICaptureVessel[3], _color);
		break;
	case 4:
		FrameAnimation(_posX, _posY, LoadRes::_spUICaptureVessel[4], _color);
		break;
	}
	//CD标记部分
	if (obj.GetIsCaptureCD()) {
		if (obj.GetCapturedValue() >= 4) {
			//_cdSpeed = _width / obj.GetCaptureCDTime() / 1000 * 60;
			_cdSpeed = 0.25f;
			_cdMove += _cdSpeed;
			Novice::DrawQuad(
				(int)_posX, (int)_posY,
				(int)_posX + (int)_cdMove, (int)_posY,
				(int)_posX, (int)_posY + (int)_higth,
				(int)_posX + (int)_cdMove, (int)_posY + (int)_higth,
				0, 0,
				(int)_cdMove, (int)_higth,
				LoadRes::_spUICaptureVessel[5],
				WHITE);
		}
	}
	else {
		FrameAnimation(_posX, _posY, LoadRes::_spUICaptureVessel[5], _color);
	}
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

void UI_HpVessel::UIStart(Player obj)
{
	FrameAnimation(_posX, _posY, LoadRes::_spUIHpVessel[0], _color);

	int hpBoxW = 62, hpBoxH = 12;
	int hpBoxTopLeftPosX = (int)_posX + 93, hpBoxTopLeftPosY = (int)_posY - 2;
	int hpBoxGapY = hpBoxH + 3;
	unsigned int hpBoxColor_ON = 0xd01716FF, hpBoxColor_OFF = 0x661111FF;
	unsigned int hpBoxColor1 = hpBoxColor_OFF;
	unsigned int hpBoxColor2 = hpBoxColor_OFF;
	unsigned int hpBoxColor3 = hpBoxColor_OFF;
	unsigned int hpBoxColor4 = hpBoxColor_OFF;
	unsigned int hpBoxColor5 = hpBoxColor_OFF;
	unsigned int hpBoxColor6 = hpBoxColor_OFF;
	if (obj.GetHp() >= 11) {
		hpBoxColor1 = hpBoxColor_ON;
		hpBoxColor2 = hpBoxColor_ON;
		hpBoxColor3 = hpBoxColor_ON;
		hpBoxColor4 = hpBoxColor_ON;
		hpBoxColor5 = hpBoxColor_ON;
		hpBoxColor6 = hpBoxColor_ON;
	}
	else if (obj.GetHp() >= 9) {
		hpBoxColor1 = hpBoxColor_ON;
		hpBoxColor2 = hpBoxColor_ON;
		hpBoxColor3 = hpBoxColor_ON;
		hpBoxColor4 = hpBoxColor_ON;
		hpBoxColor5 = hpBoxColor_ON;
	}
	else if (obj.GetHp() >= 7) {
		hpBoxColor1 = hpBoxColor_ON;
		hpBoxColor2 = hpBoxColor_ON;
		hpBoxColor3 = hpBoxColor_ON;
		hpBoxColor4 = hpBoxColor_ON;
	}
	else if (obj.GetHp() >= 5) {
		hpBoxColor1 = hpBoxColor_ON;
		hpBoxColor2 = hpBoxColor_ON;
		hpBoxColor3 = hpBoxColor_ON;
	}
	else if (obj.GetHp() >= 3) {
		hpBoxColor1 = hpBoxColor_ON;
		hpBoxColor2 = hpBoxColor_ON;
	}
	else if (obj.GetHp() >= 1) {
		hpBoxColor1 = hpBoxColor_ON;
	}
	Novice::DrawBox(hpBoxTopLeftPosX, hpBoxTopLeftPosY + hpBoxGapY * 6, hpBoxW, hpBoxH, 0, hpBoxColor1, kFillModeSolid);
	Novice::DrawBox(hpBoxTopLeftPosX, hpBoxTopLeftPosY + hpBoxGapY * 5, hpBoxW, hpBoxH, 0, hpBoxColor2, kFillModeSolid);
	Novice::DrawBox(hpBoxTopLeftPosX, hpBoxTopLeftPosY + hpBoxGapY * 4, hpBoxW, hpBoxH, 0, hpBoxColor3, kFillModeSolid);
	Novice::DrawBox(hpBoxTopLeftPosX, hpBoxTopLeftPosY + hpBoxGapY * 3, hpBoxW, hpBoxH, 0, hpBoxColor4, kFillModeSolid);
	Novice::DrawBox(hpBoxTopLeftPosX, hpBoxTopLeftPosY + hpBoxGapY * 2, hpBoxW, hpBoxH, 0, hpBoxColor5, kFillModeSolid);
	Novice::DrawBox(hpBoxTopLeftPosX, hpBoxTopLeftPosY + hpBoxGapY * 1, hpBoxW, hpBoxH, 0, hpBoxColor6, kFillModeSolid);
}
