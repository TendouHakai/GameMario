#pragma once
#include "GameObject.h"
#include "CBreakableBrick.h"

#define TAIL_BBOX_WIDTH  10
#define TAIL_BBOX_HEIGHT 6

#define ID_ANI_MARIO_TAIL_RIGHT 25001
#define ID_ANI_MARIO_TAIL_LEFT 25002

#define MARIO_TAIL_STATE_RIGHT  100
#define MARIO_TAIL_STATE_LEFT   200

#define ID_ANI_EFFECT_HIT   25003
#define TIME_EFFECT_HIT 100
class CTail :
    public CGameObject
{
protected:
    BOOLEAN isHited;
    float effecthit_start;
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    
    void OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e);
    void OnCollisionWithRedTurtle(LPCOLLISIONEVENT e);
    void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
    void OnCollisionWithWingGreenTurtle(LPCOLLISIONEVENT e);
    
    void OnNoCollision(DWORD dt){}
    void OnCollisionWith(LPCOLLISIONEVENT e);
public:
    CTail(float x, float y) :CGameObject(x, y) { isHited = false; effecthit_start = 0; }
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
        CCollision::GetInstance()->Process(this, dt, coObjects);
    };
    virtual void Render() {
        //RenderBoundingBox();
    }

    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }

    virtual void SetState(int state) { 
        this->state = state; 
    }
};

