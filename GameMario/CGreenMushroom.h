#pragma once
#include "CMushroom.h"

#define ID_ANI_GREENMUSHROOM    22002

class CGreenMushroom :
    public CMushroom
{
public:
    CGreenMushroom(float x, float y) :CMushroom(x, y){}
    virtual void Render();

	virtual void SetState(int state) {
		if (state == MUSHROOM_STATE_RUN) {
			ay = MUSHROOM_GRAVITY;
			CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			float xMario, yMario;
			scene->GetPlayer()->GetPosition(xMario, yMario);

			if (x > xMario)
				vx = -MUSHROOM_SPEED;
			else vx = MUSHROOM_SPEED;
			this->state = state;
			return;
		}

		CMushroom::SetState(state);
	}
};

