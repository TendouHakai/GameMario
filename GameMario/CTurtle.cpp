#include "CTurtle.h"
#include "PlatformNotBlock.h"
#include "CQuestionBrick.h"

void CTurtleCheck::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TURTLECHECK_BBOX_WIDTH / 2;
	top = y - TURTLECHECK_BBOX_HEIGHT / 2;
	right = left + TURTLECHECK_BBOX_WIDTH;
	bottom = top + TURTLECHECK_BBOX_HEIGHT;
}

void CTurtleCheck::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}


void CTurtleCheck::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}

}

void CTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TURTLE_STATE_WALK) {
		left = x - TURTLE_BBOX_WIDTH / 2;
		top = y - TURTLE_BBOX_HEIGHT / 2;
		right = left + TURTLE_BBOX_WIDTH;
		bottom = top + TURTLE_BBOX_HEIGHT;
	}
	else {
		left = x - TURTLE_DEAD_BBOX_WIDTH / 2;
		top = y - TURTLE_DEAD_BBOX_HEIGHT / 2;
		right = left + TURTLE_DEAD_BBOX_WIDTH;
		bottom = top + TURTLE_DEAD_BBOX_HEIGHT;
	}
}

void CTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (vx > 0) {
		check->SetPositionX(x + 18);
	}
	else { 
		check->SetPositionX(x - 18); 
	}
}

void CTurtle::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* brick = dynamic_cast<CQuestionBrick*>(e->obj);

	if (e->nx != 0) {
		brick->SetState(QUESTIONBRICK_STATE_BROKEN);
	}
}

void CTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == TURTLE_STATE_KICKED_LEFT || state == TURTLE_STATE_KICKED_RIGHT) {
		if (dynamic_cast<CQuestionBrick*>(e->obj)) {
			OnCollisionWithQuestionBrick(e);
		}
	}
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CTurtle::Render()
{
	int aniID;

	switch (state)
	{
	case TURTLE_STATE_WALK: {
		if (vx > 0) {
			aniID = ID_ANI_TURTLE_WALK_RIGHT;
		}
		else aniID = ID_ANI_TURTLE_WALK_LEFT;
		break;
	}
	case TURTLE_STATE_DEAD: {
		aniID = ID_ANI_TURTLE_DEAD;
		break;
	}
	case TURTLE_STATE_DEAD_TAILTURNING: {
		aniID = ID_ANI_TURTLE_DEAD;
		break;
	}
	case TURTLE_STATE_REVIVAL: {
		aniID = ID_ANI_TURTLE_REVIVAL;
		break;
	}
	case TURTLE_STATE_KICKED_RIGHT: {
		aniID = ID_ANI_TURTLE_DEAD;
		break;
	}
	case TURTLE_STATE_KICKED_LEFT: {
		aniID = ID_ANI_TURTLE_DEAD;
		break;
	}
	default: {
		if (vx > 0) {
			aniID = ID_ANI_TURTLE_WALK_RIGHT;
		}
		else aniID = ID_ANI_TURTLE_WALK_LEFT;
		break;
	}	
	}
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
	check->Render();
}


