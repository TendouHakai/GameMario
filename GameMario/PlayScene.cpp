#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "PlatformNotBlock.h"
#include "CQuestionBrick.h"
#include "CCannibalFlower.h"
#include "CBullet.h"
#include "CTurtle.h"
#include "ChangeCam.h"
#include "CGreenTurtle.h"
#include "CWingGreenTurtle.h"
#include "CPlatformSprite.h"
#include "CWoodBrick.h"
#include "CBreakableBrick.h"
#include "CTube.h"
#include "CMushroom.h"
#include "CRedGoomba.h"
#include "CWingOfGoomba.h"
#include "CWingRedGoomba.h"
#include "CBLockEnemies.h"
#include "CVenusflytrapFlower.h"
#include "CBreakableBrickButton.h"
#include "CNodeMapG.h"

#include "SampleKeyEventHandler.h"
#include "IntroKeyEventHandler.h"

#define ID_ANI_PAUSE	28021
#define ID_TEX_PAUSE_BACKGROUND	-101

#define ID_ANI_GAMEOVER_MENU	28022
#define ID_ANI_GAMEOVER_POINT	28023

using namespace std;

CPlayScene::CPlayScene(int id, string filePath):
	CScene(id, filePath)
{	
	map = NULL;
	player = NULL;
	if (id > 1000)
		key_handler = new IntroKeyEventHandler(this);
	else key_handler = new CSampleKeyHandler(this);
}


/*
	Parse a line in section [OBJECTS] 
*/
//void CPlayScene::_ParseSection_OBJECTS(string line)
//{
//	vector<string> tokens = split(line);
//
//	// skip invalid lines - an object set must have at least id, x, y
//	if (tokens.size() < 2) return;
//
//	int object_type = atoi(tokens[0].c_str());
//	float x = (float)atof(tokens[1].c_str());
//	float y = (float)atof(tokens[2].c_str());
//
//	CGameObject *obj = NULL;
//
//	switch (object_type)
//	{
//	case OBJECT_TYPE_MARIO:
//		if (player!=NULL) 
//		{
//			DebugOut(L"[ERROR] MARIO object was created before!\n");
//			return;
//		}
//		obj = new CMario(x,y); 
//		player = (CMario*)obj;  
//
//		DebugOut(L"[INFO] Player object has been created!\n");
//		break;
//	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x,y); break;
//	case OBJECT_TYPE_BRICK: obj = new CBrick(x,y); break;
//	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
//
//	case OBJECT_TYPE_PLATFORM:
//	{
//
//		float cell_width = (float)atof(tokens[3].c_str());
//		float cell_height = (float)atof(tokens[4].c_str());
//		int length = atoi(tokens[5].c_str());
//		int sprite_begin = atoi(tokens[6].c_str());
//		int sprite_middle = atoi(tokens[7].c_str());
//		int sprite_end = atoi(tokens[8].c_str());
//
//		obj = new CPlatform(
//			x, y,
//			cell_width, cell_height, length,
//			sprite_begin, sprite_middle, sprite_end
//		);
//
//		break;
//	}
//
//	case OBJECT_TYPE_PORTAL:
//	{
//		float r = (float)atof(tokens[3].c_str());
//		float b = (float)atof(tokens[4].c_str());
//		int scene_id = atoi(tokens[5].c_str());
//		obj = new CPortal(x, y, r, b, scene_id);
//	}
//	break;
//
//
//	default:
//		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
//		return;
//	}
//
//	// General object setup
//	obj->SetPosition(x, y);
//
//
//	objects.push_back(obj);
//}

void CPlayScene::loadMap(string mapFile)
{
	map = CGame::GetInstance()->LoadTexture(ToLPCWSTR(mapFile));
}

