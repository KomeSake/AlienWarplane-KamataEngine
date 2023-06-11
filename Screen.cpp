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

void Screen::ScreenGameUp()
{
	Game_CaptureVesselObj->FrameAnimation(Game_CaptureVesselObj->_posX, Game_CaptureVesselObj->_posY, LoadRes::_spUICaptureVessel_01, Game_CaptureVesselObj->_color);
	Game_HpVesselObj->FrameAnimation(Game_HpVesselObj->_posX, Game_HpVesselObj->_posY, LoadRes::_spUIHpVessel_01, Game_HpVesselObj->_color);
}
