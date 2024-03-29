#pragma once
#include "GameObject.h"
#include <math.h>

#define ID_ANI_BULLET	14000

#define BULLET_BBOX_WIDTH 10
#define BULLET_BBOX_HEIGHT 10

#define BULLET_SPEED 0.04f
#define BULLET_TIME 4500


class CBullet :
    public CGameObject
{
protected:
    float xLock;
    float yLock;
    ULONGLONG time_start;
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Render();
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) { 
        y += vy * dt; 
        x += vx * dt; 
        if (GetTickCount64() - time_start > BULLET_TIME)
            this->Delete();
    }
public:
    CBullet(float x, float y) : CGameObject(x, y) { xLock = yLock = 0; time_start = GetTickCount64(); }
    void setLockPosition(float x, float y) {
        xLock = x;
        yLock = y;

        /*if (xLock - this->x > 0) {
            vx = BULLET_SPEED;
        }
        else if (xLock - this->x == 0) {
            vx = 0;
            if (yLock - this->y > 0)
                vy = BULLET_SPEED;
            else vy = -BULLET_SPEED;
            return;
        }
        else vx = - BULLET_SPEED;
        vy = vx * (yLock - this->y) / (xLock - this->x);*/
        if(this->y - yLock > 0)
            vy = -sqrt((BULLET_SPEED * BULLET_SPEED) / (1 + ((this->x - xLock) / (this->y - yLock))* ((this->x - xLock) / (this->y - yLock))));
        else vy = sqrt((BULLET_SPEED * BULLET_SPEED) / (1 + ((this->x - xLock) / (this->y - yLock))* ((this->x - xLock) / (this->y - yLock))));
        vx = ((this->x - xLock) / (this->y - yLock)) * vy;
    }

    virtual int IsBlocking() { return 0; }
};

