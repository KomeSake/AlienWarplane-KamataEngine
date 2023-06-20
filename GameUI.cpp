﻿#include "GameUI.h"

void GameUI::FrameTexture(float x, float y, int sprite, unsigned int color)
{
	Novice::DrawSprite((int)x, (int)y, sprite, 1, 1, 0, color);
}

void GameUI::FrameTexture(float x, float y, std::map<int, LoadRes::SpriteList> sprite, int index, unsigned int color)
{
	int arrSprite = sprite[index].sprite;
	int arrW = sprite[index].w, arrH = sprite[index].h;
	int arrX = sprite[index].x, arrY = sprite[index].y;
	int arrSpriteW = sprite[index].listW, arrSpriteH = sprite[index].listH;
	Novice::DrawSpriteRect((int)x, (int)y, arrX, arrY, arrW, arrH, arrSprite, ((float)arrW / (float)arrSpriteW), ((float)arrH / (float)arrSpriteH), 0, color);
}

bool GameUI::Timers(int milli, int index)
{
	if (!_isTimeOpen[index]) {
		_timeStart[index] = clock();
		_isTimeOpen[index] = true;
	}
	_timeEnd[index] = clock();
	if (_timeEnd[index] - _timeStart[index] > milli) {
		_isTimeOpen[index] = false;
		return 1;
	}
	return 0;
}

UI_BackGround::UI_BackGround()
{
	_posX = 0;
	_posY = 0;
	_width = 450;
	_higth = 780;
	_speed = 0.4f;
	_color = WHITE;
}

void UI_BackGround::BgMove()
{
	_posY += _speed;
	if (_posY > 780) {
		_posY = 0;
	}
	FrameTexture(_posX, _posY, LoadRes::_spUIBg, _color);
	FrameTexture(_posX, _posY - _higth, LoadRes::_spUIBg, _color);
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
	FrameTexture(_posX, _posY, LoadRes::_spUICaptureVessel, 0, _color);
	switch (obj.GetCapturedValue()) {
	case 1:
		FrameTexture(_posX, _posY, LoadRes::_spUICaptureVessel, 1, _color);
		break;
	case 2:
		FrameTexture(_posX, _posY, LoadRes::_spUICaptureVessel, 2, _color);
		break;
	case 3:
		FrameTexture(_posX, _posY, LoadRes::_spUICaptureVessel, 3, _color);
		break;
	case 4:
		FrameTexture(_posX, _posY, LoadRes::_spUICaptureVessel, 4, _color);
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
				LoadRes::_spUICaptureVessel_05,
				WHITE);
		}
	}
	else {
		_cdMove = 0;
		FrameTexture(_posX, _posY, LoadRes::_spUICaptureVessel, 5, _color);
	}
}

UI_HpVessel::UI_HpVessel()
{
	_width = 165;
	_higth = 153;
	_posX = 450 - _width;
	_posY = 780 - _higth;
	_speed = 0;
	_color = WHITE;
}

