#include "CHUB.h"

void CHUB::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - HUB_BBOX_WIDTH / 2;
	top = y - HUB_BBOX_HEIGHT / 2;
	right = left + HUB_BBOX_WIDTH;
	bottom = top + HUB_BBOX_HEIGHT;
}

void CHUB::renderNumber(int number, int xx, int yy)
{
	CAnimations* animations = CAnimations::GetInstance();
	int sochia = number;
	int n = 0;
	if(sochia<1){
		animations->Get(ID_ANI_NUMBER00)->Render(xx - n * 10, yy);
		return;
	}
	while (sochia >= 1) {
		switch (sochia % 10)
		{
		case 0: {
			animations->Get(ID_ANI_NUMBER00)->Render(xx - n * 10, yy);
			break;
		}
		case 1: {
			animations->Get(ID_ANI_NUMBER01)->Render(xx - n * 10, yy);
			break;
		}
		case 2: {
			animations->Get(ID_ANI_NUMBER02)->Render(xx - n * 10, yy);
			break;
		}
		case 3: {
			animations->Get(ID_ANI_NUMBER03)->Render(xx - n * 10, yy);
			break;
		}
		case 4: {
			animations->Get(ID_ANI_NUMBER04)->Render(xx - n * 10, yy);
			break;
		}
		case 5: {
			animations->Get(ID_ANI_NUMBER05)->Render(xx - n * 10, yy);
			break;
		}
		case 6: {
			animations->Get(ID_ANI_NUMBER06)->Render(xx - n * 10, yy);
			break;
		}
		case 7: {
			animations->Get(ID_ANI_NUMBER07)->Render(xx - n * 10, yy);
			break;
		}
		case 8: {
			animations->Get(ID_ANI_NUMBER08)->Render(xx - n * 10, yy);
			break;
		}
		case 9: {
			animations->Get(ID_ANI_NUMBER09)->Render(xx - n * 10, yy);
			break;
		}
		default:
			break;
		}

		sochia = (int)sochia / 10;
		n++;
	}
}

void CHUB::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_HUB)->Render(x, y);
	this->coin = CGame::GetInstance()->coin;
	this->countCoin = CGame::GetInstance()->countCoin;
	this->W = CGame::GetInstance()->W;
	this->M = CGame::GetInstance()->M;
	this->time = CGame::GetInstance()->time;
	this->level = CGame::GetInstance()->level;

	// render W
	renderNumber(W, x - 36, y - 3);

	// render M
	renderNumber(M, x - 36, y + 5);

	// render coin
	renderNumber(coin, x + 33, y + 5);

	// render time
	renderNumber(time, x + 68, y + 5);

	// render count coin
	renderNumber(countCoin, x + 68, y - 3);

	// render P
	int n = 0;
	while (n < level) {
		if (n == 5) {
			animations->Get(ID_ANI_P_WHITE)->Render((x-20) + n * 10+4, y-3);
		}
		else {
			animations->Get(ID_ANI_RAISE_P_WHITE)->Render((x - 20) + n * 10, y - 3);
		}

		n++;
	}

	for (; n < 6; n++) {
		if (n == 5) {
			animations->Get(ID_ANI_P_BLACK)->Render((x - 20) + n * 10+4, y - 3);
		}
		else {
			animations->Get(ID_ANI_RAISE_P_BLACK)->Render((x - 20) + n * 10, y - 3);
		}
	}

	// render M
	animations->Get(ID_ANI_M)->Render(x - 64, y + 5);

	//RenderBoundingBox();
}
