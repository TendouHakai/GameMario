#pragma once
#include "Brick.h"

#define ID_ANI_BREAKABLEBRICK  20001
class CBreakableBrick :
    public CBrick
{
protected:

public:
    CBreakableBrick(float x, float y):CBrick(x,y){}
    virtual void Render();
};

