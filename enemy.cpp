#include "pch.h"
#include "enemy.h"
#include "Zero.h"

HRESULT enemy::init()
{
	//_idle = IMAGEMANAGER->addFrameImage("idle_e", "resources/Enemy/Boss/Colonel_Idle.bmp", 558, 292, 3, 2, true, RGB(255, 0, 255));
	//_move = IMAGEMANAGER->addFrameImage("move_e", "resources/Enemy/Boss/Colonel_FadeOut.bmp", 696, 264, 4, 2, true, RGB(255, 0, 255));
	//_ready = IMAGEMANAGER->addFrameImage("ready_e", "resources/Enemy/Boss/Colonel_StandBy.bmp", 252, 304, 2, 2, true, RGB(255, 0, 255));
	//_slash = IMAGEMANAGER->addFrameImage("slash_e", "resources/Enemy/Boss/Colonel_Idle.bmp", 3058, 416, 11, 2, true, RGB(255, 0, 255));
	//_fade = IMAGEMANAGER->addFrameImage("fade_e", "resources/Enemy/Boss/Colonel_FadeOut.bmp", 696, 264, 4, 2, true, RGB(255, 0, 255));
	//_die = IMAGEMANAGER->addFrameImage("die_e", "resources/Enemy/Boss/Colonel_Lose.bmp", 136, 232, 3, 2, true, RGB(255, 0, 255));

	return S_OK;
}

