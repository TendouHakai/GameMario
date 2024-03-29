#pragma once
#include "GameObject.h"
#include "debug.h"
#include "CEffectHitWithTail.h"
#include "CPrice.h"

#define TURTLE_BBOX_WIDTH 18
#define TURTLE_BBOX_HEIGHT 26
#define TURTLE_DEAD_BBOX_WIDTH 18
#define TURTLE_DEAD_BBOX_HEIGHT 14

#define TURTLECHECK_BBOX_WIDTH 5
#define TURTLECHECK_BBOX_HEIGHT 26

#define ID_ANI_TURTLE_WALK_LEFT 15000
#define ID_ANI_TURTLE_WALK_RIGHT 15001
#define ID_ANI_TURTLE_DEAD 15002
#define ID_ANI_TURTLE_REVIVAL 15003
#define ID_ANI_TURTLE_DEAD_TAILTURNING 15004

#define TURTLE_STATE_WALK	100
#define TURTLE_STATE_DEAD	200
#define TURTLE_STATE_REVIVAL	300
#define TURTLE_STATE_KICKED_RIGHT	400
#define TURTLE_STATE_KICKED_LEFT	500
#define TURTLE_STATE_DEAD_TAILTURNING	600
#define TURTLE_STATE_ISHOLDED	700
#define TURTLE_STATE_COLLECTION_RIGHT	800
#define TURTLE_STATE_COLLECTION_LEFT	900

#define TURTLE_SPEED	0.02f
#define TURTLE_SPEED_Y	0.3f
#define TURTLE_GRAVITY	0.002f
#define TURTLE_SPEED_KICKED	0.25f

#define TURTLE_DEAD_TIME	3000
#define TURTLE_REVIVAL_TIME	500
#define TURTLE_KICKED_TIME	1500
#define TURTLE_UNTOUCHABLE_TIME	500

