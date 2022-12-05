#pragma once
#include "Brick.h"

#define ID_ANI_WOODBRICK    19001
class CWoodBrick :
    public CBrick
{
protected:
public:
    CWoodBrick(float x, float y):CBrick(x,y){}
    virtual void Render();

};

