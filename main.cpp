#pragma warning(disable: 28251)//无视了主函数WinMain出现的警告
//未解决问题：
//子弹会突然加速
//因为敌人死亡后不是立马回收，而是会在它基础上播放一个爆炸动画，所以如果吸收敌人的时候，鼠标也在自己身上，就会短暂的触发合体状态(以后爆炸特效什么的还是应该另外触发)
#include <Novice.h>
#include "Script/LoadRes.h"
#include "Script/Player.h"
#include "Script/Enemy.h"
#include "Script/Bullet.h"
#include "Script/Level.h"
#include "Script/Scene.h"
#include "Script/DataMessage.h"

const char kWindowTitle[] = "AlienWarplane（異次元戦機）";

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
	Level* LevelObj = new Level;

	Scene SceneObj;
	DataMessage DataMessageObj;

	int bgmLoopHandle = 0;//为了循环的Bgm弄的


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
			BulletManager::_bulletUpdateVector_enemy.clear();	//但是不知道为什么不管用，只可以直接清空了
			EnemyManager::_enemyUpdateVector.clear();			//一共3个别忘了
			PlayerObj = new Player;
			LevelObj = new Level;
			PlayerObj->SetAutoShoot(SceneObj.GetIsCheckAuto());
			PlayerObj->SetEasyMode(SceneObj.GetIsCheckEasyMode());
			PlayerObj->EasyModeValue();
			DataMessageObj.Initial(PlayerObj, LevelObj);
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

			PlayerObj->FrameTexture(PlayerObj->GetPosX(), PlayerObj->GetPosY(), PlayerObj->GetSprite(), PlayerObj->GetColor());
			PlayerObj->AniPlayerUP();
			SceneObj.ScreenGameUp(*PlayerObj, *LevelObj);

			if (!Novice::IsPlayingAudio(bgmLoopHandle) || bgmLoopHandle == -1) {
				bgmLoopHandle = Novice::PlayAudio(LoadRes::_adBgm, 0, 0.05f);
			}
			break;
		case Scene::Start:
			//开始界面
			SceneObj.ScreenGameDown();
			SceneObj.SceneStart();

			Novice::StopAudio(bgmLoopHandle);
			break;
		case Scene::GameOver:
			//结束界面
			SceneObj.ScreenGameDown();
			PlayerObj->DamageCheck();
			char tempKeys = 0;//为了剥夺玩家的飞机控制，随便创建一个空的输入key
			PlayerObj->Move(&tempKeys);
			PlayerObj->CaptureEnemy();
			BulletManager::BulletUpdata();
			EnemyManager::EnemyUpdata();
			LevelObj->LevelDirector();
			DataMessageObj.MessageCheck();
			PlayerObj->FrameTexture(PlayerObj->GetPosX(), PlayerObj->GetPosY(), PlayerObj->GetSprite(), PlayerObj->GetColor());
			PlayerObj->AniPlayerUP();
			//SceneObj.ScreenGameUp(*PlayerObj);//看看到时候要不要做一个GameUI下降
			//以上都是游戏界面中有的，充当结束界面的背景图，不显得那么单调
			SceneObj.GameOverStart(*PlayerObj);
			break;
		}

		//鼠标样式
		Novice::SetMouseCursorVisibility(0);
		int mouseX = 0, mouseY = 0;
		Novice::GetMousePosition(&mouseX, &mouseY);
		Novice::DrawSprite(mouseX - 42 / 2, mouseY - 42 / 2, LoadRes::_spArrow, 1, 1, 0, WHITE);

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
