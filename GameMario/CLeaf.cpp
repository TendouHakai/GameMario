#include "CLeaf.h"

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - LEAF_BBOX_WIDTH / 2;
	top = y - LEAF_BBOX_HEIGHT / 2;
	right = left + LEAF_BBOX_WIDTH;
	bottom = top + LEAF_BBOX_HEIGHT;
}

void CLeaf::Render() {
	if(vx>0)
		CAnimations::GetInstance()->Get(ID_ANI_LEAF_RIGHT)->Render(x, y);
	else CAnimations::GetInstance()->Get(ID_ANI_LEAF_LEFT)->Render(x, y);
}