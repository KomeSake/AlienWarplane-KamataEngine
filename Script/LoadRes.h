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
	inline static int _spPlayer, _spPlayer2, _spPlayerTentacles;
	inline static int _spEnemy, _spEnemy2, _spEnemy3, _spEnemy4;
	inline static int _spBullet_player, _spBullet_enemy, _spBullet_enemyCapture, _spBullet_enemy2, _spBullet_enemy2Capture, _spBullet_enemy3, _spBullet_enemy3Capture, _spBullet_enemy4, _spBullet_enemy4Capture;
	inline static int _spArrow;

	//动画
	inline static std::map<int, SpriteList> _spAniExplode;
	inline static std::map<int, SpriteList> _spAniPlayerTentacles;
	inline static std::map<int, SpriteList> _spAniPlayerFire;
	inline static std::map<int, SpriteList> _spAniEnemyFire;
	inline static std::map<int, SpriteList> _spAniPlayerHpPlus;
	inline static std::map<int, SpriteList> _spAniPlayerHpPlus2;
	inline static std::map<int, SpriteList> _spAniMouse;


	//UI
	inline static int _spUIBg;
	inline static std::map<int, SpriteList> _spUICaptureVessel;
	inline static int _spUICaptureVessel_05;
	inline static std::map<int, int> _spUIHpVessel;
	inline static std::map<int, SpriteList> _spUISignalVessel;
	inline static std::map<int, SpriteList> _spUIStartScene;
	inline static std::map<int, SpriteList> _spUIGameOverScene;
	inline static std::map<int, SpriteList> _spUINumber;
	inline static int _spUIHelp;
	inline static int _spUIHelp2;
	inline static int _spUIHelpText1;
	inline static int _spUIHelpText2;
	inline static int _spUIHelpMessage;
	inline static std::map<int, SpriteList> _spUIDanger;

	//Audio
	inline static int _adBgm;
	inline static int _adHitEnemy;
	inline static int _adMyEnemyDead;
	inline static int _adScoreUp;
	inline static int _adSelectClick;
	inline static int _adHitPlayer;
	inline static int _adShout;
	inline static int _adPlayerDead;
	inline static int _adEnemyDead;
	inline static int _adEnemyShout;
	inline static int _adShoutUfo;
	inline static int _adShoutLaser;
	inline static int _adShoutBigGun;
	inline static int _adCapture;
	inline static int _adCaptureEat;
	inline static int _adCaptureOut;
	inline static int _adCaptureCD;


	//在主方法中调用(进行实现的材质载入)
	static void LoadResNovice();
};
