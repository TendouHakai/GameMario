#include "CTurtleWorldMap.h"

void CTurtleWorldMap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TURTLEW_BBOX_WIDTH / 2;
	top = y - TURTLEW_BBOX_HEIGHT / 2;
	right = left + TURTLEW_BBOX_WIDTH;
	bottom = top + TURTLEW_BBOX_HEIGHT;
}

void CTurtleWorldMap::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(vx>0)
		animations->Get(ID_ANI_TURTLEW_WALKING_RIGHT)->Render(x, y);
	else 
		animations->Get(ID_ANI_TURTLEW_WALKING_LEFT)->Render(x, y);
	//RenderBoundingBox();
}
