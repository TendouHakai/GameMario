#pragma once
#include "GameObject.h"
#include "CGreenTurtle.h"
#include "CEffectHitWithTail.h"

#define WINGGREENTURTLE_BBOX_WIDTH 16
#define WINGGREENTURTLE_BBOX_HEIGHT 28

#define WINGGREENTURTLE_STATE_WALK	100
#define WINGGREENTURTLE_STATE_TO_GREENTURTLE	200
#define WINGGREENTURTLE_STATE_DEAD  300
#define WINGGREENTURTLE_STATE_TAILTURNING   400

#define ID_ANI_WINGGREENTURTLE_WALK_LEFT   17000
#define ID_ANI_WINGGREENTURTLE_WALK_RIGHT   17001

#define WINGGREENTURTLE_SPEED 0.02f
#define WINGGREENTURTLE_SPEED_Y 0.2f

#define WINGGREENTURTLE_GRAVITY 0.0005f



class CWingGreenTurtle :
    public CGameObject
{
protected:
    float ay;
    BOOLEAN isOnPlatform;
    CEffectHitWithTail* effectHit;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
        vy += ay * dt;

        isOnPlatform = false;
        CCollision::GetInstance()->Process(this, dt, coObjects);

        if (state == WINGGREENTURTLE_STATE_TO_GREENTURTLE) {
            CGreenTurtle* greenturtle = new CGreenTurtle(x, y);
            coObjects->push_back(greenturtle);
            this->Delete();
        }
        else if (state == WINGGREENTURTLE_STATE_TAILTURNING) {
            CGreenTurtle* greenturtle = new CGreenTurtle(x, y);
            greenturtle->SetState(TURTLE_STATE_DEAD_TAILTURNING);
            coObjects->push_back(greenturtle);
            if (effectHit != NULL) {
                coObjects->push_back(effectHit);
                effectHit = NULL;
            }
            this->Delete();
        }
        
    };
    virtual void OnNoCollision(DWORD dt);

    void OnCollisionWithBlockEnemies(LPCOLLISIONEVENT e);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    virtual void Render();
public:
    CWingGreenTurtle(float x, float y):CGameObject(x,y){
        vx = - WINGGREENTURTLE_SPEED;
        vy = 0;
        ay = WINGGREENTURTLE_GRAVITY;
        effectHit = NULL;
    }

    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }

    virtual void SetState(int state) { 
        if (state == WINGGREENTURTLE_STATE_TAILTURNING) {
            effectHit = new CEffectHitWithTail(x, y);
        }
        this->state = state; 
    }
};

