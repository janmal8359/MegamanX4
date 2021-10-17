#include "pch.h"
#include "Zero.h"
#include "objectManager.h"
#include "enemyManager.h"


HRESULT Zero::init()
{
	// 플레이어
	_idle = IMAGEMANAGER->addFrameImage("idle", "resources/Player/Idle.bmp", 540, 200, 6, 2, true, RGB(255, 0, 255));
	_run = IMAGEMANAGER->addFrameImage("run", "resources/Player/Run.bmp", 1824, 204, 16, 2, true, RGB(255, 0, 255));
	_jump = IMAGEMANAGER->addFrameImage("jump", "resources/Player/Jump.bmp", 1664, 332, 16, 2, true, RGB(255, 0, 255));
	_hang = IMAGEMANAGER->addFrameImage("hang", "resources/Player/Hang.bmp", 912, 284, 8, 2, true, RGB(255, 0, 255));
	_dash = IMAGEMANAGER->addFrameImage("dash", "resources/Player/Dash.bmp", 1134, 200, 9, 2, true, RGB(255, 0, 255));
	_climb = IMAGEMANAGER->addFrameImage("climb", "resources/Player/Climb.bmp", 1012, 244, 11, 2, true, RGB(255, 0, 255));
	_land = IMAGEMANAGER->addFrameImage("land", "resources/Player/Landing.bmp", 2160, 328, 15, 2, true, RGB(255, 0, 255));
	_victory = IMAGEMANAGER->addFrameImage("victory", "resources/Player/Victory.bmp", 1980, 360, 15, 2, true, RGB(255, 0, 255));

	// Attack
	_slash01 = IMAGEMANAGER->addFrameImage("slash01", "resources/Player/Slash01.bmp", 3162, 260, 17, 2, true, RGB(255, 0, 255));
	_slash02 = IMAGEMANAGER->addFrameImage("slash02", "resources/Player/Slash02.bmp", 2808, 200, 12, 2, true, RGB(255, 0, 255));
	_slash03 = IMAGEMANAGER->addFrameImage("slash03", "resources/Player/Slash03.bmp", 3330, 296, 15, 2, true, RGB(255, 0, 255));
	_airSlash = IMAGEMANAGER->addFrameImage("airSlash", "resources/Player/AirSlash.bmp", 1854, 324, 9, 2, true, RGB(255, 0, 255));
	_climbSlash = IMAGEMANAGER->addFrameImage("climbSlash", "resources/Player/ClimbSlash.bmp", 2112, 292, 11, 2, true, RGB(255, 0, 255));
	_hangSlash = IMAGEMANAGER->addFrameImage("hangSlash", "resources/Player/HangSlash.bmp", 2068, 264, 11, 2, true, RGB(255, 0, 255));

	// Hit
	_hit01 = IMAGEMANAGER->addFrameImage("hit01", "resources/Player/Hit01.bmp", 400, 236, 4, 2, true, RGB(255, 0, 255));
	_hit02 = IMAGEMANAGER->addFrameImage("hit02", "resources/Player/Hit02.bmp", 992, 252, 8, 2, true, RGB(255, 0, 255));

	// EffectImage
	IMAGEMANAGER->addImage("dash", "resources/Player/Effect/Effect_Dash.bmp", 630, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jump", "resources/Player/Effect/Effect_Hang_Jump.bmp", 288, 144, true, MAGENTA);
	IMAGEMANAGER->addImage("back", "resources/Player/Effect/Effect_Dash_Back.bmp", 896, 144, true, MAGENTA);
	IMAGEMANAGER->addImage("slide", "resources/Player/Effect/Effect_Hang_Slide.bmp", 352, 172, true, MAGENTA);

	// UI
	IMAGEMANAGER->addImage("playerHp", "resources/UI/playerHp.bmp", 15, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerHpBack", "resources/UI/playerHpBack.bmp", 15, 120, true, RGB(255, 0, 255));
	_hpBackground = IMAGEMANAGER->addImage("playerHpBar", "resources/UI/playerHpBar.bmp", 105, 186, true, RGB(255, 0, 255));

	_hpBar = new progressBar;
	_hpBar->init("playerHp", "playerHpBack", 20, 20, 15, 120);
	_hpBar->setGauge(_player.currentHP, _player.maxHP);


	_speed = 7;

	// 플레이어 초기화
	_player.direction = RIGHT;
	_player.state = IDLE;
	_player.img = _idle;
	_player.img->setFrameY(1);
	_player.x = CAMERAMANAGER->getCamX() + WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_player.width = WIDTH;
	_player.height = HEIGHT;
	_player.speed = _speed;
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
	_player.isJump = true;
	_player.onGround = false;
	_player.underJump = false;
	_player.isAttack = false;
	_player.attackCount = 0;
	_player.dashCount = 0;
	_player.gravity = GRAVITY;
	_player.maxHP = _player.currentHP = 100.f;

	_count = 0;
	_index = 7;
	check = 0;

	_line.p1 = PointMake(2405, 690);
	_line.p2 = PointMake(3010, 520);

	_isBoss = false;
	_isHit = false;

	_afterTime = TIMEMANAGER->getWorldTime();
	_afterInterval = 0.2f;

	_moveCamera = false;

	// EFfect
	EFFECTMANAGER->addEffect("lDash", "resources/Player/Effect/Effect_Dash_Left.bmp", 630, 66, 90, 66, 1, 0.5f, 1000);
	EFFECTMANAGER->addEffect("rDash", "resources/Player/Effect/Effect_Dash_Right.bmp", 630, 66, 90, 66, 1, 0.5f, 1000);
	EFFECTMANAGER->addEffect("lJump", "resources/Player/Effect/Effect_Jump_Left.bmp", 288, 72, 72, 72, 1, 0.5f, 1000);
	EFFECTMANAGER->addEffect("rJump", "resources/Player/Effect/Effect_Jump_Right.bmp", 288, 72, 72, 72, 1, 0.5f, 1000);
	EFFECTMANAGER->addEffect("lBack", "resources/Player/Effect/Effect_Back_Left.bmp", 896, 72, 112, 72, 1, 0.5f, 1000);
	EFFECTMANAGER->addEffect("rBack", "resources/Player/Effect/Effect_Back_Right.bmp", 896, 72, 112, 72, 1, 0.5f, 1000);
	EFFECTMANAGER->addEffect("lSlide", "resources/Player/Effect/Effect_Slide_Left.bmp", 352, 86, 44, 86, 1, 0.3f, 1000);
	EFFECTMANAGER->addEffect("rSlide", "resources/Player/Effect/Effect_Slide_Right.bmp", 352, 86, 44, 86, 1, 0.3f, 1000);

	return S_OK;
}

void Zero::release()
{
}

void Zero::update()
{
	bossCamera();

	if (!_moveCamera)
	{
		if (_player.state != HIT)
		{
			PlayerMove();
			Jump();
			Attack();
			Dash();
			//afterImage();
		}

		Collision();
		enemyCollision();

	}
	Animation();
	EFFECTMANAGER->update();

	_hpBar->setX(77);
	_hpBar->setY(49);
	_hpBar->setGauge(_player.currentHP, _player.maxHP);
	_hpBar->update();

	if (TIMEMANAGER->getWorldTime() >= _afterTime + _afterInterval)
	{
		_afterTime = TIMEMANAGER->getWorldTime();
	}
}

void Zero::render()
{


	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		//for (_om->getVICollider() = _om->getVCollider().begin(); _om->getVICollider() != _om->getVCollider().end(); ++_om->getVICollider())
		//{
		//	RECT rc = (*_om->getVICollider())->getRect();
		//	Rectangle(getMemDC(), rc);
		//}

		//Rectangle(getMemDC(), _player.range);
		//Rectangle(getMemDC(), _player.rc);
		//RECT rc = _em->getVBoss()[0]->getRect();
		//RECT rangeRC = _em->getVBoss()[0]->getRange();
		////Rectangle(getMemDC(), rc);
		//Rectangle(getMemDC(), rangeRC);

		char str[128];

		sprintf_s(str, "direction : %d", _player.direction);
		TextOut(getMemDC(), 10, 240, str, strlen(str));

		sprintf_s(str, "state : %d", _player.state);
		TextOut(getMemDC(), 10, 270, str, strlen(str));

		sprintf_s(str, "isGround : %d", _player.onGround);
		TextOut(getMemDC(), 10, 300, str, strlen(str));

		sprintf_s(str, "isJump : %d", _player.isJump);
		TextOut(getMemDC(), 10, 330, str, strlen(str));

		sprintf_s(str, "jumpPower : %f", _player.jumpPower);
		TextOut(getMemDC(), 10, 350, str, strlen(str));

		sprintf_s(str, "gravity : %f", _player.gravity);
		TextOut(getMemDC(), 10, 370, str, strlen(str));

		sprintf_s(str, "isAttack : %d", _player.isAttack);
		TextOut(getMemDC(), 10, 400, str, strlen(str));

		sprintf_s(str, "_camX : %d", CAMERAMANAGER->getCamX());
		TextOut(getMemDC(), 10, 430, str, strlen(str));

		sprintf_s(str, "_isHit : %d", _isHit);
		TextOut(getMemDC(), WINSIZEX - 300, 10, str, strlen(str));

		sprintf_s(str, "x : %f, y : %f", _player.x, _player.y);
		TextOut(getMemDC(), WINSIZEX - 300, 30, str, strlen(str));

		sprintf_s(str, "check : %d", check);
		TextOut(getMemDC(), WINSIZEX - 300, 50, str, strlen(str));
	}

	if (TIMEMANAGER->getWorldTime() >= _afterTime + _afterInterval)
	{
		for (int i = 0; i < AFTERMAX; i++)
		{
			//if (_after[i].img == nullptr) continue;

			_player.img->render(getMemDC(), _player.x, _player.y,
				_player.img->getFrameWidth() * _index, _player.img->getFrameHeight() * _player.img->getFrameY(),
				_player.img->getFrameWidth(), _player.img->getFrameHeight());
		}
	}

	EFFECTMANAGER->render();

	//HPEN pen;
	//HPEN oldPen;
	//
	//pen = CreatePen(PS_SOLID, 10, RGB(255, 0, 255));
	//oldPen = (HPEN)SelectObject(getMemDC(), pen);
	//LineMake(getMemDC(), CAMERAMANAGER->getCamX() + _line.p1.x, _line.p1.y, CAMERAMANAGER->getCamX() + _line.p2.x, _line.p2.y);
	//SelectObject(getMemDC(), oldPen);
	//DeleteObject(pen);

	_player.rc = RectMakeCenter(_player.x, _player.y, _player.width, _player.height);

	
	if (_player.state == ATTACK)
	{
		if (_player.direction == LEFT)
		{
			if (_player.img == _slash01) _player.img->frameRender(getMemDC(), _player.rc.right - (_player.img->getFrameWidth() - 17), _player.rc.bottom - (_player.img->getFrameHeight() - 4));
			if (_player.img == _slash02) _player.img->frameRender(getMemDC(), _player.rc.right - (_player.img->getFrameWidth() - 53), _player.rc.bottom - (_player.img->getFrameHeight() - 4));
			if (_player.img == _slash03) _player.img->frameRender(getMemDC(), _player.rc.right - (_player.img->getFrameWidth() - 21), _player.rc.bottom - (_player.img->getFrameHeight() - 20));
		}
		else
		{
			if (_player.img == _slash01) _player.img->frameRender(getMemDC(), _player.rc.right - (_player.img->getFrameWidth() - _player.width - 9), _player.rc.bottom - (_player.img->getFrameHeight() - 4));
			if (_player.img == _slash02) _player.img->frameRender(getMemDC(), _player.rc.right - (_player.img->getFrameWidth() - _player.width - 21), _player.rc.bottom - (_player.img->getFrameHeight() - 4));
			if (_player.img == _slash03) _player.img->frameRender(getMemDC(), _player.rc.right - (_player.img->getFrameWidth() - _player.width - 41), _player.rc.bottom - (_player.img->getFrameHeight() - 20));
		}
	}
	else if (_player.state == AIRATTACK)
	{
		if (_player.direction == LEFT)	_player.img->frameRender(getMemDC(), _player.rc.right - (_player.img->getFrameWidth() - 30), _player.rc.bottom - (_player.img->getFrameHeight() - 25));
		else							_player.img->frameRender(getMemDC(), _player.rc.right - (_player.img->getFrameWidth() - 95), _player.rc.bottom - (_player.img->getFrameHeight() - 25));
	}

	else if (_player.state == HANGATTACK)
	{
		if (_player.direction == LEFT)	_player.img->frameRender(getMemDC(), _player.rc.left, _player.rc.top - (_player.img->getFrameHeight() - _player.height - 10));
		else							_player.img->frameRender(getMemDC(), _player.rc.left - (_player.img->getFrameWidth() - _player.width), _player.rc.top - (_player.img->getFrameHeight() - _player.height - 10));
	}
	else _player.img->frameRender(getMemDC(), _player.rc.left - (_player.img->getFrameWidth() - _player.width) / 2, _player.rc.top - (_player.img->getFrameHeight() - _player.height) / 2);

	_hpBackground->render(getMemDC(), 50, 100);
	_hpBar->render();
}

void Zero::PlayerMove()
{
	// left
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_player.state != DASH && _player.state != ATTACK) _player.x -= _player.speed;

		// idle
		if (_player.state == IDLE)
		{
			ChangeState(LEFT, RUN, _run);
			_player.img->setFrameY(1);
			_index = _player.img->getMaxFrameX() - 2;
		}

		// run
		if (_player.direction == RIGHT && _player.state == RUN)
		{
			ChangeState(LEFT, RUN, _run);
			_player.img->setFrameY(1);
			_index = _player.img->getMaxFrameX() - 2;
		}

		// jump
		if (_player.direction == RIGHT && _player.state == JUMP)
		{
			ChangeState(LEFT, JUMP, _jump);
			_player.img->setFrameY(1);
			_player.img->setFrameX(_player.img->getMaxFrameX() - _player.img->getFrameX());
		}

		// drop
		if (_player.direction == RIGHT && _player.state == DROP)
		{
			ChangeState(LEFT, DROP, _jump);
			_player.img->setFrameY(1);
			_index = (_player.img->getMaxFrameX() - _player.img->getFrameX());
		}

		// hangjump
		if (_player.state == HANGJUMP)
		{
			if (_player.direction == RIGHT)
			{
				_xPower = 0;
			}
			//ChangeState(LEFT, HANGJUMP, _hang);
			//_player.img->setFrameY(1);
			//ChangeState(LEFT, RUN, _run, 1, 0, 0, _player.img->getMaxFrameX() - 2, false);
		}

		// hang
		if (_player.direction == RIGHT && _player.state == HANG)
		{
			_player.x -= 5;
			ChangeState(LEFT, DROP, _jump, 1, 0, GRAVITY, 8, true);
		}
		//else if (_player.direction == LEFT && _player.state == HANG)
		//{
		//	for (int i = 0; i < OBJECTMAX; i++)
		//	{
		//		RECT temp;
		//
		//		if (IntersectRect(&temp, &_player.rc, &_object[i]))
		//		{
		//			int width = temp.right - temp.left;
		//			int height = temp.bottom - temp.top;
		//
		//			if (height < width)
		//			{
		//				ChangeState(RIGHT, DROP, _jump, 0, 0, GRAVITY, 7, true);
		//			}
		//		}
		//	}
		//}

		for (int j = 0; j < _om->getVCollider().size(); j++)
		{
			RECT temp;
			RECT rc = _om->getVCollider()[j]->getRect();
		
			if (IntersectRect(&temp, &_player.rc, &rc) &&
				(_player.rc.left <= rc.right && _player.rc.left > rc.left) &&
				_player.isJump && _player.state != HANG && !_player.underJump)
			{
				int width = temp.right - temp.left;
				int height = temp.bottom - temp.top;
		
				if (height > width)
				{
					ChangeState(LEFT, HANG, _hang, 1, -1.f, 0, 7, false);
				}
			}
		}
	}
	// 키를 뗄 때
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (_player.direction == LEFT && _player.state == HANG)
		{
			ChangeState(RIGHT, DROP, _jump, 0, 0, GRAVITY, 8, true);
		}
		else if (!_player.isJump && _player.state != HANG && !_player.isAttack)
		{
			ChangeState(LEFT, IDLE, _idle);
			_player.img->setFrameY(0);
			_index = 0;
		}
		if (abs(_xPower) > 0)
		{
			_xPower = 0;
		}
		//ChangeState(LEFT, IDLE, _idle);
		//_player.img->setFrameY(0);
		//_index = 0;

		// 충돌 보정
	}

	// right
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_player.state != DASH && _player.state != ATTACK) _player.x += _player.speed;

		// idle
		if (_player.state == IDLE)
		{
			ChangeState(RIGHT, RUN, _run);
			_player.img->setFrameY(0);
			_index = 2;
		}

		// run
		if (_player.direction == LEFT && _player.state == RUN)
		{
			ChangeState(RIGHT, RUN, _run);
			_player.img->setFrameY(0);
			_index = 2;
		}

		// jump
		if (_player.direction == LEFT && _player.state == JUMP)
		{
			ChangeState(RIGHT, JUMP, _jump);
			_player.img->setFrameY(0);
			_player.img->setFrameX(_player.img->getMaxFrameX() - _player.img->getFrameX());
		}

		// drop
		if (_player.direction == LEFT && _player.state == DROP)
		{
			ChangeState(RIGHT, DROP, _jump);
			_player.img->setFrameY(0);
			_index = (_player.img->getMaxFrameX() - _player.img->getFrameX());
		}

		// hangjump
		if (_player.state == HANGJUMP)
		{
			if (_player.direction == LEFT)
			{
				_xPower = 0;
			}
			//ChangeState(LEFT, RUN, _run, 1, 0, 0, _player.img->getMaxFrameX() - 2, false);
		}

		// hang
		if (_player.direction == LEFT && _player.state == HANG)
		{
			_player.x += 5;
			ChangeState(RIGHT, DROP, _jump, 0, 0, GRAVITY, 7, true);
		}
		//else if (_player.direction == RIGHT && _player.state == HANG)
		//{
		//	for (int i = 0; i < OBJECTMAX; i++)
		//	{
		//		RECT temp;
		//
		//		if (IntersectRect(&temp, &_player.rc, &_object[i]))
		//		{
		//			int width = temp.right - temp.left;
		//			int height = temp.bottom - temp.top;
		//
		//			if (height < width)
		//			{
		//				ChangeState(LEFT, DROP, _jump, 1, 0, GRAVITY, 8, true);
		//			}
		//		}
		//	}
		//}

		for (int j = 0; j < _om->getVCollider().size(); j++)
		{
			RECT temp;
			RECT rc = _om->getVCollider()[j]->getRect();
		
			if (IntersectRect(&temp, &_player.rc, &rc) &&
				(_player.rc.right >= rc.left && _player.rc.right < rc.right) &&
				_player.isJump && _player.state != HANG && !_player.underJump)
			{
				int width = temp.right - temp.left;
				int height = temp.bottom - temp.top;
		
				if (height > width)
				{
					ChangeState(RIGHT, HANG, _hang, 0, -1.f, 0, 0, false);
				}
			}
		}
	}
	// 오른쪽 키 뗐을 때
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_player.direction == RIGHT && _player.state == HANG)
		{
			ChangeState(LEFT, DROP, _jump, 1, 0, GRAVITY, 7, true);
		}

		if (!_player.isJump && _player.state != HANG && !_player.isAttack)
		{
			ChangeState(RIGHT, IDLE, _idle);
			_player.img->setFrameY(1);
			_index = _player.img->getMaxFrameX();
		}

		if (abs(_xPower) > 0)
		{
			_xPower = 0;
		}
		//ChangeState(RIGHT, IDLE, _idle);
		//_player.img->setFrameY(1);
		//_index = _player.img->getMaxFrameX();

		// 충돌 보정
	}
}

