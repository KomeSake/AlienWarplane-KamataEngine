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
std::map<int, LoadRes::SpriteList> LoadRes::_spUISignalVessel;
std::map<int, LoadRes::SpriteList> LoadRes::_spUIStartScene;
std::map<int, LoadRes::SpriteList> LoadRes::_spUIGameOverScene;
std::map<int, LoadRes::SpriteList> LoadRes::_spUINumber;
int LoadRes::_spUIHelp = 0;
std::map<int, LoadRes::SpriteList> LoadRes::_spUIDanger;

void LoadRes::LoadResNovice()
{
	int sprite = 0;
	int listW = 0, listH = 0;
	int w = 0, h = 0, x = 0, y = 0;

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
		sprite = Novice::LoadTexture("./Resources/Textures/Animation/Ani_Explode.png");
		w = 64, h = 64;
		x = i * w, y = 0;
		listW = 640, listH = 64;
		_spAniExplode[i] = { sprite,x,y,w,h,listW,listH };
	}

	for (int i = 0; i < 4; i++) {
		sprite = Novice::LoadTexture("./Resources/Textures/Animation/Ani_Player_Tentacles.png");
		w = 64, h = 64;
		x = i * w, y = 0;
		listW = 256, listH = 64;
		_spAniPlayerTentacles[i] = { sprite,x,y,w,h,listW,listH };
	}

	for (int i = 0; i < 6; i++) {
		sprite = Novice::LoadTexture("./Resources/Textures/Animation/Ani_Player_Fire.png");
		w = 32, h = 32;
		x = i * w, y = 0;
		listW = 192, listH = 32;
		_spAniPlayerFire[i] = { sprite,x,y,w,h,listW,listH };
	}

	for (int i = 0; i < 6; i++) {
		sprite = Novice::LoadTexture("./Resources/Textures/Animation/Ani_Enemy_Fire.png");
		w = 32, h = 32;
		x = i * w, y = 0;
		listW = 192, listH = 32;
		_spAniEnemyFire[i] = { sprite,x,y,w,h,listW,listH };
	}

	for (int i = 0; i < 9; i++) {
		sprite = Novice::LoadTexture("./Resources/Textures/Animation/Ani_Player_hpPlus.png");
		w = 64, h = 64;
		x = i * w, y = 0;
		listW = 640, listH = 64;
		_spAniPlayerHpPlus[i] = { sprite,x,y,w,h,listW,listH };
	}

	//UI
	_spUIBg = Novice::LoadTexture("./Resources/Textures/BG.png");

	for (int i = 0; i < 6; i++) {
		sprite = Novice::LoadTexture("./Resources/Textures/UI/CaptureVessel.png");
		w = 120, h = 135;
		x = i * w, y = 0;
		listW = 720, listH = 135;
		_spUICaptureVessel[i] = { sprite,x,y,w,h,listW,listH };
	}
	_spUICaptureVessel_05 = Novice::LoadTexture("./Resources/Textures/UI/CaptureVessel_05.png");

	_spUIHpVessel[0] = Novice::LoadTexture("./Resources/Textures/UI/HpVessel_00.png");
	_spUIHpVessel[1] = Novice::LoadTexture("./Resources/Textures/UI/HpVessel_01.png");

	sprite = Novice::LoadTexture("./Resources/Textures/UI/SignalVessel/List.png");
	listW = 359, listH = 70;
	w = 187, h = 51, x = 0, y = 0;
	_spUISignalVessel[0] = { sprite,x,y,w,h,listW,listH };
	w = 172, h = 24, x = 187, y = 0;
	_spUISignalVessel[1] = { sprite,x,y,w,h,listW,listH };
	w = 24, h = 19, x = 187 + 46 + 46 + 39, y = 24;
	_spUISignalVessel[2] = { sprite,x,y,w,h,listW,listH };
	w = 46, h = 46, x = 187, y = 24;
	_spUISignalVessel[3] = { sprite,x,y,w,h,listW,listH };
	w = 46, h = 46, x = 187 + 46, y = 24;
	_spUISignalVessel[4] = { sprite,x,y,w,h,listW,listH };
	w = 39, h = 40, x = 187 + 46 + 46, y = 24;
	_spUISignalVessel[5] = { sprite,x,y,w,h,listW,listH };


	sprite = Novice::LoadTexture("./Resources/Textures/UI/StartScene/List.png");
	listW = 900, listH = 780;
	w = 450, h = 780, x = 0, y = 0;
	_spUIStartScene[0] = { sprite,x,y,w,h,listW,listH };
	w = 450, h = 334, x = 450, y = 0;
	_spUIStartScene[1] = { sprite,x,y,w,h,listW,listH };
	w = 210, h = 73, x = 450 + 225, y = 334;
	_spUIStartScene[2] = { sprite,x,y,w,h,listW,listH };
	w = 127, h = 57, x = 450, y = 334 + 81;
	_spUIStartScene[3] = { sprite,x,y,w,h,listW,listH };
	w = 105, h = 70, x = 450 + 225, y = 334 + 73;
	_spUIStartScene[4] = { sprite,x,y,w,h,listW,listH };
	w = 225, h = 81, x = 450, y = 334;
	_spUIStartScene[5] = { sprite,x,y,w,h,listW,listH };

	sprite = Novice::LoadTexture("./Resources/Textures/UI/GameOverScene/List.png");
	listW = 900, listH = 780;
	w = 450, h = 780, x = 0, y = 0;
	_spUIGameOverScene[0] = { sprite,x,y,w,h,listW,listH };
	w = 450, h = 222, x = 450, y = 0;
	_spUIGameOverScene[1] = { sprite,x,y,w,h,listW,listH };
	w = 129, h = 46, x = 450 + 142, y = 222 + 55;
	_spUIGameOverScene[2] = { sprite,x,y,w,h,listW,listH };
	w = 133, h = 55, x = 450 + 142, y = 222;
	_spUIGameOverScene[3] = { sprite,x,y,w,h,listW,listH };
	w = 133, h = 55, x = 450 + 142 + 133, y = 222;
	_spUIGameOverScene[4] = { sprite,x,y,w,h,listW,listH };
	w = 105, h = 37, x = 450 + 142 + 129, y = 222 + 55;
	_spUIGameOverScene[5] = { sprite,x,y,w,h,listW,listH };
	w = 67, h = 37, x = 450 + 142 + 129 + 105, y = 222 + 55;
	_spUIGameOverScene[6] = { sprite,x,y,w,h,listW,listH };
	w = 142, h = 61, x = 450, y = 222;
	_spUIGameOverScene[7] = { sprite,x,y,w,h,listW,listH };

	for (int i = 0; i < 10; i++) {
		sprite = Novice::LoadTexture("./Resources/Textures/UI/Number.png");
		w = 30, h = 50;
		x = i * w, y = 0;
		listW = 300, listH = 50;
		_spUINumber[i] = { sprite,x,y,w,h,listW,listH };
	}

	_spUIHelp = Novice::LoadTexture("./Resources/Textures/UI/Help.png");

	sprite = Novice::LoadTexture("./Resources/Textures/UI/Dangaer/List.png");
	listW = 480, listH = 124;
	w = 244, h = 124, x = 0, y = 0;
	_spUIDanger[0] = { sprite,x,y,w,h,listW,listH };
	w = 190, h = 28, x = 244, y = 0;
	_spUIDanger[1] = { sprite,x,y,w,h,listW,listH };
	w = 69, h = 28, x = 244, y = 28;
	_spUIDanger[2] = { sprite,x,y,w,h,listW,listH };
	w = 23, h = 28, x = 244 + 190, y = 0;
	_spUIDanger[3] = { sprite,x,y,w,h,listW,listH };
	w = 23, h = 28, x = 244 + 190 + 23, y = 0;
	_spUIDanger[4] = { sprite,x,y,w,h,listW,listH };
	w = 23, h = 28, x = 244 + 69, y = 28;
	_spUIDanger[5] = { sprite,x,y,w,h,listW,listH };
	w = 23, h = 28, x = 244 + 69 + 23, y = 28;
	_spUIDanger[6] = { sprite,x,y,w,h,listW,listH };
}
