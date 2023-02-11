#include "StartSceneKeyHandler.h"
#include "Game.h"
#include "PlayScene.h"

void StartSceneKeyHandler::KeyState(BYTE* states)
{
}

void StartSceneKeyHandler::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	switch (KeyCode)
	{
	case DIK_UP:
	{
		CPlayScene* C_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		C_scene->selectMenu = 0;
		break;
	}
	case DIK_DOWN: {
		CPlayScene* C_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		C_scene->selectMenu = 1;
		break;
	}
	case DIK_S: {
		CGame::GetInstance()->InitiateSwitchScene(1001);
		break;
	}
	}
}

void StartSceneKeyHandler::OnKeyUp(int KeyCode)
{
}