void Zero::Jump()
{
	//// UnderJump
	//for (int i = 1; i < OBJECTMAX; i++)
	//{
	//	RECT temp;
	//
	//	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown('C') &&
	//		_player.rc.bottom < _om->getVIObject[0].top && !_player.isJump && _player.onGround)
	//	{
	//		ChangeState(_player.direction, DROP, _jump, _player.img->getFrameY(), 1.0f, GRAVITY, 7, true);
	//		_player.underJump = true;
	//	}
	//}

	//if (_player.y >= WINSIZEY - 200)
	//{
	//	ChangeState(_player.direction, IDLE, _idle);
	//	if (_player.direction == LEFT) _player.img->setFrameY(0);
	//	else _player.img->setFrameY(1);
	//	_player.jumpPower = 0;
	//	_player.gravity = 0;
	//	_player.isJump = false;
	//	_player.y = WINSIZEY - 210;
	//}

	_player.y -= _player.jumpPower;
	_player.jumpPower -= _player.gravity;

	if (KEYMANAGER->isOnceKeyDown('C') && _player.isJump == false)
	{
		//_player.img = _jump;

		// 가만히 있을 때 -> 점프
		// 뛰고 있을 때 -> 점프
		if (_player.state == IDLE || _player.state == RUN)
		{
			if (_player.direction == LEFT)
			{
				ChangeState(LEFT, JUMP, _jump);
				_player.img->setFrameY(1);
				_player.isJump = true;
				_player.onGround = false;
				_player.img->setFrameX(_player.img->getMaxFrameX());
			}
			else if (_player.direction == RIGHT)
			{
				ChangeState(RIGHT, JUMP, _jump);
				_player.img->setFrameY(0);
				_player.isJump = true;
				_player.onGround = false;
				_player.img->setFrameX(0);
			}
			_player.jumpPower = 10.0f;
			_player.gravity = GRAVITY;
		}

		// 메달리고 있을 때 -> 반대 방향으로 힘 받으면서 점프
		if (_player.state == HANG)
		{
			if (_player.direction == LEFT && KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				for (int i = 0; i < _om->getVCollider().size(); i++)
				{
					RECT temp;
					RECT rc = _om->getVCollider()[i]->getRect();
		
					if (rc.right >= _player.rc.left)
					{
						_player.rc.left = rc.right;
					}
				}
				ChangeState(LEFT, HANGJUMP, _hang, 1, 10.0f, GRAVITY, 2, true);
				EFFECTMANAGER->play("lJump", _player.x - WIDTH / 2 + 10, _player.rc.bottom);
				//_xPower = -10.0f;
				_xPower = -(_speed + 5);
			}
			else if (_player.direction == RIGHT && KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				for (int i = 0; i < _om->getVCollider().size(); i++)
				{
					RECT temp;
					RECT rc = _om->getVCollider()[i]->getRect();
		
					if (rc.left <= _player.rc.right)
					{
						_player.rc.right = rc.left;
					}
				}
				ChangeState(RIGHT, HANGJUMP, _hang, 0, 10.0f, GRAVITY, 5, true);
				EFFECTMANAGER->play("rJump", _player.x + WIDTH / 2 - 10, _player.rc.bottom);
				//_xPower = 10.0f;
				_xPower = _speed + 5;
			}
		}

	}
}
void Zero::Attack()
{
	static int aCount = 0;

	if (KEYMANAGER->isOnceKeyDown('X') && _player.attackCount != 3)
	{
		//_player.isAttack = true;

		if (_player.direction == LEFT)
		{
			_player.img->setFrameX(0);
		}
		else
		{
			_player.img->setFrameX(_player.img->getMaxFrameX());
		}

		if (_player.state == IDLE || _player.state == RUN || _player.state == ATTACK)
		{
			//if (_player.direction == LEFT)
			//{
			//	_player.img->setFrameY(0);
			//	//_player.img->setFrameX(0);
			//	_index = 0;
			//}
			//else
			//{
			//	_player.img->setFrameY(1);
			//	//_player.img->setFrameX(_player.img->getMaxFrameX());
			//	_index = _player.img->getMaxFrameX();
			//}

			// 3타
			if (_player.attackCount == 2)
			{
				ChangeState(_player.direction, ATTACK, _slash03);
				_player.isAttack = true;
				_player.attackCount = 3;
				if (_player.direction == LEFT)
				{
					_player.range = RectMake(_player.rc.left - WIDTH - 40, _player.rc.top - 30, 220, 150);
					_index = 0;
				}
				else
				{
					_player.range = RectMake(_player.rc.right - WIDTH - 20, _player.rc.top - 30, 220, 150);
					_index = _player.img->getMaxFrameX();
				}
				aCount = 0;
			}
			// 2타
			else if (_player.attackCount == 1)
			{
				ChangeState(_player.direction, ATTACK, _slash02);
				_player.isAttack = true;
				_player.attackCount = 2;
				if (_player.direction == LEFT)
				{
					_player.range = RectMake(_player.rc.left - WIDTH - 20, _player.rc.top, 230, 100);
					_index = 0;
				}
				else 
				{ 
					_player.range = RectMake(_player.rc.right - WIDTH - 50, _player.rc.top, 230, 100);
					_index = _player.img->getMaxFrameX();
				}
				aCount = 0;
			}
			// 1타
			else if (_player.attackCount == 0 && !_player.isAttack)
			{
				ChangeState(_player.direction, ATTACK, _slash01);
				_player.isAttack = true;
				_player.attackCount = 1;
				if (_player.direction == LEFT)
				{
					_player.range = RectMake(_player.rc.left - WIDTH - 10, _player.rc.top - 30, 150, 130);
					_index = 0;
				}
				else
				{
					_player.range = RectMake(_player.rc.right - WIDTH / 2 - 20, _player.rc.top - 30, 150, 130);
					_index = _player.img->getMaxFrameX();
				}
				aCount = 0;
			}
		}
		else if (_player.state == JUMP || _player.state == DROP)
		{
			// AirAttack
			ChangeState(_player.direction, AIRATTACK, _airSlash);
			if (_player.direction == LEFT) _index = 0;
			else _index = _player.img->getMaxFrameX();
			_player.isAttack = true;
			aCount = 0;
		}

		//else if (_player.state == CLIMB)
		//{
		//	// ClimbAttack
		//	ChangeState(_player.direction, CLIMBATTACK, _climbSlash);
		//	_player.isAttack = true;
		//	aCount = 0;
		//}

		else if (_player.state == HANG)
		{
			// HangAttack
			ChangeState(_player.direction, HANGATTACK, _hangSlash);
			if (_player.direction == RIGHT) _index = 0;
			else _index = _player.img->getMaxFrameX();
			_player.isAttack = true;
			aCount = 0;
		}

		//if (_player.direction == LEFT) _index = 0;
		//else _index = _player.img->getMaxFrameX();
	}

	if (_player.isAttack) aCount++;

	if (_player.state != ATTACK && _player.state != AIRATTACK && _player.state != HANGATTACK)
	{
		_player.attackCount = 0;
		_player.isAttack = false;
		aCount = 0;
	}
}

