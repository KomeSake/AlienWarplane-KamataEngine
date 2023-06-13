#include "Scene.h"

Scene::Scene()
{
	Game_BGObj = new UI_BackGround;
	Game_CaptureVesselObj = new UI_CaptureVessel;
	Game_HpVesselObj = new UI_HpVessel;

	Start_Obj = new UI_StartScene;
}

void Scene::ScreenGameDown()
{
	Game_BGObj->BgMove();
}

void Scene::ScreenGameUp(Player obj)
{
	//捕获能量UI
	Game_CaptureVesselObj->UIOpen(obj);


	//生命值UI
	Game_HpVesselObj->UIOpen(obj);
}

void Scene::SceneStart()
{
	Start_Obj->UIOpen();
}
