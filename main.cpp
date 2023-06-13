#pragma warning(disable: 28251)//无视了主函数WinMain出现的警告
#include <Novice.h>
#include "LoadRes.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Level.h"
#include "Screen.h"
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
	Player PlayerObj;
	Level LevelObj;

	Screen ScreenObj;
	DataMessage DataMessageObj(PlayerObj);


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

		ScreenObj.ScreenGameDown();

		PlayerObj.DamageCheck();
		PlayerObj.Move(keys);
		PlayerObj.Attack(keys);
		PlayerObj.CaptureEnemy();

		BulletManager::BulletUpdata();
		EnemyManager::EnemyUpdata();

		LevelObj.LevelDirector();
		DataMessageObj.MessageCheck();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		PlayerObj.FrameAnimation(PlayerObj.GetPosX(), PlayerObj.GetPosY(), LoadRes::_spPlayer, PlayerObj.GetColor());
		PlayerObj.AniPlayerUP();
		ScreenObj.ScreenGameUp(PlayerObj);


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