void Zero::Dash()
{
	if (KEYMANAGER->isOnceKeyDown('Z') && _player.state != DASH)
	{
		ChangeState(_player.direction, DASH, _dash);
		_player.dashCount = 0;

		_player.jumpPower = 0;
		_player.gravity = 0;

		if (_player.direction == LEFT)
		{
			_player.img->setFrameY(0);
			_index = 0;
			EFFECTMANAGER->play("lBack", _player.x + WIDTH / 2, _player.rc.bottom - 40);
		}

		else
		{
			_player.img->setFrameY(1);
			_index = _player.img->getMaxFrameX();
			EFFECTMANAGER->play("rBack", _player.x - WIDTH / 2 - 20, _player.rc.bottom - 40);
		}
	}
	if (KEYMANAGER->isStayKeyDown('Z') && _player.state == DASH)
	{
		_player.dashCount++;

		if (_player.direction == LEFT)	_player.x -= _player.speed;
		else							_player.x += _player.speed;
	}
	if (KEYMANAGER->isOnceKeyUp('Z') && _player.state == DASH)
	{
		if (_player.isJump)
		{
			ChangeState(_player.direction, DROP, _jump);
			_player.gravity = GRAVITY;
		}
		else
		{
			ChangeState(_player.direction, IDLE, _idle);
		}

		_player.dashCount = 100;

		if (_player.direction == LEFT)			_index = _player.img->getMaxFrameX() - 2;
		else if (_player.direction == RIGHT)	_index = 2;
	}

	if (_player.state == DASH)	_speed = 12;
	else						_speed = 7;

	_player.speed = _speed;
}




