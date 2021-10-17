#pragma once
#include "gameNode.h"
#include "Boss.h"
#include <vector>

class Zero;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

private:
	vEnemy _vBoss;
	viEnemy _viBoss;

	Zero* _player;

public:
	enemyManager() {}
	~enemyManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void setBoss(float pos);

	void removeBoss(int arrNum);

	vEnemy getVBoss() { return _vBoss; }
	viEnemy getVIBoss() { return _viBoss; }

	void setPlayerMemoryAddressLink(Zero* player) { _player = player; }
};

