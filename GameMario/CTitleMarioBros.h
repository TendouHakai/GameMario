#pragma once
#include "GameObject.h"
#include "CGreenTurtle.h"
#include "CTurtle.h"
#include "CLeaf.h"
#include "Goomba.h"
#include "CMushroom.h"
#include "PlayScene.h"
#include "CPlatformSprite.h"

#define TITLEMARIOBROS_BBOX_WIDTH   250
#define TITLEMARIOBROS_BBOX_HEIGHT   112

#define ID_ANI_TITLE_MARIOBROS3 32001
#define ID_ANI_TITLE_MARIOBROS3_3 32002

#define ID_ANI_SELECT_1_PlAYER	32003
#define ID_ANI_SELECT_2_PlAYER	32004

#define ID_ANI_TREE_1   32005
#define ID_ANI_TREE_2   32006

#define ID_ANI_RAMEN_1_LIGHT   32007
#define ID_ANI_RAMEN_2_LIGHT   32008
#define ID_ANI_RAMEN_1   32009
#define ID_ANI_RAMEN_2   32010
class CTitleMarioBros :
    public CGameObject
{
private:
    ULONGLONG timestart;
    bool isLight;
    bool isSelect;


public:
    CGameObject* greenTurtle;
    CGameObject* redTurtle;
    CGameObject* leaf;
    CGameObject* goomba;
    CGameObject* mushroom;
    CTitleMarioBros(float x, float y): CGameObject(x,y){
        timestart = GetTickCount64();
        isLight = false;
        isSelect = false;
    }

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom){ 
        left = x - TITLEMARIOBROS_BBOX_WIDTH / 2;
        top = y - TITLEMARIOBROS_BBOX_HEIGHT / 2;
        right = left + TITLEMARIOBROS_BBOX_WIDTH;
        bottom = top + TITLEMARIOBROS_BBOX_HEIGHT;
    };
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
        y += vy * dt;
        if (y >= 70)
            y = 70;
        if (GetTickCount64() - timestart > 24000) {
            isSelect = true;
        }
        else if (GetTickCount64() - timestart > 19500) {
            if (greenTurtle == nullptr)
            {
                greenTurtle = new CGreenTurtle(-20, 150);
                greenTurtle->SetState(TURTLE_STATE_DEAD);
                greenTurtle->SetState(TURTLE_STATE_KICKED_LEFT);

                coObjects->push_back(greenTurtle);
            }
        }
        else if (GetTickCount64() - timestart > 17200) {
            greenTurtle = nullptr;
        }
        else if (GetTickCount64() - timestart > 17100) {
            greenTurtle->SetState(TURTLE_STATE_DEAD);
        }
        else if (GetTickCount64() - timestart > 14900) {

        }
        else if (GetTickCount64() - timestart > 14800) {
            greenTurtle->SetState(TURTLE_STATE_DEAD);
        }
        else if (GetTickCount64() - timestart > 13500) {
            if (greenTurtle != nullptr) {
                CGreenTurtle* gt = dynamic_cast<CGreenTurtle*>(greenTurtle);
                CTurtle* rt = dynamic_cast<CTurtle*>(redTurtle);
                gt->IsPause(false);
                rt->IsPause(false);
            }
        }
        else if (GetTickCount64() - timestart > 12800) {
            if (goomba != nullptr)
            {
                CGoomba* gb = dynamic_cast<CGoomba*>(goomba);
                gb->isPause = false;
                goomba = nullptr;
            }
        }
        else if (GetTickCount64() - timestart > 6100) {
            CGreenTurtle* gt = dynamic_cast<CGreenTurtle*>(greenTurtle);
            CTurtle* rt = dynamic_cast<CTurtle*>(redTurtle);
            CGoomba* gb = dynamic_cast<CGoomba*>(goomba);
            float vx, vy;
            gt->GetSpeed(vx, vy);
            if (vy == 0)
            {
                gt->IsPause(true);
                rt->IsPause(true);
                gb->isPause = true;
            }
        }
        else if (GetTickCount64() - timestart > 6000) {
            isLight = true;
            CGame::GetInstance()->setBackgroundColor(255, 219, 161);
            if (greenTurtle == nullptr)
            {
                greenTurtle = new CGreenTurtle(155, 20);
                greenTurtle->SetState(TURTLE_STATE_DEAD);

                coObjects->push_back(greenTurtle);
            }
            if (redTurtle == nullptr) {
                redTurtle = new CTurtle(230, 20);
                redTurtle->SetState(TURTLE_STATE_DEAD);

                coObjects->push_back(redTurtle);
            }
            if (leaf == nullptr) {
                leaf = new CLeaf(160, 40);
                leaf->SetState(LEAF_STATE_START);

                coObjects->push_back(leaf);
            }
            if (goomba == nullptr) {
                goomba = new CGoomba(150, 20);

                coObjects->push_back(goomba);
            }
            if (mushroom == nullptr) {
                mushroom = new CMushroom(100, -30);
                mushroom->SetState(MUSHROOM_STATE_RUN);

                coObjects->push_back(mushroom);
            }
        }
        else if (GetTickCount64() - timestart > 4500) {
            vy = 0.15f;
        }
        
    };
    virtual void Render() {
        CPlayScene* C_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
        CAnimations* animation = CAnimations::GetInstance();

        // render title
        animation->Get(ID_ANI_TITLE_MARIOBROS3)->Render(x, y);

        // render 3
        if (isLight) {
            animation->Get(ID_ANI_TITLE_MARIOBROS3_3)->Render(x + 5, y + 36);

            // render select
            if(isSelect)
                if (C_scene->selectMenu == SELECT_1_PLAYER)
                    animation->Get(ID_ANI_SELECT_1_PlAYER)->Render(x, y + 72);
                else animation->Get(ID_ANI_SELECT_2_PlAYER)->Render(x, y + 72);
            
            // render tree
            animation->Get(ID_ANI_TREE_1)->Render(33, y + 65);
            animation->Get(ID_ANI_TREE_2)->Render(274, y + 49);
            
            // render ramen
            animation->Get(ID_ANI_RAMEN_1_LIGHT)->Render(x+100, y -50);
            animation->Get(ID_ANI_RAMEN_1_LIGHT)->Render(x-100, y -40);
            animation->Get(ID_ANI_RAMEN_2_LIGHT)->Render(10, y);
        }
        else {
            // render ramen
            animation->Get(ID_ANI_RAMEN_1)->Render(x + 100, y - 50);
            animation->Get(ID_ANI_RAMEN_1)->Render(x - 100, y - 40);
            animation->Get(ID_ANI_RAMEN_2)->Render(10, y);
        }
        //RenderBoundingBox();
    };

    virtual int IsBlocking() { return 0; }
};

