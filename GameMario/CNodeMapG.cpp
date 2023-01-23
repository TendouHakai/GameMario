#include "CNodeMapG.h"

void CNodeMapG::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - NODEMAP_BBOX_WIDTH / 2;
	top = y - NODEMAP_BBOX_HEIGHT / 2;
	right = left + NODEMAP_BBOX_WIDTH;
	bottom = top + NODEMAP_BBOX_HEIGHT;
}

void CNodeMapG::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == NODEMAP_STATE_DONE) {
		if (type == NODEMAP_TYPE_SCENE) {
			animations->Get(ID_ANI_NODEMAP_TYPE1_DONE)->Render(x, y);
		}
	}
	
	//RenderBoundingBox();
}
