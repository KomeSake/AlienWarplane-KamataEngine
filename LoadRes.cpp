#include "LoadRes.h"

int LoadRes::_spPlayer;
int LoadRes::_spbullet;
int LoadRes::_spPlayerTentacles01;
int LoadRes::_spPlayerTentacles02;
int LoadRes::_spEnemy;
int LoadRes::_spEnemyBullet;
int LoadRes::_explode;
int LoadRes::_spBg;

void LoadRes::LoadResNovice()
{
	_spPlayer = Novice::LoadTexture("./Resources/Textures/Player0-0.png");
	_spbullet = Novice::LoadTexture("./Resources/Textures/Bullet.png");
	_spEnemy = Novice::LoadTexture("./Resources/Textures/Enemy.png");
	_spEnemyBullet = Novice::LoadTexture("./Resources/Textures/Enemy_Bullet.png");
	_explode = Novice::LoadTexture("./Resources/Textures/Explode.png");
	_spBg = Novice::LoadTexture("./Resources/Textures/BG.png");
	_spPlayerTentacles01 = Novice::LoadTexture("./Resources/Textures/PlayerTentacles01.png");
	_spPlayerTentacles02 = Novice::LoadTexture("./Resources/Textures/PlayerTentacles02.png");
}
