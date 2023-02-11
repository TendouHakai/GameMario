#include "CGreenMario.h"

int CGreenMario::GetAniIdBig()
{
	int aniId = -1;

	if (isOnPlatform == false)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (isHolding) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_HOLDING_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_HOLDING_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
			}
		}
		else
		{
			if (isHolding) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_HOLDING_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_HOLDING_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_GREENMARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_GREENMARIO_JUMP_WALK_LEFT;
			}
		}
	}
	else
		if (isHolding) {
			if (vx == 0) {
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_HOLDING_RIGHT;
				else aniId = ID_ANI_GREENMARIO_IDLE_HOLDING_LEFT;
			}
			else {
				if (nx > 0) aniId = ID_ANI_MARIO_HOLDING_RIGHT;
				else aniId = ID_ANI_GREENMARIO_HOLDING_LEFT;
			}
		}
		else if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (isKicking) {
				if (nx > 0)
					aniId = ID_ANI_MARIO_KICK_RIGHT;
				else
					aniId = ID_ANI_GREENMARIO_KICKING_LEFT;
			}
			else if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_GREENMARIO_IDLE_RIGHT;
				else aniId = ID_ANI_GREENMARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_GREENMARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_GREENMARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}
