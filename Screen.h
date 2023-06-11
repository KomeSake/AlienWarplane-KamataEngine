#pragma once
#include <Novice.h>
#include "LoadRes.h"
#include "GameUI.h"
#include "Player.h"
class Screen
{
	//这个类的作用是控制每个场景中出现的UI
	//所以它会在内部创建UI对象，到时候调用这个对象即可
public:
	Screen();
	void ScreenGameDown();
	void ScreenGameUp();
private:
	UI_BackGround* Game_BGObj;
	UI_CaptureVessel* Game_CaptureVesselObj;
	UI_HpVessel* Game_HpVesselObj;
};