#pragma once
#include "GameObject.h"

#define WINGS_OPEN_BBOX_WIDTH    24
#define WINGS_OPEN_BBOX_HEIGHT   14
#define WINGS_CLOSE_BBOX_WIDTH   24
#define WINGS_CLOSE_BBOX_HEIGHT   9

#define WING_OPEN_WIDTH 8
#define WING_OPEN_HEIGHT    14
#define WING_CLOSE_WIDTH    8
#define WING_CLOSE_HEIGHT   9

#define WINGS_STATE_OPEN  100
#define WINGS_STATE_CLOSE  200
#define WINGS_STATE_FLAPPING  300

#define ID_ANI_WINGS_OPEN_RIGHT 24001
#define ID_ANI_WINGS_OPEN_LEFT 24002
#define ID_ANI_WINGS_CLOSE_RIGHT 24003
#define ID_ANI_WINGS_CLOSE_LEFT 24004
#define ID_ANI_WINGS_FLAPPING_RIGHT 24005
#define ID_ANI_WINGS_FLAPPING_LEFT 24006
class CWingOfGoomba :
    public CGameObject
{
protected:
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
        
    };
    
public:
    CWingOfGoomba(float x, float y) :CGameObject(x, y) { state = WINGS_STATE_FLAPPING; }

    virtual void Render();

    virtual int IsBlocking() { return 0; }
    virtual int IsCollidable() { return 0; };

    virtual void SetState(int state) { this->state = state; }
};

