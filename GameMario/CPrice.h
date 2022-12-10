#include "GameObject.h"

#define TIME_PRICE_EXIST	1000

#define ID_ANI_PRICE_100	25001

#define PRICE_GRAVITY	0.0005f
#define PRICE_SPEED_Y	0.2f

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
public:
	CPrice(float x, float y) :CGameObject(x, y){
		vy = -PRICE_SPEED_Y;
		ay = PRICE_GRAVITY;
	}

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
};