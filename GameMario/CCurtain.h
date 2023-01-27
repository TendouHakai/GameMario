#pragma once
#include "CTube.h"
class CCurtain :
    public CTube
{
private:
    ULONGLONG start = GetTickCount64();
public:
    CCurtain(float x, float y, float cell_width, float cell_height, int height,
        int idSpriteTL, int idSpriteTR, int idSpriteML, int idSpriteMR, int idSpriteBL, int idSpriteBR): CTube(x, y, cell_width, cell_height, height, idSpriteTL, idSpriteTR, idSpriteML, idSpriteMR, idSpriteBL, idSpriteBR){}
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
        y += vy * dt;
        if (y <= -161)
            y = -161;
        if (GetTickCount64() - start > 5000) {
            y = -140;
            this->idSpriteBL = 126004;
            this->idSpriteBR = 126004;
            vy = 0;
        }
        else if (GetTickCount64() - start > 1000) {
            vy = -0.08f;
        }
    };
};

