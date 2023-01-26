#pragma once
#include "GameObject.h"
#include "CNodeMapG.h"

#define MARIO_WORLD_WIDTH 14
#define MARIO_WORLD_HEIGHT 16

#define ID_ANI_MARIOW   2007

#define MARIOW_STATE_UP 100
#define MARIOW_STATE_DOWN 200
#define MARIOW_STATE_LEFT 300
#define MARIOW_STATE_RIGHT 400

#define STEP    50
#define SPEED    0.12f
class MarioWorldMaps :
    public CGameObject
{
public:
    int xNext, yNext;
    MarioWorldMaps(float x, float y) : CGameObject(x, y){}

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
        if (vx != 0) {
            if ((vx > 0 && x >= xNext) || (vx < 0 && x <= xNext)) {
                x = xNext;
                vx = 0;
            }
        }
        else if (vy != 0) {
            if ((vy > 0 && y >= yNext) || (vy < 0 && y <= yNext)) {
                y = yNext;
                vy = 0;
            }
        }
        CCollision::GetInstance()->Process(this, dt, coObjects);
    };
    virtual void OnNoCollision(DWORD dt) {
        x += vx * dt;
        y += vy * dt;
    };
    virtual void Render();

    void SetState(int state) { 
        switch (state)
        {
        case MARIOW_STATE_UP:
            vy = -SPEED;
            break;
        case MARIOW_STATE_DOWN:
            vy = SPEED;
            break;
        case MARIOW_STATE_LEFT:
            vx = -SPEED;
            break;
        case MARIOW_STATE_RIGHT:
            vx = SPEED;
            break;
        default:
            break;
        }
        this->state = state; 
    }
};

