#pragma once
#include <Novice.h>
#include <queue>
#include <vector>
#include "LoadRes.h"
class Bullet
{
protected:
	float _posX;
	float _posY;
	float _width;
	float _higth;

	int _damage;
	float _speed;
	int _sprite;
	int _type;
	bool _isFire;

	void FrameAnimation(float x, float y, int sprite);

public:
	static enum BulletType {
		player,
		enemy,
		enemyCapture,
		laser,
		laserCapture,
	}bulletType;

	Bullet(BulletType type);
	void Initial(BulletType type);
	void Fire(float x, float y);
	void Move();

	int GetSprite();
	float GetPosX();
	float GetPosY();
	float GetWidth();
	float GetHigth();
	int GetType();
	int GetDamage();
	void SetType(int type);
};

class BulletManager
{
public:
	static std::vector<Bullet*> _bulletUpdateVector;			//我方子弹容器
	static std::vector<Bullet*> _bulletUpdateVector_enemy;		//敌方子弹容器

	//在主循环中进行调用，用以不断遍历里面的东西达到更新效果
	static void BulletUpdata();
	//下面这些队列是用来装闲置的子弹(注意敌人的子弹有两种，一种自己的一种被抓后的)
	static std::queue<Bullet*> _bulletIdiePool_player;
	static std::queue<Bullet*> _bulletIdiePool_enemy;
	static std::queue<Bullet*> _bulletIdiePool_enemyCapture;
	static std::queue<Bullet*> _bulletIdiePool_laser;
	static std::queue<Bullet*> _bulletIdiePool_laserCapture;


	static Bullet* AcquireBullet(Bullet::BulletType type);
	static void ReleaseBullet(Bullet* bullet);
};
