#include "CVenusflytrapFlower.h"

void CVenusflytrapFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - VENUSFLYTRAPFLOWER_BBOX_WIDTH / 2;
	top = y - VENUSFLYTRAPFLOWER_BBOX_HEIGHT / 2;
	right = left + VENUSFLYTRAPFLOWER_BBOX_WIDTH;
	bottom = top + VENUSFLYTRAPFLOWER_BBOX_HEIGHT;
}

void CVenusflytrapFlower::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_VENUSFLYTRAPFLOWER)->Render(x, y);
	//RenderBoundingBox();
}