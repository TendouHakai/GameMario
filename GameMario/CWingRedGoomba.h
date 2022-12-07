#pragma once
#include "CRedGoomba.h"
#include "CWingOfGoomba.h"

#define WINGGOOMBA_STATE_WALK   100
#define WINGGOOMBA_STATE_PREPARETOFLY   200
#define WINGGOOMBA_STATE_FLY   300

#define TIME_WALK   1000
#define TIME_PREPARE    1000

#define WINGGOMBA_GRAVITY   0.0005f
#define WINGGOOMBA_SPEED_Y  0.15f
#define WINGGOOMBA_SPEED_Y_PREPARE  0.07f

class CWingRedGoomba :
    public CRedGoomba
{
protected:
    CWingOfGoomba* wings;
    float ay;
    float walk_start;
    float prepare_start;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
public:
    CWingRedGoomba(float x, float y):CRedGoomba(x,y){
        wings = new CWingOfGoomba(x, y-GOOMBA_BBOX_HEIGHT/2);
        walk_start = 0;
        prepare_start = 0;
        ay = WINGGOMBA_GRAVITY;
    }

    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    virtual void Render();
    virtual void SetState(int state);
};

