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
	//感觉分成两个容器比较好，而不是通过辨别子弹类型，两个容器一个是我方子弹，一个是敌方子弹
	//这样直接把容器中的东西来出来对比就可以做出伤害辨认了
	static std::vector<Bullet*> _bulletUpdateVector;			//需要在主循环中调用的容器

	//在主循环中进行调用，用以不断遍历里面的东西达到更新效果
	static void BulletUpdata();
	//下面这些队列只是用来装闲置的子弹，所以我方和敌人都混在一起即可
	static std::queue<Bullet*> _bulletIdiePool_normal;			//闲置子弹容器1
	static std::queue<Bullet*> _bulletIdiePool_enemy;
	static std::queue<Bullet*> _bulletIdiePool_laser;			//闲置子弹容器2

	static Bullet* AcquireBullet(int type);
	static void ReleaseBullet(Bullet* bullet);
};
