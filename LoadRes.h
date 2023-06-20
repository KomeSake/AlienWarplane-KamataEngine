#pragma once
#include <Novice.h>
#include <map>

class LoadRes
{
public:
	//图集结构体
	static struct SpriteList
	{
		int sprite = 0;
		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;
		int listW = 0;
		int listH = 0;
	}_spriteList;

	//Sprite贴图
	static int _spPlayer, _spPlayer2, _spPlayerTentacles;
	static int _spEnemy, _spEnemy2, _spEnemy3, _spEnemy4;
	static int _spBullet_player, _spBullet_enemy, _spBullet_enemyCapture, _spBullet_enemy2, _spBullet_enemy2Capture, _spBullet_enemy3, _spBullet_enemy3Capture, _spBullet_enemy4, _spBullet_enemy4Capture;

	//动画
	static std::map<int, SpriteList> _spAniExplode;
	static std::map<int, SpriteList> _spAniPlayerTentacles;
	static std::map<int, SpriteList> _spAniPlayerFire;
	static std::map<int, SpriteList> _spAniEnemyFire;
	static std::map<int, SpriteList> _spAniPlayerHpPlus;
	static std::map<int, SpriteList> _spAniPlayerHpPlus2;


	//UI
	static int _spUIBg;
	static std::map<int, SpriteList> _spUICaptureVessel;
	static int _spUICaptureVessel_05;
	static std::map<int, int> _spUIHpVessel;
	static std::map<int, SpriteList> _spUISignalVessel;
	static std::map<int, SpriteList> _spUIStartScene;
	static std::map<int, SpriteList> _spUIGameOverScene;
	static std::map<int, SpriteList> _spUINumber;
	static int _spUIHelp;
	static std::map<int, SpriteList> _spUIDanger;

	//在主方法中调用(进行实现的材质载入)
	static void LoadResNovice();
};
