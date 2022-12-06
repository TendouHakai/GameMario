#pragma once
#include "CRedGoomba.h"
#include "CWingOfGoomba.h"

class CWingRedGoomba :
    public CRedGoomba
{
protected:
    CWingOfGoomba* wings;
public:
    CWingRedGoomba(float x, float y):CRedGoomba(x,y){
        wings = new CWingOfGoomba(x, y-GOOMBA_BBOX_HEIGHT/2);
    }

    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

    virtual void Render();
};

