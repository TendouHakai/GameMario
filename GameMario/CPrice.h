#pragma once
#include "GameObject.h"

#define TIME_PRICE_EXIST	1000

#define ID_ANI_PRICE_100	25004
#define ID_ANI_PRICE_1000	25005
#define ID_ANI_PRICE_200	25006
#define ID_ANI_PRICE_1M	25007

#define PRICE_GRAVITY	0.0005f
#define PRICE_SPEED_Y	0.2f

//NUMBER
#define ID_ANI_NUMBER00	28002
#define ID_ANI_NUMBER01	28003
#define ID_ANI_NUMBER02	28004
#define ID_ANI_NUMBER03	28005
#define ID_ANI_NUMBER04	28006
#define ID_ANI_NUMBER05	28007
#define ID_ANI_NUMBER06	28008
#define ID_ANI_NUMBER07	28009
#define ID_ANI_NUMBER08	28010
#define ID_ANI_NUMBER09	28011

class CPrice : public CGameObject 
{
protected:
	float ay;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom){};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		vy += ay * dt;

		if (vy > 0) {
			this->Delete();
		}

		y += vy * dt;
	};

	virtual void Render();
	virtual void SetState(int state) { this->state = state; }

	int number = -1;
public:
	CPrice(float x, float y, int number = -1) :CGameObject(x, y){
		vy = -PRICE_SPEED_Y;
		ay = PRICE_GRAVITY;
		this->number = number;
	}

	

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
};