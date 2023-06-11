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
	void CapturedValueAdd(int num);
private:
	int _attackTime = 0;
	//触手的两点坐标是从中心开始！
	float _tentaclePosX = 0, _tentaclePosY = 0;
	bool _isCapture = false;

	Enemy* _enemyCaptured;//记录被抓住的敌人(放在触手上的)
	int _capturedValue = 0;
};