#include "pch.h"
#include "enemyManager.h"
#include "Zero.h"

HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	//_vBoss[0]->update();
	//_boss->update();

	for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
	{
		(*_viBoss)->update();
		(*_viBoss)->setPlayerMemoryAddressLink(_player);
	}
}

void enemyManager::render()
{
	//_vBoss[0]->render();
	//_boss->update();

	for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
	{
		(*_viBoss)->render();
	}
}

void enemyManager::setBoss(float pos)
{
	enemy* _boss;
	_boss = new Boss;
	_boss->init("eIdle", PointMake(pos, 620));
	_vBoss.push_back(_boss);
}

void enemyManager::removeBoss(int arrNum)
{
	//_vBoss.erase(_vBoss.begin() + arrNum);
	_vBoss.clear();
}
