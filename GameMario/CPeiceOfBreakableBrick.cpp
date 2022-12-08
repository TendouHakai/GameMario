#include "CPeiceOfBreakableBrick.h"

void CPeiceOfBreakableBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PEICEOFBREAKABLEBRICK_BBOX_WIDTH / 2;
	top = y - PEICEOFBREAKABLEBRICK_BBOX_HEIGHT / 2;
	right = left + PEICEOFBREAKABLEBRICK_BBOX_WIDTH;
	bottom = top + PEICEOFBREAKABLEBRICK_BBOX_HEIGHT;
}
