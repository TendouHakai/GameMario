#include "CEffectHitWithTail.h"

void CEffectHitWithTail::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_EFFECT_HIT)->Render(x, y);
}
