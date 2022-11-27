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
	int aniID;
	switch (state)
	{
	case CANNIBALFLOWER_STATE_ATTACK:
		if (direct == 0) {
			aniID = ID_ANI_CANNIBALFLOWER_ATTACK_LEFT;
		}
		else aniID = ID_ANI_CANNIBALFLOWER_ATTACK_RIGHT;
		break;
	default:
		if (direct == 0) {
			aniID = ID_ANI_CANNIBALFLOWER_LOCK_LEFT;
		}
		else aniID = ID_ANI_CANNIBALFLOWER_LOCK_RIGHT;
		break;
	}
	CAnimations::GetInstance()->Get(aniID)->Render(x, y, 1);
	//RenderBoundingBox();
}
