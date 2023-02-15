#pragma once
#include "GameObject.h"
#include <math.h>

#define ID_ANI_SHURIKEN	34001
class CircleShuriken :
    public CGameObject
{
private:
	float r;
	float radianSTart;
	bool isExpand = true;
	float xEnd, yEnd;
public:
	CircleShuriken(float x, float y, float xEnd = 0, float yEnd = 0) : CGameObject(x, y) {
		r = 0;
		radianSTart = 0;

		vx = -0.1f;
		this->xEnd = xEnd;
		vy = vx * (y-yEnd) / (x-xEnd);
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		radianSTart += 0.1;
		if (r > 65)
			isExpand = false;
		if (isExpand)
			r += 1;
		else {
			r -= 1; 
			x += vx * dt;
			y += vy * dt;
			if (x <= xEnd)
				this->Delete();
		}

	};
	virtual void Render();
};

