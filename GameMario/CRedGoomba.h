#pragma once
#include "Goomba.h"

#define ID_ANI_REDGOOMBA_WALKING 23001
#define ID_ANI_REDGOOMBA_DIE 23002
class CRedGoomba :
    public CGoomba
{
protected:
    virtual void Render();
public:
    CRedGoomba(float x, float y):CGoomba(x,y){}
};