void Zero::Collision()
{
	for (int i = 0; i < _om->getVCollider().size(); i++)
	{
		RECT temp;
		RECT rc = _om->getVCollider()[i]->getRect();
		int width, height;


		if (IntersectRect(&temp, &_player.rc, &rc))
		{
			width = temp.right - temp.left;
			height = temp.bottom - temp.top;

			if (width > height)
			{
				check = i;
				_player.onGround = true;
			}
			else if (width < height)
			{
				check = i;
				_player.onGround = false;
			}
		}

		RECT checkRC = _om->getVCollider()[check]->getRect();

		if (((_player.rc.right < checkRC.left && _player.rc.right < checkRC.right) ||
			(_player.rc.left > checkRC.right && _player.rc.left > checkRC.left)) &&
			_player.rc.top < checkRC.top && _player.state != HANG && _player.onGround)
		{
			_player.onGround = false;
		}

		if (!IntersectRect(&temp, &_player.rc, &checkRC) && !_player.onGround && !_player.isAttack && _player.state != DASH && !_player.isHit)
		{
			_player.isJump = true;
			_player.onGround = false;
			_player.gravity = GRAVITY;
			_index = 7;
			ChangeState(_player.direction, DROP, _jump);

			if (_player.direction == LEFT)	_player.img->setFrameY(1);
			else _player.img->setFrameY(0);

		}

		//if (_player.y <= _om->getVCollider()[i]->getRect().top - 50 && (_player.state == IDLE || _player.state == RUN))
		//{
		//}
	}

	// 공중에 있을 경우 자유낙하
	for (int i = 0; i < _om->getVCollider().size(); i++)
	{
		
	}

	_player.x -= _xPower;
	if (_xPower > 0.0f) _xPower -= 0.5f;
	else if (_xPower < 0.0f) _xPower += 0.5f;

	// object collision
	for (int i = 0; i < _om->getVCollider().size(); i++)
	{
		RECT temp;
		int height = 0;
		int width = 0;
		int num = 0;
		
		RECT rc = _om->getVCollider()[i]->getRect();
		
		//if (IntersectRect(&temp, &_player.rc, &rc))
		//{
		//	height = temp.bottom - temp.top;
		//	width = temp.right - temp.left;
		//	num = i;
		//}
		
		// 위에서 밟으면(ground)
		if (/*_player.y > rc.top - 50 && _player.rc.top < rc.top &&
			_player.rc.right > rc.left && _player.rc.left < rc.right*/
			IntersectRect(&temp, &_player.rc, &rc))
		{
			height = temp.bottom - temp.top;
			width = temp.right - temp.left;

			if (height < width)
			{
				if (_player.rc.bottom >= rc.top && _player.rc.top < rc.top)
				{
					_player.isJump = false;
					_player.onGround = true;
					_player.gravity = 0;
					_player.jumpPower = 0;
					// 땅에 착지할 때 state 변경
					ChangeState(_player.direction, IDLE, _idle);
					_player.y = rc.top - HEIGHT / 2;
					_player.rc.bottom = rc.top;
					//_player.rc = RectMakeCenter(_player.x, _player.y, WIDTH, HEIGHT);

					_xPower = 0;

					check = i;
				}
				else if (_player.rc.top <= rc.bottom && _player.rc.bottom > rc.bottom)
				{
					_player.jumpPower = 0;
					ChangeState(_player.direction, DROP, _jump);
					_player.y = rc.bottom + HEIGHT / 2;
					
					if (_player.gravity <= GRAVITY) _player.gravity = GRAVITY;
				}
			}

			else if (height > width)
			{
				if (_player.rc.left <= rc.right && _player.rc.right > rc.right && _player.direction == LEFT)
				{
					_player.x = rc.right + 35;

					if (_player.isJump)
					{
						ChangeState(_player.direction, DROP, _jump);
					}
				}

				else if (_player.rc.right >= rc.left && _player.rc.left < rc.left && _player.direction == RIGHT)
				{
					_player.x = rc.left - 35;

					if (_player.isJump)
					{
						ChangeState(_player.direction, DROP, _jump);
					}
				}
			}
		
		}
		
		//// 밑 점프를 한 다음 한 개의 오브젝트를 지나가면 다시 충돌체크
		//else if (_player.rc.bottom > _om->getVCollider()[i]->getRect().bottom && _player.underJump)
		//{
		//	_player.underJump = false;
		//}
		
		//// 땅을 벗어나면 떨어짐
		//if (((_player.rc.right < rc.left && _player.rc.right < rc.right) ||
		//	(_player.rc.left > rc.right && _player.rc.left > rc.left)) &&
		//	_player.rc.top < rc.top && _player.state != HANG && _player.onGround)
		//{
		//	if (check != 0)	continue;
		//
		//	_player.gravity = GRAVITY;
		//
		//	_player.isJump = true;
		//	_player.onGround = false;
		//}
	}



}

