#pragma once
#include "gameNode.h"
#include "progressBar.h"

//#define SPEED 7
#define GRAVITY 0.35f

#define WIDTH 80
#define HEIGHT 100

#define GROUNDMAX 3
#define OBJECTMAX 4

#define AFTERMAX 5

class objectManager;
class enemyManager;

struct Line
{
	POINT p1, p2;
};


enum PLAYERSTATE
{
	IDLE,
	RUN,	// = 1
	JUMP,
	HANG,
	DROP,
	HANGJUMP,
	DASH,	// = 6
	CLIMB,
	LAND,
	ATTACK,
	AIRATTACK,
	CLIMBATTACK,
	HANGATTACK,
	HIT
};

enum PLAYERDIRECTION
{
	LEFT,
	RIGHT
};

struct tagPlayer
{
	image* img;
	RECT rc;
	RECT range;
	PLAYERDIRECTION direction;
	PLAYERSTATE state;
	PLAYERSTATE lastState;
	float x, y;
	float width, height;
	float jumpPower;
	float gravity;
	float speed;
	float currentHP;
	float maxHP;
	bool isJump;
	bool onGround;
	bool underJump;
	bool isAttack;
	int attackCount;
	int dashCount;
	bool isHit;
};

struct afterPlayer
{
	image* img;
	float x, y;
	int frameX, frameY;

};


class Zero : public gameNode
{
private:
	// Move
	image* _idle;
	image* _run;
	image* _jump;
	image* _hang;
	image* _dash;
	image* _climb;
	image* _land;
	image* _victory;

	// Attack
	image* _slash01;
	image* _slash02;
	image* _slash03;
	image* _airSlash;
	image* _climbSlash;
	image* _hangSlash;

	// Hit
	image* _hit01;
	image* _hit02;

	//// effect
	//effect* _dashEffect;
	//effect* _dashBackEffect;
	//effect* _jumpEffect;
	//effect* _hangEffect;


	// player struct
	tagPlayer _player;
	afterPlayer _after[AFTERMAX];

	// animation
	int _count, _index;

	float _xPower, _yPower;

	// 점프 상태 여부
	bool _isJump;

	float _speed;

	objectManager* _om;
	enemyManager* _em;

	int check;

	Line _line;

	bool _isBoss;

	bool _isHit;

	float _afterTime;
	float _afterInterval;

	bool _moveCamera;


	// hp bar
	progressBar* _hpBar;
	image* _hpBackground;


public:
	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

	void PlayerMove();
	void Jump();
	void Attack();
	void Dash();

	void Collision();
	void enemyCollision();
	void Animation();

	void hpManagement();

	void afterImage();

	void bossCamera();

	void ChangeState(PLAYERDIRECTION direction, PLAYERSTATE state, image* img, int frameY, float jumpPower, float gravity, int index, bool jump);
	void ChangeState(PLAYERDIRECTION direction, PLAYERSTATE state, image* img);

	tagPlayer getPlayer() { return _player; }
	void setPlayer(tagPlayer player) { _player = player; }

	// get
	RECT getRect() { return _player.rc; }
	float getX() { return _player.x; }
	float getY() { return _player.y; }
	float getJumpPower() { return _player.jumpPower; }
	float getGravity() { return _player.gravity; }
	float getPlayerSpeed() { return _player.speed; }
	float getSpeed() { return _speed; }
	bool getBoss() { return _isBoss; }
	image* getImage() { return _player.img; }
	float getHP() { return _player.currentHP; }
	bool getHit() { return _player.isHit; }
	PLAYERSTATE getState() { return _player.state; }

	// set
	void setX(float x) { _player.x = x; }
	void setY(float y) { _player.y = y; }
	void setJumpPower(float jump) { _player.jumpPower = jump; }
	void setGravity(float gravity) { _player.gravity = gravity; }
	void setSpeed(float speed) { _player.speed = speed; }
	void setHP(float damage) { _player.currentHP -= damage; }
	void setState(int state) { _player.state = (PLAYERSTATE)state; }
	void setImage(image* img) { _player.img = img; }
	void setDirection(int dir) { _player.direction = (PLAYERDIRECTION)dir; }
	void setIndex(int index) { _index = index; }
	void setHit(bool hit) { _player.isHit = hit; }
	void setXPower(float power) { _xPower = power; }
	void setBoss(bool boss) { _isBoss = boss; }
	void setMoveCamera(bool move) { _moveCamera = move; }

	// Memory
	void setOmMemoryAddressLink(objectManager* om) { _om = om; }
	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }
};

