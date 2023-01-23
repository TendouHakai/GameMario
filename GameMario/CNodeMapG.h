#pragma once
#include "GameObject.h"

#define NODEMAP_TYPE_SCENE  1

#define NODEMAP_BBOX_WIDTH  16
#define NODEMAP_BBOX_HEIGHT  16

#define NODEMAP_STATE_DONE    100
#define NODEMAP_STATE_NOTDONE    200

#define ID_ANI_NODEMAP_TYPE1_DONE   26001
class CNodeMapG :
    public CGameObject
{
public:
    int type;
    CNodeMapG(float x, float y): CGameObject(x,y){}
    CNodeMapG(float x, float y, int type) : CGameObject(x, y) {
        this->type = type;
        state = NODEMAP_STATE_NOTDONE;
    }
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Render();

};

