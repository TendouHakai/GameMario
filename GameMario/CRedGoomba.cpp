#include "CRedGoomba.h"

void CRedGoomba::Render()
{
	int aniId = ID_ANI_REDGOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_REDGOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
