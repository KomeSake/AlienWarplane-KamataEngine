#pragma warning(disable: 28251)//无视了主函数WinMain出现的警告
//未解决问题：
//子弹会突然加速
#include <Novice.h>
#include "LoadRes.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Level.h"
#include "Scene.h"
#include "DataMessage.h"

#include <Windows.h>
#include <string>

const char kWindowTitle[] = "LC1C_15_ソウ_チョウキ_v20230413";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 450, 780);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//自己的变量
	LoadRes::LoadResNovice();
	Player* PlayerObj = new Player;
	Level* LevelObj = nullptr;

	Scene SceneObj;
	DataMessage DataMessageObj;


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		switch (SceneObj._sceneIndex) {
		case Scene::Loading:
			delete PlayerObj;
			delete LevelObj;
			BulletManager::_bulletUpdateVector.clear();			//本来还是想用对象池的回收方法的
			BulletManager::_bulletUpdateVector_enemy.clear();	//但是不知道为什么不管用，所以只可以直接清空了
			EnemyManager::_enemyUpdateVector.clear();
			PlayerObj = new Player;
			LevelObj = new Level;
			DataMessageObj.Initial(PlayerObj);
			Scene::_sceneIndex = Scene::Game;
			break;
		case Scene::Game:
			//游戏开始
			SceneObj.ScreenGameDown();

			PlayerObj->DamageCheck();
			PlayerObj->Move(keys);
			PlayerObj->Attack(keys);
			PlayerObj->CaptureEnemy();

			BulletManager::BulletUpdata();
			EnemyManager::EnemyUpdata();

			LevelObj->LevelDirector();
			DataMessageObj.MessageCheck();

			PlayerObj->FrameTexture(PlayerObj->GetPosX(), PlayerObj->GetPosY(), LoadRes::_spPlayer, PlayerObj->GetColor());
			PlayerObj->AniPlayerUP();
			SceneObj.ScreenGameUp(*PlayerObj);
			Novice::ScreenPrintf(296, 758, "1868315");//直接用显示数字的函数好想也可以替代分数
			break;
		case Scene::Start:
			//开始界面
			SceneObj.ScreenGameDown();
			SceneObj.SceneStart();
			break;
		case Scene::GameOver:
			//结束界面
			SceneObj.ScreenGameDown();
			PlayerObj->DamageCheck();
			char temp = 0;//为了剥夺玩家的控制，随便创建一个空的输入key
			PlayerObj->Move(&temp);
			PlayerObj->CaptureEnemy();
			BulletManager::BulletUpdata();
			EnemyManager::EnemyUpdata();
			LevelObj->LevelDirector();
			DataMessageObj.MessageCheck();
			PlayerObj->FrameTexture(PlayerObj->GetPosX(), PlayerObj->GetPosY(), LoadRes::_spPlayer, PlayerObj->GetColor());
			PlayerObj->AniPlayerUP();
			//SceneObj.ScreenGameUp(*PlayerObj);//看看到时候要不要做一个GameUI下降
			//以上都是游戏界面中有的，充当结束界面的背景图，不显得那么单调
			SceneObj.GameOverStart();
			break;
		}

		//std::string output = "X: " + std::to_string(PlayerObj.GetPosX()) + ",Y: " + std::to_string(PlayerObj.GetPosY()) + "\n";
		//OutputDebugStringA(output.c_str());

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
