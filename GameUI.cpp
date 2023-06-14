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

void UI_CaptureVessel::UIOpen(Player obj)
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
			_cdSpeed = _width / ((float)(obj.GetCaptureCDTime()) / 1000 * 60) * 0.7f;
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
		_cdMove = 0;
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

void UI_HpVessel::UIOpen(Player obj)
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

UI_StartScene::UI_StartScene()
{
	_posX = 0, _posY = 0;
	_width = 450, _higth = 780;
	_color = WHITE;

	_titlePosX = 0, _titlePosY = 50;
	_buttonW = 210, _buttonH = 73;
	_buttonPosX_Start = 450.f / 2 - _buttonW / 2, _buttonPosY_Start = 450;
	_buttonPosX_Help = 450.f / 2 - _buttonW / 2, _buttonPosY_Help = 600;
	_buttonTextW_Start = 127;
	_buttonTextW_Help = 105;
}

void UI_StartScene::UIOpen()
{
	FrameAnimation(0, 0, LoadRes::_spUIStartScene[0], WHITE);
	FrameAnimation(_titlePosX, _titlePosY, LoadRes::_spUIStartScene[1], WHITE);
	FrameAnimation(_buttonPosX_Start, _buttonPosY_Start, LoadRes::_spUIStartScene[2], WHITE);
	FrameAnimation(_buttonPosX_Help, _buttonPosY_Help, LoadRes::_spUIStartScene[2], WHITE);
	int mouseX = 0, mouseY = 0;
	Novice::GetMousePosition(&mouseX, &mouseY);
	if (mouseX >= _buttonPosX_Start && mouseX <= _buttonPosX_Start + _buttonW
		&& mouseY >= _buttonPosY_Start && mouseY <= _buttonPosY_Start + _buttonH) {
		FrameAnimation(_buttonPosX_Start - 8, _buttonPosY_Start - 7, LoadRes::_spUIStartScene[5], WHITE);
		//点击Start按钮触发效果
		if (Novice::IsPressMouse(0)) {
			_isButton_Start = true;
		}
	}
	if (mouseX >= _buttonPosX_Help && mouseX <= _buttonPosX_Help + _buttonW
		&& mouseY >= _buttonPosY_Help && mouseY <= _buttonPosY_Help + _buttonH) {
		FrameAnimation(_buttonPosX_Help - 8, _buttonPosY_Help - 7, LoadRes::_spUIStartScene[5], WHITE);
		//点击Help按钮触发效果
	}
	FrameAnimation(_buttonPosX_Start + _buttonW / 2 - _buttonTextW_Start / 2, _buttonPosY_Start - 15, LoadRes::_spUIStartScene[3], WHITE);
	FrameAnimation(_buttonPosX_Help + +_buttonW / 2 - _buttonTextW_Help / 2, _buttonPosY_Help - 15, LoadRes::_spUIStartScene[4], WHITE);
}

UI_GameOverScene::UI_GameOverScene()
{
	//因为读取图片的函数有错误，这个界面的具体数据还没有去读取
	_posX = 0, _posY = 0;
	_width = 450, _higth = 780;
	_color = WHITE;

	_titlePosX = 0, _titlePosY = 50;
	_buttonW = 133, _buttonH = 55;
	_buttonPosX_Restart = 450.f / 2 - _buttonW / 2, _buttonPosY_Restart = 450;
	_buttonPosX_Back = 450.f / 2 - _buttonW / 2, _buttonPosY_Back = 600;
	_buttonTextW_Restart = 105;
	_buttonTextW_Back = 67;
}

void UI_GameOverScene::UIOpen()
{
	FrameAnimation(0, 0, LoadRes::_spUIStartScene[0], WHITE);
	FrameAnimation(_titlePosX, _titlePosY, LoadRes::_spUIStartScene[1], WHITE);
	FrameAnimation(_buttonPosX_Restart, _buttonPosY_Restart, LoadRes::_spUIStartScene[2], WHITE);
	FrameAnimation(_buttonPosX_Back, _buttonPosY_Back, LoadRes::_spUIStartScene[2], WHITE);
	int mouseX = 0, mouseY = 0;
	Novice::GetMousePosition(&mouseX, &mouseY);
	if (mouseX >= _buttonPosX_Restart && mouseX <= _buttonPosX_Restart + _buttonW
		&& mouseY >= _buttonPosY_Restart && mouseY <= _buttonPosY_Restart + _buttonH) {
		FrameAnimation(_buttonPosX_Restart - 8, _buttonPosX_Restart - 7, LoadRes::_spUIStartScene[5], WHITE);
		//点击Start按钮触发效果
		if (Novice::IsPressMouse(0)) {
		}
	}
	if (mouseX >= _buttonPosX_Back && mouseX <= _buttonPosX_Back + _buttonW
		&& mouseY >= _buttonPosY_Back && mouseY <= _buttonPosY_Back + _buttonH) {
		FrameAnimation(_buttonPosX_Back - 8, _buttonPosY_Back - 7, LoadRes::_spUIStartScene[5], WHITE);
		//点击Help按钮触发效果
	}
	FrameAnimation(_buttonPosX_Restart + _buttonW / 2 - _buttonTextW_Restart / 2, _buttonPosY_Restart - 15, LoadRes::_spUIStartScene[3], WHITE);
	FrameAnimation(_buttonPosX_Back + +_buttonW / 2 - _buttonTextW_Back / 2, _buttonPosY_Back - 15, LoadRes::_spUIStartScene[4], WHITE);
}
