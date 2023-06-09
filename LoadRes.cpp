#include "LoadRes.h"

int LoadRes::_spPlayer = 0;
int LoadRes::_spbullet = 0;
int LoadRes::_spPlayerTentaclesOne = 0;
int LoadRes::_spPlayerTentaclesTwo = 0;
int LoadRes::_spEnemy = 0;
int LoadRes::_spEnemyBullet = 0;
int LoadRes::_spBg = 0;
int LoadRes::_spAniExplode[9] = { 0 };
std::map<int, int> LoadRes::_spAniExplode2;
int LoadRes::_spAniPlayerTentaclesTwo[4] = { 0 };
int LoadRes::_spAniPlayerFire[6] = { 0 };
int LoadRes::_spAniEnemyFire[6] = { 0 };

void LoadRes::LoadResNovice()
{
	_spPlayer = Novice::LoadTexture("./Resources/Textures/Player0-0.png");
	_spbullet = Novice::LoadTexture("./Resources/Textures/Bullet.png");
	_spEnemy = Novice::LoadTexture("./Resources/Textures/Enemy.png");
	_spEnemyBullet = Novice::LoadTexture("./Resources/Textures/Enemy_Bullet.png");
	_spBg = Novice::LoadTexture("./Resources/Textures/BG.png");
	_spPlayerTentaclesOne = Novice::LoadTexture("./Resources/Textures/PlayerTentaclesOne.png");
	_spPlayerTentaclesTwo = Novice::LoadTexture("./Resources/Textures/PlayerTentaclesTwo.png");

	_spAniExplode[0] = Novice::LoadTexture("./Resources/Textures/Animation/Explode1.png");
	_spAniExplode[1] = Novice::LoadTexture("./Resources/Textures/Animation/Explode2.png");
	_spAniExplode[2] = Novice::LoadTexture("./Resources/Textures/Animation/Explode3.png");
	_spAniExplode[3] = Novice::LoadTexture("./Resources/Textures/Animation/Explode4.png");
	_spAniExplode[4] = Novice::LoadTexture("./Resources/Textures/Animation/Explode5.png");
	_spAniExplode[5] = Novice::LoadTexture("./Resources/Textures/Animation/Explode6.png");
	_spAniExplode[6] = Novice::LoadTexture("./Resources/Textures/Animation/Explode7.png");
	_spAniExplode[7] = Novice::LoadTexture("./Resources/Textures/Animation/Explode8.png");
	_spAniExplode[8] = Novice::LoadTexture("./Resources/Textures/Animation/Explode9.png");

	_spAniExplode2[0] = Novice::LoadTexture("./Resources/Textures/Animation/Explode1.png");
	_spAniExplode2[1] = Novice::LoadTexture("./Resources/Textures/Animation/Explode2.png");
	_spAniExplode2[2] = Novice::LoadTexture("./Resources/Textures/Animation/Explode3.png");
	_spAniExplode2[3] = Novice::LoadTexture("./Resources/Textures/Animation/Explode4.png");
	_spAniExplode2[4] = Novice::LoadTexture("./Resources/Textures/Animation/Explode5.png");
	_spAniExplode2[5] = Novice::LoadTexture("./Resources/Textures/Animation/Explode6.png");
	_spAniExplode2[6] = Novice::LoadTexture("./Resources/Textures/Animation/Explode7.png");
	_spAniExplode2[7] = Novice::LoadTexture("./Resources/Textures/Animation/Explode8.png");
	_spAniExplode2[8] = Novice::LoadTexture("./Resources/Textures/Animation/Explode9.png");

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
}
