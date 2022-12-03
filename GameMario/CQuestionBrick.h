#pragma once
#include "Brick.h"
#include "Coin.h"
#include "debug.h"
#define ID_ANI_QUESTIONBRICK_IDLE 12000
#define ID_ANI_QUESTIONBRICK_BROKEN 12001

#define QUESTIONBRICK_STATE_IDLE 100
#define QUESTIONBRICK_STATE_BROKEN 200

#define QUESTIONBRICK_SPEED	0.25f
#define QUESTIONBRICK_GRAVITY	0.002f
class CQuestionBrick :public CBrick
{
protected:
	float yBrick;
	float ay;
	CCoin* coin;
	BOOLEAN isBroken;
public:
	CQuestionBrick(float x, float y) : CBrick(x, y) { state = QUESTIONBRICK_STATE_IDLE; yBrick = y; ay = 0; coin = NULL; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		vy += ay * dt;
		y += vy * dt;
		if (coin != NULL && state == QUESTIONBRICK_STATE_BROKEN) {
			coObjects->push_back(coin);
			coin = NULL;
		}
		if (y > yBrick) {
			y = yBrick;
			vy = 0;
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
			coin = new CCoin(x, y - 30);
			coin->SetState(COIN_STATE_COLLECTION);
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

