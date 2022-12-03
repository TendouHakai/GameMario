#pragma once
#include "GameObject.h"

#define CHAGE_TYPE_FORCUS_PLAYER    1
#define CHAGE_TYPE_NOT_FORCUS_PLAYER    2

class ChangeCam :
    public CGameObject
{
protected:
    float w;
    float h;

    int typeChange;
public:
    float yCamMax;
    float yCamMin;
    ChangeCam(float x, float y, float w, float h, float yCamMax, float yCamMin):CGameObject(x,y){
        this->w = w;
        this->h = h;

        this->typeChange = CHAGE_TYPE_FORCUS_PLAYER;

        this->yCamMax = yCamMax;
        this->yCamMin = yCamMin;
    }
    virtual void Render();
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    }
    void GetBoundingBox(float& l, float& t, float& r, float& b);

    int GetChangeCamType() { return this->typeChange; }

    virtual int IsBlocking() { return 0; }
    virtual int IsCollidable() { return 1; };
};

