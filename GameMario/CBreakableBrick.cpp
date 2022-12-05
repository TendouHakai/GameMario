#include "CBreakableBrick.h"

void CBreakableBrick::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_BREAKABLEBRICK)->Render(x, y);
	//RenderBoundingBox();
}
