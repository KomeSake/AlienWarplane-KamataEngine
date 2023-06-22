#pragma once
#include "Plane.h"
#include "Enemy.h"
class Player :
	public Plane
{
public:
	Player();
	void Move(char keys[]);
	void Attack(char keys[]);
	void CaptureEnemy();
	void DamageCheck();
	void AniPlayerUP();			//这个方法放一些要显示在玩家图像上面的特效
	void EasyModeValue();		//这个方法放一些简单模式下需要修改的值;
	int GetSprite();
	int GetHp();
	int GetCapturedValue();
	void CapturedValueAdd();
	bool GetIsCapture();
	bool GetIsCaptureCD();
	int GetCaptureCDTime();
	int GetScoreSum();
	void SetScorePlus(int value);
	Enemy::EnemyType GetCaptureEnemyType();
	void SetAutoShoot(bool taf);
	void SetEasyMode(bool taf);
	bool GetEasyMode();
private:
	int _attackTime = 0;//攻击频率
	//触手的两点坐标是从中心开始！
	float _tentaclePosX = 0, _tentaclePosY = 0;
	bool _isCapture = false;
	bool _isCaptureCD = false;
	int _captureCDTime = 0;
	int _capturedValue = 0;
	float _captureSpeed = 0;
	bool _isPlayerHpPlus = false;
	Enemy* _enemyCaptured;//记录被抓住的敌人(放在触手上的)
	//下面是针对提前抓爆被抓敌人的设定
	int _captureDamageCount = 0;
	bool _iscaptureDamage = false;//这个值代表是否吸收了敌人
	Enemy::EnemyType _captureEnemyType = Enemy::null;
	bool PlayerAndTentaclePlus();//这个方法会判断触手和玩家是否合体，而且会进行一些合体的变化
	bool _isCaptureBoomAni = false;//抓爆敌人后播放一个特效
	//界面逻辑相关
	int _scoreSum = 0;//分数就写这里吧，这里方便读取
	bool _isAutoShoot = false, _isEasyMode = false;
};