#pragma once
#include "GameObject.h"

#define HUB_BBOX_WIDTH	152
#define HUB_BBOX_HEIGHT	20

#define ID_ANI_HUB	28001

//NUMBER
#define ID_ANI_NUMBER00	28002
#define ID_ANI_NUMBER01	28003
#define ID_ANI_NUMBER02	28004
#define ID_ANI_NUMBER03	28005
#define ID_ANI_NUMBER04	28006
#define ID_ANI_NUMBER05	28007
#define ID_ANI_NUMBER06	28008
#define ID_ANI_NUMBER07	28009
#define ID_ANI_NUMBER08	28010
#define ID_ANI_NUMBER09	28011

//P
#define ID_ANI_RAISE_P_BLACK	28012
#define ID_ANI_P_BLACK	28013
#define ID_ANI_RAISE_P_WHITE	28014
#define ID_ANI_P_WHITE	28015

// Mode M or L
#define ID_ANI_M	28016

// SPOIL
#define ID_ANI_SPOIL_EMPTY	28017
#define ID_ANI_SPOIL_MUSHROOM	28018
#define ID_ANI_SPOIL_FLOWER	28019
#define ID_ANI_SPOIL_STAR	28020

#define SPOIL_TYPE_EMPTY	100
#define SPOIL_TYPE_MUSHROOM	200
#define SPOIL_TYPE_FLOWER	300
#define SPOIL_TYPE_STAR	400

class CHUB :
    public CGameObject
{
private:

public:
	int coin = 0;
	int time = 0;
	int M = 0;
	int W = 1;
	int countCoin = 0;
	int level = 3;
	int Spoils[3];

	CHUB(float x, float y) : CGameObject(x, y){
		coin = 0;
		time = 0;
		M = 0;
		W = 1;
		countCoin = 0;
		level = 3;
		Spoils[0] = SPOIL_TYPE_STAR;
		Spoils[1] = SPOIL_TYPE_MUSHROOM;
		Spoils[2] = SPOIL_TYPE_FLOWER;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	void renderNumber(int number, int xx, int yy);
	virtual void Render();

};
