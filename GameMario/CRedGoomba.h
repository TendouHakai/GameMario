#pragma once
#include "Goomba.h"
#include "Mario.h"

#define ID_ANI_REDGOOMBA_WALKING 23001
#define ID_ANI_REDGOOMBA_DIE 23002
#define ID_ANI_REDGOOMBA_DIE_TAILTURNING 23003
class CRedGoomba :
    public CGoomba
{
protected:
    virtual void Render();
public:
    CRedGoomba(float x, float y) :CGoomba(x, y) { }
};

