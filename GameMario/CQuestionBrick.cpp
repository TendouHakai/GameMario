#include "CQuestionBrick.h"

void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == QUESTIONBRICK_STATE_IDLE)
		animations->Get(ID_ANI_QUESTIONBRICK_IDLE)->Render(x, y);
	else animations->Get(ID_ANI_QUESTIONBRICK_BROKEN)->Render(x, y);
}
