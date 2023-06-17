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
	int GetHp();
	int GetCapturedValue();
	void CapturedValueAdd();
	bool GetIsCapture();
	bool GetIsCaptureCD();
	int GetCaptureCDTime();
	int GetScoreSum();
	void SetScorePlus(int value);
private:
	int _attackTime = 0;
	//触手的两点坐标是从中心开始！
	float _tentaclePosX = 0, _tentaclePosY = 0;
	bool _isCapture = false;
	bool _isCaptureCD = false;
	int _captureCDTime = 0;
	int _capturedValue = 0;
	float _captureSpeed = 0;
	bool _isPlayerHpPlus = false;
	//这两个是针对提前抓爆被抓敌人的设定
	int _captureDamageCount = 0;
	bool _iscaptureDamage = false;

	Enemy* _enemyCaptured;//记录被抓住的敌人(放在触手上的)
	int _scoreSum = 0;//分数就写这里吧，这里方便读取
};