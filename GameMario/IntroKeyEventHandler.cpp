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
	CGame* game = CGame::GetInstance();
	MarioWorldMaps* mario = (MarioWorldMaps*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		DebugOut(L"Switch scene\n");
		break;
	case DIK_UP:
	{
		LPNodeMap nodeMap = game->getCurrentNodeMap();
		if (nodeMap->nodeUPId == -1)
			break;
		else {
			game->setCurrentNodeMap(nodeMap->nodeUPId);
			nodeMap = game->getNodeMap(nodeMap->nodeUPId);
			mario->SetPosition(nodeMap->x, nodeMap->y);
		}
		break;
	}
	case DIK_DOWN: {
		LPNodeMap nodeMap = game->getCurrentNodeMap();
		if (nodeMap->nodeDOWNId == -1)
			break;
		else {
			game->setCurrentNodeMap(nodeMap->nodeDOWNId);
			nodeMap = game->getNodeMap(nodeMap->nodeDOWNId);
			mario->SetPosition(nodeMap->x, nodeMap->y);
		}
		break;
	}
	case DIK_LEFT: {
		LPNodeMap nodeMap = game->getCurrentNodeMap();
		if (nodeMap->nodeLEFTId == -1)
			break;
		else {
			game->setCurrentNodeMap(nodeMap->nodeLEFTId);
			nodeMap = game->getNodeMap(nodeMap->nodeLEFTId);
			mario->SetPosition(nodeMap->x, nodeMap->y);
		}
		break;
	}
	case DIK_RIGHT:
		LPNodeMap nodeMap = game->getCurrentNodeMap();
		
		if (nodeMap->nodeRIGHTId == -1)
			break;
		else {
			game->setCurrentNodeMap(nodeMap->nodeRIGHTId);
			nodeMap = game->getNodeMap(nodeMap->nodeRIGHTId);
			mario->SetPosition(nodeMap->x, nodeMap->y);
		}
		break;
	}
}

void IntroKeyEventHandler::OnKeyUp(int KeyCode)
{
}
