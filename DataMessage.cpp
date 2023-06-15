#include "DataMessage.h"

void DataMessage::Initial(Player* obj)
{
	PlayerObj = obj;
}

void DataMessage::MessageCheck()
{
	//检查敌人的信息
	for (Enemy* element : EnemyManager::_enemyUpdateVector) {
		if (!element->GetIsLive() && !element->_isMessageOver_isLive) {
			PlayerObj->CapturedValueAdd();
			element->_isMessageOver_isLive = true;
		}
	}
}
