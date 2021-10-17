#include "pch.h"
#include "cameraManager.h"
#include "Zero.h"

HRESULT cameraManager::init()
{
	_player = new Zero;

	_camX = -12000;
	_camY = 0;

	return S_OK;
}

void cameraManager::update()
{
}

void cameraManager::render()
{
	//char str[128];
	//
	//sprintf_s(str, "_camX : %d", _camX);
	//TextOut(getMemDC(), 10, 400, str, strlen(str));
}

void cameraManager::release()
{
}

void cameraManager::SetCamera(int left, int top, int width, int height)
{
	_camera.left = left;
	_camera.top = top;
	_camera.right = _camera.left + width;
	_camera.bottom = _camera.top + height;
}

void cameraManager::CameraMove()
{// 카메라 체크 상자 설정
	SetCamera(300, 200, 600, 400);

	// camera 상자 안에서만 플레이어가 직접 이동(혹은 카메라 이동이 불가능할 경우)
	if (IMAGEMANAGER->findImage("배경")->getHeight() <= WINSIZEY - _camY || _camY == 0 || _player->getRect().bottom < _camera.bottom || _player->getRect().top > _camera.top)
	{
		//y -= jumpPower;
		//jumpPower -= gravity;

		//_player->setY(_player->getY() - _player->getJumpPower());
		//_player->setJumpPower(_player->getJumpPower() - _player->getGravity());
	}

	// 배경화면의 왼쪽 끝이 윈도우 창의 왼쪽이랑 같아지면 이동 정지
	// 배경화면의 오른쪽 끝이 윈도우 창의 오른쪽이랑 같아지면 이동 정지
	if (_camX >= 0 || _camX + WINSIZEX <= IMAGEMANAGER->findImage("배경")->getWidth() - 1150)
	{
		//playerSpeed = speed;
		_player->setSpeed(_player->getSpeed());
	}


	// 1. 사각형을 이용하는 방법
	// 일정 범위의 사각형 rc와 캐릭터의 rc의 같은 요소(left, right, top, bottom)의 값이 같아지면
	// 해당 방향으로 카메라 이동

	// 카메라 왼쪽으로 이동 (배경은 오른쪽으로)
	if (_player->getX() <= _camera.left + 40 && (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown('Z')))
	{
		if (_camX < 0)
		{
			_camX += _player->getSpeed();
			//playerSpeed = 0;
			//x = _camera.left + 40;
			_player->setSpeed(0);
			_player->setX(_camera.left + 40);
		}
	}
	// 카메라 오른쪽으로 이동 (배경은 왼쪽으로)
	else if (_player->getX() >= _camera.right - 40 && (KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown('Z')))
	{
		if (_camX + IMAGEMANAGER->findImage("배경")->getWidth() - 1150 >= WINSIZEX)
		{
			_camX -= _player->getSpeed();
			//playerSpeed = 0;
			//x = _camera.right - 40;
			_player->setSpeed(0);
			_player->setX(_camera.right - 40);
		}
	}
	else
	{
		//playerSpeed = speed;
		_player->setSpeed(_player->getSpeed());
	}


	//// 카메라 위쪽으로 이동 (배경은 아래쪽으로)
	//if (_player->getY() <= _camera.top + 50 && _player->getJumpPower() > 0)
	//{
	//	if (_camY < 0)
	//	{
	//		//_camY += jumpPower;
	//		//y = _camera.top + 50;
	//		_camY += _player->getJumpPower();
	//		_player->setY(_camera.top + 50);
	//	}
	//}
	//
	//// 카메라 아래쪽으로 이동 (배경은 위쪽으로)
	//if (_player->getY() >= _camera.bottom - 50)
	//{
	//	if (IMAGEMANAGER->findImage("배경")->getHeight() >= WINSIZEY - _camY)
	//	{
	//		//_camY += jumpPower;
	//		//y = _camera.bottom - 50;
	//		_camY += _player->getJumpPower();
	//		_player->setY(_camera.bottom - 50);
	//	}
	//}



	// 2. 좌표값을 이용하는 방법
	// 캐릭터의 중심 x,y좌표값을 일정 좌표값과 비교해서
	// 카메라 이동
}

void cameraManager::MakeObject(RECT& rect, int left, int top, int width, int height)
{
	rect.left = _camX + left;
	rect.right = rect.left + width;
	rect.top = _camY + top;
	rect.bottom = rect.top + height;

	//RendObject(rect);
}
