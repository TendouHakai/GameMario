#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "MarioWorldMaps.h"
#include "Goomba.h"
//#include "Koopas.h"
#include "CTileMap.h"
#include "CHUB.h"

#define GAME_OVER_SELECT_CONTINUE	0
#define GAME_OVER_SELECT_END	1

#define SELECT_1_PLAYER	0
#define SELECT_2_PLAYER	1

class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;	


	vector<LPGAMEOBJECT> objects;
	LPTEXTURE map;
	int mapL;
	int mapT;
	int mapR;
	int mapB;

	CTileMap* tileMap;

	
	void loadMap(string mapFile);
	void LoadAssets(string assetFile);
	
public: 
	//HUB
	CHUB* hub;
	// timer
	int isStart = 0;
	ULONGLONG timeStart = 0;
	// is PAUSE
	bool isPAUSE = false;
	bool isPAUSEMario = false;
	ULONGLONG PAUSEMario_start = 0;
	// is GameOver
	int selectMenu = 1;
	CPlayScene(int id, string filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	void RenderPauseBackground();
	virtual void Render();
	virtual void Unload();

	virtual LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