void CPlayScene::LoadAssets(string assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	TiXmlDocument doc(assetFile.c_str());
	if (doc.LoadFile()) {
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* sprites = root->FirstChildElement("SPRITES");
		TiXmlElement* animations = root->FirstChildElement("ANIMATIONS");

		// đọc sprites
		for (TiXmlElement* node = sprites->FirstChildElement("Sprite"); node != nullptr; node = node->NextSiblingElement("Sprite")) {
			int ID = atoi(node->Attribute("spriteID"));
			int l = atoi(node->Attribute("l"));
			int t = atoi(node->Attribute("t"));
			int r = atoi(node->Attribute("r"));
			int b = atoi(node->Attribute("b"));
			int texID = atoi(node->Attribute("textureID"));

			LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
			if (tex == NULL)
			{
				DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
				return;
			}

			CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
		}
		// đọc animation
		for (TiXmlElement* node = animations->FirstChildElement("animation"); node != nullptr; node = node->NextSiblingElement("animation")) {
			int ani_id = atoi(node->Attribute("aniID"));
			LPANIMATION ani = new CAnimation();
			for (TiXmlElement* nodeSprite = node->FirstChildElement("Sprite"); nodeSprite != nullptr; nodeSprite = nodeSprite->NextSiblingElement("Sprite"))	// why i+=2 ?  sprite_id | frame_time  
			{
				int sprite_id = atoi(nodeSprite->Attribute("SpriteID"));
				int frame_time = atoi(nodeSprite->Attribute("time"));
				ani->Add(sprite_id, frame_time);
			}

			CAnimations::GetInstance()->Add(ani_id, ani);
		}
	}
	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);
	// create HUB
	if (id < 1000)
	{
		isStart = 1;
		timeStart = GetTickCount64();
	}
	else isStart = 0;
	hub = new CHUB(50,400);
	isPAUSE = false;
	selectGameOverMenu = GAME_OVER_SELECT_CONTINUE;

	TiXmlDocument doc(sceneFilePath.c_str());
	if (doc.LoadFile()) {
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* mapXML = root->FirstChildElement("MAP");
		TiXmlElement* tilemap = root->FirstChildElement("TILEMAP");
		TiXmlElement* assetsXML = root->FirstChildElement("ASSETS");
		TiXmlElement* objectsXML = root->FirstChildElement("OBJECTS");
		// đọc map
		if (mapXML != NULL)
		{
			loadMap(mapXML->Attribute("link"));
			if (id > 1000 && !CGame::GetInstance()->checkWorldMap())
			{
				mapL = atoi(mapXML->Attribute("l"));
				mapT = atoi(mapXML->Attribute("t"));
				mapR = atoi(mapXML->Attribute("r"));
				mapB = atoi(mapXML->Attribute("b"));
				// load nodemaps
				for (TiXmlElement* node = mapXML->FirstChildElement("nodemap"); node != nullptr; node = node->NextSiblingElement("nodemap")) {
					int nodemapID = atoi(node->Attribute("id"));
					float x = (float)atoi(node->Attribute("x"));
					float y = (float)atoi(node->Attribute("y"));
					int idLEFT = atoi(node->Attribute("left"));
					int idRIGHT = atoi(node->Attribute("right"));
					int idTOP = atoi(node->Attribute("top"));
					int idBOTTOM = atoi(node->Attribute("bottom"));
					int sceneID = atoi(node->Attribute("sceneID"));

					LPNodeMap nodeMap = new CNodeMap(x, y, idLEFT, idRIGHT, idTOP, idBOTTOM, sceneID);
					CGame::GetInstance()->addNodemap(nodemapID, nodeMap);
				}
				CGame::GetInstance()->setcurrentWorldMap();
			}
		}
		// đọc tile map
		if (tilemap != NULL)
		{
			tileMap = new CTileMap(tilemap->Attribute("filePath"));	
		}
		// đọc assets
		if(assetsXML!=NULL)
			for (TiXmlElement* node = assetsXML->FirstChildElement("asset"); node != nullptr; node = node->NextSiblingElement("asset")) {
				LoadAssets(node->Attribute("link"));
			}
		// đọcc objects
		if(objectsXML !=NULL)
			for (TiXmlElement* node = objectsXML->FirstChildElement("object"); node != nullptr; node = node->NextSiblingElement("object")) {
				int objectID = atoi(node->Attribute("type"));
				float x = (float)atoi(node->Attribute("x"));
				float y = (float)atoi(node->Attribute("y"));
				CGameObject* obj = NULL;
				switch (objectID)
				{
				case OBJECT_TYPE_MARIO_WORLDMAP: {
					if (player != NULL) {
						DebugOut(L"[ERROR] MARIO object was created before!\n");
						return;
					}
					if (CGame::GetInstance()->getCurrentNodeMap()!= nullptr) {
						x = CGame::GetInstance()->getCurrentNodeMap()->x;
						y = CGame::GetInstance()->getCurrentNodeMap()->y;
					}
					else{
						int start = atoi(node->Attribute("start"));
						CGame::GetInstance()->setCurrentNodeMap(start);
						x = CGame::GetInstance()->getNodeMap(start)->x;
						y = CGame::GetInstance()->getNodeMap(start)->y;
					}
					obj = new MarioWorldMaps(x, y);
					player = (MarioWorldMaps*)obj;

					DebugOut(L"[INFO] Player object has been created!\n");
					break;
				}
				case OBJECT_TYPE_NODEMAP_WORLDMAP: {
					int nodeid = atoi(node->Attribute("nodeId"));
					x = CGame::GetInstance()->getNodeMap(nodeid)->x;
					y = CGame::GetInstance()->getNodeMap(nodeid)->y;
					int nodeType = atoi(node->Attribute("nodeType"));

					obj = new CNodeMapG(x, y, nodeType);
					obj->SetState(CGame::GetInstance()->getNodeMap(nodeid)->status);
					break;
				}
				case OBJECT_TYPE_MARIO:
					if (player != NULL)
					{
						DebugOut(L"[ERROR] MARIO object was created before!\n");
						return;
					}
					obj = new CMario(x, y);
					player = (CMario*)obj;

					DebugOut(L"[INFO] Player object has been created!\n");
					break;
				case OBJECT_TYPE_BRICK: 
				{
					obj = new CBrick(x, y);
					break; 
				}
				case OBJECT_TYPE_WOODBRICK: {
					obj = new CWoodBrick(x, y); break;
				}
				case OBJECT_TYPE_BREAKABLEBRICK: {
					obj = new CBreakableBrick(x, y); break;
				}
				case OBJECT_TYPE_PLATFORM:
				{
				
					float cell_width = (float)atof(node->Attribute("cellW"));
					float cell_height = (float)atof(node->Attribute("cellH"));
					int length = atoi(node->Attribute("length"));
				
					obj = new CPlatform(
						x, y,
						cell_width, cell_height, length
					);
				
					break;
				}
				case OBJECT_TYPE_PLATFORM_NOTBLOCK: {
					float cell_width = (float)atof(node->Attribute("cellW"));
					float cell_height = (float)atof(node->Attribute("cellH"));
					int length = atoi(node->Attribute("length"));

					obj = new CPlatformNotBlock(
						x, y,
						cell_width, cell_height, length
					);
					break;
				}
				case OBJECT_TYPE_QUESTIONBRICK: {
					int BrickType = atoi(node->Attribute("brickType"));
					obj = new CQuestionBrick(x, y, BrickType);
					break;
				}
				case OBJECT_TYPE_COIN: {
					obj = new CCoin(x, y);
					break;
				}
				case OBJECT_TYPE_CANNIBALFLOWER: {
					obj = new CCannibalFlower(x, y);
					break;
				}
				case OBJECT_TYPE_BULLET: {
					obj = new CBullet(x, y);
					break;
				}
				case OBJECT_TYPE_REDTURTLE: {
					obj = new CTurtle(x, y);
					break;
				}
				case OBJECT_TYPE_REDTURTLE_CHECK: {
					obj = new CTurtleCheck(x, y);
					break;
				}
				case OBJECT_TYPE_CHANGECAM: {
					float w = (float)atof(node->Attribute("w"));
					float h = (float)atof(node->Attribute("h"));
					float yChangeCamMax = (float)atof(node->Attribute("yCamMax"));
					float yChangeCamMin = (float)atof(node->Attribute("yCamMin"));
					obj = new ChangeCam(x, y, w, h, yChangeCamMax, yChangeCamMin);
					break;
				}
				case OBJECT_TYPE_GREENTURTLE: {
					obj = new CGreenTurtle(x, y);
					break;
				}
				case OBJECT_TYPE_WINGGREENTURTLE: {
					obj = new CWingGreenTurtle(x, y);
					break;
				}
				case OBJECT_TYPE_PLATFORMSPRITE: {
					float cell_width = (float)atof(node->Attribute("cellW"));
					float cell_height = (float)atof(node->Attribute("cellH"));
					int length = atoi(node->Attribute("length"));
					int idBegin = atoi(node->Attribute("idSpriteBegin"));
					int idMiddle = atoi(node->Attribute("idSpriteMiddle"));
					int idEnd = atoi(node->Attribute("idSpriteEnd"));

					obj = new CPlatformSprite(
						x, y,
						cell_width, cell_height, length,
						idBegin, idMiddle, idEnd
					);
					break;
				}
				case OBJECT_TYPE_GREENTUBE: {
					float cell_width = (float)atof(node->Attribute("cellW"));
					float cell_height = (float)atof(node->Attribute("cellH"));
					int height = atoi(node->Attribute("height"));
					int idTL = atoi(node->Attribute("idSpriteTL"));
					int idTR = atoi(node->Attribute("idSpriteTR"));
					int idML = atoi(node->Attribute("idSpriteML"));
					int idMR = atoi(node->Attribute("idSpriteMR"));
					int idBL = atoi(node->Attribute("idSpriteBL"));
					int idBR = atoi(node->Attribute("idSpriteBR"));

					obj = new CTube(x, y, cell_width, cell_height, height, idTL, idTR, idML, idMR, idBL, idBR);
					break;
				}
				case OBJECT_TYPE_MUSHROOM: {
					obj = new CMushroom(x, y);
					break;
				}
				case OBJECT_TYPE_GOOMBA: {
					obj = new CGoomba(x, y);
					break;
				}
				case OBJECT_TYPE_REDGOOMBA: {
					obj = new CRedGoomba(x, y);
					break;
				}
				case OBJECT_TYPE_WINGOFREDGOOMBA: {
					obj = new CWingOfGoomba(x, y);
					break;
				}
				case OBJECT_TYPE_WINGREDGOOMBA: {
					obj = new CWingRedGoomba(x, y);
					break;
				}
				case OBJECT_TYPE_BLOCKENEMIES: {
					float width = (float)atof(node->Attribute("width"));
					float height = (float)atof(node->Attribute("height"));
					obj = new CBLockEnemies(x, y, width, height);
					break;
				}
				case OBJECT_TYPE_VENUSFLYTRAPFLOWER: {
					obj = new CVenusflytrapFlower(x, y);
					break;
				}
				case OBJECT_TYPE_BREAKBLEBRICKBUTTON: {
					obj = new CbreakableBrickButton(x, y);
					CbreakableBrickButton* button = dynamic_cast<CbreakableBrickButton*>(obj);
					float amount = (float)atof(node->Attribute("amount"));
					for (size_t i = objects.size()-1; i>0 && amount>0; i--)
					{
						if (dynamic_cast<CBreakableBrick*>(objects[i])) {
							CBreakableBrick* brick = dynamic_cast<CBreakableBrick*>(objects[i]);
							button->addBrick(brick);
						}
						amount--;
					}
				
					break;
				}
				case OBJECT_TYPE_TELEPORT: {
					float xtele = (float)atof(node->Attribute("xtele"));
					float ytele = (float)atof(node->Attribute("ytele"));
					float yChangeCamMin = (float)atof(node->Attribute("yChangeCamMin"));
					float yChangeCamMax = (float)atof(node->Attribute("yChangeCamMax"));

					obj = new CTelePort(x, y, xtele, ytele, yChangeCamMin, yChangeCamMax);
					break;
				}
				}

				obj->SetPosition(x, y);
				objects.push_back(obj);
			}

	}


	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	// update HUB
	if (isPAUSE == false) {
		if (isStart == 1 && GetTickCount64() - timeStart > 1000)
		{
			CGame::GetInstance()->time += 1;
			timeStart = GetTickCount64();
		}
	}

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	if(isPAUSE==false){
		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &objects);
		}
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;

	if (cx < 0) cx = 0;
	else if (cx + game->GetBackBufferWidth() > map->getWidth() ) cx = map->getWidth() - game->GetBackBufferWidth();
	if (cy < 0) cy = 0;

	if (id < 1000) {
		float height = CGame::GetInstance()->GetBackBufferHeight();

		if (CGame::GetInstance()->isForcusPlayer == false) {
			cy = CGame::GetInstance()->yForcusMin - (0.7 * height / 4);
		}
		else {
			if (cy <= CGame::GetInstance()->yForcusMin) {
				CGame::GetInstance()->yForcusMin = cy;
				CGame::GetInstance()->yForcusMax = cy + height / 2 + 0.3*height/4;
				cy = cy - (1 * height / 4);
			}
			else if (cy >= CGame::GetInstance()->yForcusMax) {
				CGame::GetInstance()->yForcusMax = cy;
				CGame::GetInstance()->yForcusMin = cy - height / 2;
				cy = cy - (3 * height / 4);
			}
			else {
				cy = CGame::GetInstance()->yForcusMin - (1 * height / 4);;
			}
			if (cy > CGame::GetInstance()->yChangeCamMax) {
				cy = CGame::GetInstance()->yChangeCamMax; CGame::GetInstance()->isForcusPlayer = false;
				CGame::GetInstance()->yForcusMin = CGame::GetInstance()->yChangeCamMax + (1 * height / 4);
				CGame::GetInstance()->yForcusMax = CGame::GetInstance()->yChangeCamMax + (3 * height / 4);
			}
			if (cy < CGame::GetInstance()->yChangeCamMin) cy = CGame::GetInstance()->yChangeCamMin;

		}
	}
	else {
		float xC, yC;
		CGame::GetInstance()->GetCamPos(xC, yC);
		cy = yC;
		cx = xC;
	}
	
	CGame::GetInstance()->SetCamPos(cx, cy);
	if(id<1000)
		tileMap->SetTileRender(cx, cy, cx+CGame::GetInstance()->GetBackBufferWidth(), cy+CGame::GetInstance()->GetBackBufferHeight());

	PurgeDeletedObjects();
}

