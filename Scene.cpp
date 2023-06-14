#include "Scene.h"

Scene::SceneName Scene::_sceneIndex = Scene::Start;
Scene::Scene()
{
	_sceneIndex = Start;

	Game_BGObj = new UI_BackGround;
	Game_CaptureVesselObj = new UI_CaptureVessel;
	Game_HpVesselObj = new UI_HpVessel;

	Start_Obj = new UI_StartScene;
	GameOver_Obj = new UI_GameOverScene;
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
	if (Start_Obj->_isButton_Start) {
		_sceneIndex = Game;
	}
}

void Scene::GameOverStart()
{
	GameOver_Obj->UIOpen();
}