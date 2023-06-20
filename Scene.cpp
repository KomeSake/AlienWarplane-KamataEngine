#include "Scene.h"

Scene::SceneName Scene::_sceneIndex = Scene::Start;
Scene::Scene()
{
	_sceneIndex = Start;

	Game_BGObj = new UI_BackGround;
	Game_CaptureVesselObj = new UI_CaptureVessel;
	Game_HpVesselObj = new UI_HpVessel;
	Game_SignalVesselObj = new UI_SignalVessel;
	Game_DanagerMarningObj = new UI_DanagerWarning;

	Start_Obj = new UI_StartScene;
	_isCheck_AutoShoot = false, _isCheck_EasyMode = false;
	GameOver_Obj = new UI_GameOverScene;
}

void Scene::ScreenGameDown()
{
	Game_BGObj->BgMove();
}

void Scene::ScreenGameUp(Player obj, Level obj2)
{
	//捕获能量UI
	Game_CaptureVesselObj->UIOpen(obj);
	//生命值UI
	Game_HpVesselObj->UIOpen(obj);
	//危险度UI
	Game_SignalVesselObj->UIOpen(obj2);
	//危险波次警告
	Game_DanagerMarningObj->UIOpen(obj2);

	//检测玩家状态
	if (obj.GetHp() <= 0) {
		GameOver_Obj->_isMouseCheckStart = false;
		_sceneIndex = GameOver;
	}
}

void Scene::SceneStart()
{
	Start_Obj->UIOpen();
	_isCheck_AutoShoot = Start_Obj->_isCheck_AutoShoot;
	_isCheck_EasyMode = Start_Obj->_isCheck_EasyMode;
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

bool Scene::GetIsCheckAuto()
{
	return _isCheck_AutoShoot;
}

bool Scene::GetIsCheckEasyMode()
{
	return _isCheck_EasyMode;
}
