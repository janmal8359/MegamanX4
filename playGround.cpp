#include "pch.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ���⿡�� �ض�!!!
HRESULT playGround::init()
{
	gameNode::init(true);

	// ���
	_background = IMAGEMANAGER->addImage("���", "resources/background/Background.bmp", 13200, 800, true, RGB(255, 0, 255));

	_player = new Zero;
	_player->init();

	_om = new objectManager;
	_om->init();
	_om->setCollider();

	_em = new enemyManager;

	_em->init();
	_em->setBoss(13000);

	//_enemy = new enemy;
	//_enemy->init();

	CAMERAMANAGER->setPlayerMemoryAddressLink(_player);
	_player->setOmMemoryAddressLink(_om);
	_player->setEmMemoryAddressLink(_em);
	_em->setPlayerMemoryAddressLink(_player);
	//_enemy->setPlayerMemoryAddressLink(_player);

	//CAMERAMANAGER->setCamX(-12000);

	return S_OK;
}

//�޸� ������ ����� �ض�!!!!
void playGround::release()
{
	gameNode::release();


}

//����ó���� ����ٰ�!
void playGround::update()
{
	gameNode::update();

	//if (_player->getBoss() && _em->getVBoss()[0]->getStart())
	//{
	//	// ī�޶� �̵� �� ����
	//	// ���� ����
	//	//_em->setBoss(1000);
	//}

	RECT temp;
	RECT plRC = _player->getRect();
	RECT omRC = _om->getVCollider()[35]->getRect();

	if (IntersectRect(&temp, &plRC, &omRC) && !_player->getBoss())
	{
		_player->setMoveCamera(true);
	}

	if (!_player->getBoss()) CAMERAMANAGER->CameraMove();

	_player->update();
	_om->update();
	_em->update();
}

//����� �׷����!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//==============������ ���� �ǵ帮�� ���� ============

	_background->render(getMemDC(), CAMERAMANAGER->getCamX(), CAMERAMANAGER->getCamY());
	_om->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		char str[128];

		sprintf_s(str, "x : %d, y : %d", _ptMouse.x, _ptMouse.y);
		TextOut(getMemDC(), 10, 10, str, strlen(str));

		sprintf_s(str, "_pHP : %f, _eHP : %f", _player->getHP(), _em->getVBoss()[0]->getHP());
		TextOut(getMemDC(), 300, 30, str, strlen(str));


		TIMEMANAGER->render(getMemDC());

		RECT rc = CAMERAMANAGER->getCamera();
		Rectangle(getMemDC(), rc);
	}
	_player->render();
	_em->render();

	//=============== �ؿ��� �ǵ������� ================
	_backBuffer->render(getHDC(), 0, 0);

}

void playGround::SetCamera(RECT& camera, int left, int top, int width, int height)
{
	camera.left = left;
	camera.right = _camera.left + width;
	camera.top = top;
	camera.bottom = _camera.top + height;
}

void playGround::MakeGround(RECT& rect, int left, int right, int top, int bottom)
{
	rect.left = left;
	rect.right = right;
	rect.top = top;
	rect.bottom = bottom;

	RendObject(rect);
}

void playGround::MakeObject(RECT& rect, int left, int top, int width, int height)
{
	rect.left = _camX + left;
	rect.right = rect.left + width;
	rect.top = _camY + top;
	rect.bottom = rect.top + height;

	RendObject(rect);
}

void playGround::RendObject(RECT rect[], int max)
{
	for (int i = 0; i < max; i++)
	{
		rect[i] = RectMake(rect[i].left, rect[i].top, rect[i].right - rect[i].left, rect[i].bottom - rect[i].top);
	}
}

void playGround::RendObject(RECT& rect)
{
	rect = RectMake(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
}