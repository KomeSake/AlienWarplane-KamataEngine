#pragma once
#include <Novice.h>
#include <map>

class LoadRes
{
public:
	//Sprite贴图
	static int _spPlayer, _spbullet, _spPlayerTentaclesOne, _spPlayerTentaclesTwo;
	static int _spEnemy, _spEnemyBullet;

	//动画
	static std::map<int, int> _spAniExplode;
	static std::map<int, int> _spAniPlayerTentaclesTwo;
	static std::map<int, int> _spAniPlayerFire;
	static std::map<int, int> _spAniEnemyFire;

	//UI
	static int _spUIBg;
	static std::map<int, int> _spUICaptureVessel;
	static std::map<int, int> _spUIHpVessel;

	static void LoadResNovice();
};
