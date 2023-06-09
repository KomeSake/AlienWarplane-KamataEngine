#pragma once
#include <Novice.h>
#include <map>

class LoadRes
{
public:
	static int _spPlayer, _spbullet, _spPlayerTentaclesOne, _spPlayerTentaclesTwo;
	static int _spEnemy, _spEnemyBullet;
	static int _spBg;

	static int _spAniExplode[9];
	static std::map<int, int> _spAniExplode2;
	static int _spAniPlayerTentaclesTwo[4];
	static int _spAniPlayerFire[6];
	static int _spAniEnemyFire[6];

	static void LoadResNovice();
};
