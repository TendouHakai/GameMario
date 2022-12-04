#include "CWingGreenTurtle.h"

void CWingGreenTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - WINGGREENTURTLE_BBOX_WIDTH / 2;
	top = y - WINGGREENTURTLE_BBOX_HEIGHT / 2;
	right = left + WINGGREENTURTLE_BBOX_WIDTH;
	bottom = top + WINGGREENTURTLE_BBOX_HEIGHT;
}

void CWingGreenTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CWingGreenTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = -WINGGREENTURTLE_SPEED_Y;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CWingGreenTurtle::Render()
{
	if (vx > 0)
		CAnimations::GetInstance()->Get(ID_ANI_WINGGREENTURTLE_WALK_RIGHT)->Render(x, y);
	else CAnimations::GetInstance()->Get(ID_ANI_WINGGREENTURTLE_WALK_LEFT)->Render(x, y);

	RenderBoundingBox();
}
