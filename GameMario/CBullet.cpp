#include "CBullet.h"

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BULLET_BBOX_WIDTH / 2;
	top = y - BULLET_BBOX_HEIGHT / 2;
	right = left + BULLET_BBOX_WIDTH;
	bottom = top + BULLET_BBOX_HEIGHT;
}

void CBullet::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_BULLET)->Render(x, y);
	//RenderBoundingBox();
}
