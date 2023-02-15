#include "CircleShuriken.h"

void CircleShuriken::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void CircleShuriken::Render()
{
	float xS, yS;
	for (int i = 0; i < 8; i++) {
		xS = x + cos(radianSTart + 0.785*i) * r;
		yS = y + sin(radianSTart + 0.785*i) * r;
		CAnimations::GetInstance()->Get(ID_ANI_SHURIKEN)->Render(xS, yS);
	}
}
