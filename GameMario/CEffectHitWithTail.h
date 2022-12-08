#pragma once
#include "GameObject.h"
#define ID_ANI_EFFECT_HIT   25003
#define TIME_EFFECT_HIT 100


class CEffectHitWithTail :
    public CGameObject
{
protected:
    float time_start;
public:
    CEffectHitWithTail(float x, float y) :CGameObject(x, y) { time_start = GetTickCount64(); }
    virtual int IsCollidable() { return 0; };
    virtual int IsBlocking() { return 0; }

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom){
        left = 0;
        top = 0;
        right = 0;
        bottom = 0;
    };
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
        if (GetTickCount64() - time_start > TIME_EFFECT_HIT) {
            this->Delete();
        }
    };
    virtual void Render();
};

