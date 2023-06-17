#pragma once
#include <Novice.h>
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
class DataMessage
{
private:
	Player* _PlayerObj;
	Level* _LevelObj;
public:
	void Initial(Player* playerObj, Level* levelObj);
	void MessageCheck();//检查敌人信息
};