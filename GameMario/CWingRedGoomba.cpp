#include "CWingRedGoomba.h"

void CWingRedGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CRedGoomba::Update(dt, coObjects);
	wings->SetPosition(x, y - GOOMBA_BBOX_HEIGHT / 2);
}

void CWingRedGoomba::Render()
{
	wings->Render();
	CRedGoomba::Render();
}