void Zero::enemyCollision()
{
	if (_player.isAttack)
	{
		RECT temp;
		RECT emRC = _em->getVBoss()[0]->getRect();

		if (IntersectRect(&temp, &_player.range, &emRC) && !_em->getVBoss()[0]->getHit())
		{
			_em->getVBoss()[0]->setHit(true);
			_em->getVBoss()[0]->setHP(10);

			_em->getVBoss()[0]->setHitTime(TIMEMANAGER->getWorldTime());
			//_em->removeBoss(0);
			//_isHit = true;
		}
	}
}

void Zero::Animation()
{
	_count++;

	if (_count % 3 == 0)
	{
		static int c = 0;
		static int ec = 0;

		// Move
		switch (_player.state)
		{
		case IDLE:
			if (c % 3 == 0)
			{
				if (_player.direction == LEFT)
				{
					_player.img->setFrameX(_index);
					_index--;

					if (_index <= 0) _index = _player.img->getMaxFrameX();
				}
				else	// right
				{
					_player.img->setFrameX(_index);
					_index++;

					if (_index >= _player.img->getMaxFrameX()) _index = 0;
				}
			}

			c++;
			break;

		case RUN:
			if (_player.direction == LEFT)
			{
				_player.img->setFrameX(_index);
				_index--;

				if (_index <= 0) _index = _player.img->getMaxFrameX() - 2;
			}
			else	// right
			{
				_player.img->setFrameX(_index);
				_index++;

				if (_index >= _player.img->getMaxFrameX()) _index = 2;
			}

			break;

		case JUMP:
			if (_player.direction == LEFT)
			{
				if (_player.jumpPower > 0) _player.img->setFrameX(_player.img->getFrameX() - 1);

				if (_player.img->getFrameX() < 2 && _player.jumpPower <= 0) _player.img->setFrameX(6);
			}
			else	// right
			{
				if (_player.jumpPower > 0) _player.img->setFrameX(_player.img->getFrameX() + 1);

				if (_player.img->getFrameX() > _player.img->getMaxFrameX() - 2 && _player.jumpPower <= 0) _player.img->setFrameX(9);
			}

			break;

		case HANG:

			if (_player.direction == LEFT)
			{
				if (ec % 5 == 0)
				{
					EFFECTMANAGER->play("lSlide", _player.x - WIDTH / 2 + 10, _player.rc.bottom - 20);
					ec = 0;
				}
				//if (_player.img != _hang) _player.img = _hang;
				_player.img->setFrameX(_index);
				if (_index > 4)
				{
					_index--;
				}
			}
			else	// right
			{
				if (ec % 5 == 0)
				{
					EFFECTMANAGER->play("rSlide", _player.x + WIDTH / 2 - 10, _player.rc.bottom - 20);
					ec = 0;
				}
				_player.img->setFrameX(_index);
				if (_index < _player.img->getMaxFrameX() - 4)
				{
					_index++;
				}
			}

			ec++;

			//if (_index <= 0) _index = _player.img->getMaxFrameX();
			break;

		case DROP:
			if (_player.direction == LEFT)
			{
				_player.img->setFrameX(_index);
				_index--;

				if (_index <= 4) _index = 7;
			}
			else	// right
			{
				_player.img->setFrameX(_index);
				_index++;

				if (_index >= 11) _index = 8;
			}

			break;

		case HANGJUMP:
			if (_player.direction == LEFT)
			{
				_player.img->setFrameX(_index);
				if (_index > 0) _index--;

				if (_player.img->getFrameX() <= 0)
				{
					ChangeState(LEFT, DROP, _jump);
					_player.img->setFrameY(1);
					_index = 7;
				}
			}
			else	// right
			{
				_player.img->setFrameX(_index);
				if (_index < _player.img->getMaxFrameX()) _index++;

				if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
				{
					ChangeState(RIGHT, DROP, _jump);
					_player.img->setFrameY(0);
					_index = 8;
				}
			}
			break;

		case DASH:
			if (_player.direction == LEFT)
			{
				_player.img->setFrameX(_index);
				if (_index < _player.img->getMaxFrameX()) _index++;

				if (_index == 2)
				{
					EFFECTMANAGER->play("lDash", _player.x + WIDTH / 2, _player.rc.bottom - 20);
				}

				if (_player.dashCount < 30)
				{
					if (_index >= 5) _index = 2;
				}
				if (_index >= _player.img->getMaxFrameX())
				{
					ChangeState(_player.direction, IDLE, _idle);
					_player.img->setFrameY(0);
					_index = 0;
					_player.dashCount = 0;
				}
			}
			else
			{
				_player.img->setFrameX(_index);
				if (_index > 0) _index--;

				if (_index == 6)
				{
					EFFECTMANAGER->play("rDash", _player.x - WIDTH / 2 - 10, _player.rc.bottom - 20);
				}

				if (_player.dashCount < 30)
				{
					if (_index <= 3) _index = 6;
				}
				if (_index <= 0)
				{
					ChangeState(_player.direction, IDLE, _idle);
					_player.img->setFrameY(1);
					_index = _player.img->getMaxFrameX();
					_player.dashCount = 0;
				}
			}
			break;
		case LAND:
			break;

		case HIT:
			_player.jumpPower = 0;
			_player.gravity = 0;
			if (c % 2 == 0)
			{
				if (_player.direction == LEFT)
				{
					_player.img->setFrameY(1);
					_player.img->setFrameX(_index);
					if (_index > 0) _index--;

					if (_index <= 0)
					{
						ChangeState(_player.direction, IDLE, _idle);
						_player.img->setFrameY(0);
						_index = 0;
						_player.isHit = false;
					}
				}
				else
				{
					_player.img->setFrameY(0);
					_player.img->setFrameX(_index);

					if (_index < _player.img->getMaxFrameX()) _index++;

					if (_index >= _player.img->getMaxFrameX())
					{
						ChangeState(_player.direction, IDLE, _idle);
						_player.img->setFrameY(1);
						_index = _player.img->getMaxFrameX();
						_player.isHit = false;
					}
				}
			}
			c++;

			break;

		}

		_count = 0;
	}

	static int cc = 0;
	if (cc % 2 == 0)
	{
		// Attack
		switch (_player.state)
		{
		case ATTACK:
			if (_player.direction == LEFT)
			{

				_player.img->setFrameY(0);
				_player.img->setFrameX(_index);
				if (_index < _player.img->getMaxFrameX()) _index++;

				if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
				{
					ChangeState(_player.direction, IDLE, _idle);
					_player.img->setFrameY(0);
					_index = 0;
				}
			}
			else
			{
				_player.img->setFrameY(1);
				_player.img->setFrameX(_index);
				if (_index > 0) _index--;

				if (_player.img->getFrameX() <= 0)
				{
					ChangeState(_player.direction, IDLE, _idle);
					_player.img->setFrameY(1);
					_index = _player.img->getMaxFrameX();
				}
			}
			break;
		case AIRATTACK:
			if (_player.direction == LEFT)
			{
				_player.img->setFrameY(0);
				_player.img->setFrameX(_index);
				if (_index < _player.img->getMaxFrameX()) _index++;

				if (_index >= _player.img->getMaxFrameX())
				{
					ChangeState(_player.direction, JUMP, _jump);
					_player.img->setFrameY(1);
					_index = 0;
				}
			}
			else
			{
				_player.img->setFrameY(1);
				_player.img->setFrameX(_index);
				if (_index > 0) _index--;

				if (_index <= 0)
				{
					ChangeState(_player.direction, JUMP, _jump);
					_player.img->setFrameY(0);
					_index = _player.img->getMaxFrameX();
				}
			}
			break;
		case HANGATTACK:
			if (_player.direction == LEFT)
			{
				_player.img->setFrameY(1);
				_player.img->setFrameX(_index);
				if (_index > 0) _index--;

				if (_index <= 0)
				{
					ChangeState(_player.direction, HANG, _hang);
					_player.img->setFrameY(1);
					_index = _player.img->getMaxFrameX() - 4;
				}
			}
			else
			{
				_player.img->setFrameY(0);
				_player.img->setFrameX(_index);
				if (_index < _player.img->getMaxFrameX()) _index++;

				if (_index >= _player.img->getMaxFrameX())
				{
					ChangeState(_player.direction, HANG, _hang);
					_player.img->setFrameY(0);
					_index = 4;
				}
			}
			break;
		case CLIMBATTACK:
			if (_player.direction == LEFT)
			{
				_player.img->setFrameY(0);
				_player.img->setFrameX(_index);
				if (_index < _player.img->getMaxFrameX()) _index++;

				if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
				{
					ChangeState(_player.direction, CLIMB, _climb);
					_player.img->setFrameY(0);
					_index = 5;
				}
			}
			else
			{
				_player.img->setFrameY(1);
				_player.img->setFrameX(_index);
				if (_index > 0) _index--;

				if (_player.img->getFrameX() <= 0)
				{
					ChangeState(_player.direction, CLIMB, _climb);
					_player.img->setFrameY(1);
					_index = _player.img->getMaxFrameX() - 5;
				}
			}
			break;
		}
	}
	cc++;

}

