#pragma once
#include "Brick.h"
#include "CMushroom.h"
#include "CGreenMushroom.h"
#include "Coin.h"
#include "CLeaf.h"
#include "debug.h"
#define ID_ANI_QUESTIONBRICK_IDLE 12000
#define ID_ANI_QUESTIONBRICK_BROKEN 12001

#define QUESTIONBRICK_STATE_IDLE 100
#define QUESTIONBRICK_STATE_BROKEN 200

#define QUESTIONBRICK_SPEED	0.25f
#define QUESTIONBRICK_GRAVITY	0.002f

#define QUESTIONBRICK_TYPE_COIN	1
#define QUESTIONBRICK_TYPE_REDMUSHROOM	2
#define QUESTIONBRICK_TYPE_GREENMUSHROOM	4
#define QUESTIONBRICK_TYPE_LEAF	3
class CQuestionBrick :public CBrick
{
protected:
	float yBrick;
	float ay;
	CGameObject* coin;
	BOOLEAN isBroken;
	int type;
public:
	CQuestionBrick(float x, float y, int type) : CBrick(x, y) { state = QUESTIONBRICK_STATE_IDLE; yBrick = y; ay = 0; coin = NULL; this->type = type; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		vy += ay * dt;
		y += vy * dt;
		if (coin != NULL && state == QUESTIONBRICK_STATE_BROKEN) {
			if (type == QUESTIONBRICK_TYPE_COIN || type == QUESTIONBRICK_TYPE_LEAF)
			{
				coObjects->push_back(coin);
				coin = NULL;
			}
		}
		
		if (y > yBrick) {
			y = yBrick;
			vy = 0;
			if (coin != NULL && state == QUESTIONBRICK_STATE_BROKEN && (type == QUESTIONBRICK_TYPE_REDMUSHROOM || type == QUESTIONBRICK_TYPE_GREENMUSHROOM)) {
				coObjects->insert(coObjects->begin() + 1, coin);
				coin = NULL;
			}
		}

	}
	void Render();
	void SetState(int state) { 
		switch (state)
		{
		case QUESTIONBRICK_STATE_IDLE: {
			break;
		}
		case QUESTIONBRICK_STATE_BROKEN: {
			
			vy = -QUESTIONBRICK_SPEED;
			ay = QUESTIONBRICK_GRAVITY;
			if (type == QUESTIONBRICK_TYPE_COIN)
			{
				coin = new CCoin(x, y - 30);
				coin->SetState(COIN_STATE_COLLECTION);
			}
			else if (type == QUESTIONBRICK_TYPE_REDMUSHROOM) {
				coin = new CMushroom(x, y);
				coin->SetState(MUSHROOM_STATE_APPEAR);
			}
			else if (type == QUESTIONBRICK_TYPE_GREENMUSHROOM) {
				coin = new CGreenMushroom(x, y);
				coin->SetState(MUSHROOM_STATE_APPEAR);
			}
			else if (type == QUESTIONBRICK_TYPE_LEAF) {
				coin = new CLeaf(x, y-30);
				coin->SetState(LEAF_STATE_START);
			}
			break;
		}
		default:
			break;
		}
		this->state = state; 
	}
	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; }
};

