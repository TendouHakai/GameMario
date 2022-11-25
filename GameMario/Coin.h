#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000
#define ID_ANI_COIN_COLLECTION 11001

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_STATE_IDLE	100
#define COIN_STATE_COLLECTION	200
#define COIN_PRICE_STATE_COLLECTION	300

#define COIN_SPEED	0.5f
#define COIN_PRICE_SPEED	0.17f
#define COIN_PRICE_GRAVITY	0.0005f
#define COIN_GRAVITY	0.002f

class CCoin : public CGameObject {
protected:
	float ay;
	int isCollecting;
public:
	CCoin(float x, float y) : CGameObject(x, y) {
		ay = 0; state = COIN_STATE_IDLE;
		isCollecting = 0;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		vy += ay * dt;
		if (isCollecting == 1 && vy>=0) {
			isCollecting = 0;
			this->Delete();
		}
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	void OnNoCollision(DWORD dt) { y += vy * dt; }
	void OnCollisionWith(LPCOLLISIONEVENT e) {
		if (e->ny != 0 && e->obj->IsBlocking())
		{
			vy = 0;
			/*if (isCollecting == 0)
			{
				isCollecting = 1;
				vy = -COIN_PRICE_SPEED;
				ay = COIN_PRICE_GRAVITY;
			}*/
			SetState(COIN_PRICE_STATE_COLLECTION);
		}
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void SetState(int state) {
		switch (state)
		{
		case COIN_STATE_IDLE: {
			break;
		}
		case COIN_STATE_COLLECTION: {
			vy = -COIN_SPEED;
			ay = COIN_GRAVITY;
			break;
		}
		case COIN_PRICE_STATE_COLLECTION: {
			if (isCollecting == 0)
			{
				isCollecting = 1;
				vy = -COIN_PRICE_SPEED;
				ay = COIN_PRICE_GRAVITY;
			}
		}
		default:
			break;
		}
		this->state = state;
	}
};