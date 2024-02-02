#include "GameUI.h"

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

void GameUI::FrameAnimation(float x, float y, std::map<int, LoadRes::SpriteList> sprite, float angle, int frameTime, int index)
{
	if (Timers(frameTime, index)) {
		_frameIndex[index]++;
	}
	if (_frameIndex[index] > (int)sprite.size() - 1 || _frameIndex[index] < 0) {
		_frameIndex[index] = 0;
	}
	int arrSprite = sprite[_frameIndex[index]].sprite;
	int arrW = sprite[_frameIndex[index]].w, arrH = sprite[_frameIndex[index]].h;
	int arrX = sprite[_frameIndex[index]].x, arrY = sprite[_frameIndex[index]].y;
	int arrSpriteW = sprite[_frameIndex[index]].listW, arrSpriteH = sprite[_frameIndex[index]].listH;
	Novice::DrawSpriteRect((int)x, (int)y, arrX, arrY, arrW, arrH, arrSprite, ((float)arrW / (float)arrSpriteW), ((float)arrH / (float)arrSpriteH), angle, WHITE);
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
	int hpMultiplier = 1;
	if (obj.GetEasyMode()) {
		hpMultiplier = 2;//打开了Easy模式就把这个倍率换成2，这样血量UI也会按照2倍去展示
	}
	unsigned int hpBoxColor_ON = 0xd01716FF, hpBoxColor_OFF = 0x661111FF;
	unsigned int hpBoxColor1 = hpBoxColor_ON;
	unsigned int hpBoxColor2 = hpBoxColor_ON;
	unsigned int hpBoxColor3 = hpBoxColor_ON;
	unsigned int hpBoxColor4 = hpBoxColor_ON;
	unsigned int hpBoxColor5 = hpBoxColor_ON;
	unsigned int hpBoxColor6 = hpBoxColor_ON;
	if (obj.GetHp() <= 0) {
		hpBoxColor1 = hpBoxColor_OFF;
		hpBoxColor2 = hpBoxColor_OFF;
		hpBoxColor3 = hpBoxColor_OFF;
		hpBoxColor4 = hpBoxColor_OFF;
		hpBoxColor5 = hpBoxColor_OFF;
		hpBoxColor6 = hpBoxColor_OFF;
	}
	else if (obj.GetHp() <= 2 * hpMultiplier) {
		hpBoxColor2 = hpBoxColor_OFF;
		hpBoxColor3 = hpBoxColor_OFF;
		hpBoxColor4 = hpBoxColor_OFF;
		hpBoxColor5 = hpBoxColor_OFF;
		hpBoxColor6 = hpBoxColor_OFF;
	}
	else if (obj.GetHp() <= 4 * hpMultiplier) {
		hpBoxColor3 = hpBoxColor_OFF;
		hpBoxColor4 = hpBoxColor_OFF;
		hpBoxColor5 = hpBoxColor_OFF;
		hpBoxColor6 = hpBoxColor_OFF;
	}
	else if (obj.GetHp() <= 6 * hpMultiplier) {
		hpBoxColor4 = hpBoxColor_OFF;
		hpBoxColor5 = hpBoxColor_OFF;
		hpBoxColor6 = hpBoxColor_OFF;
	}
	else if (obj.GetHp() <= 8 * hpMultiplier) {
		hpBoxColor5 = hpBoxColor_OFF;
		hpBoxColor6 = hpBoxColor_OFF;
	}
	else if (obj.GetHp() <= 10 * hpMultiplier) {
		hpBoxColor6 = hpBoxColor_OFF;
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
	_posX = 0, _posY = 0;
	_width = 450, _higth = 780;
	_color = WHITE;

	_isButton_Start = false, _isButton_Help = false;
	_isCheck_AutoShoot = false, _isCheck_EasyMode = false;
	_button_HelpPage = 0;
	_isMessage_Mouse = false;

	//Start界面
	_titlePosX = 0, _titlePosY = 50;
	_buttonW = 210, _buttonH = 73;
	_buttonPosX_Start = 450.f / 2 - _buttonW / 2, _buttonPosY_Start = 450;
	_buttonPosX_Help = 450.f / 2 - _buttonW / 2, _buttonPosY_Help = 600;
	_buttonTextW_Start = 127;
	_buttonTextW_Help = 105;
	_checkBottomX_Auto = 48, _checkBottomY_Auto = 711;
	_checkX_Auto = 48, _checkY_Auto = 708;
	_textX_Auto = 84, _textY_Auto = 711;
	_checkBottomX_Easy = 271, _checkBottomY_Easy = 711;
	_checkX_Easy = 271, _checkY_Easy = 708;
	_textX_Easy = 310, _textY_Easy = 711;
	_checkBottomW = 29, _checkBottomH = 29;
	//Help弹窗
	_helpPosX = 450.f / 2 - 437.f / 2, _helpPosY = 20;
	_helpPosX_CheckAuto = 0, _helpPosY_CheckAuto = 0;
	_helpPosX_checkEasy = 0, _helpPosY_CheckEasy = 0;
	_helpPosX_BackButton = 450.f / 2 - 133 - 30, _helpPosY_BackButton = 670;
	_helpPosX_NextButton = 450.f / 2 + 30, _helpPosY_NextButton = 670;
	//鼠标提示信息
	_messageX_mouseStart = _buttonPosX_Start + _buttonW - 50, _messageY_mouseStart = _buttonPosY_Start + _buttonW - 50;
	_messageX_mouse = _messageX_mouseStart, _messageY_mouse = _messageX_mouseStart;
	_messageSpeed_mouse = 2;
	_isMessage_MouseStart = false;
}

void UI_StartScene::UIOpen()
{
	FrameTexture(0, 0, LoadRes::_spUIStartScene, 0, WHITE);
	FrameTexture(_titlePosX, _titlePosY, LoadRes::_spUIStartScene, 1, WHITE);
	FrameTexture(_buttonPosX_Start, _buttonPosY_Start, LoadRes::_spUIStartScene, 6, WHITE);
	FrameTexture(_buttonPosX_Help, _buttonPosY_Help, LoadRes::_spUIStartScene, 2, WHITE);
	int mouseX = 0, mouseY = 0;
	Novice::GetMousePosition(&mouseX, &mouseY);
	if (!_isButton_Help) {
		//Start界面
		if (mouseX >= _buttonPosX_Start && mouseX <= _buttonPosX_Start + _buttonW
			&& mouseY >= _buttonPosY_Start && mouseY <= _buttonPosY_Start + _buttonH) {
			FrameTexture(_buttonPosX_Start - 8, _buttonPosY_Start - 7, LoadRes::_spUIStartScene, 5, WHITE);
			//点击Start按钮触发效果
			if (Novice::IsTriggerMouse(0)) {
				_isButton_Start = true;
				Novice::PlayAudio(LoadRes::_adSelectClick, 0, 0.3f);
			}
		}
		if (mouseX >= _buttonPosX_Help && mouseX <= _buttonPosX_Help + _buttonW
			&& mouseY >= _buttonPosY_Help && mouseY <= _buttonPosY_Help + _buttonH) {
			FrameTexture(_buttonPosX_Help - 8, _buttonPosY_Help - 7, LoadRes::_spUIStartScene, 5, WHITE);
			//点击Help按钮触发效果
			if (Novice::IsTriggerMouse(0)) {
				_isButton_Help = true;
				_button_HelpPage = 0;//每次打开都从Help的第一页开始
				Novice::PlayAudio(LoadRes::_adSelectClick, 0, 0.3f);
			}
		}
		if (mouseX >= _checkBottomX_Auto && mouseX <= _checkBottomX_Auto + _checkBottomW
			&& mouseY >= _checkBottomY_Auto && mouseY <= _checkBottomY_Auto + _checkBottomH) {
			//点击AutoShooting选项
			if (Novice::IsTriggerMouse(0)) {
				Novice::PlayAudio(LoadRes::_adSelectClick, 0, 0.3f);
				if (!_isCheck_AutoShoot) {
					_isCheck_AutoShoot = true;
				}
				else {
					_isCheck_AutoShoot = false;
				}
			}
		}
		if (mouseX >= _checkBottomX_Easy && mouseX <= _checkBottomX_Easy + _checkBottomW
			&& mouseY >= _checkBottomY_Easy && mouseY <= _checkBottomY_Easy + _checkBottomH) {
			//点击EasyMode选项
			if (Novice::IsTriggerMouse(0)) {
				Novice::PlayAudio(LoadRes::_adSelectClick, 0, 0.3f);
				if (!_isCheck_EasyMode) {
					_isCheck_EasyMode = true;
				}
				else {
					_isCheck_EasyMode = false;
				}
			}
		}
		//鼠标提示判断(时间内不移动鼠标就会出现提示)
		if (!_isMessage_MouseStart) {
			_isMessage_MouseStart = true;
			_timeStart[4] = clock();//重置一下计时
		}
		if (Timers(6000, 4) && !_isMessage_Mouse && _isMessage_MouseStart) {
			_mousePosX_Back = mouseX;
			_mousePosY_Back = mouseY;
			_messageX_mouse = _messageX_mouseStart;
			_messageY_mouse = _messageY_mouseStart;
		}
		if (_mousePosX_Back == mouseX && _mousePosY_Back == mouseY) {
			_isMessage_Mouse = true;
		}
		else {
			_isMessage_Mouse = false;
		}
		//鼠标使用提示
		if (_isMessage_Mouse) {
			if (_messageY_mouse < _buttonPosY_Start + 50) {
				if (Timers(500, 3)) {
					_messageX_mouse = _messageX_mouseStart;
					_messageY_mouse = _messageY_mouseStart;
				}
			}
			else {
				_messageX_mouse -= _messageSpeed_mouse / 2;
				_messageY_mouse -= _messageSpeed_mouse;
			}
		}

		FrameTexture(_buttonPosX_Start + _buttonW / 2 - _buttonTextW_Start / 2, _buttonPosY_Start - 15, LoadRes::_spUIStartScene, 3, WHITE);
		FrameTexture(_buttonPosX_Help + +_buttonW / 2 - _buttonTextW_Help / 2, _buttonPosY_Help - 15, LoadRes::_spUIStartScene, 4, WHITE);
		FrameTexture(_checkBottomX_Auto, _checkBottomY_Auto, LoadRes::_spUIStartScene, 10, WHITE);
		FrameTexture(_textX_Auto, _textY_Auto, LoadRes::_spUIStartScene, 8, WHITE);
		FrameTexture(_checkBottomX_Easy, _checkBottomY_Easy, LoadRes::_spUIStartScene, 10, WHITE);
		FrameTexture(_textX_Easy, _textY_Easy, LoadRes::_spUIStartScene, 7, WHITE);
		if (mouseX >= _checkBottomX_Easy && mouseX <= _textX_Easy + LoadRes::_spUIStartScene[7].w && mouseY >= _checkBottomY_Easy && mouseY <= _textY_Easy + LoadRes::_spUIStartScene[7].h) {
			//展示Easy模式修改项信息
			FrameTexture(_checkBottomX_Easy, _textY_Easy - 90, LoadRes::_spUIHelpMessage, WHITE);
		}
		if (_isCheck_AutoShoot) {
			FrameTexture(_checkX_Auto, _checkY_Auto, LoadRes::_spUIStartScene, 9, WHITE);
		}
		if (_isCheck_EasyMode) {
			FrameTexture(_checkX_Easy, _checkY_Easy, LoadRes::_spUIStartScene, 9, WHITE);
		}
		if (_isMessage_Mouse) {
			FrameAnimation(_messageX_mouse, _messageY_mouse, LoadRes::_spAniMouse, 3.14159f / 180 * -30, 100, 0);
		}
	}
	else {
		//Help弹窗
		switch (_button_HelpPage) {
		case 0:
			FrameTexture(_helpPosX, _helpPosY, LoadRes::_spUIHelp, WHITE);
			break;
		case 1:
			FrameTexture(_helpPosX, _helpPosY, LoadRes::_spUIHelp2, WHITE);
			break;
		}
		FrameTexture(_helpPosX_BackButton, _helpPosY_BackButton, LoadRes::_spUIGameOverScene, 4, WHITE);
		FrameTexture(_helpPosX_BackButton + 133.f / 2 - 67.f / 2, _helpPosY_BackButton + 5, LoadRes::_spUIGameOverScene, 6, WHITE);
		if (mouseX >= _helpPosX_BackButton && mouseX <= _helpPosX_BackButton + 133
			&& mouseY >= _helpPosY_BackButton && mouseY <= _helpPosY_BackButton + 55) {
			FrameTexture(_helpPosX_BackButton - 5, _helpPosY_BackButton - 5, LoadRes::_spUIGameOverScene, 7, WHITE);
			//点击Help界面中Back按钮触发效果
			if (Novice::IsTriggerMouse(0)) {
				_isButton_Help = false;
				Novice::PlayAudio(LoadRes::_adSelectClick, 0, 0.3f);
			}
		}
		if (_isButton_Help) {
			switch (_button_HelpPage) {
			case 0: {
				//Help界面在第一页
				FrameTexture(_helpPosX_NextButton, _helpPosY_NextButton, LoadRes::_spUIGameOverScene, 3, WHITE);
				FrameTexture(_helpPosX_NextButton + 133.f / 2 - 91.f / 2, _helpPosY_NextButton + 2, LoadRes::_spUIHelpText1, WHITE);
				if (mouseX >= _helpPosX_NextButton && mouseX <= _helpPosX_NextButton + 133
					&& mouseY >= _helpPosY_NextButton && mouseY <= _helpPosY_NextButton + 55) {
					FrameTexture(_helpPosX_NextButton - 5, _helpPosY_NextButton - 5, LoadRes::_spUIGameOverScene, 7, WHITE);
					//点击Help界面中Next按钮触发效果
					if (Novice::IsTriggerMouse(0)) {
						_button_HelpPage = 1;
						Novice::PlayAudio(LoadRes::_adSelectClick, 0, 0.3f);
					}
				}
				break;
			}
			case 1: {
				//Help界面在第二页
				FrameTexture(_helpPosX_NextButton, _helpPosY_NextButton, LoadRes::_spUIGameOverScene, 3, WHITE);
				FrameTexture(_helpPosX_NextButton + 133.f / 2 - 91.f / 2, _helpPosY_NextButton + 2, LoadRes::_spUIHelpText2, WHITE);
				if (mouseX >= _helpPosX_NextButton && mouseX <= _helpPosX_NextButton + 133
					&& mouseY >= _helpPosY_NextButton && mouseY <= _helpPosY_NextButton + 55) {
					FrameTexture(_helpPosX_NextButton - 5, _helpPosY_NextButton - 5, LoadRes::_spUIGameOverScene, 7, WHITE);
					//点击Help界面中Previous按钮触发效果
					if (Novice::IsTriggerMouse(0)) {
						_button_HelpPage = 0;
						Novice::PlayAudio(LoadRes::_adSelectClick, 0, 0.3f);
					}
				}
				break;
			}
			}
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

	_scoreUpLoopHandle = -1;
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
			Novice::PlayAudio(LoadRes::_adSelectClick, 0, 0.3f);
		}
	}
	if (mouseX >= _buttonPosX_Back && mouseX <= _buttonPosX_Back + _buttonW
		&& mouseY >= _buttonPosY_Back && mouseY <= _buttonPosY_Back + _buttonH) {
		FrameTexture(_buttonPosX_Back - 5, _buttonPosY_Back - 6, LoadRes::_spUIGameOverScene, 7, WHITE);
		//点击Back按钮触发效果
		if (Novice::IsTriggerMouse(0)) {
			_isButton_Back = true;
			_isScoreAniStart = false;
			Novice::PlayAudio(LoadRes::_adSelectClick, 0, 0.3f);
		}
	}
	FrameTexture(_buttonPosX_Restart + _buttonW / 2 - _buttonTextW_Restart / 2, _buttonPosY_Restart + 4, LoadRes::_spUIGameOverScene, 5, WHITE);
	FrameTexture(_buttonPosX_Back + _buttonW / 2 - _buttonTextW_Back / 2, _buttonPosY_Back + 4, LoadRes::_spUIGameOverScene, 6, WHITE);

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
		if (!Novice::IsPlayingAudio(_scoreUpLoopHandle) || _scoreUpLoopHandle == -1) {
			_scoreUpLoopHandle = Novice::PlayAudio(LoadRes::_adScoreUp, 0, 0.7f);
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
