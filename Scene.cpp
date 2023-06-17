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

	//检测玩家状态
	if (obj.GetHp() <= 0) {
		_sceneIndex = GameOver;
	}
}

void Scene::SceneStart()
{
	Start_Obj->UIOpen();
	if (Start_Obj->_isButton_Start) {
		_sceneIndex = Loading;
		Start_Obj->_isButton_Start = false;
	}
}

void Scene::GameOverStart(Player obj)
{
	GameOver_Obj->UIOpen(obj);
	if (GameOver_Obj->_isButton_Restart) {
		_sceneIndex = Loading;
		GameOver_Obj->_isButton_Restart = false;
	}
	else if (GameOver_Obj->_isButton_Back) {
		_sceneIndex = Start;
		GameOver_Obj->_isButton_Back = false;
	}
}