HRESULT enemy::init(const char* imageName, POINT position)
{
	_eIdle = IMAGEMANAGER->addFrameImage("eIdle", "resources/Enemy/Boss/Colonel_Idle.bmp", 558, 292, 3, 2, true, RGB(255, 0, 255));
	_eMove = IMAGEMANAGER->addFrameImage("eMove", "resources/Enemy/Boss/Colonel_FadeOut.bmp", 696, 264, 4, 2, true, RGB(255, 0, 255));
	_eReady = IMAGEMANAGER->addFrameImage("eReady", "resources/Enemy/Boss/Colonel_StandBy.bmp", 252, 304, 2, 2, true, RGB(255, 0, 255));
	_eSlash = IMAGEMANAGER->addFrameImage("eSlash", "resources/Enemy/Boss/Colonel_Slash.bmp", 3058, 416, 11, 2, true, RGB(255, 0, 255));
	_eFade = IMAGEMANAGER->addFrameImage("eFade", "resources/Enemy/Boss/Colonel_FadeOut.bmp", 696, 264, 4, 2, true, RGB(255, 0, 255));
	_eDie = IMAGEMANAGER->addFrameImage("eDie", "resources/Enemy/Boss/Colonel_Lose.bmp", 136, 232, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("auraBlade", "resources/Enemy/Boss/auraBlade.bmp", 192, 232, 3, 2, true, MAGENTA);

	IMAGEMANAGER->addImage("enemyHp", "resources/UI/enemyHp.bmp", 15, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemyHpBack", "resources/UI/enemyHpBack.bmp", 15, 144, true, RGB(255, 0, 255));
	_hpBackground = IMAGEMANAGER->addImage("enemyHpBar", "resources/UI/enemyHpBar.bmp", 78, 216, true, RGB(255, 0, 255));

	_hpBar = new progressBar;
	_hpBar->init("enemyHp", "enemyHpBack", WINSIZEX - 20, 20, 15, 144);
	_hpBar->setGauge(_boss.currentHP, _boss.maxHP);

	_boss.currentFrameX = _boss.currentFrameY = 0;
	_boss.count = 0;

	_boss.rndPattern = 0;

	_boss.direction = eLEFT;
	_boss.state = eIDLE;
	_boss.img = IMAGEMANAGER->findImage(imageName);

	_boss.isAttack = false;
	_boss.attackCount = 0;
	
	_boss.x = position.x;
	_boss.y = position.y;

	_boss.rc = RectMakeCenter(position.x, position.y, _boss.img->getFrameWidth(), _boss.img->getFrameHeight());

	_boss.attackInterval = 1.0f;
	_boss.fadeInterval = 2;
	_boss.hitInterval = 0.5f;

	_boss.maxHP = _boss.currentHP = 100.f;

	_isStart = false;


	// bullet
	_auraBlade = new hellFire;
	_auraBlade->init(3, 1200);
	_auraBlade->setEnemyMemoryAddressLink(this);

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	//if (_player->getBoss()) _isStart = true;

	if (_boss.state != eDIE && _isStart)
	{
		hpManagement();
		animation();
		pattern();
		collision();
		bulletCollision();


		_hpBar->setX(WINSIZEX - 100);
		_hpBar->setY(17);
		_hpBar->setGauge(_boss.currentHP, _boss.maxHP);
		_hpBar->update();
	}

	_auraBlade->update();
}

void enemy::render()
{
	draw();

	if (_boss.state != eDIE && _isStart)
	{
		_hpBackground->render(getMemDC(), WINSIZEX - 130, 80);
		_hpBar->render();
	}
	_auraBlade->render();
}

void enemy::animation()
{
	_boss.count++;

	//if (_boss.count % 2 == 0)
	//{
	//	if (_boss.currentFrameX >= _boss.img->getMaxFrameX()) _boss.currentFrameX = 0;
	//
	//	_boss.img->setFrameX(_boss.currentFrameX);
	//	_boss.currentFrameX++;
	//
	//	_boss.count = 0;
	//}

	////////////////////////////////////////////////////////////////////////////////////////////////

	static int c = 0;


	if (_boss.count % 3 == 0)
	{
		_boss.count = 0;

		_boss.img->setFrameX(_boss.currentFrameX);

		switch (_boss.state)
		{
		case eIDLE:
			if (_boss.direction == eLEFT)
			{
				_boss.currentFrameX++;

				if (_boss.currentFrameX >= _boss.img->getMaxFrameX()) _boss.currentFrameX = 0;
			}
			else
			{
				_boss.currentFrameX--;

				if (_boss.currentFrameX <= 0) _boss.currentFrameX = _boss.img->getMaxFrameX();
			}
			break;
		case eMOVE:
			if (_boss.direction == eLEFT)
			{
				_boss.currentFrameX++;

				if (_boss.currentFrameX >= _boss.img->getMaxFrameX()) _boss.currentFrameX = 0;
			}
			else
			{
				_boss.currentFrameX--;

				if (_boss.currentFrameX <= 0) _boss.currentFrameX = _boss.img->getMaxFrameX();
			}
			break;
		case eREADY:
			if (_boss.direction == eLEFT)
			{
				_boss.currentFrameX++;

				if (_boss.currentFrameX >= _boss.img->getMaxFrameX()) _boss.currentFrameX = 0;
			}
			else
			{
				_boss.currentFrameX--;

				if (_boss.currentFrameX <= 0) _boss.currentFrameX = _boss.img->getMaxFrameX();
			}
			break;
		case eSLASH:
			if (c % 3 == 0)
			{
				if (_boss.direction == eLEFT)
				{
					_boss.currentFrameX++;

					if (_boss.currentFrameX == 2)
					{
						//_auraBlade->fire(_boss.rc.left - _boss.img->getWidth(), _boss.rc.top + _boss.img->getHeight());
						_auraBlade->fire(_boss.x, _boss.rc.top + 50);
					}
					else if (_boss.currentFrameX == 8)
					{
						_auraBlade->fire(_boss.x, _boss.rc.bottom - 50);
					}

					if (_boss.currentFrameX >= _boss.img->getMaxFrameX())
					{
						_boss.isAttack = false;
						_boss.state = eIDLE;
						_boss.img = _eIdle;
						_boss.currentFrameX = 0;
					}
				}
				else
				{
					_boss.currentFrameX--;

					if (_boss.currentFrameX == 2)
					{
						//_auraBlade->fire(_boss.rc.left + _boss.img->getWidth(), _boss.rc.top + _boss.img->getHeight());
						_auraBlade->fire(_boss.x, _boss.rc.bottom - 50);
					}
					else if (_boss.currentFrameX == 8)
					{
						_auraBlade->fire(_boss.x, _boss.rc.top + 50);
					}

					if (_boss.currentFrameX <= 0)
					{
						_boss.isAttack = false;
						_boss.state = eIDLE;
						_boss.img = _eIdle;
						_boss.currentFrameX = _boss.img->getMaxFrameX();
					}
				}
			}
			c++;
			break;
		case eFADESLASH:
			if (_boss.direction == eLEFT)
			{
				if (_boss.currentFrameX < _boss.img->getMaxFrameX()) _boss.currentFrameX++;

				if (_boss.currentFrameX >= _boss.img->getMaxFrameX())
				{
					_boss.isAttack = false;
					//_deltaTime = TIMEMANAGER->getWorldTime();
				}
			}
			else
			{
				if (_boss.currentFrameX > 0) _boss.currentFrameX--;

				if (_boss.currentFrameX <= 0)
				{
					_boss.isAttack = false;
					//_deltaTime = TIMEMANAGER->getWorldTime();
				}
			}
			break;
		case eFADE:
			if (c % 2 == 0)
			{
				if (_boss.direction == eLEFT)
				{
					_boss.currentFrameX++;

					if (_boss.currentFrameX >= _boss.img->getMaxFrameX()) _boss.x = 1400;// _boss.currentFrameX = 0;
				}
				else
				{
					_boss.currentFrameX--;

					if (_boss.currentFrameX <= 0) _boss.x = 1400;// _boss.currentFrameX = _boss.img->getMaxFrameX();
				}
			}
			c++;
			break;
		case eDIE:
			//_boss.x = 1000;
			//_boss.direction = eLEFT;

			if (_boss.direction == eLEFT)
			{
				_boss.currentFrameX++;

				if (_boss.currentFrameX >= _boss.img->getMaxFrameX()) _boss.currentFrameX = 0;
			}
			else
			{
				_boss.currentFrameX--;

				if (_boss.currentFrameX <= 0) _boss.currentFrameX = _boss.img->getMaxFrameX();
			}
			break;
		}
	}
}

void enemy::pattern()
{
	//_auraBlade->fire(_boss.x, _boss.rc.top);

	if (_boss.isHit && TIMEMANAGER->getWorldTime() >= _hitTime + _boss.hitInterval)
	{
		_boss.isHit = false;
	}

	if (!_isTimeCheck)
	{
		_deltaTime = TIMEMANAGER->getWorldTime();
		_isTimeCheck = true;
	}

	if (TIMEMANAGER->getWorldTime() >= _deltaTime + _boss.fadeInterval)
	{
		_boss.rndPattern = RND->getFromIntTo(1, 3);		// 1 or 2
		// 1번 패턴 - 맵 가장자리에서 검기날리기
		// 2번 패턴 - 사라졌다가 캐릭터 옆에 나타나서 베기


		if (!_boss.isFade && _boss.state == eIDLE)
		{
			_boss.state = eFADE;
			_boss.img = _eFade;
			_boss.currentFrameX = 0;
			_boss.isFade = true;

			_deltaTime = TIMEMANAGER->getWorldTime();
		}
	}

	if (_boss.state == eFADE)
	{
		if (_boss.direction == LEFT && _boss.currentFrameX >= _boss.img->getMaxFrameX()) _boss.x = 1400;
		else if (_boss.direction == RIGHT && _boss.currentFrameX <= 0) _boss.x = 1400;
	}

	if (_boss.state == eFADESLASH)
	{
		if (TIMEMANAGER->getWorldTime() >= _deltaTime + _boss.attackInterval && !_boss.isFade)
		{
			_boss.state = eFADE;
			_boss.img = _eFade;

			_boss.isFade = true;

			if (_boss.direction == eLEFT) _boss.currentFrameX = 0;
			else _boss.currentFrameX = _boss.img->getMaxFrameX();

			_deltaTime = TIMEMANAGER->getWorldTime();
		}
	}

	if (_boss.state == eSLASH)
	{
		if (TIMEMANAGER->getWorldTime() >= _deltaTime + 3 && !_boss.isFade)
		{
			_boss.state = eFADE;
			_boss.img = _eFade;

			_boss.isFade = true;

			if (_boss.direction == eLEFT) _boss.currentFrameX = 0;
			else _boss.currentFrameX = _boss.img->getMaxFrameX();

			_deltaTime = TIMEMANAGER->getWorldTime();
		}
	}

	switch (_boss.rndPattern)
	{
	case 1:
		if (TIMEMANAGER->getWorldTime() >= _deltaTime + _boss.fadeInterval && _boss.isFade)
		{
			_boss.state = eSLASH;
			_boss.img = _eSlash;

			if (_player->getX() < WINSIZEX / 2)
			{
				_boss.direction = eLEFT;
				_boss.x = 1000;
				_attackTime = TIMEMANAGER->getWorldTime();
				//_auraBlade->fire(_boss.x, _boss.rc.top);
			}
			else
			{
				_boss.direction = eRIGHT;
				_boss.x = 200;
				_attackTime = TIMEMANAGER->getWorldTime();
				//_auraBlade->fire(_boss.x, _boss.rc.top);
			}

			if (_boss.direction == eLEFT) _boss.currentFrameX = 0;
			else _boss.currentFrameX = _boss.img->getMaxFrameX();

			_deltaTime = TIMEMANAGER->getWorldTime();
			_boss.isAttack = true;
			_boss.isFade = false;
		}
		break;
	case 2:
		if (TIMEMANAGER->getWorldTime() >= _deltaTime + _boss.fadeInterval && _boss.isFade)
		{
			_boss.state = eFADESLASH;
			_boss.img = _eSlash;

			if (_player->getX() < WINSIZEX / 2)
			{
				_boss.direction = eLEFT;
				_boss.x = _player->getX() + 100;
				_attackTime = TIMEMANAGER->getWorldTime();
				//_boss.range = RectMakeCenter(_boss.rc.left - 40, _boss.y, 100, 80);
			}
			else
			{
				_boss.direction = eRIGHT;
				_boss.x = _player->getX() - 100;
				_attackTime = TIMEMANAGER->getWorldTime();
				//_boss.range = RectMakeCenter(_boss.rc.right - 40, _boss.y, 100, 80);
			}

			if (TIMEMANAGER->getWorldTime() >= _attackTime + _boss.attackInterval)
			{
				if (_boss.direction == eLEFT) _boss.range = RectMakeCenter(_boss.rc.left - 40, _boss.y, 100, 80);
				else _boss.range = RectMakeCenter(_boss.rc.right - 40, _boss.y, 100, 80);
			}

			if (_boss.direction == eLEFT) _boss.currentFrameX = 6;
			else _boss.currentFrameX = _boss.img->getMaxFrameX() - 6;

			_deltaTime = TIMEMANAGER->getWorldTime();
			_boss.isAttack = true;

			_boss.isFade = false;
		}
		break;
	default:
		break;
	}
}

void enemy::draw()
{
	if (_boss.direction == eLEFT) _boss.img->frameRender(getMemDC(), _boss.rc.left, _boss.rc.top, _boss.currentFrameX, 0);
	else if (_boss.direction == eRIGHT) _boss.img->frameRender(getMemDC(), _boss.rc.left, _boss.rc.top, _boss.currentFrameX, 1);

	_boss.rc = RectMakeCenter(_boss.x, _boss.y, _boss.img->getFrameWidth(), _boss.img->getFrameHeight());
	
	if (_boss.isAttack)
	{
		if (_boss.direction == eLEFT) _boss.range = RectMakeCenter(_boss.rc.left + 40, _boss.y, 100, 80);
		else _boss.range = RectMakeCenter(_boss.rc.right - 40, _boss.y, 100, 80);
	}

	//Rectangle(getMemDC(), _boss.range);

	//_boss.img->frameRender(getMemDC(), _boss.rc.left, _boss.rc.top, _boss.currentFrameX, _boss.currentFrameY);
}

void enemy::collision()
{
	if (_boss.isAttack)
	{
		RECT temp;
		RECT plRC = _player->getRect();

		if (IntersectRect(&temp, &_boss.range, &plRC) && !_player->getHit() && _boss.state == eFADESLASH)
		{
			_player->setState(13);
			_player->setHP(10.f);
			_player->setDirection((int)_boss.direction);
			_player->setImage(IMAGEMANAGER->findImage("hit02"));
			_player->setHit(true);
			if (_boss.direction == eLEFT)
			{
				_player->setIndex(_player->getImage()->getMaxFrameX());
				_player->setXPower(3.f);
			}
			else
			{
				_player->setIndex(0);
				_player->setXPower(-3.f);
			}

			_boss.isAttack = false;
		}
	}
}

void enemy::bulletCollision()
{
	for (int i = 0; i < _auraBlade->getVBullet().size(); i++)
	{
		RECT temp;
		RECT rc = _player->getRect();

		if (IntersectRect(&temp, &_auraBlade->getVBullet()[i].rc, &rc))
		{
			_auraBlade->removeMissile(i);

			_player->setHP(15);
			_player->setState(13);
			_player->setDirection((int)_boss.direction);
			_player->setImage(IMAGEMANAGER->findImage("hit02"));
			_player->setHit(true);

			if (_boss.direction == eLEFT)
			{
				_player->setIndex(_player->getImage()->getMaxFrameX());
				_player->setXPower(3.f);
			}
			else
			{
				_player->setIndex(0);
				_player->setXPower(-3.f);
			}

			break;
		}
	}
}

void enemy::hpManagement()
{
	if (_boss.currentHP <= 0)
	{
		_boss.currentHP = 0;
		_boss.state = eDIE;
		_boss.img = _eDie;

		_boss.x = 1000;
		_boss.direction = eLEFT;
		
		if (_boss.direction == eLEFT) _boss.currentFrameX = 0;
		else _boss.currentFrameX = _boss.img->getMaxFrameX();
	}
}
