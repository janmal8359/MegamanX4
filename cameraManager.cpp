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
{// ī�޶� üũ ���� ����
	SetCamera(300, 200, 600, 400);

	// camera ���� �ȿ����� �÷��̾ ���� �̵�(Ȥ�� ī�޶� �̵��� �Ұ����� ���)
	if (IMAGEMANAGER->findImage("���")->getHeight() <= WINSIZEY - _camY || _camY == 0 || _player->getRect().bottom < _camera.bottom || _player->getRect().top > _camera.top)
	{
		//y -= jumpPower;
		//jumpPower -= gravity;

		//_player->setY(_player->getY() - _player->getJumpPower());
		//_player->setJumpPower(_player->getJumpPower() - _player->getGravity());
	}

	// ���ȭ���� ���� ���� ������ â�� �����̶� �������� �̵� ����
	// ���ȭ���� ������ ���� ������ â�� �������̶� �������� �̵� ����
	if (_camX >= 0 || _camX + WINSIZEX <= IMAGEMANAGER->findImage("���")->getWidth() - 1150)
	{
		//playerSpeed = speed;
		_player->setSpeed(_player->getSpeed());
	}


	// 1. �簢���� �̿��ϴ� ���
	// ���� ������ �簢�� rc�� ĳ������ rc�� ���� ���(left, right, top, bottom)�� ���� ��������
	// �ش� �������� ī�޶� �̵�

	// ī�޶� �������� �̵� (����� ����������)
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
	// ī�޶� ���������� �̵� (����� ��������)
	else if (_player->getX() >= _camera.right - 40 && (KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown('Z')))
	{
		if (_camX + IMAGEMANAGER->findImage("���")->getWidth() - 1150 >= WINSIZEX)
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


	//// ī�޶� �������� �̵� (����� �Ʒ�������)
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
	//// ī�޶� �Ʒ������� �̵� (����� ��������)
	//if (_player->getY() >= _camera.bottom - 50)
	//{
	//	if (IMAGEMANAGER->findImage("���")->getHeight() >= WINSIZEY - _camY)
	//	{
	//		//_camY += jumpPower;
	//		//y = _camera.bottom - 50;
	//		_camY += _player->getJumpPower();
	//		_player->setY(_camera.bottom - 50);
	//	}
	//}



	// 2. ��ǥ���� �̿��ϴ� ���
	// ĳ������ �߽� x,y��ǥ���� ���� ��ǥ���� ���ؼ�
	// ī�޶� �̵�
}

void cameraManager::MakeObject(RECT& rect, int left, int top, int width, int height)
{
	rect.left = _camX + left;
	rect.right = rect.left + width;
	rect.top = _camY + top;
	rect.bottom = rect.top + height;

	//RendObject(rect);
}
