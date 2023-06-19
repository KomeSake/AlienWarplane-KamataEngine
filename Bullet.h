#pragma once
#include <Novice.h>
#include <queue>
#include <vector>
#include <ctime>
#include "LoadRes.h"

class Bullet
{
protected:
	float _posX = 0, _posY = 0;
	float _width = 0, _higth = 0;
	float _scaleX = 1, _scaleY = 1;
	unsigned int _color = WHITE;

	int _damage;
	float _speedY = 0;
	float _speedX = 0;
	int _sprite;
	int _type;
	bool _isFire;

	void FrameTexture(float x, float y, int sprite);
	//子弹的特殊处理(注意在方法开头要做类型判断，因为这个方法会直接调用)
	void BulletUfo();
	void BulletBigGun();
public:
	static enum BulletType {
		player,
		enemy,
		enemyCapture,
		laser,
		laserCapture,
		ufo,
		ufoCapture,
		bigGun,
		bigGunCapture,
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
	float GetSpeed(int xy);
	void SetType(int type);
	//两种模式，0：直接设置值，1：倍率设置值(推荐);速度有X轴和Y轴；
	void SetSpeed(int type, int xy, float num);
	//特殊子弹变量
	bool _isBigGunFirst = true;//判断是不是第一颗
private:
	//从Plane类偷来的计时器
	bool Timers(int milli, int index);
	clock_t _timeStart[11] = { 0 };
	clock_t _timeEnd[11] = { 0 };
	bool _isTimeOpen[11] = { 0 };
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
	static std::queue<Bullet*> _bulletIdiePool_ufo;
	static std::queue<Bullet*> _bulletIdiePool_ufoCapture;
	static std::queue<Bullet*> _bulletIdiePool_bigGun;
	static std::queue<Bullet*> _bulletIdiePool_bigGunCapture;


	static Bullet* AcquireBullet(Bullet::BulletType type);
	static void ReleaseBullet(Bullet* bullet);
};