void UI_HpVessel::UIOpen(Player obj)
{
	FrameTexture(_posX, _posY, LoadRes::_spUIHpVessel[0], _color);
	//吸收敌机指示坐标
	int captureEnemyX = (int)_posX + 180, captureEnemyY = (int)_posY + 40;
	float captureEnemyAngle = 3.14159f / 180 * 150;
	switch (obj.GetCaptureEnemyType()) {
	case Enemy::normal:
		Novice::DrawSprite(captureEnemyX, captureEnemyY, LoadRes::_spEnemy, 0.75f, 0.75f, captureEnemyAngle, WHITE);
		break;
	case Enemy::laser:
		Novice::DrawSprite(captureEnemyX, captureEnemyY, LoadRes::_spEnemy2, 0.75f, 0.75f, captureEnemyAngle, WHITE);
		break;
	case Enemy::ufo:
		captureEnemyX -= 7, captureEnemyY -= 7;
		Novice::DrawSprite(captureEnemyX, captureEnemyY, LoadRes::_spEnemy3, 0.75f, 0.75f, captureEnemyAngle, WHITE);
		break;
	case Enemy::bigGun:
		captureEnemyX += 3, captureEnemyY += 3;
		Novice::DrawSprite(captureEnemyX, captureEnemyY, LoadRes::_spEnemy4, 0.75f, 0.75f, captureEnemyAngle, WHITE);
		break;
	}
	FrameTexture(_posX, _posY, LoadRes::_spUIHpVessel[1], _color);
	//血条相关坐标
	int hpBoxW = 62, hpBoxH = 12;
	int hpBoxTopLeftPosX = (int)_posX + 93, hpBoxTopLeftPosY = (int)_posY + 42;
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

	//直接用显示数字的函数来替代分数
	int score = obj.GetScoreSum();
	int scoreX = 0;
	if (obj.GetScoreSum() >= 9999999) {
		score = 9999999;
		scoreX = 297;
	}
	else if (obj.GetScoreSum() >= 100000) {
		scoreX = 353 - 9 * 5;
	}
	else if (obj.GetScoreSum() >= 10000) {
		scoreX = 353 - 9 * 4;
	}
	else if (obj.GetScoreSum() >= 1000) {
		scoreX = 353 - 9 * 3;
	}
	else if (obj.GetScoreSum() >= 100) {
		scoreX = 353 - 9 * 2;
	}
	else if (obj.GetScoreSum() >= 10) {
		scoreX = 353 - 9;
	}
	else if (obj.GetScoreSum() == 0) {
		score = 0;
		scoreX = 353;
	}
	Novice::ScreenPrintf(scoreX, 758, "%d", score);
}

UI_SignalVessel::UI_SignalVessel()
{
	_width = 187;
	_higth = 97;
	_posX = 0;
	_posY = 0;
	_speed = 0;
	_color = WHITE;

	_bottomPosX = 0, _bottomPosY = 0;
	_numberPosX = 3, _numberPosY = 8;
	_redPosX = -1, _redPosY = 23;
	_signalPosX = 0, _signalPosY = 49;

	_dangerLevelSum = 0;
	_isDangerAniStart = false;
}

void UI_SignalVessel::UIOpen(Level obj)
{
	FrameTexture(_signalPosX, _signalPosY, LoadRes::_spUISignalVessel, 3, _color);
	if (_dangerLevelSum < obj.GetDangerLevelSum()) {
		_isDangerAniStart = true;
	}
	if (_isDangerAniStart == true) {
		FrameTexture(_signalPosX, _signalPosY, LoadRes::_spUISignalVessel, 4, _color);
		if (Timers(100, 1)) {
			FrameTexture(_signalPosX, _signalPosY, LoadRes::_spUISignalVessel, 3, _color);
		}
		if (Timers(300, 0)) {
			_isDangerAniStart = false;
		}
	}
	_dangerLevelSum = obj.GetDangerLevelSum();
	FrameTexture(_signalPosX, _signalPosY, LoadRes::_spUISignalVessel, 5, _color);
	FrameTexture(_bottomPosX, _bottomPosY, LoadRes::_spUISignalVessel, 0, _color);
	FrameTexture(_numberPosX, _numberPosY, LoadRes::_spUISignalVessel, 1, _color);
	if (_redPosX + (float)(_dangerLevelSum * 4.8f) <= 154) {
		FrameTexture(_redPosX + (float)(_dangerLevelSum * 4.8f), _redPosY, LoadRes::_spUISignalVessel, 2, _color);
	}
	else {
		FrameTexture(154, _redPosY, LoadRes::_spUISignalVessel, 2, _color);
	}
}

UI_StartScene::UI_StartScene()
{
	_isButton_Start = false, _isButton_Help = false;
	_isCheck_AutoShoot = false, _isCheck_EasyMode = false;
	_posX = 0, _posY = 0;
	_width = 450, _higth = 780;
	_color = WHITE;

	_titlePosX = 0, _titlePosY = 50;
	_buttonW = 210, _buttonH = 73;
	_buttonPosX_Start = 450.f / 2 - _buttonW / 2, _buttonPosY_Start = 450;
	_buttonPosX_Help = 450.f / 2 - _buttonW / 2, _buttonPosY_Help = 600;
	_buttonTextW_Start = 127;
	_buttonTextW_Help = 105;
	_helpPosX = 450.f / 2 - 437.f / 2, _helpPosY = 50;
}

