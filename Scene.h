#pragma once
#include <Novice.h>
#include "LoadRes.h"
#include "GameUI.h"
#include "Player.h"
#include "Level.h"
class Scene
{
	//这个类的作用是控制每个场景中出现的UI
	//所以它会在内部创建UI对象，到时候调用这个对象即可
public:
	static enum SceneName
	{
		Loading,	//这个会重置游戏，所以开始新游戏的时候请载入这个
		Start,
		Game,
		GameOver,
	}_sceneIndex;

	Scene();
	void ScreenGameDown();
	void ScreenGameUp(Player obj, Level obj2);

	void SceneStart();
	void GameOverStart(Player obj);
private:
	UI_BackGround* Game_BGObj;
	UI_CaptureVessel* Game_CaptureVesselObj;
	UI_HpVessel* Game_HpVesselObj;
	UI_SignalVessel* Game_SignalVesselObj;

	UI_StartScene* Start_Obj;
	UI_GameOverScene* GameOver_Obj;
};