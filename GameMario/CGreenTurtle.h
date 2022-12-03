#pragma once
#include "CTurtle.h"

#define ID_ANI_GREENTURTLE_WALK_LEFT 16000
#define ID_ANI_GREENTURTLE_WALK_RIGHT 16001
#define ID_ANI_GREENTURTLE_DEAD 16002
#define ID_ANI_GREENTURTLE_REVIVAL 16003
#define ID_ANI_GREENTURTLE_KICK 16004


class CGreenTurtle :
    public CTurtle
{
protected:
    virtual void Render();
public:
    CGreenTurtle(float x, float y) :CTurtle(x, y){}
};

