#include "LoadRes.h"

int LoadRes::_spPlayer = 0;
int LoadRes::_spPlayerTentaclesOne = 0;
int LoadRes::_spPlayerTentaclesTwo = 0;
int LoadRes::_spEnemy = 0;
int LoadRes::_spEnemy2 = 0;
int LoadRes::_spBullet_player = 0;
int LoadRes::_spBullet_enemy = 0;
int LoadRes::_spBullet_enemy2 = 0;
int LoadRes::_spBullet_enemyCapture = 0;
int LoadRes::_spBullet_enemy2Capture = 0;

std::map<int, int> LoadRes::_spAniExplode;
std::map<int, int> LoadRes::_spAniPlayerTentaclesTwo;
std::map<int, int> LoadRes::_spAniPlayerFire;
std::map<int, int> LoadRes::_spAniEnemyFire;
std::map<int, int> LoadRes::_spAniPlayerHpPlus;
std::map<int, int> LoadRes::_spAniPlayerHpPlus2;

int LoadRes::_spUIBg = 0;
std::map<int, int> LoadRes::_spUICaptureVessel;
std::map<int, int> LoadRes::_spUIHpVessel;
std::map<int, int> LoadRes::_spUIStartScene;

void LoadRes::LoadResNovice()
{
	//Sprite贴图
	_spPlayer = Novice::LoadTexture("./Resources/Textures/Player0-0.png");
	_spPlayerTentaclesOne = Novice::LoadTexture("./Resources/Textures/PlayerTentaclesOne.png");
	_spPlayerTentaclesTwo = Novice::LoadTexture("./Resources/Textures/PlayerTentaclesTwo.png");

	_spEnemy = Novice::LoadTexture("./Resources/Textures/Enemy.png");
	_spEnemy2 = Novice::LoadTexture("./Resources/Textures/Enemy2.png");

	_spBullet_player = Novice::LoadTexture("./Resources/Textures/Bullet.png");
	_spBullet_enemy = Novice::LoadTexture("./Resources/Textures/Bullet_Enemy.png");
	_spBullet_enemyCapture = Novice::LoadTexture("./Resources/Textures/Bullet_Enemy(Captured).png");
	_spBullet_enemy2 = Novice::LoadTexture("./Resources/Textures/Bullet_Enemy2.png");
	_spBullet_enemy2Capture = Novice::LoadTexture("./Resources/Textures/Bullet_Enemy2(Captured).png");

	//动画
	_spAniExplode[0] = Novice::LoadTexture("./Resources/Textures/Animation/Explode1.png");
	_spAniExplode[1] = Novice::LoadTexture("./Resources/Textures/Animation/Explode2.png");
	_spAniExplode[2] = Novice::LoadTexture("./Resources/Textures/Animation/Explode3.png");
	_spAniExplode[3] = Novice::LoadTexture("./Resources/Textures/Animation/Explode4.png");
	_spAniExplode[4] = Novice::LoadTexture("./Resources/Textures/Animation/Explode5.png");
	_spAniExplode[5] = Novice::LoadTexture("./Resources/Textures/Animation/Explode6.png");
	_spAniExplode[6] = Novice::LoadTexture("./Resources/Textures/Animation/Explode7.png");
	_spAniExplode[7] = Novice::LoadTexture("./Resources/Textures/Animation/Explode8.png");
	_spAniExplode[8] = Novice::LoadTexture("./Resources/Textures/Animation/Explode9.png");
	_spAniExplode[9] = Novice::LoadTexture("./Resources/Textures/Animation/Explode10.png");

	_spAniPlayerTentaclesTwo[0] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerTentaclesTwo1.png");
	_spAniPlayerTentaclesTwo[1] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerTentaclesTwo2.png");
	_spAniPlayerTentaclesTwo[2] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerTentaclesTwo3.png");
	_spAniPlayerTentaclesTwo[3] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerTentaclesTwo4.png");

	_spAniPlayerFire[0] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerFire1.png");
	_spAniPlayerFire[1] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerFire2.png");
	_spAniPlayerFire[2] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerFire3.png");
	_spAniPlayerFire[3] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerFire4.png");
	_spAniPlayerFire[4] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerFire5.png");
	_spAniPlayerFire[5] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerFire6.png");

	_spAniEnemyFire[0] = Novice::LoadTexture("./Resources/Textures/Animation/EnemyFire1.png");
	_spAniEnemyFire[1] = Novice::LoadTexture("./Resources/Textures/Animation/EnemyFire2.png");
	_spAniEnemyFire[2] = Novice::LoadTexture("./Resources/Textures/Animation/EnemyFire3.png");
	_spAniEnemyFire[3] = Novice::LoadTexture("./Resources/Textures/Animation/EnemyFire4.png");
	_spAniEnemyFire[4] = Novice::LoadTexture("./Resources/Textures/Animation/EnemyFire5.png");
	_spAniEnemyFire[5] = Novice::LoadTexture("./Resources/Textures/Animation/EnemyFire6.png");

	_spAniPlayerHpPlus[0] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerHpPlus1.png");
	_spAniPlayerHpPlus[1] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerHpPlus2.png");
	_spAniPlayerHpPlus[2] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerHpPlus3.png");
	_spAniPlayerHpPlus[3] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerHpPlus4.png");
	_spAniPlayerHpPlus[4] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerHpPlus5.png");
	_spAniPlayerHpPlus[5] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerHpPlus6.png");
	_spAniPlayerHpPlus[6] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerHpPlus7.png");
	_spAniPlayerHpPlus[7] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerHpPlus8.png");
	_spAniPlayerHpPlus[8] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerHpPlus9.png");

	_spAniPlayerHpPlus2 = _spAniPlayerHpPlus;

	//UI
	_spUIBg = Novice::LoadTexture("./Resources/Textures/BG.png");

	_spUICaptureVessel[0] = Novice::LoadTexture("./Resources/Textures/UI/CaptureVessel_00.png");
	_spUICaptureVessel[1] = Novice::LoadTexture("./Resources/Textures/UI/CaptureVessel_01.png");
	_spUICaptureVessel[2] = Novice::LoadTexture("./Resources/Textures/UI/CaptureVessel_02.png");
	_spUICaptureVessel[3] = Novice::LoadTexture("./Resources/Textures/UI/CaptureVessel_03.png");
	_spUICaptureVessel[4] = Novice::LoadTexture("./Resources/Textures/UI/CaptureVessel_04.png");
	_spUICaptureVessel[5] = Novice::LoadTexture("./Resources/Textures/UI/CaptureVessel_05.png");

	_spUIHpVessel[0] = Novice::LoadTexture("./Resources/Textures/UI/HpVessel_00.png");

	_spUIStartScene[0] = Novice::LoadTexture("./Resources/Textures/UI/StartScene/0.png");
	_spUIStartScene[1] = Novice::LoadTexture("./Resources/Textures/UI/StartScene/1.png");
	_spUIStartScene[2] = Novice::LoadTexture("./Resources/Textures/UI/StartScene/2.png");
	_spUIStartScene[3] = Novice::LoadTexture("./Resources/Textures/UI/StartScene/3.png");
	_spUIStartScene[4] = Novice::LoadTexture("./Resources/Textures/UI/StartScene/4.png");
}
