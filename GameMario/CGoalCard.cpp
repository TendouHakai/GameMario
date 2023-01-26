#include "CGoalCard.h"

void CGoalCard::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - GOADCARD_BBOX_WIDTH / 2;
	top = y - GOADCARD_BBOX_HEIGHT / 2;
	right = left + GOADCARD_BBOX_WIDTH;
	bottom = top + GOADCARD_BBOX_HEIGHT;
}

void CGoalCard::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	switch (state)
	{
	case GOALCARD_STATE_COLLECT: {
		if (currentCard == GOALCARD_TYPE_MUSHROOM)
			aniId = ID_ANI_GOALCARD_MUSHROOM;
		else if (currentCard == GOALCARD_TYPE_FLOWER)
			aniId = ID_ANI_GOALCARD_FLOWER;
		else aniId = ID_ANI_GOALCARD_STAR;
		break;
	}
	default: {
		aniId = ID_ANI_GOALCARD;
		break;
	}
		
	}
	animations->Get(aniId)->Render(x, y);
	
	// render title 
	float xC, yC;
	CGame::GetInstance()->GetCamPos(xC, yC);
	float sx = CGame::GetInstance()->GetBackBufferWidth();
	if (isShowTitle >= 1) {
		animations->Get(ID_ANI_GOALCARD_TITLE1)->Render(xC+sx/2, yC+20);
	}
	if (isShowTitle >= 2) {
		animations->Get(ID_ANI_GOALCARD_TITLE2)->Render(xC + sx / 2, yC + 55);
		// render card collection
		if (currentCard == GOALCARD_TYPE_MUSHROOM)
			animations->Get(ID_ANI_SPOIL_MUSHROOM)->Render(xC + sx / 2 + 60, yC + 54);
		else if (currentCard == GOALCARD_TYPE_FLOWER)
			animations->Get(ID_ANI_SPOIL_FLOWER)->Render(xC + sx / 2 + 60, yC + 54);
		else animations->Get(ID_ANI_SPOIL_STAR)->Render(xC + sx / 2 + 60, yC + 54);
	}
	//RenderBoundingBox();
}
