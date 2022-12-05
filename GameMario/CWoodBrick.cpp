#include "CWoodBrick.h"

void CWoodBrick::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_WOODBRICK)->Render(x, y);
	//RenderBoundingBox();
}
