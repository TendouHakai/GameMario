#include "CWingOfGoomba.h"

void CWingOfGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == WINGS_STATE_OPEN) {
		left = x - WINGS_OPEN_BBOX_WIDTH / 2;
		top = y - WINGS_OPEN_BBOX_HEIGHT / 2;
		right = left + WINGS_OPEN_BBOX_WIDTH;
		bottom = top + WINGS_OPEN_BBOX_HEIGHT;
	}
	else {
		left = x - WINGS_CLOSE_BBOX_WIDTH / 2;
		top = y - WINGS_CLOSE_BBOX_HEIGHT / 2;
		right = left + WINGS_CLOSE_BBOX_WIDTH;
		bottom = top + WINGS_CLOSE_BBOX_HEIGHT;
	}
}

void CWingOfGoomba::Render()
{
	CAnimations* animation = CAnimations::GetInstance();
	if (state == WINGS_STATE_OPEN) {
		animation->Get(ID_ANI_WINGS_OPEN_LEFT)->Render(x - WING_OPEN_WIDTH, y);
		animation->Get(ID_ANI_WINGS_OPEN_RIGHT)->Render(x + WING_OPEN_WIDTH, y);
	}
	else if (state== WINGS_STATE_CLOSE) {
		animation->Get(ID_ANI_WINGS_CLOSE_LEFT)->Render(x - WING_OPEN_WIDTH, y);
		animation->Get(ID_ANI_WINGS_CLOSE_RIGHT)->Render(x + WING_OPEN_WIDTH, y);
	}
	else {
		animation->Get(ID_ANI_WINGS_FLAPPING_LEFT)->Render(x - WING_OPEN_WIDTH, y);
		animation->Get(ID_ANI_WINGS_FLAPPING_RIGHT)->Render(x + WING_OPEN_WIDTH, y);
	}
}
