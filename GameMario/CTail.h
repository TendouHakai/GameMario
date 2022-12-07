#pragma once
#include "GameObject.h"

#define TAIL_BBOX_WIDTH  10
#define TAIL_BBOX_HEIGHT 6

#define ID_ANI_MARIO_TAIL_RIGHT 25001
#define ID_ANI_MARIO_TAIL_LEFT 25002

#define MARIO_TAIL_STATE_RIGHT  100
#define MARIO_TAIL_STATE_LEFT   200
class CTail :
    public CGameObject
{
protected:
    BOOLEAN isActive;
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
    
    
public:
    CTail(float x, float y) :CGameObject(x, y) {
        isActive = false;
    }

    virtual void Render() {
    }

    void setActive(bool active) {
        isActive = active;
    }

    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }

    virtual void SetState(int state) { 
        this->state = state; 
    }
};

