#include "CWingGreenTurtle.h"

void CWingGreenTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - WINGGREENTURTLE_BBOX_WIDTH / 2;
	top = y - WINGGREENTURTLE_BBOX_HEIGHT / 2;
	right = left + WINGGREENTURTLE_BBOX_WIDTH;
	bottom = top + WINGGREENTURTLE_BBOX_HEIGHT;
}

void CWingGreenTurtle::Render()
{
	if (vx > 0)
		CAnimations::GetInstance()->Get(ID_ANI_WINGGREENTURTLE_WALK_RIGHT)->Render(x, y);
	else CAnimations::GetInstance()->Get(ID_ANI_WINGGREENTURTLE_WALK_LEFT)->Render(x, y);

	RenderBoundingBox();
}
