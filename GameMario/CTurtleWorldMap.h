#pragma once
#include "GameObject.h"
#include <time.h>

#define TURTLEW_BBOX_WIDTH  18
#define TURTLEW_BBOX_HEIGHT  18

#define TURTLEW_STATE_IDLE   100
#define TURTLEW_STATE_DOWN   200
#define TURTLEW_STATE_UP   300
#define TURTLEW_STATE_LEFT   400
#define TURTLEW_STATE_RIGHT   500

#define TURTLEW_WALKING_SPEED   0.015f
#define TURTLEW_SPEED   0.12f

#define ID_ANI_TURTLEW_WALKING_LEFT 30001
#define ID_ANI_TURTLEW_WALKING_RIGHT 30002

#define SPACE   13

#define DOWN 0
#define UP 1
#define LEFT 2
#define RIGHT 3
class CTurtleWorldMap :
    public CGameObject
{
    float xMin, xMax;
    float xNext, yNext;
    bool isEnd = false;
public:
    CTurtleWorldMap(float x, float y) : CGameObject(x, y) {
        xMin = x - SPACE;
        xMax = x + SPACE;
        vx = TURTLEW_WALKING_SPEED;
        state = TURTLEW_STATE_IDLE;
    }

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
        if(state== TURTLEW_STATE_IDLE){
            if (x > xMax || x < xMin)
                vx = -vx;
        }
        else {
            if (vx != 0) {
                if ((vx > 0 && x >= xNext) || (vx < 0 && x <= xNext)) {
                    x = xNext;
                    xMin = x - SPACE;
                    xMax = x + SPACE;
                    SetState(TURTLEW_STATE_IDLE);
                }
            }
            else if (vy != 0) {
                if ((vy > 0 && y >= yNext) || (vy < 0 && y <= yNext)) {
                    y = yNext;
                    xMin = x - SPACE;
                    xMax = x + SPACE;
                    SetState(TURTLEW_STATE_IDLE);
                }
            }
        }

        CCollision::GetInstance()->Process(this, dt, coObjects);
    };
    void Next() {
        int direct[4];
        int n = 0;
        LPNodeMap node = CGame::GetInstance()->getCurretnNodeMapTurtle();
        if (node->nodeDOWNId != -1)
            direct[n++] = DOWN;
        if (node->nodeUPId != -1)
            direct[n++] = UP;
        if (node->nodeLEFTId != -1)
            direct[n++] = LEFT;
        if (node->nodeRIGHTId != -1)
            direct[n++] = RIGHT;
        srand(time(NULL));
        int RandIndex = rand() % n;
        switch (direct[RandIndex])
        {
        case DOWN: {
            CGame::GetInstance()->setCurrentNodeMapTurtle(node->nodeDOWNId);
            node = CGame::GetInstance()->getNodeMap(node->nodeDOWNId);
            xNext = node->x;
            yNext = node->y;
            SetState(TURTLEW_STATE_DOWN);
            break;
        }
        case UP: {
            CGame::GetInstance()->setCurrentNodeMapTurtle(node->nodeUPId);
            node = CGame::GetInstance()->getNodeMap(node->nodeUPId);
            xNext = node->x;
            yNext = node->y;
            SetState(TURTLEW_STATE_UP);
            break;
        }
        case LEFT: {
            CGame::GetInstance()->setCurrentNodeMapTurtle(node->nodeLEFTId);
            node = CGame::GetInstance()->getNodeMap(node->nodeLEFTId);
            xNext = node->x;
            yNext = node->y;
            SetState(TURTLEW_STATE_LEFT);
            break;
        }
        case RIGHT: {
            CGame::GetInstance()->setCurrentNodeMapTurtle(node->nodeRIGHTId);
            node = CGame::GetInstance()->getNodeMap(node->nodeRIGHTId);
            xNext = node->x;
            yNext = node->y;
            SetState(TURTLEW_STATE_RIGHT);
            break;
        }
        default:
            break;
        }

    }
    virtual void OnNoCollision(DWORD dt) {
        x += vx * dt;
        y += vy * dt;
    };
    virtual void Render();
    virtual void SetState(int state) { 
        switch (state)
        {
        case TURTLEW_STATE_UP:
            vy = -TURTLEW_SPEED;
            break;
        case TURTLEW_STATE_DOWN:
            vy = TURTLEW_SPEED;
            break;
        case TURTLEW_STATE_LEFT:
            vx = -TURTLEW_SPEED;
            break;
        case TURTLEW_STATE_RIGHT:
            vx = TURTLEW_SPEED;
            break;
        case TURTLEW_STATE_IDLE:
            vx = TURTLEW_WALKING_SPEED;
            break;
        default:
            break;
        }
        this->state = state; 
    }
};

