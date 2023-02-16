#include "IntroKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "PlayScene.h"
#include "MarioWorldMaps.h"
#include "CircleShuriken.h"

void IntroKeyEventHandler::KeyState(BYTE* states)
{

}

void IntroKeyEventHandler::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	MarioWorldMaps* mario = (MarioWorldMaps*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_UP:
	{
		CPlayScene* C_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		if (CGame::GetInstance()->isGameOver == true) {
			if (C_scene->selectMenu > 0)
				C_scene->selectMenu--;
		}
		else {
			LPNodeMap nodeMap = game->getCurrentNodeMap();
			
			if (nodeMap->nodeUPId == -1)
				break;
			else if (nodeMap->type == NODEMAP_TYPE_MISSION && nodeMap->status != NODEMAP_STATE_DONE && game->getNodeMap(nodeMap->nodeUPId)->status != NODEMAP_STATE_DONE)
				break;
			else {
				if (nodeMap->type != NODEMAP_TYPE_MISSION)
					nodeMap->setDone();
				game->setCurrentNodeMap(nodeMap->nodeUPId);
				nodeMap = game->getNodeMap(nodeMap->nodeUPId);
				mario->xNext = nodeMap->x;
				mario->yNext = nodeMap->y;
				mario->SetState(MARIOW_STATE_UP);
				//mario->SetPosition(nodeMap->x, nodeMap->y);
			}
		}
		break;
	}
	case DIK_DOWN: {
		CPlayScene* C_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		if (CGame::GetInstance()->isGameOver == true) {
			if (C_scene->selectMenu < 1)
				C_scene->selectMenu++;
		}
		else {
			LPNodeMap nodeMap = game->getCurrentNodeMap();
			
			if (nodeMap->nodeDOWNId == -1)
				break;
			else if (nodeMap->type == NODEMAP_TYPE_MISSION && nodeMap->status != NODEMAP_STATE_DONE && game->getNodeMap(nodeMap->nodeDOWNId)->status != NODEMAP_STATE_DONE)
				break;
			else {
				if(nodeMap->type != NODEMAP_TYPE_MISSION)
					nodeMap->setDone();
				game->setCurrentNodeMap(nodeMap->nodeDOWNId);
				nodeMap = game->getNodeMap(nodeMap->nodeDOWNId);
				mario->xNext = nodeMap->x;
				mario->yNext = nodeMap->y;
				mario->SetState(MARIOW_STATE_DOWN);
				//mario->SetPosition(nodeMap->x, nodeMap->y);
			}
		}
		break;
	}
	case DIK_LEFT: {
		LPNodeMap nodeMap = game->getCurrentNodeMap();
		if (nodeMap->nodeLEFTId == -1)
			break;
		else if (nodeMap->type == NODEMAP_TYPE_MISSION && nodeMap->status != NODEMAP_STATE_DONE && game->getNodeMap(nodeMap->nodeLEFTId)->status != NODEMAP_STATE_DONE) {
			break;
		}
		else {
			if (nodeMap->type != NODEMAP_TYPE_MISSION)
				nodeMap->setDone();
			game->setCurrentNodeMap(nodeMap->nodeLEFTId);
			nodeMap = game->getNodeMap(nodeMap->nodeLEFTId);
			mario->xNext = nodeMap->x;
			mario->yNext = nodeMap->y;
			mario->SetState(MARIOW_STATE_LEFT);
			//mario->SetPosition(nodeMap->x, nodeMap->y);
		}
		break;
	}
	case DIK_RIGHT: {
		LPNodeMap nodeMap = game->getCurrentNodeMap();

		if (nodeMap->nodeRIGHTId == -1)
			break;
		else if (nodeMap->type == NODEMAP_TYPE_MISSION && nodeMap->status != NODEMAP_STATE_DONE && game->getNodeMap(nodeMap->nodeRIGHTId)->status != NODEMAP_STATE_DONE)
			break;
		else {
			if (nodeMap->type != NODEMAP_TYPE_MISSION)
				nodeMap->setDone();
			game->setCurrentNodeMap(nodeMap->nodeRIGHTId);
			nodeMap = game->getNodeMap(nodeMap->nodeRIGHTId);
			mario->xNext = nodeMap->x;
			mario->yNext = nodeMap->y;
			mario->SetState(MARIOW_STATE_RIGHT);
			//mario->SetPosition(nodeMap->x, nodeMap->y);
		}
		break;
	}
	case DIK_S: {
		CPlayScene* C_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		if (CGame::GetInstance()->isStartM) {
			CGame::GetInstance()->isStartM = false;
			CGameObject* obj = new CircleShuriken(150, 80, 68, 50);
			C_scene->addGameObject(obj);
		}
		else if (CGame::GetInstance()->isGameOver) {
			if (C_scene->selectMenu == GAME_OVER_SELECT_CONTINUE) {
				CGame::GetInstance()->M = 4;
				CGame::GetInstance()->isGameOver = false;
				CGame::GetInstance()->isStartM = true;
				CGame::GetInstance()->clearWorlMap();
				C_scene->Clear();
				C_scene->Load();

			}
			else {
				exit(0);
			}
		}
		else {
			LPNodeMap nodeMap = game->getCurrentNodeMap();
			if (nodeMap->sceneID == -1 || nodeMap->status == NODEMAP_STATE_DONE)
				break;
			CGame::GetInstance()->InitiateSwitchScene(nodeMap->sceneID);
		}
		break;
	}
		
	}
}

void IntroKeyEventHandler::OnKeyUp(int KeyCode)
{
}
