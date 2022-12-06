#pragma once
#include "GameObject.h"
#include "PlayScene.h"

#define ID_ANI_MUSHROOM 22001

#define MUSHROOM_STATE_APPEAR   100
#define MUSHROOM_STATE_RUN  200
#define MUSHROOM_STATE_EATEN    300
#define MUSHROOM_STATE_IDLE    400

#define MUSHROOM_BBOX_WIDTH	16
#define MUSHROOM_BBOX_HEIGHT	16

#define MUSHROOM_GRAVITY	0.002f
#define MUSHROOM_SPEED_Y_APPEAR	0.02f
#define MUSHROOM_SPEED	0.07f
class CMushroom :
    public CGameObject
{
protected:
	float ay;
	float ystart;

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CMushroom(float x, float y):CGameObject(x,y){
		SetState(MUSHROOM_STATE_IDLE);
		ystart = y;

	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		vy += ay * dt;
		
		if (state == MUSHROOM_STATE_APPEAR) {
			if (abs(ystart - y) > 18) {
				SetState(MUSHROOM_STATE_RUN);
			}
		}
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};
	virtual void Render();
	virtual void SetState(int state) { 
		switch (state)
		{
		case MUSHROOM_STATE_IDLE: {
			ay = 0;
			vx = 0;
			vy = 0;
			break;
		}
		case MUSHROOM_STATE_APPEAR: {
			ay = 0;
			vy = -MUSHROOM_SPEED_Y_APPEAR;
			break;
		}
		case MUSHROOM_STATE_RUN: {
			ay = MUSHROOM_GRAVITY;
			CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			float xMario, yMario;
			scene->GetPlayer()->GetPosition(xMario, yMario);

			if (x > xMario)
				vx = MUSHROOM_SPEED;
			else vx = -MUSHROOM_SPEED;
			break;
		}
		case MUSHROOM_STATE_EATEN: {
			this->Delete();
			break;
		}
		default:
			break;
		}
		this->state = state; 
	}

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
};

