#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "PlatformNotBlock.h"
#include "CQuestionBrick.h"
#include "CTurtle.h"
#include "ChangeCam.h"
#include "CWingGreenTurtle.h"
#include "CMushroom.h"
#include "CWingRedGoomba.h"
#include "CBullet.h"

#include "Collision.h"


void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	DebugOut(L"vx, vy: %f, %f\n", vx, vy);

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	
	isOnPlatform = false;
	isOnPlatformNotBlock = false;

	if (nx > 0)
		tail->SetPosition(x + MARIO_BIG_BBOX_WIDTH-2, y+6);
	else tail->SetPosition(x - MARIO_BIG_BBOX_WIDTH+2, y+6);
	
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (isTailTurning) {
		tail->Update(dt, coObjects);
	}
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0)
		{
			isOnPlatform = true;
			SetState(MARIO_STATE_FLY_RELEASE);
		}
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}
	
	if (dynamic_cast<CWingRedGoomba*>(e->obj))
		OnCollisionWithWingRedGoomba(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CTurtle*>(e->obj))
		OnCollisionWithRedTurtle(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<ChangeCam*>(e->obj))
		OnCollisionWithChangeCam(e);
	else if (dynamic_cast<CWingGreenTurtle*>(e->obj))
		OnCollisionWithWingGreenTurtle(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithRedMushroom(e);
	else if (dynamic_cast<CBullet*>(e->obj))
		OnCollisionWithBullet(e);
	
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithRedTurtle(LPCOLLISIONEVENT e)
{
	CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);

	if (e->ny < 0){
		if (turtle->GetState() != TURTLE_STATE_DEAD && turtle->GetState() != TURTLE_STATE_REVIVAL)
		{
			turtle->SetState(TURTLE_STATE_DEAD);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (turtle->GetState() == TURTLE_STATE_DEAD || turtle->GetState() == TURTLE_STATE_DEAD_TAILTURNING) {
			if (nx < 0) {
				isKicking = true;
				turtle->SetState(TURTLE_STATE_KICKED_RIGHT);
			}
			else {
				isKicking = true;
				turtle->SetState(TURTLE_STATE_KICKED_LEFT);
			}
		}
	}
	else {
		if (untouchable == 0 && turtle->IsUntouchable()==0)
		{
			if (turtle->GetState() != TURTLE_STATE_DEAD && turtle->GetState() != TURTLE_STATE_REVIVAL && turtle->GetState() != TURTLE_STATE_DEAD_TAILTURNING)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
			else 
				if (e->nx > 0)
				{
					isKicking = true;
					turtle->SetState(TURTLE_STATE_KICKED_RIGHT);

				}
				else if(e->nx < 0)
				{
					isKicking = true;
					turtle->SetState(TURTLE_STATE_KICKED_LEFT);

				}
		}
	}

}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	CCoin* c = dynamic_cast<CCoin*>(e->obj);
	
	c->SetState(COIN_PRICE_STATE_COLLECTION);
	coin+=100;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithPlatformNotBlock(LPCOLLISIONEVENT e)
{
	CPlatformNotBlock* platform = dynamic_cast<CPlatformNotBlock*>(e->obj);
	
	if (e->ny != 0 && this->vy>0) {
		isOnPlatformNotBlock = true;
		float x, y;
		platform->GetPosition(x, y);
		float l,t,r,b;
		platform->GetBoundingBox(l,t,r,b);
		yPlatformNotBlock = y - (b-t)/2;
	}
	
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionBr = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->ny > 0) {
		if (questionBr->GetState() == QUESTIONBRICK_STATE_IDLE) {
			questionBr->SetState(QUESTIONBRICK_STATE_BROKEN);
		}
	}
}

void CMario::OnCollisionWithChangeCam(LPCOLLISIONEVENT e)
{
	ChangeCam* changeCam = dynamic_cast<ChangeCam*>(e->obj);
	if(e->nx < 0)
		if (changeCam->GetChangeCamType() == CHAGE_TYPE_FORCUS_PLAYER) {
			CGame::GetInstance()->isForcusPlayer = true;
			CGame::GetInstance()->yChangeCamMax = changeCam->yCamMax;
			CGame::GetInstance()->yChangeCamMin = changeCam->yCamMin;
		}
		else {
			CGame::GetInstance()->isForcusPlayer = false;
		}
	else if (e->nx > 0) {
		CGame::GetInstance()->isForcusPlayer = false;
	}
}

void CMario::OnCollisionWithWingGreenTurtle(LPCOLLISIONEVENT e)
{
	CWingGreenTurtle* winggreenturtle = dynamic_cast<CWingGreenTurtle*>(e->obj);
	if (e->ny < 0)
	{
		winggreenturtle->SetState(WINGGREENTURTLE_STATE_TO_GREENTURTLE);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}

void CMario::OnCollisionWithRedMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	if (level == MARIO_LEVEL_SMALL)
		SetLevel(MARIO_LEVEL_BIG);
	else if (level == MARIO_LEVEL_BIG) {
		SetLevel(MARIO_LEVEL_RACCON);
	}
	mushroom->Delete();
}