class CTurtleCheck :
	public CGameObject
{
protected:
	float ay;
	BOOLEAN isOnPlatform;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	
public:
	CTurtleCheck(float x, float y) :CGameObject(x, y) {
		vx = 0;
		ay = TURTLE_GRAVITY;
		isOnPlatform = false;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		vy += ay * dt;

		isOnPlatform = false;
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	virtual void Render() {
		//RenderBoundingBox();
	}
	void SetPositionX(float x) {
		this->x = x;
	}
	void SetPositionY(float y) {
		this->y = y;
	}
	float GetPositionY() {
		return this->y;
	}
	
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
};

class CTurtle :
    public CGameObject
{
protected:
	float xStart;
	float ay;
	BOOLEAN isOnPlatform;
	bool isdeadTailTurning;
	int isUntouchable;

	ULONGLONG dead_start;
	ULONGLONG revival_start;
	ULONGLONG untouchable_start;
	ULONGLONG kicked_start;

	CTurtleCheck * check;

	CGameObject* effecthit;
	CGameObject* price;

	bool isPause = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		vy += ay * dt;
		if (isPause)
			return;

		isOnPlatform = false;
		check->Update(dt, coObjects);

		if (state == TURTLE_STATE_DEAD) {
			if (GetTickCount64() - dead_start > TURTLE_DEAD_TIME)
			{
				dead_start = 0;
				SetState(TURTLE_STATE_REVIVAL);
			}
		}
		else if (state == TURTLE_STATE_DEAD_TAILTURNING) {
			isUntouchable = 0;
			untouchable_start = 0;
			if (effecthit != NULL)
			{
				coObjects->push_back(effecthit);
				effecthit = NULL;
			}
			if (GetTickCount64() - dead_start > TURTLE_DEAD_TIME)
			{
				dead_start = 0;
				SetState(TURTLE_STATE_REVIVAL);
				isdeadTailTurning = false;
			}
		}
		else if (state == TURTLE_STATE_REVIVAL) {
			if (GetTickCount64() - revival_start > TURTLE_REVIVAL_TIME)
			{
				revival_start = 0;
				SetState(TURTLE_STATE_WALK);
			}
		}
		/*else if (state == TURTLE_STATE_KICKED_RIGHT || state == TURTLE_STATE_KICKED_LEFT) {
			if (GetTickCount64() - kicked_start > TURTLE_KICKED_TIME)
			{
				kicked_start = 0;
				this->Delete();
			}
		}*/
		else 
			if (state == TURTLE_STATE_COLLECTION_RIGHT || state == TURTLE_STATE_COLLECTION_LEFT) {
			if (price != NULL) {
				coObjects->push_back(price);
				price = NULL;
			}
			/*if (GetTickCount64() - untouchable_start > 1500) {
				isUntouchable = 0;
				untouchable_start = 0;
			}*/
		}

		if (isUntouchable == 1) {
			ULONGLONG time = TURTLE_UNTOUCHABLE_TIME;
			if (state == TURTLE_STATE_COLLECTION_LEFT || state == TURTLE_STATE_COLLECTION_RIGHT) {
				time = 1500;
				if (GetTickCount64() - untouchable_start > time) {
					isUntouchable = 0;
					untouchable_start = 0;
					this->Delete();
				}
			}
			else if (GetTickCount64() - untouchable_start > time) {
				isUntouchable = 0;
				untouchable_start = 0;
			}
		}
		
		CCollision::GetInstance()->Process(this, dt, coObjects);

		if (state == TURTLE_STATE_WALK)
		{
			if (check->GetPositionY() > this->y) {
				vx = -vx;
				check->SetPositionY(y);
			}
			if (vx > 0) {
				check->SetPositionX(x + 10);
			}
			else {
				check->SetPositionX(x - 10);
			}
		}
		
	}
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithWingGreenTurtle(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithTurtle(LPCOLLISIONEVENT e);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	
public:
	void IsPause(bool isPause) {
		this->isPause = isPause;
		if (isPause == false)
			dead_start = GetTickCount64();
	}
	CTurtle(float x, float y) :CGameObject(x, y) { 
		vx = TURTLE_SPEED;  
		ay = TURTLE_GRAVITY; 
		state = TURTLE_STATE_WALK;
		isOnPlatform = false;
		isUntouchable = 0;
		dead_start = 0;
		revival_start = 0;
		kicked_start = 0;
		effecthit = NULL;
		price = NULL;
		isdeadTailTurning = false;
		check = new CTurtleCheck(x+10, y);
	}
	virtual void Render();
	int IsCollidable() { return (state != TURTLE_STATE_COLLECTION_RIGHT && state != TURTLE_STATE_COLLECTION_LEFT); };
	int IsBlocking() { return 0; }
	int IsUntouchable() { return isUntouchable; }
	void SetState(int state) { 
		switch (state)
		{
		case TURTLE_STATE_WALK: {
			vx = TURTLE_SPEED;
			ay = TURTLE_GRAVITY;
			y -= (TURTLE_BBOX_HEIGHT - TURTLE_DEAD_BBOX_HEIGHT) / 2;
			break;
		}
		case TURTLE_STATE_DEAD: {
			vx = 0;
			vy = 0;
			dead_start = GetTickCount64();
			break;
		}
		case TURTLE_STATE_REVIVAL: {
			revival_start = GetTickCount64();
			break;
		}
		case TURTLE_STATE_KICKED_RIGHT: {
			//kicked_start = GetTickCount64();
			vx = -TURTLE_SPEED_KICKED;
			ay = TURTLE_GRAVITY;
			isUntouchable = 1;
			untouchable_start = GetTickCount64();
			break;
		}
		case TURTLE_STATE_KICKED_LEFT: {
			//kicked_start = GetTickCount64();
			vx = TURTLE_SPEED_KICKED;
			ay = TURTLE_GRAVITY;
			isUntouchable = 1;
			untouchable_start = GetTickCount64();
			break;
		}
		case TURTLE_STATE_DEAD_TAILTURNING: {
			isdeadTailTurning = true;
			vx = 0;
			vy = -TURTLE_SPEED_Y;
			effecthit = new CEffectHitWithTail(x, y);
			dead_start = GetTickCount64();
			break;
		}
		case TURTLE_STATE_ISHOLDED: {
			ay = 0;
			vx = 0;
			vy = 0;
			break;
		}
		case TURTLE_STATE_COLLECTION_RIGHT: {
			isUntouchable = 1;
			untouchable_start = GetTickCount64();
			vy = -TURTLE_SPEED_Y;
			vx = -0.1f;
			price = new CPrice(x, y);
			break;
		}
		case TURTLE_STATE_COLLECTION_LEFT: {
			isUntouchable = 1;
			untouchable_start = GetTickCount64();
			vy = -TURTLE_SPEED_Y;
			vx = 0.1f;
			price = new CPrice(x, y);
			break;
		}
		default:
			break;
		}
		this->state = state; 
	}
};

