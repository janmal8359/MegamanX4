#pragma once
#include "gameNode.h"
#include <vector>
#include "collider.h"

//#define COLLMAX 38
#define COLLMAX 38

class objectManager : public gameNode
{
private:
	typedef vector<object*>					vObject;
	typedef vector<object*>::iterator		viObject;

private:
	vObject _vCollider;
	viObject _viCollider;



public:
	objectManager() {}
	~objectManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void setCollider();

	void removeCollider();

	// get
	vObject getVCollider() { return _vCollider; }
	viObject getVICollider() { return _viCollider; }

};

