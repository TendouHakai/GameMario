#include "CTelePort.h"

void CTelePort::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - TELEPORT_BBOX_WIDTH / 2;
	top = y - TELEPORT_BBOX_HEIGHT / 2;
	right = left + TELEPORT_BBOX_WIDTH;
	bottom = top + TELEPORT_BBOX_HEIGHT;
}