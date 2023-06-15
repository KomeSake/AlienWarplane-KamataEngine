#include "LoadRes.h"

LoadRes::SpriteList LoadRes::_spriteList;

int LoadRes::_spPlayer = 0;
int LoadRes::_spPlayerTentacles = 0;
int LoadRes::_spEnemy = 0;
int LoadRes::_spEnemy2 = 0;
int LoadRes::_spEnemy3 = 0;
int LoadRes::_spBullet_player = 0;
int LoadRes::_spBullet_enemy = 0;
int LoadRes::_spBullet_enemy2 = 0;
int LoadRes::_spBullet_enemy3 = 0;
int LoadRes::_spBullet_enemyCapture = 0;
int LoadRes::_spBullet_enemy2Capture = 0;
int LoadRes::_spBullet_enemy3Capture = 0;

std::map<int, LoadRes::SpriteList> LoadRes::_spAniExplode;
std::map<int, LoadRes::SpriteList> LoadRes::_spAniPlayerTentacles;
std::map<int, LoadRes::SpriteList> LoadRes::_spAniPlayerFire;
std::map<int, LoadRes::SpriteList> LoadRes::_spAniEnemyFire;
std::map<int, LoadRes::SpriteList> LoadRes::_spAniPlayerHpPlus;

int LoadRes::_spUIBg = 0;
std::map<int, LoadRes::SpriteList> LoadRes::_spUICaptureVessel;
int LoadRes::_spUICaptureVessel_05 = 0;
std::map<int, int> LoadRes::_spUIHpVessel;
std::map<int, int> LoadRes::_spUIStartScene;
std::map<int, int> LoadRes::_spUIGameOverScene;

void LoadRes::LoadResNovice()
{
	//Sprite贴图
	_spPlayer = Novice::LoadTexture("./Resources/Textures/Player0-0.png");
	_spPlayerTentacles = Novice::LoadTexture("./Resources/Textures/PlayerTentacles.png");

	_spEnemy = Novice::LoadTexture("./Resources/Textures/Enemy.png");
	_spEnemy2 = Novice::LoadTexture("./Resources/Textures/Enemy2.png");
	_spEnemy3 = Novice::LoadTexture("./Resources/Textures/Enemy3.png");

	_spBullet_player = Novice::LoadTexture("./Resources/Textures/Bullet.png");
	_spBullet_enemy = Novice::LoadTexture("./Resources/Textures/Bullet_Enemy.png");
	_spBullet_enemyCapture = Novice::LoadTexture("./Resources/Textures/Bullet_Enemy(Captured).png");
	_spBullet_enemy2 = Novice::LoadTexture("./Resources/Textures/Bullet_Enemy2.png");
	_spBullet_enemy2Capture = Novice::LoadTexture("./Resources/Textures/Bullet_Enemy2(Captured).png");
	_spBullet_enemy3 = Novice::LoadTexture("./Resources/Textures/Bullet_Enemy3.png");
	_spBullet_enemy3Capture = Novice::LoadTexture("./Resources/Textures/Bullet_Enemy3(Captured).png");

	//动画
	for (int i = 0; i < 10; i++) {
		int sprite = Novice::LoadTexture("./Resources/Textures/Animation/Ani_Explode.png");
		int w = 64, h = 64;
		int x = i * w, y = 0;
		int listW = 640, listH = 64;
		_spAniExplode[i] = { sprite,x,y,w,h,listW,listH };
	}

	for (int i = 0; i < 4; i++) {
		int sprite = Novice::LoadTexture("./Resources/Textures/Animation/Ani_Player_Tentacles.png");
		int w = 64, h = 64;
		int x = i * w, y = 0;
		int listW = 256, listH = 64;
		_spAniPlayerTentacles[i] = { sprite,x,y,w,h,listW,listH };
	}

	for (int i = 0; i < 6; i++) {
		int sprite = Novice::LoadTexture("./Resources/Textures/Animation/Ani_Player_Fire.png");
		int w = 32, h = 32;
		int x = i * w, y = 0;
		int listW = 192, listH = 32;
		_spAniPlayerFire[i] = { sprite,x,y,w,h,listW,listH };
	}

	for (int i = 0; i < 6; i++) {
		int sprite = Novice::LoadTexture("./Resources/Textures/Animation/Ani_Enemy_Fire.png");
		int w = 32, h = 32;
		int x = i * w, y = 0;
		int listW = 192, listH = 32;
		_spAniEnemyFire[i] = { sprite,x,y,w,h,listW,listH };
	}

	for (int i = 0; i < 9; i++) {
		int sprite = Novice::LoadTexture("./Resources/Textures/Animation/Ani_Player_hpPlus.png");
		int w = 64, h = 64;
		int x = i * w, y = 0;
		int listW = 640, listH = 64;
		_spAniPlayerHpPlus[i] = { sprite,x,y,w,h,listW,listH };
	}

	//UI
	_spUIBg = Novice::LoadTexture("./Resources/Textures/BG.png");

	for (int i = 0; i < 6; i++) {
		int sprite = Novice::LoadTexture("./Resources/Textures/UI/CaptureVessel.png");
		int w = 120, h = 135;
		int x = i * w, y = 0;
		int listW = 720, listH = 135;
		_spUICaptureVessel[i] = { sprite,x,y,w,h,listW,listH };
	}
	_spUICaptureVessel_05 = Novice::LoadTexture("./Resources/Textures/UI/CaptureVessel_05.png");

	_spUIHpVessel[0] = Novice::LoadTexture("./Resources/Textures/UI/HpVessel_00.png");

	_spUIStartScene[0] = Novice::LoadTexture("./Resources/Textures/UI/StartScene/0.png");
	_spUIStartScene[1] = Novice::LoadTexture("./Resources/Textures/UI/StartScene/1.png");
	_spUIStartScene[2] = Novice::LoadTexture("./Resources/Textures/UI/StartScene/2.png");
	_spUIStartScene[3] = Novice::LoadTexture("./Resources/Textures/UI/StartScene/3.png");
	_spUIStartScene[4] = Novice::LoadTexture("./Resources/Textures/UI/StartScene/4.png");
	_spUIStartScene[5] = Novice::LoadTexture("./Resources/Textures/UI/StartScene/5.png");

	_spUIGameOverScene[0] = Novice::LoadTexture("./Resources/Textures/UI/GameOverScene/0.png");
	_spUIGameOverScene[1] = Novice::LoadTexture("./Resources/Textures/UI/GameOverScene/1.png");
	_spUIGameOverScene[2] = Novice::LoadTexture("./Resources/Textures/UI/GameOverScene/2.png");
	_spUIGameOverScene[3] = Novice::LoadTexture("./Resources/Textures/UI/GameOverScene/3.png");
	_spUIGameOverScene[4] = Novice::LoadTexture("./Resources/Textures/UI/GameOverScene/4.png");
	_spUIGameOverScene[5] = Novice::LoadTexture("./Resources/Textures/UI/GameOverScene/5.png");
	_spUIGameOverScene[6] = Novice::LoadTexture("./Resources/Textures/UI/GameOverScene/6.png");
	_spUIGameOverScene[7] = Novice::LoadTexture("./Resources/Textures/UI/GameOverScene/7.png");
}
