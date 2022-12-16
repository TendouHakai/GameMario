#pragma once
#include "CTurtle.h"
#include "CPrice.h"

#define ID_ANI_GREENTURTLE_WALK_LEFT 16000
#define ID_ANI_GREENTURTLE_WALK_RIGHT 16001
#define ID_ANI_GREENTURTLE_DEAD 16002
#define ID_ANI_GREENTURTLE_REVIVAL 16003
#define ID_ANI_GREENTURTLE_KICK 16004
#define ID_ANI_GREENTURTLE_DEAD_TAILTURNING 16005

#define GREENTURTLE_STATE_COLLECTION    800

class CGreenTurtle :
    public CTurtle
{
protected:
	float isCollection;
	CPrice* price;
    virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		if (state == GREENTURTLE_STATE_COLLECTION) {
			if (price != NULL) {
				coObjects->push_back(price);
				price = NULL;
			}
			if (GetTickCount64() - untouchable_start > TURTLE_KICKED_TIME) {
				this->Delete();
			}
		}

		CTurtle::Update(dt, coObjects);
	}
public:
	CGreenTurtle(float x, float y) :CTurtle(x, y) { 
		untouchable_start = GetTickCount64();
		isUntouchable = 1;
		isCollection = 0; 
		price = NULL;
	}

	void SetState(int state) {
		if (state == GREENTURTLE_STATE_COLLECTION) {
			vy = -TURTLE_SPEED_Y;
			untouchable_start = GetTickCount64();
			isUntouchable = 1;
			isCollection = 1;
			price = new CPrice(x, y);
			this->state = state;
			return;
		}
		CTurtle::SetState(state);
	}

	int IsCollidable() { return !isCollection; }
};

