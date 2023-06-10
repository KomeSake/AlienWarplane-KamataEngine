#pragma once
#include <Novice.h>
#include <map>

class LoadRes
{
public:
	static int _spPlayer, _spbullet, _spPlayerTentaclesOne, _spPlayerTentaclesTwo;
	static int _spEnemy, _spEnemyBullet;
	static int _spBg;

	static std::map<int, int> _spAniExplode;
	static std::map<int, int> _spAniPlayerTentaclesTwo;
	static std::map<int, int> _spAniPlayerFire;
	static std::map<int, int> _spAniEnemyFire;

	static void LoadResNovice();
};