void CPlayScene::RenderPauseBackground()
{
	RECT rect;
	float sx, sy;
	sx = CGame::GetInstance()->GetBackBufferWidth();
	sy = CGame::GetInstance()->GetBackBufferHeight();

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_PAUSE_BACKGROUND);

	rect.left = 0;
	rect.top = 0;
	rect.right = CGame::GetInstance()->GetBackBufferWidth();
	rect.bottom = CGame::GetInstance()->GetBackBufferHeight();

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(sx/2, sy/2, bbox, &rect, BBOX_ALPHA);
}

void CPlayScene::Render()
{
	float cx, cy;
	float sx, sy;
	sx = CGame::GetInstance()->GetBackBufferWidth();
	sy = CGame::GetInstance()->GetBackBufferHeight();
	CGame::GetInstance()->GetCamPos(cx, cy);
	if (id > 1000)
	{
		RECT rect;
		rect.left = mapL;
		rect.right = mapR;
		rect.top = mapT;
		rect.bottom = mapB;
		CGame::GetInstance()->Draw(sx / 2, sy / 2 - 15, map, &rect);
	}
	else tileMap->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	hub->SetPosition(cx+95, cy+185);
	hub->Render();
	// render PAUSE
	if (isPAUSE) {
		RenderPauseBackground();
		CAnimations::GetInstance()->Get(ID_ANI_PAUSE)->Render(cx + sx / 2, cy + sy / 2);
	}
	// render GameOver
	if (CGame::GetInstance()->isGameOver) {
		CAnimations::GetInstance()->Get(ID_ANI_GAMEOVER_MENU)->Render(cx + sx / 2, cy + sy / 2 - 20);
		switch (selectGameOverMenu)
		{
		case GAME_OVER_SELECT_CONTINUE: {
			CAnimations::GetInstance()->Get(ID_ANI_GAMEOVER_POINT)->Render(cx + sx / 2 - 22, cy + sy / 2 - 8);
			break;
		}
		case GAME_OVER_SELECT_END: {
			CAnimations::GetInstance()->Get(ID_ANI_GAMEOVER_POINT)->Render(cx + sx / 2 - 22, cy + sy / 2 );
			break;
		}
		default:
			break;
		}
	}
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
	player = nullptr;
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	CGame::GetInstance()->SetCamPos(0, 0);

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted() && o!=NULL)
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}