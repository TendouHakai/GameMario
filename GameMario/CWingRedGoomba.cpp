#include "CWingRedGoomba.h"

void CWingRedGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - GOOMBA_BBOX_WIDTH / 2;
	top = y - GOOMBA_BBOX_HEIGHT / 2;
	right = left + GOOMBA_BBOX_WIDTH;
	bottom = top + GOOMBA_BBOX_HEIGHT;
}

void CWingRedGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if ((state == WINGGOOMBA_STATE_WALK) && (GetTickCount64() - walk_start > TIME_WALK))
	{
		walk_start = 0;
		SetState(WINGGOOMBA_STATE_PREPARETOFLY);
	}
	if ((state == WINGGOOMBA_STATE_PREPARETOFLY) && (GetTickCount64() - prepare_start > TIME_PREPARE)) {
		prepare_start = 0;
		SetState(WINGGOOMBA_STATE_FLY);
	}
	if (state == WINGGOOMBA_STATE_TOREDGOOMBA) {
		CRedGoomba* goomba = new CRedGoomba(x, y);
		coObjects->push_back(goomba);
		this->Delete();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	wings->SetPosition(x, y - GOOMBA_BBOX_HEIGHT / 2);
}

void CWingRedGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0) {
			if (state == WINGGOOMBA_STATE_FLY) {
				SetState(WINGGOOMBA_STATE_WALK);
			}
			else if (state == WINGGOOMBA_STATE_PREPARETOFLY) {
				vy = -WINGGOOMBA_SPEED_Y_PREPARE;
			}
		}
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CWingRedGoomba::Render()
{
	if (state == WINGGOOMBA_STATE_WALK) {
		wings->SetState(WINGS_STATE_CLOSE);
	}
	else if (state == WINGGOOMBA_STATE_PREPARETOFLY) {
		wings->SetState(WINGS_STATE_FLAPPING);
	}
	else {
		wings->SetState(WINGS_STATE_OPEN);
	}

	wings->Render();
	CAnimations::GetInstance()->Get(ID_ANI_REDGOOMBA_WALKING)->Render(x, y);
	
}

void CWingRedGoomba::SetState(int state)
{
	switch (state)
	{
	case WINGGOOMBA_STATE_WALK: {
		walk_start = GetTickCount64();
		break;
	}
	case WINGGOOMBA_STATE_PREPARETOFLY: {
		prepare_start = GetTickCount64();
		vy = -WINGGOOMBA_SPEED_Y_PREPARE;
		break;
	}
	case WINGGOOMBA_STATE_FLY: {
		vy = -WINGGOOMBA_SPEED_Y;
		break;
	}
	case WINGGOOMBA_STATE_TOREDGOOMBA: {
		break;
	}
	default:
		break;
	}
	this->state = state;
}
