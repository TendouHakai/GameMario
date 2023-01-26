#pragma once
#include "GameObject.h"
#include "PlayScene.h"

#define GOADCARD_BBOX_WIDTH 24
#define GOADCARD_BBOX_HEIGHT 24

#define ID_ANI_GOALCARD 29001
#define ID_ANI_GOALCARD_MUSHROOM 29002
#define ID_ANI_GOALCARD_FLOWER 29003
#define ID_ANI_GOALCARD_STAR 29004
#define ID_ANI_GOALCARD_TITLE1  29005
#define ID_ANI_GOALCARD_TITLE2  29006
#define ID_ANI_SPOIL_MUSHROOM	28018
#define ID_ANI_SPOIL_FLOWER	28019
#define ID_ANI_SPOIL_STAR	28020

#define GOALCARD_STATE_IDLE 100
#define GOALCARD_STATE_COLLECT  200

#define GOALCARD_TYPE_MUSHROOM  0
#define GOALCARD_TYPE_FLOWER  1
#define GOALCARD_TYPE_STAR  2
class CGoalCard :
    public CGameObject
{
private:
    ULONGLONG timestart;
    int isShowTitle = -1;
    ULONGLONG timeShowStart;
    int currentCard;
public:
    CGoalCard(float x, float y): CGameObject(x,y){
        timestart = GetTickCount64();
        currentCard = GOALCARD_TYPE_MUSHROOM;
        state = GOALCARD_STATE_IDLE;
    }

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {  
        y += vy * dt;

        if (isShowTitle > -1 && isShowTitle <=2 && GetTickCount64() - timeShowStart > 750) {
            isShowTitle ++;
            timeShowStart = GetTickCount64();
        }
        else if (isShowTitle == 3) {
            CPlayScene* C_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

            C_scene->hub->addCard(currentCard);
            isShowTitle++;
        }
    };

    virtual void Render();
    virtual int IsBlocking() { return 0; }

    void SetCurrentCard() {
        ULONGLONG time = GetTickCount64() - timestart;

        currentCard = (time / 150)%3;
    }
    virtual void SetState(int state) { 
        switch (state)
        {
        case GOALCARD_STATE_COLLECT: {
            SetCurrentCard();
            isShowTitle = 0;
            timeShowStart = GetTickCount64();
            vy = -0.1f;
            break;
        }
        default:
            break;
        }
        this->state = state; 
    }
};

