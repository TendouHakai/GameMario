#pragma once
#include "Platform.h"
class CPlatformSprite :
    public CPlatform
{
protected:
    int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
    
public:
    CPlatformSprite(float x, float y,
        float cell_width, float cell_height, int length,
        int spriteIdBegin, int spriteIdMiddle, int spriteIdEnd) :CPlatform(x, y, cell_width, cell_height, length) 
    {
        this->spriteIdBegin = spriteIdBegin;
        this->spriteIdMiddle = spriteIdMiddle;
        this->spriteIdEnd = spriteIdEnd;
    }
    void Render();


};

