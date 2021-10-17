#include "pch.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기에다 해라!!!
HRESULT playGround::init()
{
	gameNode::init(true);

	// 배경
	_background = IMAGEMANAGER->addImage("배경", "resources/background/Background.bmp", 13200, 800, true, RGB(255, 0, 255));

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

//메모리 해제는 여기다 해라!!!!
void playGround::release()
{
	gameNode::release();


}

//연산처리는 여기다가!
void playGround::update()
{
	gameNode::update();

	//if (_player->getBoss() && _em->getVBoss()[0]->getStart())
	//{
	//	// 카메라 이동 후 고정
	//	// 보스 생성
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

//여기다 그려줘라!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//==============위에는 제발 건드리지 마라 ============

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

	//=============== 밑에도 건들지마라 ================
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