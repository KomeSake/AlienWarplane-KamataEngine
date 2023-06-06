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

	int _damage;
	float _speed;
	int _sprite;
	//0:normal,1:enemy,2:laser,3:Shoutgun
	int _type;
	bool _isFire;

	void FrameAnimation(float x, float y, int sprite);

public:
	//子弹初始化里面，我还少写了一个要根据生成类型做一些特殊初始化
	Bullet();
	void Initial();
	void Fire(float x, float y);
	void Move();
	int GetSprite();
	float GetPosX();
	float GetPosY();
	int GetType();
	void SetType(int type);
};

//这个类没有使用
class BulletPool
{
public:
	std::queue<Bullet*> pool;
	BulletPool(int initialSum);
	~BulletPool();
	//Bullet* AcquireBullet();
	//void ReleaseBullet(Bullet* bullet);
};

class BulletManager
{
	//首先必须要有一个向量来存储所有动态的子弹指针
	//这样才可以在主循环中不断遍历这个向量来达到绘制、伤害检查、飞行等等，需要循环的方法
	//接着还需要对应的队列列表，把闲置的子弹又插回去，用一下一次的调用
public:
	static std::vector<Bullet*> _bulletUpdateVector;				//需要在主循环中调用的容器
	static void BulletUpdata();									//在主循环中进行调用，用以不断遍历里面的东西达到更新效果
	static std::queue<Bullet*> _bulletIdiePool_normal;			//闲置子弹容器1
	static std::queue<Bullet*> _bulletIdiePool_enemy;
	static std::queue<Bullet*> _bulletIdiePool_laser;			//闲置子弹容器2

	static Bullet* AcquireBullet(int type);
	static void ReleaseBullet(Bullet* bullet);
};
