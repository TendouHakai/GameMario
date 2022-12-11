#include "CBreakableBrick.h"

#define CBREAKABLEBRICKBUTTON_STATE_BROKEN	300
#define CBREAKABLEBRICKBUTTON_STATE_PRESSED	400

#define CBREAKABLEBRICKBUTTON_GRAVITY	0.002f
#define CBREAKABLEBRICKBUTTON_SPEED_Y	0.25f

#define ID_ANI_CBREAKABLEBRICKBUTTON_BROKEN 12001
#define ID_ANI_CBREAKABLEBRICKBUTTON_BUTTON 20003
#define ID_ANI_CBREAKABLEBRICKBUTTON_BUTTON_PRESSED 20004

#define BUTTON_BBOX_WIDTH	16
#define BUTTON_BBOX_HEIGHT	17
#define BUTTON_BBOX_HEIGHT_PRESSED	7

class CbreakableBrickButton : public CBreakableBrick
{
protected:
	float ay;
	float ybrick;
	vector<CBreakableBrick*> listBrick;
	bool isChangeCoin;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		vy += ay * dt;
		y += vy * dt;
		if (state == CBREAKABLEBRICKBUTTON_STATE_PRESSED) {
			if (isChangeCoin) {
				for (size_t i = 0; i < listBrick.size(); i++)
				{
					if(!listBrick[i]->IsDeleted())
						listBrick[i]->SetState(BREAKABLEBRICK_STATE_TO_COIN);
				}
				isChangeCoin = false;
			}
		}
		if (y > ybrick) {
			y = ybrick;
			vy = 0;
		}
		else CBreakableBrick::Update(dt, coObjects);
	}
	virtual void Render();
public:

	CbreakableBrickButton(float x, float y) :CBreakableBrick(x, y) {
		ybrick = y; ay = 0; vy = 0; isChangeCoin = false;
	}

	virtual void SetState(int state) {
		if (state == CBREAKABLEBRICKBUTTON_STATE_BROKEN) {
			ay = CBREAKABLEBRICKBUTTON_GRAVITY;
			vy = -CBREAKABLEBRICKBUTTON_SPEED_Y;
		}
		else if (state == CBREAKABLEBRICKBUTTON_STATE_PRESSED) {
			isChangeCoin = true;
		}
		CBreakableBrick::SetState(state);
	}
	void addBrick(CBreakableBrick* brick) {
		listBrick.push_back(brick);
	}
};