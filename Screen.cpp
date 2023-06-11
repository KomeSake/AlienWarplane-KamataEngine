#include "Screen.h"

Screen::Screen()
{
	Game_BGObj = new UI_BackGround;
	Game_CaptureVesselObj = new UI_CaptureVessel;
	Game_HpVesselObj = new UI_HpVessel;
}

void Screen::ScreenGameDown()
{
	Game_BGObj->BgMove();
}

void Screen::ScreenGameUp(Player obj)
{
	//捕获能量UI
	Game_CaptureVesselObj->UIStart(obj);


	//生命值UI
	Game_HpVesselObj->UIStart(obj);
}
