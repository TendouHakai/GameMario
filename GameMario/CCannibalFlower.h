#pragma once
#include "GameObject.h"

#define ID_ANI_CANNIBALFLOWER	13000

#define CANNIBALFLOWER_BBOX_WIDTH 33
#define CANNIBALFLOWER_BBOX_HEIGHT 60
#define CANNIBALFLOWER_BBOX_HEIGHT_DIE 7
class CCannibalFlower :public CGameObject
{
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){}
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	/*virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);*/
public:
	CCannibalFlower(float x, float y):CGameObject(x,y){}
};

