#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "bullets.h"

#define WHITE RGB(255, 255, 255)

class Zero;

enum ENEMYSTATE
{
	eIDLE,			// ���
	eMOVE,			// ���� �̵�
	eREADY,
	eSLASH,			// ���鼭 �˱� ������
	eFADESLASH,		// ��Ÿ���鼭 ����
	eTHUNDER,		//
	eFADE,			// �������
	eDIE				// �й�
};

enum ENEMYDIRECTION
{
	eLEFT,
	eRIGHT
};

struct boss
{
	image* img;
	RECT rc;
	RECT range;
	ENEMYSTATE state;
	ENEMYDIRECTION direction;
	float x, y;
	bool isHit;
	float speed;
	float currentHP;
	float maxHP;

	int count;		// Frame Count;
	int index;
	int rndPattern;
	int attackCount;

	float fadeX, fadeY;		// ������� ��ġ�� �ӽ� ��ǥ

	int currentFrameX;
	int currentFrameY;

	bool isAttack;
	bool isFade;

	//int attackCount;

	float attackInterval;
	float fadeInterval;
	float hitInterval;
};

class enemy : public gameNode
{
protected:
	// iamge
	image* _eIdle;
	image* _eMove;
	image* _eReady;
	image* _eSlash;
	image* _eFade;
	image* _eDie;

	// struct
	boss _boss;

	RGBTRIPLE _originRGB;		// �̹����� ���� �÷�

	// float
	float _deltaTime;
	float _attackTime;
	float _hitTime;

	// class
	Zero* _player;
	progressBar* _hpBar;
	image* _hpBackground;
	hellFire* _auraBlade;

	// bool
	bool _isTimeCheck;

	bool _isStart;

public:
	enemy() {}
	~enemy() {}

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void animation();
	void pattern();
	void draw();


	void collision();
	void bulletCollision();

	void hpManagement();

	// get
	inline RECT getRect() { return _boss.rc; }
	inline RECT getRange() { return _boss.range; }
	inline float getHP() { return _boss.currentHP; }
	inline bool getHit() { return _boss.isHit; }
	inline bool getStart() { return _isStart; }
	inline int getDirection() { return (int)_boss.direction; }

	// set
	inline void setPlayerMemoryAddressLink(Zero* player) { _player = player; }
	inline void setHP(float damage) { _boss.currentHP -= damage; }
	inline void setHit(bool hit) { _boss.isHit = hit; }
	inline void setHitTime(float time) { _hitTime = time; }
	inline void setStart(bool start) { _isStart = start; }
	inline void setX(float x) { _boss.x = x; }

};