void UI_StartScene::UIOpen()
{
	FrameTexture(0, 0, LoadRes::_spUIStartScene, 0, WHITE);
	FrameTexture(_titlePosX, _titlePosY, LoadRes::_spUIStartScene, 1, WHITE);
	FrameTexture(_buttonPosX_Start, _buttonPosY_Start, LoadRes::_spUIStartScene, 2, WHITE);
	FrameTexture(_buttonPosX_Help, _buttonPosY_Help, LoadRes::_spUIStartScene, 2, WHITE);
	int mouseX = 0, mouseY = 0;
	Novice::GetMousePosition(&mouseX, &mouseY);
	//Start界面
	if (!_isButton_Help) {
		if (mouseX >= _buttonPosX_Start && mouseX <= _buttonPosX_Start + _buttonW
			&& mouseY >= _buttonPosY_Start && mouseY <= _buttonPosY_Start + _buttonH) {
			FrameTexture(_buttonPosX_Start - 8, _buttonPosY_Start - 7, LoadRes::_spUIStartScene, 5, WHITE);
			//点击Start按钮触发效果
			if (Novice::IsTriggerMouse(0)) {
				_isButton_Start = true;
			}
		}
		if (mouseX >= _buttonPosX_Help && mouseX <= _buttonPosX_Help + _buttonW
			&& mouseY >= _buttonPosY_Help && mouseY <= _buttonPosY_Help + _buttonH) {
			FrameTexture(_buttonPosX_Help - 8, _buttonPosY_Help - 7, LoadRes::_spUIStartScene, 5, WHITE);
			//点击Help按钮触发效果
			if (Novice::IsTriggerMouse(0)) {
				_isButton_Help = true;
			}
		}
		FrameTexture(_buttonPosX_Start + _buttonW / 2 - _buttonTextW_Start / 2, _buttonPosY_Start - 15, LoadRes::_spUIStartScene, 3, WHITE);
		FrameTexture(_buttonPosX_Help + +_buttonW / 2 - _buttonTextW_Help / 2, _buttonPosY_Help - 15, LoadRes::_spUIStartScene, 4, WHITE);
	}
	//Help弹窗
	else {
		FrameTexture(_helpPosX, _helpPosY, LoadRes::_spUIHelp, WHITE);
		if (mouseX >= _helpPosX + 50 && mouseX <= _helpPosX + 50 + 50 && mouseY >= (int)_helpPosY + 550 && mouseY <= (int)_helpPosY + 550 + 50) {
			if (Novice::IsTriggerMouse(0)) {
				//点击Help界面中的AutoShoot选项
				if (!_isCheck_AutoShoot) {
					_isCheck_AutoShoot = true;
				}
				else {
					_isCheck_AutoShoot = false;
				}
			}
		}
		if (mouseX >= _helpPosX + 250 && mouseX <= _helpPosX + 250 + 50 && mouseY >= (int)_helpPosY + 550 && mouseY <= (int)_helpPosY + 550 + 50) {
			if (Novice::IsTriggerMouse(0)) {
				//点击Help界面中的EasyMode选项
				if (!_isCheck_EasyMode) {
					_isCheck_EasyMode = true;
				}
				else {
					_isCheck_EasyMode = false;
				}
			}
		}
		if (mouseX >= _helpPosX + 153 && mouseX <= _helpPosX + 153 + 133
			&& mouseY >= _helpPosY + 625 && mouseY <= _helpPosY + 625 + 55) {
			FrameTexture(_helpPosX + 153 - 5, _helpPosY + 625 - 5, LoadRes::_spUIGameOverScene, 7, WHITE);
			//点击Help界面中Back按钮触发效果
			if (Novice::IsTriggerMouse(0)) {
				_isButton_Help = false;
			}
		}
		//两个选项操控按钮(占位)
		if (!_isCheck_AutoShoot) {
			Novice::DrawBox((int)_helpPosX + 50, (int)_helpPosY + 550, 50, 50, 0, WHITE, kFillModeSolid);
		}
		else {
			Novice::DrawBox((int)_helpPosX + 50, (int)_helpPosY + 550, 50, 50, 0, RED, kFillModeSolid);
		}
		if (!_isCheck_EasyMode) {
			Novice::DrawBox((int)_helpPosX + 250, (int)_helpPosY + 550, 50, 50, 0, WHITE, kFillModeSolid);
		}
		else {
			Novice::DrawBox((int)_helpPosX + 250, (int)_helpPosY + 550, 50, 50, 0, RED, kFillModeSolid);
		}
	}
}

