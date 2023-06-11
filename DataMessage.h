#pragma once
#include <Novice.h>
#include "Player.h"
#include "Enemy.h"
class DataMessage
{
private:
	Player& PlayerObj;
public:
	DataMessage(Player& obj) :PlayerObj(obj) {};
	void MessageCheck();
};