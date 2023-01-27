#include "CGreenMushroom.h"

void CGreenMushroom::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_GREENMUSHROOM)->Render(x, y);
}
