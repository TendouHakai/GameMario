#include "IntroKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "PlayScene.h"
#include "MarioWorldMaps.h"

void IntroKeyEventHandler::KeyState(BYTE* states)
{

}

void IntroKeyEventHandler::OnKeyDown(int KeyCode)
{
	MarioWorldMaps* mario = (MarioWorldMaps*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		DebugOut(L"Switch scene\n");
		break;
	case DIK_UP:
		mario->SetState(MARIOW_STATE_UP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIOW_STATE_DOWN);
		break;
	case DIK_LEFT:
		mario->SetState(MARIOW_STATE_LEFT);
		break;
	case DIK_RIGHT:
		mario->SetState(MARIOW_STATE_RIGHT);
		break;
	}
}

void IntroKeyEventHandler::OnKeyUp(int KeyCode)
{
}
