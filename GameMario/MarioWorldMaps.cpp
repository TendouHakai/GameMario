#include "MarioWorldMaps.h"
#include "debug.h"

void MarioWorldMaps::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MARIO_WORLD_WIDTH / 2;
	top = y - MARIO_WORLD_HEIGHT / 2;
	right = left + MARIO_WORLD_WIDTH;
	bottom = top + MARIO_WORLD_HEIGHT;
}

void MarioWorldMaps::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	//DebugOut(L"%f, %f: \n", x, y);
	if (CGame::GetInstance()->player_level == MARIO_LEVEL_SMALL)
		animations->Get(ID_ANI_MARIOW_SMALL)->Render(x, y);
	else if (CGame::GetInstance()->player_level == MARIO_LEVEL_BIG)
		animations->Get(ID_ANI_MARIOW_BIG)->Render(x, y);
	else animations->Get(ID_ANI_MARIOW_RACCON)->Render(x, y);
	//RenderBoundingBox();
}
