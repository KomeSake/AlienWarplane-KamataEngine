#include "LoadRes.h"

int LoadRes::_spPlayer;
int LoadRes::_spbullet;
int LoadRes::_spEnemy;
int LoadRes::_spEnemyBullet;

void LoadRes::LoadResNovice()
{
	_spPlayer = Novice::LoadTexture("./Resources/Textures/Player0-0.png");
	_spbullet = Novice::LoadTexture("./Resources/Textures/Bullet.png");
	_spEnemy = Novice::LoadTexture("./Resources/Textures/Enemy.png");
	_spEnemyBullet = Novice::LoadTexture("./Resources/Textures/Enemy_Bullet.png");
}
