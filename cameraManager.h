#pragma once
#include "pch.h"
#include "singletonBase.h"

class Zero;

class cameraManager : public singletonBase <cameraManager>
{
private:
	// Camera
	RECT _camera;
	int _camX, _camY;

	Zero* _player;

public:
	HRESULT init();
	void update();
	void render();
	void release();

	void SetCamera(int left, int top, int width, int height);
	//void CameraMove(RECT& camera, tagPlayer player, float speed);
	void CameraMove();

	void MakeObject(RECT& rect, int left, int top, int width, int height);		// �� �� ������Ʈ(ī�޶� �̵�)

	int getCamX() { return _camX; }
	int getCamY() { return _camY; }

	void setCamX(int camX) { _camX = camX; }

	RECT getCamera() { return _camera; }

	void setPlayerMemoryAddressLink(Zero* player) { _player = player; }

};

