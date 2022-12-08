#include "CTail.h"

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TAIL_BBOX_WIDTH / 2;
	top = y - TAIL_BBOX_HEIGHT / 2;
	right = left + TAIL_BBOX_WIDTH;
	bottom = top + TAIL_BBOX_HEIGHT;
}

void CTail::OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e)
{
	CBreakableBrick* brick = dynamic_cast<CBreakableBrick*>(e->obj);

	brick->SetState(BREAKABLEBRICK_STATE_BROKEN);
}

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBreakableBrick*>(e->obj))
		OnCollisionWithBreakableBrick(e);
}
