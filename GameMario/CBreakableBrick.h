#pragma once
#include "Brick.h"
#include "CPeiceOfBreakableBrick.h"

#define ID_ANI_BREAKABLEBRICK  20001

#define BREAKABLEBRICK_STATE_IDLE   100
#define BREAKABLEBRICK_STATE_BROKEN 200

class CBreakableBrick :
    public CBrick
{
protected:

public:
    CBreakableBrick(float x, float y) :CBrick(x, y) { state = BREAKABLEBRICK_STATE_IDLE; }
    virtual void Render();
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
        if (state == BREAKABLEBRICK_STATE_BROKEN) {
            CPeiceOfBreakableBrick* peice1 = new CPeiceOfBreakableBrick(x-BRICK_BBOX_WIDTH/4, y-BRICK_BBOX_HEIGHT/4);
            peice1->SetState(PEICE_STATE_TOPLEFT);
            CPeiceOfBreakableBrick* peice2 = new CPeiceOfBreakableBrick(x+BRICK_BBOX_WIDTH/4, y-BRICK_BBOX_HEIGHT/4);
            peice2->SetState(PEICE_STATE_TOPRIGHT);
            CPeiceOfBreakableBrick* peice3 = new CPeiceOfBreakableBrick(x-BRICK_BBOX_WIDTH/4, y+BRICK_BBOX_HEIGHT/4);
            peice3->SetState(PEICE_STATE_BOTTOMLEFT);
            CPeiceOfBreakableBrick* peice4 = new CPeiceOfBreakableBrick(x+BRICK_BBOX_WIDTH/4, y+BRICK_BBOX_HEIGHT/4);
            peice4->SetState(PEICE_STATE_BOTTOMRIGHT);
            
            coObjects->push_back(peice1);
            coObjects->push_back(peice2);
            coObjects->push_back(peice3);
            coObjects->push_back(peice4);
            this->Delete();
        }
    }
    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 1; }

    virtual void SetState(int state) {
        switch (state)
        {
        case BREAKABLEBRICK_STATE_IDLE: {

            break;
        }
        case BREAKABLEBRICK_STATE_BROKEN: {

            break;
        }
        default:
            break;
        }
        this->state = state;
    }
};

