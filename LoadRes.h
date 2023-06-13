#pragma once
#include <Novice.h>
#include <map>

class LoadRes
{
public:
	//Sprite贴图
	static int _spPlayer, _spPlayerTentaclesOne, _spPlayerTentaclesTwo;
	static int _spEnemy, _spEnemy2;
	static int _spBullet_player, _spBullet_enemy, _spBullet_enemyCapture, _spBullet_enemy2, _spBullet_enemy2Capture;

	//动画
	static std::map<int, int> _spAniExplode;
	static std::map<int, int> _spAniPlayerTentaclesTwo;
	static std::map<int, int> _spAniPlayerFire;
	static std::map<int, int> _spAniEnemyFire;
	static std::map<int, int> _spAniPlayerHpPlus;

	//UI
	static int _spUIBg;
	static std::map<int, int> _spUICaptureVessel;
	static std::map<int, int> _spUIHpVessel;

	//在主方法中调用(进行实现的材质载入)
	static void LoadResNovice();
};
