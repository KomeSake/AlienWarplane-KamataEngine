#pragma once
#include <Novice.h>
#include "Player.h"
#include "Enemy.h"
class DataMessage
{
private:
	Player* PlayerObj;
public:
	void Initial(Player* obj);
	void MessageCheck();
};