void Zero::hpManagement()
{
	if (_player.currentHP <= 0)
	{
		_player.currentHP = 0;
		
	}
}

void Zero::afterImage()
{
	if (TIMEMANAGER->getWorldTime() >= _afterTime + _afterInterval)
	{
		_after[0].img = _player.img;
		//_after[0].x = _player.x;
		//_after[0].y = _player.y;
		_after[0].frameX = _index;
		_after[0].frameX = _player.img->getFrameY();

		for (int i = AFTERMAX - 1; i >= 0; i--)
		{
			if (_after[i].img == nullptr) continue;

			_after[i + 1].img = _after[i].img;
			//_after[i + 1].x = _after[i].x;
			//_after[i + 1].y = _after[i].y;
			_after[i + 1].frameX = _after[i].frameX;
			_after[i + 1].frameY = _after[i].frameY;
		}

		_afterTime = TIMEMANAGER->getWorldTime();
	}
}

void Zero::bossCamera()
{
	//if (_isBoss && CAMERAMANAGER->getCamX() != 12000)
	//{
	//	_moveCamera = true;
	//}
	static bool isisisis = false;

	if (CAMERAMANAGER->getCamX() == -12000 && !isisisis)
	{
		isisisis = true;
		_moveCamera = false;
		_isBoss = true;
		_em->getVBoss()[0]->setStart(true);
		_em->getVBoss()[0]->setX(1000);
	}

	if (_moveCamera)
	{
		if (CAMERAMANAGER->getCamX() >= -12000)
		{
			CAMERAMANAGER->setCamX(CAMERAMANAGER->getCamX() - 5);
		}
		else
		{
			CAMERAMANAGER->setCamX(-12000);
		}
		if (_player.x >= 200)
		{
			_player.x -= 5;
		}
	}
}

void Zero::ChangeState(PLAYERDIRECTION direction, PLAYERSTATE state, image* img, int frameY, float jumpPower, float gravity, int index, bool jump)
{
	_player.direction = direction;
	_player.lastState = _player.state;
	_player.state = state;
	_player.img = img;
	_player.img->setFrameY(frameY);
	_player.jumpPower = jumpPower;
	_player.gravity = gravity;
	_player.isJump = jump;
	_index = index;
}

void Zero::ChangeState(PLAYERDIRECTION direction, PLAYERSTATE state, image* img)
{
	_player.direction = direction;
	_player.lastState = _player.state;
	_player.state = state;
	_player.img = img;
}