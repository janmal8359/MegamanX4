#pragma once
#include "gameNode.h"
#include "Zero.h"
#include "objectManager.h"
#include "enemyManager.h"
//#include "enemy.h"

class playGround : public gameNode
{
private:
	Zero* _player;
	objectManager* _om;
	enemyManager* _em;
	//enemy* _enemy;

	// background image
	image* _background;

	// Camera
	RECT _camera;
	int _camX, _camY;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

	//void Collision();

	void SetCamera(RECT& camera, int left, int top, int width, int height);
	//void CameraMove(RECT& camera);

	void MakeGround(RECT& rect, int left, int right, int top, int bottom);		// 지형 (고정됨)
	void MakeObject(RECT& rect, int left, int top, int width, int height);		// 그 외 오브젝트(카메라 이동)
	void RendObject(RECT rect[], int max);
	void RendObject(RECT& rect);


	//void EnemyMove();
};

