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

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, string filePath):
	CScene(id, filePath)
{	
	map = NULL;
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
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

	//ifstream f;
	//f.open(assetFile);

	//int section = ASSETS_SECTION_UNKNOWN;

	//char str[MAX_SCENE_LINE];
	//while (f.getline(str, MAX_SCENE_LINE))
	//{
	//	string line(str);

	//	if (line[0] == '#') continue;	// skip comment lines	

	//	if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
	//	if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
	//	if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

	//	//
	//	// data section
	//	//
	//	switch (section)
	//	{
	//	case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
	//	case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
	//	}
	//	
	//}

	//f.close();
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

	//ifstream f;
	//f.open(sceneFilePath);

	//// current resource section flag
	//int section = SCENE_SECTION_UNKNOWN;					

	//char str[MAX_SCENE_LINE];
	//while (f.getline(str, MAX_SCENE_LINE))
	//{
	//	string line(str);

	//	if (line[0] == '#') continue;	// skip comment lines	
	//	if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
	//	if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
	//	if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

	//	//
	//	// data section
	//	//
	//	switch (section)
	//	{ 
	//		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
	//		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
	//	}
	//}

	//f.close();
	TiXmlDocument doc(sceneFilePath.c_str());
	if (doc.LoadFile()) {
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* mapXML = root->FirstChildElement("MAP");
		TiXmlElement* assetsXML = root->FirstChildElement("ASSETS");
		TiXmlElement* objectsXML = root->FirstChildElement("OBJECTS");
		// đọc map
		loadMap(mapXML->Attribute("link"));
		// đọc assets
		for (TiXmlElement* node = assetsXML->FirstChildElement("asset"); node != nullptr; node = node->NextSiblingElement("asset")) {
			LoadAssets(node->Attribute("link"));
		}
		// đọcc objects
		for (TiXmlElement* node = objectsXML->FirstChildElement("object"); node != nullptr; node = node->NextSiblingElement("object")) {
			int objectID = atoi(node->Attribute("type"));
			float x = (float)atoi(node->Attribute("x"));
			float y = (float)atoi(node->Attribute("y"));
			CGameObject* obj = NULL;
			switch (objectID)
			{
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

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &objects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 5;

	if (cx < 0) cx = 0;
	else if (cx + game->GetBackBufferWidth() > map->getWidth() ) cx = map->getWidth() - game->GetBackBufferWidth();
	if (cy < 0) cy = 0;
	

	if (CGame::GetInstance()->isForcusPlayer == false) {
		CGame::GetInstance()->SetCamPos(cx, 240.0f);
	}
	else {
		if (cy > CGame::GetInstance()->yChangeCamMax) cy = CGame::GetInstance()->yChangeCamMax;
		if (cy < CGame::GetInstance()->yChangeCamMin) cy = CGame::GetInstance()->yChangeCamMin;

		CGame::GetInstance()->SetCamPos(cx, cy);
	}
	

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	RECT rect;
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	float sx, sy;	
	sx = CGame::GetInstance()->GetBackBufferWidth();
	sy = CGame::GetInstance()->GetBackBufferHeight();
	rect.left = cx;
	rect.right = rect.left + sx +1;
	rect.top = cy;
	rect.bottom = rect.top + sy +1;
	CGame::GetInstance()->Draw(sx/2, sy/2, map, &rect);
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
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