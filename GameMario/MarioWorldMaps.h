#pragma once
#include "GameObject.h"

#define MARIO_WORLD_WIDTH 14
#define MARIO_WORLD_HEIGHT 16

#define ID_ANI_MARIOW   2007

#define MARIOW_STATE_UP 100
#define MARIOW_STATE_DOWN 200
#define MARIOW_STATE_LEFT 300
#define MARIOW_STATE_RIGHT 400

#define STEP    50
class MarioWorldMaps :
    public CGameObject
{
public:
    MarioWorldMaps(float x, float y) : CGameObject(x, y){}

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Render();

    void SetState(int state) { 
        switch (state)
        {
        case MARIOW_STATE_UP:
            y -= STEP;
            break;
        case MARIOW_STATE_DOWN:
            y += STEP;
            break;
        case MARIOW_STATE_LEFT:
            x -= STEP;
            break;
        case MARIOW_STATE_RIGHT:
            x += STEP;
            break;
        default:
            break;
        }
        this->state = state; 
    }
};

