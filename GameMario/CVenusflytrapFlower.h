#include "GameObject.h"
#include "CEffectHitWithTail.h"
#include "CPrice.h"

#define ID_ANI_VENUSFLYTRAPFLOWER	27001

#define VENUSFLYTRAPFLOWER_BBOX_WIDTH	16
#define VENUSFLYTRAPFLOWER_BBOX_HEIGHT	32

#define VENUSFLYTRAPFLOWER_STATE_HIDE	100
#define VENUSFLYTRAPFLOWER_STATE_ATTACK	200
#define VENUSFLYTRAPFLOWER_STATE_MOVEUP	300
#define VENUSFLYTRAPFLOWER_STATE_MOVEDOWN	400
#define VENUSFLYTRAPFLOWER_STATE_DIE_TAILTURNING	500

#define VENUSFLYTRAPFLOWER_SPEED_Y	0.05f

#define TIME_WAIT	1500

class CVenusflytrapFlower : public CGameObject
{
protected:
	float wait_start;
	float yMin;
	float yMax;
	BOOLEAN isWait;
	CEffectHitWithTail* effectHit;
	CPrice* price;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		if (state == VENUSFLYTRAPFLOWER_STATE_DIE_TAILTURNING) {
			if (effectHit != NULL)
			{
				coObjects->push_back(effectHit);
				coObjects->push_back(price);
				effectHit = NULL;
				price = NULL;
			}
			this->Delete();
		}

		if (isWait && GetTickCount64() - wait_start > TIME_WAIT) {
			isWait = false;
			wait_start = 0;
			if (state == VENUSFLYTRAPFLOWER_STATE_ATTACK)
				SetState(VENUSFLYTRAPFLOWER_STATE_MOVEDOWN);
			else SetState(VENUSFLYTRAPFLOWER_STATE_MOVEUP);
		}
		if (state == VENUSFLYTRAPFLOWER_STATE_MOVEDOWN && y > yMax) {
			SetState(VENUSFLYTRAPFLOWER_STATE_HIDE);
		}
		else if (state == VENUSFLYTRAPFLOWER_STATE_MOVEUP && y < yMin) {
			SetState(VENUSFLYTRAPFLOWER_STATE_ATTACK);
		}
		
		y += vy * dt;
	};
	virtual void Render();
	
public:
	CVenusflytrapFlower(float x, float y): CGameObject(x,y){
		yMin = y;
		yMax = y + 32;
		effectHit = NULL;
		price = NULL;
		SetState(VENUSFLYTRAPFLOWER_STATE_ATTACK);
	}
	virtual void SetState(int state) {
		switch (state)
		{
		case VENUSFLYTRAPFLOWER_STATE_HIDE:
			vy = 0;
			isWait = true;
			wait_start = GetTickCount64();
			break;
		case VENUSFLYTRAPFLOWER_STATE_ATTACK:
			vy = 0;
			isWait = true;
			wait_start = GetTickCount64();
			break;
		case VENUSFLYTRAPFLOWER_STATE_MOVEUP:
			vy = -VENUSFLYTRAPFLOWER_SPEED_Y;
			break;
		case VENUSFLYTRAPFLOWER_STATE_MOVEDOWN:
			vy = VENUSFLYTRAPFLOWER_SPEED_Y;
			break;
		case VENUSFLYTRAPFLOWER_STATE_DIE_TAILTURNING:
			effectHit = new CEffectHitWithTail(x, y);
			price = new CPrice(x, y);
			break;
		default:
			break;
		}
		this->state = state;
	}

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
};