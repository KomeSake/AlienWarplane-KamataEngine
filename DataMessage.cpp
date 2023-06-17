#include "DataMessage.h"

void DataMessage::Initial(Player* playerObj, Level* levelObj)
{
	_PlayerObj = playerObj;
	_LevelObj = levelObj;
}

void DataMessage::MessageCheck()
{
	for (Enemy* element : EnemyManager::_enemyUpdateVector) {
		//敌人是否被抓
		if (!element->GetIsLive() && !element->_isMessageOver_isLive) {
			_PlayerObj->CapturedValueAdd();
			element->_isMessageOver_isLive = true;
		}
		//敌人是否死亡(加分)
		if (!element->GetIsLive()) {
			_PlayerObj->SetScorePlus(element->GetScore());
		}
		//敌人是否已逃逸
		if (element->_message_isFree == 1) {
			switch (element->GetType()) {
			case Enemy::normal:
				_LevelObj->DangerLevelPlus(1);
				break;
			case Enemy::laser:
				_LevelObj->DangerLevelPlus(2);
				break;
			case Enemy::ufo:
				_LevelObj->DangerLevelPlus(1);
				break;
			}
			element->_message_isFree = 2;
		}
	}
}
