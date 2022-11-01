#pragma once

// Mario
#pragma region Form Mario
#define MARIO_FORM_BIG		0
#define MARIO_FORM_SMALL	1
#pragma endregion

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
// animation Mario Big
#define ID_ANI_MARIO_IDLE_RIGHT "big_idle_right"
#define ID_ANI_MARIO_IDLE_LEFT "big_idle_left"

#define ID_ANI_MARIO_WALKING_RIGHT "big_walk_right"
#define ID_ANI_MARIO_WALKING_LEFT "big_walk_left"

#define ID_ANI_MARIO_RUNNING_RIGHT "big_run_right"
#define ID_ANI_MARIO_RUNNING_LEFT "big_run_left"

#define ID_ANI_MARIO_JUMP_WALK_RIGHT "big_jump_walk_right"
#define ID_ANI_MARIO_JUMP_WALK_LEFT "big_jump_walk_left"

#define ID_ANI_MARIO_JUMP_RUN_RIGHT "big_jump_run_right"
#define ID_ANI_MARIO_JUMP_RUN_LEFT "big_jump_run_left"

#define ID_ANI_MARIO_SIT_RIGHT "big_sit_right"
#define ID_ANI_MARIO_SIT_LEFT "big_sit_left"

#define ID_ANI_MARIO_BRACE_RIGHT "big_brace_right"
#define ID_ANI_MARIO_BRACE_LEFT "big_brace_left"

// animation Mario Small
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT "small_idle_right"
#define ID_ANI_MARIO_SMALL_IDLE_LEFT "small_idle_left"

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT "small_walk_right"
#define ID_ANI_MARIO_SMALL_WALKING_LEFT "small_walk_left"

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT "small_run_right"
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT "small_run_left"

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT "small_jump_walk_right"
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT "small_jump_walk_left"

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT "small_jump_run_right"
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT "small_jump_run_left"

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT "small_brace_right"
#define ID_ANI_MARIO_SMALL_BRACE_LEFT "small_brace_left"
#pragma endregion

#pragma region Mario stats
#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.45f
#define MARIO_JUMP_RUN_SPEED_Y	0.5f

#define MARIO_GRAVITY			0.0012f
#pragma endregion



