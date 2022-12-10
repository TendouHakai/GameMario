#include "CTail.h"
#include "CTurtle.h"
#include "Goomba.h"
#include "CWingGreenTurtle.h"

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

void CTail::OnCollisionWithRedTurtle(LPCOLLISIONEVENT e)
{
	CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);

	if (turtle->GetState() != TURTLE_STATE_DEAD && turtle->GetState() != TURTLE_STATE_DEAD_TAILTURNING) {
		turtle->SetState(TURTLE_STATE_DEAD_TAILTURNING);
	}
}

void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_TAILTURNING) {
		goomba->SetState(GOOMBA_STATE_DIE_TAILTURNING);
	}
}

void CTail::OnCollisionWithWingGreenTurtle(LPCOLLISIONEVENT e) {
	CWingGreenTurtle* turtle = dynamic_cast<CWingGreenTurtle*>(e->obj);

	if (turtle->GetState() != WINGGREENTURTLE_STATE_TO_GREENTURTLE && turtle->GetState() != WINGGREENTURTLE_STATE_TAILTURNING) {
		turtle->SetState(WINGGREENTURTLE_STATE_TAILTURNING);
	}
}

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBreakableBrick*>(e->obj))
		OnCollisionWithBreakableBrick(e);
	else if (dynamic_cast<CTurtle*>(e->obj))
		OnCollisionWithRedTurtle(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CWingGreenTurtle*>(e->obj))
		OnCollisionWithWingGreenTurtle(e);
}
