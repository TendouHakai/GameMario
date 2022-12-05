#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"

#define ID_ANI_BRICK_BLUE 10000

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16
class CBrick : public CGameObject {
protected:
public:
	CBrick(float x, float y) : CGameObject(x, y) {}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};