UI_GameOverScene::UI_GameOverScene()
{
	_isButton_Restart = false;
	_isButton_Back = false;
	_posX = 0, _posY = 0;
	_width = 450, _higth = 780;
	_color = WHITE;

	_titlePosX = 0, _titlePosY = 50;
	_buttonW = 133, _buttonH = 55;
	_scoreW = 129, _scoreH = 46;
	_scoreX = 450.f / 2 - _scoreW / 2, _scoreY = 350;
	_scoreNumX = _scoreX + (_scoreW / 2) - 15, _scoreNumY = _scoreY + 70;
	_scoreNumIntervalX = 34;
	_isScoreAniStart = false, _scoreAnimation = 0;
	_buttonPosX_Restart = 450.f / 2 + 50, _buttonPosY_Restart = 600;
	_buttonPosX_Back = 450.f / 2 - 50 - _buttonW, _buttonPosY_Back = 600;
	_buttonTextW_Restart = 105;
	_buttonTextW_Back = 67;
	_isMouseCheckStart = false;
}

void UI_GameOverScene::UIOpen(Player obj)
{
	FrameTexture(0, 0, LoadRes::_spUIGameOverScene, 0, WHITE);
	FrameTexture(_titlePosX, _titlePosY, LoadRes::_spUIGameOverScene, 1, WHITE);
	FrameTexture(_scoreX + 5, _scoreY, LoadRes::_spUIGameOverScene, 2, WHITE);
	FrameTexture(_buttonPosX_Restart, _buttonPosY_Restart, LoadRes::_spUIGameOverScene, 3, WHITE);
	FrameTexture(_buttonPosX_Back, _buttonPosY_Back, LoadRes::_spUIGameOverScene, 4, WHITE);
	int mouseX = 0, mouseY = 0;
	//延迟一段时间再获取鼠标位置，避免玩家快速按到Restart按钮
	if (Timers(1000, 2)) {
		_isMouseCheckStart = true;
	}
	if (_isMouseCheckStart) {
		Novice::GetMousePosition(&mouseX, &mouseY);
	}
	if (mouseX >= _buttonPosX_Restart && mouseX <= _buttonPosX_Restart + _buttonW
		&& mouseY >= _buttonPosY_Restart && mouseY <= _buttonPosY_Restart + _buttonH) {
		FrameTexture(_buttonPosX_Restart - 5, _buttonPosY_Restart - 6, LoadRes::_spUIGameOverScene, 7, WHITE);
		//点击Restart按钮触发效果
		if (Novice::IsTriggerMouse(0)) {
			_isButton_Restart = true;
			_isScoreAniStart = false;
		}
	}
	if (mouseX >= _buttonPosX_Back && mouseX <= _buttonPosX_Back + _buttonW
		&& mouseY >= _buttonPosY_Back && mouseY <= _buttonPosY_Back + _buttonH) {
		FrameTexture(_buttonPosX_Back - 5, _buttonPosY_Back - 6, LoadRes::_spUIGameOverScene, 7, WHITE);
		//点击Back按钮触发效果
		if (Novice::IsTriggerMouse(0)) {
			_isButton_Back = true;
			_isScoreAniStart = false;
		}
	}
	FrameTexture(_buttonPosX_Restart + _buttonW / 2 - _buttonTextW_Restart / 2, _buttonPosY_Restart + 4, LoadRes::_spUIGameOverScene, 5, WHITE);
	FrameTexture(_buttonPosX_Back + +_buttonW / 2 - _buttonTextW_Back / 2, _buttonPosY_Back + 4, LoadRes::_spUIGameOverScene, 6, WHITE);

	//分数显示部分
	int score = obj.GetScoreSum();
	unsigned int color = WHITE;
	if (!_isScoreAniStart) {
		_scoreAnimation = (int)(score * 0.7f);
		_isScoreAniStart = true;
	}
	if (_scoreAnimation >= 9999999) {
		_scoreAnimation = 9999999;
		color = RED;
	}
	else if (_scoreAnimation < score) {
		if (_scoreAnimation >= 1000000) {
			_scoreAnimation += 11111;
			color = RED;
		}
		else if (_scoreAnimation >= 100000) {
			_scoreAnimation += 1111;
			color = GREEN;
		}
		else if (_scoreAnimation >= 10000) {
			_scoreAnimation += 111;
			color = 0x29b6f6FF;
		}
		else if (_scoreAnimation >= 1000) {
			_scoreAnimation += 11;
			color = WHITE;
		}
		else if (_scoreAnimation >= 100) {
			_scoreAnimation += 11;
			color = WHITE;
		}
		else if (_scoreAnimation >= 10) {
			_scoreAnimation += 1;
			color = WHITE;
		}
	}
	else {
		_scoreAnimation = score;
	}
	int num1 = _scoreAnimation % 10;
	int num2 = (_scoreAnimation / 10) % 10;
	int num3 = (_scoreAnimation / 100) % 10;
	int num4 = (_scoreAnimation / 1000) % 10;
	int num5 = (_scoreAnimation / 10000) % 10;
	int num6 = (_scoreAnimation / 100000) % 10;
	int num7 = (_scoreAnimation / 1000000) % 10;
	if (score >= 9999999) {
		color = RED;
		_scoreNumX = _scoreX + (_scoreW / 2) - (_scoreNumIntervalX * 4) + (_scoreNumIntervalX / 2);
		FrameTexture(_scoreNumX, _scoreNumY, LoadRes::_spUINumber, num7, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 1, _scoreNumY, LoadRes::_spUINumber, num6, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 2, _scoreNumY, LoadRes::_spUINumber, num5, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 3, _scoreNumY, LoadRes::_spUINumber, num4, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 4, _scoreNumY, LoadRes::_spUINumber, num3, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 5, _scoreNumY, LoadRes::_spUINumber, num2, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 6, _scoreNumY, LoadRes::_spUINumber, num1, color);
	}
	else if (obj.GetScoreSum() >= 1000000) {
		color = RED;
		_scoreNumX = _scoreX + (_scoreW / 2) - (_scoreNumIntervalX * 4) + (_scoreNumIntervalX / 2);
		FrameTexture(_scoreNumX, _scoreNumY, LoadRes::_spUINumber, num7, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 1, _scoreNumY, LoadRes::_spUINumber, num6, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 2, _scoreNumY, LoadRes::_spUINumber, num5, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 3, _scoreNumY, LoadRes::_spUINumber, num4, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 4, _scoreNumY, LoadRes::_spUINumber, num3, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 5, _scoreNumY, LoadRes::_spUINumber, num2, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 6, _scoreNumY, LoadRes::_spUINumber, num1, color);
	}
	else if (obj.GetScoreSum() >= 100000) {
		color = GREEN;
		_scoreNumX = _scoreX + (_scoreW / 2) - (_scoreNumIntervalX * 3);
		FrameTexture(_scoreNumX, _scoreNumY, LoadRes::_spUINumber, num6, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 1, _scoreNumY, LoadRes::_spUINumber, num5, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 2, _scoreNumY, LoadRes::_spUINumber, num4, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 3, _scoreNumY, LoadRes::_spUINumber, num3, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 4, _scoreNumY, LoadRes::_spUINumber, num2, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 5, _scoreNumY, LoadRes::_spUINumber, num1, color);
	}
	else if (obj.GetScoreSum() >= 10000) {
		color = 0x29b6f6FF;
		_scoreNumX = _scoreX + (_scoreW / 2) - (_scoreNumIntervalX * 3) + (_scoreNumIntervalX / 2);
		FrameTexture(_scoreNumX, _scoreNumY, LoadRes::_spUINumber, num5, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 1, _scoreNumY, LoadRes::_spUINumber, num4, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 2, _scoreNumY, LoadRes::_spUINumber, num3, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 3, _scoreNumY, LoadRes::_spUINumber, num2, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 4, _scoreNumY, LoadRes::_spUINumber, num1, color);
	}
	else if (obj.GetScoreSum() >= 1000) {
		color = WHITE;
		_scoreNumX = _scoreX + (_scoreW / 2) - (_scoreNumIntervalX * 2);
		FrameTexture(_scoreNumX, _scoreNumY, LoadRes::_spUINumber, num4, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 1, _scoreNumY, LoadRes::_spUINumber, num3, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 2, _scoreNumY, LoadRes::_spUINumber, num2, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 3, _scoreNumY, LoadRes::_spUINumber, num1, color);
	}
	else if (obj.GetScoreSum() >= 100) {
		color = WHITE;
		_scoreNumX = _scoreX + (_scoreW / 2) - (_scoreNumIntervalX * 1) + (_scoreNumIntervalX / 2);
		FrameTexture(_scoreNumX, _scoreNumY, LoadRes::_spUINumber, num3, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 1, _scoreNumY, LoadRes::_spUINumber, num2, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 2, _scoreNumY, LoadRes::_spUINumber, num1, color);
	}
	else if (obj.GetScoreSum() >= 10) {
		color = WHITE;
		_scoreNumX = _scoreX + (_scoreW / 2) - (_scoreNumIntervalX * 1);
		FrameTexture(_scoreNumX, _scoreNumY, LoadRes::_spUINumber, num2, color);
		FrameTexture(_scoreNumX + _scoreNumIntervalX * 1, _scoreNumY, LoadRes::_spUINumber, num1, color);
	}
	else if (obj.GetScoreSum() == 0) {
		color = WHITE;
		_scoreNumX = _scoreX + (_scoreW / 2) - (_scoreNumIntervalX / 2);
		FrameTexture(_scoreNumX, _scoreNumY, LoadRes::_spUINumber, num1, color);
	}
}

