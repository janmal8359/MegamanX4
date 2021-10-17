#include "pch.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(string topKey, string bottomKey, int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	top = topKey;
	bottom = bottomKey;

	_rcProgress = RectMake(x, y, width, height);
	//IMAGEMANAGER->addImage("playerHp", "resources/UI/playerHp.bmp", width, height, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("playerHpBar", "resources/UI/enemyHp.bmp", width, height, true, RGB(255, 0, 255));

	//_progressBarTop = IMAGEMANAGER->addImage("frontBar", "hpBarTop.bmp", width, height, true, RGB(255, 0, 255));
	//_progressBarBottom = IMAGEMANAGER->addImage("backBar", "hpBarBottom.bmp", width, height, true, RGB(255, 0, 255));

	_progressBarTop = IMAGEMANAGER->findImage(topKey);
	_progressBarBottom = IMAGEMANAGER->findImage(bottomKey);

	_width = _progressBarTop->getWidth();
	_height = _progressBarTop->getHeight();

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->getWidth(),
		_progressBarTop->getHeight());
}

void progressBar::render()
{
	IMAGEMANAGER->render(bottom, getMemDC(),
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	IMAGEMANAGER->render(top, getMemDC(), 
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() * 1.5f - _height, 0, 0,
		_progressBarBottom->getWidth(), _height);
}

//게이지 조절하는 함수
void progressBar::setGauge(float currentGauge, float maxGauge)
{
	current = currentGauge;
	max = maxGauge;

	//이해 안가신다면 외우셔도 좋습니다 *-_-*
	_height = (currentGauge / maxGauge) * _progressBarBottom->getHeight();

}
