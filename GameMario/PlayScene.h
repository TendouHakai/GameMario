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
	CHUB* hub;

	
	void loadMap(string mapFile);
	void LoadAssets(string assetFile);
	
public: 
	// timer
	int isStart = 0;
	ULONGLONG timeStart = 0;
	// is PAUSE
	bool isPAUSE = false;
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

