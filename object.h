#pragma once
#include "gameNode.h"

//struct Line
//{
//	POINT p1;
//	POINT p2;
//
//};

// ������Ʈ ���� Ʋ
class object : public gameNode
{
protected:
	// �浹üũ�� RECT
	RECT _rc;

	int _x, _y;
	int _width, _height;


public:
	object() {}
	~object() {}

	virtual HRESULT init();
	virtual HRESULT init(POINT position, int width, int height);
	virtual void release();
	virtual void update();
	virtual void render();

	RECT getRect() { return _rc; }


};

