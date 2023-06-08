#include "LoadRes.h"

int LoadRes::_spPlayer;
int LoadRes::_spbullet;
int LoadRes::_spPlayerTentaclesOne;
int LoadRes::_spPlayerTentaclesTwo;
int LoadRes::_spEnemy;
int LoadRes::_spEnemyBullet;
int LoadRes::_spExplode;
int LoadRes::_spBg;
int LoadRes::_spAniPlayerTentaclesTwo[4];

void LoadRes::LoadResNovice()
{
	_spPlayer = Novice::LoadTexture("./Resources/Textures/Player0-0.png");
	_spbullet = Novice::LoadTexture("./Resources/Textures/Bullet.png");
	_spEnemy = Novice::LoadTexture("./Resources/Textures/Enemy.png");
	_spEnemyBullet = Novice::LoadTexture("./Resources/Textures/Enemy_Bullet.png");
	_spExplode = Novice::LoadTexture("./Resources/Textures/Explode.png");
	_spBg = Novice::LoadTexture("./Resources/Textures/BG.png");
	_spPlayerTentaclesOne = Novice::LoadTexture("./Resources/Textures/PlayerTentaclesOne.png");
	_spPlayerTentaclesTwo = Novice::LoadTexture("./Resources/Textures/PlayerTentaclesTwo.png");

	_spAniPlayerTentaclesTwo[0] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerTentaclesTwo1.png");
	_spAniPlayerTentaclesTwo[1] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerTentaclesTwo2.png");
	_spAniPlayerTentaclesTwo[2] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerTentaclesTwo3.png");
	_spAniPlayerTentaclesTwo[3] = Novice::LoadTexture("./Resources/Textures/Animation/PlayerTentaclesTwo4.png");
}
