#include "GameObject.h"

#define LEAF_STATE_START	100
#define LEAF_STATE_FALL_RIGHT	200
#define LEAF_STATE_FALL_LEFT	201
#define LEAF_STATE_COLLECTION	300

#define LEAF_GRAVITY	0.0003f
#define LEAF_ACCEL_X	0.0002f
#define LEAF_SPEED_Y	0.1f

#define LEAF_ACCEL_Y	0.0002f
#define LEAF_SPEED_Y_FALL	0.07f
#define LEAF_SPEED	0.12f

#define LEAF_BBOX_WIDTH	16
#define LEAF_BBOX_HEIGHT	16

#define ID_ANI_LEAF_RIGHT	26002
#define ID_ANI_LEAF_LEFT	26001	

class CLeaf : public CGameObject {
protected:
	float ax, ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		vx += ax * dt;
		vy += ay * dt;

		if (state== LEAF_STATE_START&& vy > 0) {
			SetState(LEAF_STATE_FALL_RIGHT);
		}
		else if (state == LEAF_STATE_FALL_RIGHT && vx<0) {
			SetState(LEAF_STATE_FALL_LEFT);
		}
		else if (state == LEAF_STATE_FALL_LEFT && vx > 0) {
			SetState(LEAF_STATE_FALL_RIGHT);
		}
		

		x += vx * dt;
		y += vy * dt;
	};
	virtual void Render();
	virtual void SetState(int state) { 
		switch (state)
		{
		case LEAF_STATE_START:
			ax = 0;
			vx = 0;
			ay = LEAF_GRAVITY;
			vy = -LEAF_SPEED_Y;
			break;
		case LEAF_STATE_FALL_RIGHT:
			ax = -LEAF_ACCEL_X;
			vx = LEAF_SPEED;
			ay = -LEAF_ACCEL_Y;
			vy = LEAF_SPEED_Y_FALL;
			break;
		case LEAF_STATE_FALL_LEFT:
			ax = LEAF_ACCEL_X;
			vx = -LEAF_SPEED;
			ay = -LEAF_ACCEL_Y;
			vy = LEAF_SPEED_Y_FALL;
			break;
		default:
			break;
		}
		this->state = state; 
	}
public:
	CLeaf(float x, float y):CGameObject(x,y){}

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }


};