void CMario::OnCollisionWithWingRedGoomba(LPCOLLISIONEVENT e)
{
	CWingRedGoomba* wingredgoomba = dynamic_cast<CWingRedGoomba*>(e->obj);

	if (e->ny < 0) {
		if (wingredgoomba->GetState() != WINGGOOMBA_STATE_TOREDGOOMBA) {
			wingredgoomba->SetState(WINGGOOMBA_STATE_TOREDGOOMBA);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			y -= 10;
		}
	}
	else {
		if (untouchable == 0)
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}

void CMario::OnCollisionWithBullet(LPCOLLISIONEVENT e)
{
	CBullet* butlet = dynamic_cast<CBullet*>(e->obj);
	
	if (level != MARIO_LEVEL_SMALL) {
		level -= 1;
	}
	else {
		SetState(MARIO_STATE_DIE);
	}

	butlet->Delete();
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (isOnPlatform == false && isOnPlatformNotBlock == false)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


int CMario::GetAniRaccon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isTailTurning) {
			if (nx > 0) aniId = ID_ANI_MARIO_RACCON_TAIL_TURNING_RIGHT;
			else if (nx < 0) aniId = ID_ANI_MARIO_RACCON_TAIL_TURNING_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				if(ay<=MARIO_GRAVITY_FLY)
					aniId = ID_ANI_MARIO_RACCON_FLY_RIGHT;
				else aniId = ID_ANI_MARIO_RACCON_JUMP_RUN_RIGHT;
			else
				if(ay<=MARIO_GRAVITY_FLY)
					aniId = ID_ANI_MARIO_RACCON_FLY_LEFT;
				else aniId = ID_ANI_MARIO_RACCON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCON_SIT_LEFT;
		}
		else 
			if (isKicking) {
				isKicking = false;
				if (vx > 0)
					aniId = ID_ANI_MARIO_RACCON_KICK_RIGHT;
				else if (vx < 0)
					aniId = ID_ANI_MARIO_RACCON_KICK_LEFT;
			}
			else if (isTailTurning) {
				if (nx > 0) aniId = ID_ANI_MARIO_RACCON_TAIL_TURNING_RIGHT;
				else if (nx < 0) aniId = ID_ANI_MARIO_RACCON_TAIL_TURNING_LEFT;
			}
			else if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCON_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (isOnPlatform==false)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isKicking) {
			isKicking = false;
			if (vx > 0)
				aniId = ID_ANI_MARIO_KICK_RIGHT;
			else if (vx < 0)
				aniId = ID_ANI_MARIO_KICK_LEFT;
		}
		else if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	float xx = x;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_RACCON) {
		aniId = GetAniRaccon();
		if (nx > 0) { 
			if (!isTailTurning)
				xx -= 2;
			else xx += 3;
		}
		else { 
			if (!isTailTurning)
				xx += 2;
			else xx -= 3;
		}
	}
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	animations->Get(aniId)->Render(xx, y);
	tail->Render();

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform || isOnPlatformNotBlock)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_FLY:
		if (level != MARIO_LEVEL_RACCON) break;
		if (!isOnPlatform && !isOnPlatformNotBlock) {
			if (abs(this->vx) == MARIO_RUNNING_SPEED) {
				ay = 0.0f;
				vy = -MARIO_RUNNING_SPEED;
			}
			else ay = MARIO_GRAVITY_FLY;
		}
		break;
	case MARIO_STATE_FLY_RELEASE:
		ay = MARIO_GRAVITY;
		break;
	case MARIO_STATE_TAIL_TURNING: {
		isTailTurning = true;
		break;
	}
	case MARIO_STATE_TAIL_TURNING_RELEASE: {
		isTailTurning = false;
		break;
	}
	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level!=MARIO_LEVEL_SMALL)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}

	/*if (level == MARIO_LEVEL_SMALL) {
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_BIG) {
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACCON) {
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			if (nx > 0) {
				left = x - MARIO_BIG_BBOX_WIDTH / 2;
				top = y - MARIO_BIG_BBOX_HEIGHT / 2;
				right = left + MARIO_BIG_BBOX_WIDTH;
				bottom = top + MARIO_BIG_BBOX_HEIGHT;
			}
			else {
				left = x - MARIO_BIG_BBOX_WIDTH / 2;
				top = y - MARIO_BIG_BBOX_HEIGHT / 2;
				right = left + MARIO_BIG_BBOX_WIDTH;
				bottom = top + MARIO_BIG_BBOX_HEIGHT;
			}
			
		}*/
	
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