UI_DanagerWarning::UI_DanagerWarning()
{
	_bottomPosX = 450.f / 2 - 224.f / 2, _bottomPosY = -125;
	_text1PosX = _bottomPosX + 112 - 190.f / 2 + 10, _text1PosY = _bottomPosY + 30;
	_text2PosX = _bottomPosX + 70, _text2PosY = _bottomPosY + 65;
	_levelPosX = _text2PosX + 80, _levelPosY = _text2PosY;
	_speed = 5;
}

void UI_DanagerWarning::UIOpen(Level obj)
{
	_text1PosY = _bottomPosY + 30;
	_text2PosY = _bottomPosY + 65;
	_levelPosY = _text2PosY;

	if (obj.GetDangerMarningAni()) {
		if (_bottomPosY < 70) {
			_bottomPosY += _speed;
		}
	}
	else {
		if (_bottomPosY > -125) {
			_bottomPosY -= _speed;
		}
	}
	FrameTexture(_bottomPosX, _bottomPosY, LoadRes::_spUIDanger, 0, WHITE);
	FrameTexture(_text1PosX, _text1PosY, LoadRes::_spUIDanger, 1, WHITE);
	FrameTexture(_text2PosX, _text2PosY, LoadRes::_spUIDanger, 2, WHITE);
	if (obj.GetDangerLevelSum() >= obj.GetDangerLevelMax3()) {
		FrameTexture(_levelPosX, _levelPosY, LoadRes::_spUIDanger, 5, WHITE);
	}
	else if (obj.GetDangerLevelSum() >= obj.GetDangerLevelMax2()) {
		FrameTexture(_levelPosX, _levelPosY, LoadRes::_spUIDanger, 4, WHITE);
	}
	else if (obj.GetDangerLevelSum() >= obj.GetDangerLevelMax1()) {
		FrameTexture(_levelPosX, _levelPosY, LoadRes::_spUIDanger, 3, WHITE);
	}
	else {
		FrameTexture(_levelPosX, _levelPosY, LoadRes::_spUIDanger, 6, WHITE);
	}
}
