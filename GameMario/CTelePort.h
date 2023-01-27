#pragma once
#include "GameObject.h"

#define TIME_TElE	2000
#define TELEPORT_BBOX_WIDTH	25
#define TELEPORT_BBOX_HEIGHT	10

#define TELEPORT_STATE_TELE	100

#define TELEPORT_TYPE_DOWN 0
#define TELEPORT_TYPE_UP 1
class CTelePort : public CGameObject
{
protected:
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {

	};
	virtual void Render() { RenderBoundingBox(); };
	virtual void SetState(int state) { 

		this->state = state; 
	}

public:
	float xtele, ytele;
	float yChangeCamMax;
	float yChangeCamMin;
	int type;
	CTelePort(float x, float y, float xtele, float ytele, float yChangeCamMin, float yChangeCamMax, int type):CGameObject(x,y){
		this->xtele = xtele;
		this->ytele = ytele;
		this->yChangeCamMax = yChangeCamMax;
		this->yChangeCamMin = yChangeCamMin;
		this->type = type;
	}

	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }
};