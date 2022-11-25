#include "CCannibalFlower.h"

void CCannibalFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - CANNIBALFLOWER_BBOX_WIDTH / 2;
	top = y - CANNIBALFLOWER_BBOX_HEIGHT / 2;
	right = left + CANNIBALFLOWER_BBOX_WIDTH;
	bottom = top + CANNIBALFLOWER_BBOX_HEIGHT;
}

void CCannibalFlower::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_CANNIBALFLOWER)->Render(x, y);
	//RenderBoundingBox();
}
