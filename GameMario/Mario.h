#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "CTail.h"
#include "CTurtle.h"
#include "CTelePort.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f
#define MARIO_JUMP_TELE_SPEED_Y	0.15f

#define MARIO_GRAVITY			0.002f
#define MARIO_GRAVITY_FLY			0.0007f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_TIME_KICK	200

// define state

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_FLY				700
#define MARIO_STATE_FLY_RELEASE		701

#define MARIO_STATE_TAIL_TURNING	800
#define MARIO_STATE_TAIL_TURNING_RELEASE	801

#define MARIO_STATE_HOLDING	900

#define MARIO_STATE_TELE	901

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_KICK_RIGHT 998
#define ID_ANI_MARIO_KICK_LEFT 997

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

// RACCON MARIO
#define ID_ANI_MARIO_RACCON_IDLE_RIGHT 1700
#define ID_ANI_MARIO_RACCON_IDLE_LEFT 1701

#define ID_ANI_MARIO_RACCON_IDLE_RIGHT_HOLDING 1702
#define ID_ANI_MARIO_RACCON_IDLE_LEFT_HOLDING 1703

#define ID_ANI_MARIO_RACCON_WALKING_RIGHT 1800
#define ID_ANI_MARIO_RACCON_WALKING_LEFT 1801

#define ID_ANI_MARIO_RACCON_WALKING_RIGHT_HOLDING 1802
#define ID_ANI_MARIO_RACCON_WALKING_LEFT_HOLDING 1803

#define ID_ANI_MARIO_RACCON_RUNNING_RIGHT 1900
#define ID_ANI_MARIO_RACCON_RUNNING_LEFT 1901

#define ID_ANI_MARIO_RACCON_JUMP_WALK_RIGHT 2000
#define ID_ANI_MARIO_RACCON_JUMP_WALK_LEFT 2001

#define ID_ANI_MARIO_RACCON_JUMP_WALK_RIGHT_HOLDING 2002
#define ID_ANI_MARIO_RACCON_JUMP_WALK_LEFT_HOLDING 2003
#define ID_ANI_MARIO_RACCON_TELE 2004

#define ID_ANI_MARIO_RACCON_JUMP_RUN_RIGHT 2100
#define ID_ANI_MARIO_RACCON_JUMP_RUN_LEFT 2101

#define ID_ANI_MARIO_RACCON_BRACE_RIGHT 2200
#define ID_ANI_MARIO_RACCON_BRACE_LEFT 2201

#define ID_ANI_MARIO_RACCON_SIT_RIGHT 2300
#define ID_ANI_MARIO_RACCON_SIT_LEFT 2301

#define ID_ANI_MARIO_RACCON_FLY_RIGHT 2400
#define ID_ANI_MARIO_RACCON_FLY_LEFT 2401

#define ID_ANI_MARIO_RACCON_KICK_RIGHT 2500
#define ID_ANI_MARIO_RACCON_KICK_LEFT 2501

#define ID_ANI_MARIO_RACCON_TAIL_TURNING_RIGHT	2600
#define ID_ANI_MARIO_RACCON_TAIL_TURNING_LEFT	2601

#define ID_ANI_MARIO_RACCON_JUMPFLY_RIGHT	2005
#define ID_ANI_MARIO_RACCON_JUMPFLY_LEFT	2006
#pragma endregion

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  13
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float yPlatformNotBlock;

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG kick_start;
	BOOLEAN isOnPlatform;
	BOOLEAN isOnPlatformNotBlock;
	BOOLEAN isKicking;
	BOOLEAN isTailTurning;
	BOOLEAN isHolding;
	BOOLEAN isTele;
	ULONGLONG tele_start;
	CTelePort* tele;
	int coin; 
	CTail* tail;
	CTurtle* turtleShell;
	

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithRedTurtle(LPCOLLISIONEVENT e);
	void OnCollisionWithGreenTurtle(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatformNotBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithChangeCam(LPCOLLISIONEVENT e);
	void OnCollisionWithWingGreenTurtle(LPCOLLISIONEVENT e);
	void OnCollisionWithRedMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithWingRedGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithCannibalFlower(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusflytrapFlower(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusBreakableBrickButton(LPCOLLISIONEVENT e);
	void OnCollisionWithTelePort(LPCOLLISIONEVENT e);

	int GetAniRaccon();
	int GetAniIdBig();
	int GetAniIdSmall();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;

		isOnPlatformNotBlock = false;
		yPlatformNotBlock = 500;

		isKicking = false;

		isTailTurning = false;
		tail = new CTail(x, y);

		isHolding = false;
		turtleShell = NULL;
	
		kick_start = 0;
		coin = 0;

		isTele = false;
		tele_start = 0;
		tele = NULL;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE );
	}

	int IsBlocking() { /*return (state != MARIO_STATE_DIE && untouchable==0);*/  return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void revival() { this->state = MARIO_STATE_IDLE; this->vy = 0; }
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};