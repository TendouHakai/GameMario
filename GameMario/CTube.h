#pragma once
#include "GameObject.h"


class CTube :
    public CGameObject
{
protected:
    float cell_width;
    float cell_height;
    int height;

    int idSpriteTL;
    int idSpriteTR;
    int idSpriteML;
    int idSpriteMR;
    int idSpriteBL;
    int idSpriteBR;
public:
    CTube(float x, float y, float cell_width, float cell_height, int height, 
        int idSpriteTL, int idSpriteTR, int idSpriteML, int idSpriteMR, int idSpriteBL, int idSpriteBR) :CGameObject(x, y) {
        this->cell_height = cell_height;
        this->cell_width = cell_width;
        this->height = height;

        this->idSpriteTL = idSpriteTL;
        this->idSpriteTR = idSpriteTR;
        this->idSpriteML = idSpriteML;
        this->idSpriteMR = idSpriteMR;
        this->idSpriteBL = idSpriteBL;
        this->idSpriteBR = idSpriteBR;
    }

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
    virtual void Render();
    virtual void SetState(int state) { this->state = state; }
};

