#pragma once
#include "GameObject.h"

#define PEICEOFBREAKABLEBRICK_BBOX_WIDTH    8
#define PEICEOFBREAKABLEBRICK_BBOX_HEIGHT    8

#define TIMELIFE_PEICEOFBREAKABLEBRICK  1000

#define ID_ANI_PEICEOFBREAKABLEBRICK    20002

#define PEICE_STATE_TOPLEFT 100
#define PEICE_STATE_TOPRIGHT 200
#define PEICE_STATE_BOTTOMLEFT 300
#define PEICE_STATE_BOTTOMRIGHT 400

#define PEICE_SPEED_Y_TOP   0.25f
#define PEICE_SPEED_Y_BOTTOM   0.08f
#define PEICE_SPEED_X   0.1f
#define PEICE_GRAVITY   0.002f

class CPeiceOfBreakableBrick :
    public CGameObject
{
protected:
    float lifeTime_start;
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
        vy += PEICE_GRAVITY * dt;

        if (GetTickCount64() - lifeTime_start > TIMELIFE_PEICEOFBREAKABLEBRICK)
        {
            lifeTime_start = 0;
            this->Delete();
        }

        x += vx * dt;
        y += vy * dt;

    };
    virtual void Render(){
        CAnimations::GetInstance()->Get(ID_ANI_PEICEOFBREAKABLEBRICK)->Render(x, y);
    };
public:
    CPeiceOfBreakableBrick(float x, float y) :CGameObject(x, y) {
        lifeTime_start = GetTickCount64();
    }
    virtual int IsCollidable() { return 0; };
    virtual int IsBlocking() { return 0; }

    virtual void SetState(int state) {
        switch (state)
        {
        case PEICE_STATE_TOPLEFT:
            vx = -PEICE_SPEED_X;
            vy = -PEICE_SPEED_Y_TOP;
            break;
        case PEICE_STATE_TOPRIGHT:
            vx = PEICE_SPEED_X;
            vy = -PEICE_SPEED_Y_TOP;
            break;
        case PEICE_STATE_BOTTOMLEFT:
            vx = -PEICE_SPEED_X;
            vy = -PEICE_SPEED_Y_BOTTOM;
            break;
        case PEICE_STATE_BOTTOMRIGHT:
            vx = PEICE_SPEED_X;
            vy = -PEICE_SPEED_Y_BOTTOM;
            break;
        default:
            break;
        }
        this->state = state;
    }
};

