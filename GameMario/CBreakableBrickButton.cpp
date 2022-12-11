#include "CBreakableBrickButton.h"

void CbreakableBrickButton::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (state == CBREAKABLEBRICKBUTTON_STATE_BROKEN) {
		left = x - BRICK_BBOX_WIDTH / 2;
		top = y - BRICK_BBOX_HEIGHT / 2 - BUTTON_BBOX_HEIGHT;
		right = left + BRICK_BBOX_WIDTH;
		bottom = top + BRICK_BBOX_HEIGHT + BUTTON_BBOX_HEIGHT;
	}
	else if (state == CBREAKABLEBRICKBUTTON_STATE_PRESSED) {
		left = x - BRICK_BBOX_WIDTH / 2;
		top = y - BRICK_BBOX_HEIGHT / 2 - BUTTON_BBOX_HEIGHT_PRESSED;
		right = left + BRICK_BBOX_WIDTH;
		bottom = top + BRICK_BBOX_HEIGHT + BUTTON_BBOX_HEIGHT_PRESSED;
	}
	else {
		left = x - BRICK_BBOX_WIDTH / 2;
		top = y - BRICK_BBOX_HEIGHT / 2;
		right = left + BRICK_BBOX_WIDTH;
		bottom = top + BRICK_BBOX_HEIGHT;
	}
}

void CbreakableBrickButton::Render() {
	if (state == CBREAKABLEBRICKBUTTON_STATE_BROKEN) {
		CAnimations::GetInstance()->Get(ID_ANI_CBREAKABLEBRICKBUTTON_BROKEN)->Render(x,y);
		CAnimations::GetInstance()->Get(ID_ANI_CBREAKABLEBRICKBUTTON_BUTTON)->Render(x, y - BRICK_BBOX_WIDTH / 2 - BUTTON_BBOX_HEIGHT / 2);
	}
	else if (state == CBREAKABLEBRICKBUTTON_STATE_PRESSED) {
		CAnimations::GetInstance()->Get(ID_ANI_CBREAKABLEBRICKBUTTON_BROKEN)->Render(x, y);
		CAnimations::GetInstance()->Get(ID_ANI_CBREAKABLEBRICKBUTTON_BUTTON_PRESSED)->Render(x, y - BRICK_BBOX_WIDTH / 2 - BUTTON_BBOX_HEIGHT_PRESSED / 2);
	}
	else CBreakableBrick::Render();

	//RenderBoundingBox();
}