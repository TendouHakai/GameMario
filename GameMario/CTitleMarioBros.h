#pragma once
#include "GameObject.h"
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


public:
    CTitleMarioBros(float x, float y): CGameObject(x,y){
        timestart = GetTickCount64();
        isLight = false;
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

        if (GetTickCount64() - timestart > 5000) {
            isLight = true;
            CGame::GetInstance()->setBackgroundColor(255, 219, 161);
        }
        else if (GetTickCount64() - timestart > 3500) {
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
};

