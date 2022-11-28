#include "CTurtle.h"
#include "PlatformNotBlock.h"

void CTurtleCheck::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TURTLE_BBOX_WIDTH / 2;
	top = y - TURTLE_BBOX_HEIGHT / 2;
	right = left + TURTLE_BBOX_WIDTH;
	bottom = top + TURTLE_BBOX_HEIGHT;
}

void CTurtleCheck::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CTurtleCheck::OnCollisionWithPlatformNotBlock(LPCOLLISIONEVENT e)
{
	CPlatformNotBlock* platform = dynamic_cast<CPlatformNotBlock*>(e->obj);

	if (e->ny != 0 && this->vy > 0) {
		isOnPlatformNotBlock = true;
		float x, y;
		platform->GetPosition(x, y);
		float l, t, r, b;
		platform->GetBoundingBox(l, t, r, b);
		yPlatformNotBlock = y - (b - t) / 2;
	}
}

void CTurtleCheck::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPlatformNotBlock*>(e->obj))
		OnCollisionWithPlatformNotBlock(e);
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

void CTurtle::OnCollisionWithPlatformNotBlock(LPCOLLISIONEVENT e)
{
	CPlatformNotBlock* platform = dynamic_cast<CPlatformNotBlock*>(e->obj);

	if (e->ny != 0 && this->vy > 0) {
		isOnPlatformNotBlock = true;
		float x, y;
		platform->GetPosition(x, y);
		float l, t, r, b;
		platform->GetBoundingBox(l, t, r, b);
		yPlatformNotBlock = y - (b - t) / 2;
	}
}

void CTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPlatformNotBlock*>(e->obj))
		OnCollisionWithPlatformNotBlock(e);
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
	case TURTLE_STATE_REVIVAL: {
		aniID = ID_ANI_TURTLE_REVIVAL;
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


