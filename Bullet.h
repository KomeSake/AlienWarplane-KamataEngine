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
	//0:normal,1:enemy,2:laser,3:Shoutgun
	int _type;
	bool _isFire;

	void FrameAnimation(float x, float y, int sprite);

public:
	static enum BulletType {
		player,
		enemy
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

//这个类没有使用
//class BulletPool
//{
//public:
//	std::queue<Bullet*> pool;
//	BulletPool(int initialSum);
//	~BulletPool();
//	Bullet* AcquireBullet();
//	void ReleaseBullet(Bullet* bullet);
//};



class BulletManager
{
public:
	static std::vector<Bullet*> _bulletUpdateVector;			//我方子弹容器
	static std::vector<Bullet*> _bulletUpdateVector_enemy;		//敌方子弹容器

	//在主循环中进行调用，用以不断遍历里面的东西达到更新效果
	static void BulletUpdata();
	//下面这些队列只是用来装闲置的子弹，所以我方和敌人都混在一起即可
	static std::queue<Bullet*> _bulletIdiePool_player;			//闲置子弹容器1
	static std::queue<Bullet*> _bulletIdiePool_enemy;
	static std::queue<Bullet*> _bulletIdiePool_laser;			//闲置子弹容器2


	static Bullet* AcquireBullet(Bullet::BulletType type);
	static void ReleaseBullet(Bullet* bullet);
};
