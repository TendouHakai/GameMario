#pragma once
#include "GameObject.h"
#include "CGreenTurtle.h"

#define WINGGREENTURTLE_BBOX_WIDTH 16
#define WINGGREENTURTLE_BBOX_HEIGHT 28

#define WINGGREENTURTLE_STATE_WALK	100
#define WINGGREENTURTLE_STATE_TO_GREENTURTLE	200

#define ID_ANI_WINGGREENTURTLE_WALK_LEFT   17000
#define ID_ANI_WINGGREENTURTLE_WALK_RIGHT   17001

#define WINGGREENTURTLE_SPEED 0.02f
#define WINGGREENTURTLE_SPEED_Y 0.2f

#define WINGGREENTURTLE_GRAVITY 0.0005f

#define WINGGREENTURTLE_STATE_WALK  1
#define WINGGREENTURTLE_STATE_DEAD  2

class CWingGreenTurtle :
    public CGameObject
{
protected:
    float ay;
    BOOLEAN isOnPlatform;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
        vy += ay * dt;

        isOnPlatform = false;
        CCollision::GetInstance()->Process(this, dt, coObjects);

        if (state == WINGGREENTURTLE_STATE_TO_GREENTURTLE) {
            this->Delete();
            CGreenTurtle* greenturtle = new CGreenTurtle(x, y);
            coObjects->push_back(greenturtle);
        }
        
    };
    virtual void OnNoCollision(DWORD dt);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    virtual void Render();
public:
    CWingGreenTurtle(float x, float y):CGameObject(x,y){
        vx = - WINGGREENTURTLE_SPEED;
        vy = 0;
        ay = WINGGREENTURTLE_GRAVITY;
    }

    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }

    virtual void SetState(int state) { 
        this->state = state; 
    }
};

