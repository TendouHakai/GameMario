#pragma once

// Mario
#pragma region State Mario
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#pragma endregion

#pragma region Animation Mario ID
#define ID_ANI_MARIO_IDLE_RIGHT "Mario_idle_right"
#define ID_ANI_MARIO_IDLE_LEFT "Mario_idle_left"

#define ID_ANI_MARIO_WALKING_RIGHT "Mario_walk_right"
#define ID_ANI_MARIO_WALKING_LEFT "Mario_walk_left"

#define ID_ANI_MARIO_RUNNING_RIGHT "Mario_run_right"
#define ID_ANI_MARIO_RUNNING_LEFT "Mario_run_left"

#define ID_ANI_MARIO_JUMP_WALK_RIGHT "Mario_jump_walk_right"
#define ID_ANI_MARIO_JUMP_WALK_LEFT "Mario_jump_walk_left"

#define ID_ANI_MARIO_JUMP_RUN_RIGHT "Mario_jump_run_right"
#define ID_ANI_MARIO_JUMP_RUN_LEFT "Mario_jump_run_left"

#define ID_ANI_MARIO_SIT_RIGHT "Mario_sit_right"
#define ID_ANI_MARIO_SIT_LEFT "Mario_sit_left"

#define ID_ANI_MARIO_BRACE_RIGHT "Mario_brace_right"
#define ID_ANI_MARIO_BRACE_LEFT "Mario_brace_left"
#pragma endregion

#pragma region Mario stats
#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f
#pragma endregion



