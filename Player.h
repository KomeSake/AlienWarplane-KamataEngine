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
	int GetCapturedValue();
	void CapturedValueAdd();
private:
	int _attackTime = 0;
	//触手的两点坐标是从中心开始！
	float _tentaclePosX = 0, _tentaclePosY = 0;
	bool _isCapture = false;
	bool _isCaptureCD = false;
	int _captureCDTime = 0;
	int _capturedValue = 0;

	Enemy* _enemyCaptured;//记录被抓住的敌人(放在触手上的)
};