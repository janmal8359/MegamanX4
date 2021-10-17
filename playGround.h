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

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

	//void Collision();

	void SetCamera(RECT& camera, int left, int top, int width, int height);
	//void CameraMove(RECT& camera);

	void MakeGround(RECT& rect, int left, int right, int top, int bottom);		// ���� (������)
	void MakeObject(RECT& rect, int left, int top, int width, int height);		// �� �� ������Ʈ(ī�޶� �̵�)
	void RendObject(RECT rect[], int max);
	void RendObject(RECT& rect);


	//void EnemyMove();
};

