#pragma once
#include "GameObject.h"
#include "CBullet.h"
#include "PlayScene.h"

#define ID_ANI_CANNIBALFLOWER_LOCK_LEFT	13000
#define ID_ANI_CANNIBALFLOWER_ATTACK_LEFT	13001
#define ID_ANI_CANNIBALFLOWER_LOCK_RIGHT	13002
#define ID_ANI_CANNIBALFLOWER_ATTACK_RIGHT	13003

#define CANNIBALFLOWER_BBOX_WIDTH 33
#define CANNIBALFLOWER_BBOX_HEIGHT 60
#define CANNIBALFLOWER_BBOX_HEIGHT_DIE 7

#define CANNIBALFLOWER_STATE_HIDE 100
#define CANNIBALFLOWER_STATE_ATTACK 200
#define CANNIBALFLOWER_STATE_LOCK 300

#define TIME_HIDE 2000

#define CANNIBALFLOWER_SPEED_Y	0.02f

class CCannibalFlower :public CGameObject
{
protected:
	float yAttack;
	float yHide;
	bool isWait;
	int direct;
	float hide_start;
	CBullet* bullet;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){
		y += vy * dt;
		CPlayScene* scene = dynamic_cast<CPlayScene*>((CGame::GetInstance()->GetCurrentScene()));
		float xMario, yMario;
		scene->GetPlayer()->GetPosition(xMario, yMario);
		if (xMario > this->x) {
			direct = 1;
		}
		else direct = 0;
		if (isWait == true && GetTickCount64() - hide_start > TIME_HIDE) {
			
			SetState(CANNIBALFLOWER_STATE_LOCK);
		}
		if (y < yAttack) {
			y = yAttack;
			vy = 0;
			SetState(CANNIBALFLOWER_STATE_ATTACK);
			bullet->setLockPosition(xMario, yMario);

			if (bullet != NULL)
			{
				coObjects->push_back(bullet);
				bullet = NULL;
			}
			hide_start = GetTickCount64();
			isWait = true;
		}
		if (y > yHide) {
			y = yHide;
			hide_start = GetTickCount64();
			SetState(CANNIBALFLOWER_STATE_HIDE);
		}

	}
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	/*virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);*/
public:
	CCannibalFlower(float x, float y) :CGameObject(x,y) { 
		state = CANNIBALFLOWER_STATE_HIDE; 
		yAttack = y-30; 
		yHide = y;
		isWait = true; 
		hide_start = GetTickCount64(); 
		bullet = NULL;
		direct = 0;
	}
	void SetState(int state) { 
		switch (state)
		{
		case CANNIBALFLOWER_STATE_ATTACK: {
			if (direct == 0)
				bullet = new CBullet(x - 15, y);
			else bullet = new CBullet(x + 15, y);
			break;
		}
		case CANNIBALFLOWER_STATE_LOCK: {
			isWait = false;
			if (y == yAttack) {
				vy = CANNIBALFLOWER_SPEED_Y;
			}
			else vy = -CANNIBALFLOWER_SPEED_Y;
			break;
		}
		case CANNIBALFLOWER_STATE_HIDE: {
			vy = 0;
			isWait = true;
			break;
		}
		default:
			break;
		}
		this->state = state; 
	}
};

